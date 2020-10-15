#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

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
    int fdJoueur[4][2];
    pipe(fdMaitre[0]);
    pipe(fdMaitre[1]);
    pid_t pidMaitre = getpid();
    int plateau[56];
    int maisons[6][4];
    int chevaux[6][4];
    // Ne pas oublier de considerer que l'on peut jouer de 2 a 4 joueurs



    for(int i = 0; i < 4; i++) pipe(fdJoueur[i]); // On cree les pipes qui correspondent aux interactions entre joueurs
    
    for (int i = 0; i < 6; i++) {
        if (getpid() == pidMaitre){
            fork();
        }
    }


}