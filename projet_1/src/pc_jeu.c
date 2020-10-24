#include "../hdr/pc_jeu.h"

void viderPlateau(plateau_t * p) {
    for (int i=0; i < TAILLE_PLATEAU; i++)
        p->cases[i] = CS_CASE_VIDE;
    for (int i=0; i < NOMBRE_JOUEURS; i++)
        for (int j=0; j < NOMBRE_CHEVEAUX; j++)
            p->ecuries[i][j] = CS_CASE_VIDE;
}

int caseEstVide(case_t c) {
    return c == CS_CASE_VIDE;
}

int entierAleatoire(int min, int max) {
    return rand() % max + min;
}

int lancerDe6() {
    return entierAleatoire(1,6);
}