#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include "../hdr/pc_jeu.h"
#include "../hdr/pc_utils.h"

int main() {
    /** Vérification de la valeur des constantes. */
    if (NOMBRE_JOUEURS <= 1 || NOMBRE_JOUEURS >= 5) {
        fprintf(stderr, "Le nombre de joueurs doit être compris entre 2 et 4.\nTrouvé : %d\n", NOMBRE_JOUEURS);
        exit(EXIT_FAILURE);
    }
    if (NOMBRE_CHEVEAUX < 1) {
        fprintf(stderr, "Il doit y avoir au moins un cheval par joueur.\nTrouvé : %d\n", NOMBRE_CHEVEAUX);
        exit(EXIT_FAILURE);
    }
    if (TAILLE_PLATEAU < 4 || (TAILLE_PLATEAU % 4)) {
        fprintf(stderr, "Le plateau doit avoir une taille positive et celle-ci doit être un multiple de 4.\nTrouvé : %d\n", TAILLE_PLATEAU);
    }

    /**
    * Déclaration des variables globales.
    */
    int fdMaitre[2][2]; // Descripteurs de fichiers du maître du jeu.
    pipe(fdMaitre[0]); // Tube du maître au joueur 0 (entrée dans le cycle ; sortie du maître).
    pipe(fdMaitre[1]); // Tube du joueur 0 au maître (sortie du cycle ; entrée dans le maître).
    pid_t pidMaitre = getpid(); // PID du processus père (pour transmission aux fils).
    int fdJoueur[NOMBRE_JOUEURS][2]; // Descripteurs de fichiers pour les interactions entre deux joueurs consécutifs.
    pid_t pidJoueur[NOMBRE_JOUEURS]; // Tableau des PID de chaque joueur.
    int numJoueur = -1; // Numéro du joueur courant ; le numéro du maître est -1.
    int finDePartie = 0; // Booléen valant 0 si la partie est en cours, 1 sinon.
    jeu_t jeu; // Déclaration de la structure de jeu.
    srand(((unsigned int)time(NULL))*getpid()); // Renseignement de la graine pour la génération aléatoire de nombres.

    // On crée les pipes qui correspondent aux interactions entre joueurs.
    for(int i = 0; i < NOMBRE_JOUEURS; i++) pipe(fdJoueur[i]);

    // On crée un fils pour chaque joueur.
    for(int i = 0; i < NOMBRE_JOUEURS; i++) {
        if (getpid() == pidMaitre) {
            if ((pidJoueur[i] = fork()) == -1) {
                fprintf(stderr, "Un des joueurs n'a pas pu être créé.\n");
                exit(EXIT_FAILURE);
            }
            if (getpid() != pidMaitre) numJoueur = i; // On définit le numéro de chaque joueur.
        }
    }

    info_t info; // Structure d'information propre à chaque processus servant à communiquer des données.

    /** Initialisation du jeu dans le maître. */
    if (getpid() == pidMaitre) {
        jeu.nbTours = 0; // Nombre de tours joués (i.e. nombre de fois que tous les jours ont tous joué).
        viderPlateau(&(jeu.plateau)); // Initialisation du plateau avec toutes les cases vides.

        // Définition de la première information à envoyer pour démarrer la partie.
        info.type = IT_TOUR_JOUEUR; // L'information concerne le joueur à qui c'est le tour.
        info.statut = ST_DEMANDE; // Il s'agit d'une demande de confirmation.
        info.data = 0; // La donnée indique le joueur cible i.e. le joueur 0 pour commencer.
        info.source = numJoueur; // La source de l'information est le maître du jeu (-1).

        // Démarrage du jeu !
        printf("\033[0;35m*** DEBUT DE LA PARTIE ***\033[0;0m\n");
        write(FD_M_J0[ECRIRE], &info, sizeof(info_t)); // On envoie dans le cycle que c'est le tour au joueur 0.
    }

    // Fermeture des descripteurs inutiles.
    fermDescInut(numJoueur, fdJoueur, fdMaitre);

    // Boucle de déroulement de la partie.
    while (!finDePartie) {
        switch (numJoueur) {
            case 0:
                // Lecture des données du maître du jeu.
                read(FD_M_J0[LIRE], &info, sizeof(info_t));
                info = actionJoueur(&info, numJoueur, fdJoueur, fdMaitre);
                // Lecture des données du dernier joueur.
                read(fdJoueur[NOMBRE_JOUEURS-1][LIRE], &info, sizeof(info_t));
                info = actionJoueur(&info, numJoueur, fdJoueur, fdMaitre);
                break;
            case 1:
            case 2:
            case 3:
                // Lecture des données du joueur précédent.
                read(fdJoueur[mathMod(numJoueur-1,NOMBRE_JOUEURS)][LIRE], &info, sizeof(info_t));
                info = actionJoueur(&info, numJoueur, fdJoueur, fdMaitre);
                if (info.type == IT_FIN_PARTIE) finDePartie = 1;
                break;
            case -1:
                // Lecture des données du premier joueur (fin de cycle).
                read(FD_J0_M[LIRE], &info, sizeof(info_t));
                info = actionMaitre(&info, &jeu, fdJoueur, fdMaitre);
                if (info.type == IT_FIN_PARTIE) {
                    finDePartie = 1;
                    close(FD_M_J0[ECRIRE]);
                    close(FD_J0_M[LIRE]);
                    for (int j = 0; j < NOMBRE_JOUEURS; j++) wait(NULL);
                    printf("\033[0;35m*** FIN DE PARTIE ***\033[0;0m\n");
                }
                break;
            default:
                fprintf(stderr, "Je ne devrais pas arriver ici...\n");
            }
    }

    return 0;
}
