/**
 * \file pc_jeu.c
 * \brief Module de jeu du projet Petits Chevaux.
 * \author Hedi TURKI SANEKLI, Alexis YVON
 * \version 1.0
 * \date Octobre 2020
 *
 * Ce fichier contient les fonctions de mise à jour du jeu du projet Petits Chevaux.
 * Il s'agit des fonctions permettant de modifier et de vérifier l'état courant du jeu,
 * ainsi que de faire jouer les joueurs.
 */

#include "../hdr/pc_jeu.h"

void viderPlateau(plateau_t * p) {
    for (int i=0; i < TAILLE_PLATEAU; i++) // Vidage du plateau.
        p->cases[i] = CS_CASE_VIDE;
    for (int i=0; i < NOMBRE_JOUEURS; i++) // Vidage des écuries.
        for (int j=0; j < NOMBRE_CHEVAUX; j++)
            p->ecuries[i][j] = CS_CASE_VIDE;
}

int caseEstVide(case_e c) {
    return c == CS_CASE_VIDE;
}

int entierAleatoire(int min, int max) {
    return rand() % max + min;
}

int lancerDe6() {
    return entierAleatoire(1,6);
}