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
    int endGame = 0; // on déclare si le jeu est fini ou pas
    int tourJoueur = 0;
    int nbTours = 0;
    Infos info;

    /**
     * Définition de l'environnement de jeu.
     */
    Plateau plateau; // Déclaration du plateau de jeu.
    viderPlateau(&plateau); // Initialisation du plateau avec toutes les cases vides.
    int chevaux[NOMBRE_JOUEURS][NOMBRE_CHEVEAUX];


    for(int i = 0; i < NOMBRE_JOUEURS; i++) {
        pipe(fdJoueur[i]); // On crée les pipes qui correspondent aux interactions entre joueurs.
    }

    for(int i = 0; i < NOMBRE_JOUEURS; i++) {
        if (getpid() == pidMaitre) {

          if(fork() == -1){
            fprintf(stderr, "%s\n", "Erreur fork");
            exit(-1);
          } // On crée un fils pour chaque joueur.

          if (getpid() != pidMaitre) numJoueur = i; // On définit le numéro de chaque joueur.
        }
    }

    int entier = -1;

    while (!endGame && nbTours < 4){

      switch (numJoueur) {
          case 0:
              endGame = readFile(fdMaitre[0][0], numJoueur);
              writeFile(fdJoueur[0][1], numJoueur, endGame);

            /*  endGame = readFile(fdJoueur[3][0], numJoueur);
              writeFile(fdMaitre[1][1], numJoueur, endGame);*/
              tourJoueur = readFile(fdMaitre[0][0], numJoueur);
              writeFile(fdJoueur[0][1], numJoueur, tourJoueur);
              if (tourJoueur == numJoueur){
                printf("c'est mon tour, %d\n", tourJoueur);

                //lance de de
              }



              if (endGame){
                exit(0);
              } else {
                printf("%d ne s'est pas bien arrêté\n", numJoueur);
                exit(1);
              }


              break;
          case 1:
              endGame = readFile(fdJoueur[0][0], numJoueur);
              writeFile(fdJoueur[1][1], numJoueur, endGame);

              tourJoueur = readFile(fdJoueur[0][0], numJoueur);
              writeFile(fdJoueur[1][1], numJoueur, tourJoueur);
              if (tourJoueur == numJoueur){
                printf("c'est mon tour, %d\n", tourJoueur);

                //lance de de
              }

              if (endGame){
                exit(0);
              } else {
                printf("%d ne s'est pas bien arrêté\n", numJoueur);
                exit(1);
              }

              break;
          case 2:
              endGame = readFile(fdJoueur[1][0], numJoueur);
              writeFile(fdJoueur[2][1], numJoueur, endGame);

              tourJoueur = readFile(fdJoueur[1][0], numJoueur);
              writeFile(fdJoueur[2][1], numJoueur, tourJoueur);
              if (tourJoueur == numJoueur){
                printf("c'est mon tour, %d\n", tourJoueur);

                //lance de de
              }

              if (endGame){
                exit(0);
              } else {
                printf("%d ne s'est pas bien arrêté\n", numJoueur);
                exit(1);
              }

              break;
          case 3:
              endGame = readFile(fdJoueur[2][0], numJoueur);
              //writeFile(fdJoueur[3][1], numJoueur, endGame);

              tourJoueur = readFile(fdJoueur[2][0], numJoueur);

              if (tourJoueur == numJoueur){
                printf("c'est mon tour, %d\n", tourJoueur);
              //  writeFile(fdJoueur[1][1], numJoueur, tourJoueur);
                //lance de de
              }

              if (endGame){
                exit(0);
              } else {
                printf("%d ne s'est pas bien arrêté\n", numJoueur);
                exit(1);
              }

              break;
          case -1:
              writeFile(fdMaitre[0][1], numJoueur, info);
              //endGame = readFile(fdMaitre[1][0], numJoueur);
              printf("%d\n", endGame);

              //tourJoueur = readFile(fdJoueur[1][0], numJoueur);
              //printf("je suis dans le pere, tourJoueur : %d\n", tourJoueur);

              int status;
              nbTours += 1;
              printf("nbTours = %d\n", nbTours);

              for (int i = 0; i < NOMBRE_JOUEURS; i++){
                  wait(&status);
                  printf("status = %d\n", status);
              }

              break;
          default:
              printf("Je ne devrais pas arriver ici...\n");
              break;
      }
    }

    return 0;
}
