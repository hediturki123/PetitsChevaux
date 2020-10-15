#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

/** Définition des constantes de l'environnement de jeu. */
#define NOMBRE_JOUEURS 4 // Nombre de joueurs dans une partie ; par défaut 4, minimum 2, maximum 4.
#define NOMBRE_CHEVEAUX 4 // Nombre de cheveaux par joueurs ; par défaut 4, minimum 1.
#define TAILLE_PLATEAU 56 // Taille du plateau de jeu en nombre de cases ; par défaut 56, minimum 4 (doit être un multiple de 4).


/*initialisation du générateur aléatoire
* lancé du dé (les valeurs sont entre 1 et 6)
*/
int des() {
    srand(time(NULL));
    return rand() % 6 + 1;
}

 

int main() {
    /*On definit les descripteurs de fichiers du maitre du jeu (processus pere) qui en a 2 : 
    *    - le premier pour intéragir du maitre au joueur definit par fdMaitre[0]
    *    - et le deuxieme pour interagir du joueur au maitre definit par fdMaitre[1]
    * Ensuite on definit un descripteur de fichier par interaction entre 2 joueurs consecutifs
    */
    
    int fdMaitre[2][2]; 
    pipe(fdMaitre[0]);
    pipe(fdMaitre[1]);
    pid_t pidMaitre = getpid(); // Récupération du PID du processus père pour le transmettre aux fils.
  
    /** Définition des descripteurs de fichier pour les interactions entre deux joueurs consécutifs. */
    int fdJoueur[NOMBRE_JOUEURS][2];
    
    /**
     * Définition de l'environnement de jeu.
     */
    int plateau[TAILLE_PLATEAU];
    int ecuries[NOMBRE_JOUEURS][NOMBRE_CHEVEAUX];
    int chevaux[NOMBRE_JOUEURS][NOMBRE_CHEVEAUX];
    // Ne pas oublier de considerer que l'on peut jouer de 2 a 4 joueurs



    for(int i = 0; i < 4; i++) pipe(fdJoueur[i]); // On cree les pipes qui correspondent aux interactions entre joueurs
    
    for (int i = 0; i < 6; i++) {
        if (getpid() == pidMaitre){
            fork();
        }
    }


}