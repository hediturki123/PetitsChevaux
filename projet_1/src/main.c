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
    pid_t pidJoueur[NOMBRE_JOUEURS]; // Tableau des PID de chaque joueur.
    int numJoueur = -1; // Numéro du joueur courant ; le numéro du maître est -1.
    int finDePartie = 0; // on déclare si le jeu est fini ou pas
    int nbTours = 0;
    info_t info;

    // On crée les pipes qui correspondent aux interactions entre joueurs.
    for(int i = 0; i < NOMBRE_JOUEURS; i++) pipe(fdJoueur[i]);

    // On crée un fils pour chaque joueur.
    for(int i = 0; i < NOMBRE_JOUEURS; i++) {
        if (getpid() == pidMaitre) {
            if ((pidJoueur[i] = fork()) == -1) {
                fprintf(stderr, "%s\n", "Erreur fork");
                exit(-1);
            }
            if (getpid() != pidMaitre) numJoueur = i; // On définit le numéro de chaque joueur.
        }
    }

    // Initialisation du jeu dans le maître.
    if (getpid() == pidMaitre) {
        plateau_t plateau; // Déclaration du plateau de jeu.
        viderPlateau(&plateau); // Initialisation du plateau avec toutes les cases vides.
        int chevaux[NOMBRE_JOUEURS][NOMBRE_CHEVEAUX];
    }

    // Boucle de déroulement de la partie.
    while (!finDePartie && nbTours < 4){

      switch (numJoueur) {
          case 0:
              break;
          case 1 :
          case 2 :
          case 3 :
              read(fdJoueur[(numJoueur-1)%NOMBRE_JOUEURS][0], &info, sizeof(info_t));
              interpreteInfo(&info, numJoueur, fdJoueur);
              break;
          case -1:
              break;
          default:
              printf("Je ne devrais pas arriver ici...\n");
              break;
      }
    }



    return 0;
}
