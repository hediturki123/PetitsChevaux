#include <stdlib.h>
#include <time.h>
#include "../hdr/pc_jeu.h"

// Fonction permettant de vider un plateau de jeu.
// Les cases régulières aussi bien que les écuries sont réinitialisées à CASE_VIDE (-1).
void viderPlateau(Plateau * p) {
    for (int i=0; i < TAILLE_PLATEAU; i++)
        p->cases[i] = CASE_VIDE;
    for (int i=0; i < NOMBRE_JOUEURS; i++)
        for (int j=0; j < NOMBRE_CHEVEAUX; j++)
            p->ecuries[i][j] = CASE_VIDE;
}

// Fonction permettant d'indiquer si une case est vide.
// Retourne 1 si la case est vide, 0 sinon.
int caseEstVide(Case c) {
    return c == CASE_VIDE;
}

// Fonction retournant un entier aléatoire compris entre min et max.
int entierAleatoire(int min, int max) {
    srand(time(NULL));
    return rand() % max + min;
}

// Fonction permettant de lancer un dé à six faces.
// Le résultat est un entier compris entre 1 et 6.
int lancerDe6() {
    return entierAleatoire(1,6);
}