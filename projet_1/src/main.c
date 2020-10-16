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
    /* On definit les descripteurs de fichiers du maitre du jeu (processus pere) qui en a 2 :
    * - le premier pour intéragir du maitre au joueur definit par fdMaitre[0]
    * - et le deuxieme pour interagir du joueur au maitre definit par fdMaitre[1]
    * Ensuite on definit un descripteur de fichier par interaction entre 2 joueurs consecutifs
    */
    int fdMaitre[2][2]; // Descripteurs de fichiers du maître du jeu.
    pipe(fdMaitre[0]); // Tube du maître au joueur 0 (entrée dans le cycle ; sortie du maître).
    pipe(fdMaitre[1]); // Tube du joueur 0 au maître (sortie du cycle : entrée dans le maître).
    pid_t pidMaitre = getpid(); // PID du processus père (pour transmission aux fils).
    int fdJoueur[NOMBRE_JOUEURS][2]; // Descripteurs de fichiers pour les interactions entre deux joueurs consécutifs.
    int numJoueur = -1; // Numéro du joueur courant ; le numéro du maître est -1.

    /**
     * Définition de l'environnement de jeu.
     */
    Plateau plateau; // Déclaration du plateau de jeu.
    viderPlateau(&plateau); // Initialisation du plateau avec toutes les cases vides.
    int chevaux[NOMBRE_JOUEURS][NOMBRE_CHEVEAUX];


    for(int i = 0; i < NOMBRE_JOUEURS; i++) {

        pipe(fdJoueur[i]); // On crée les pipes qui correspondent aux interactions entre joueurs.

        if (getpid() == pidMaitre) {
            fork(); // On crée un fils pour chaque joueur.
            if (getpid() != pidMaitre) numJoueur = i; // On définit le numéro de chaque joueur.
        }
    }

    switch (numJoueur) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case -1:
            redirectOutput(fdMaitre[0]);
            redirectInput(fdMaitre[1]);
            break;
        default:
            printf("Je ne devrais pas arriver ici...\n");
            break;
    }

    return 0;
}