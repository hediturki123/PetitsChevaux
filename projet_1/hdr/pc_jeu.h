#include <stdlib.h>
#include <time.h>

#ifndef __PC_JEU_H__
#define __PC_JEU_H__

/**
 * Définition des constantes de l'environnement de jeu.
 * Ces contantes peuvent être redéfinies lors de la compilation pour moduler le jeu.
 * */
#define NOMBRE_JOUEURS 4 // Nombre de joueurs dans une partie ; par défaut 4, minimum 2, maximum 4.
#define NOMBRE_CHEVEAUX 4 // Nombre de cheveaux par joueurs ; par défaut 4, minimum 1.
#define TAILLE_PLATEAU 56 // Taille du plateau de jeu en nombre de cases ; par défaut 56, minimum 4 (doit être un multiple de 4).

/** Macros pour les descripteurs du maître. */
#define FD_M_J0 fdMaitre[0] // Descripteurs de fichiers pour l'interaction du maître vers le joueur 0.
#define FD_J0_M fdMaitre[1] // Descripteurs de fichiers pour l'interaction du joueur 0 vers le maître.

// Une case de plateau de jeu.
// L'entier -1 (CS_CASE_VIDE) correspond à une case vide, tandis qu'un entier n (n allant de 0 à 3) correspondent à un cheval du joueur n (CASE_Jn).
typedef enum case_t {
    CS_CASE_VIDE = -1, // Une case vide.
    CS_CVL_J0 = 0, // Un cheval du joueur 0.
    CS_CVL_J1 = 1, // Un cheval du joueur 1.
    CS_CVL_J2 = 2, // Un cheval du joueur 2.
    CS_CVL_J3 = 3 // Un cheval du joueur 3.
} case_t;

// Un plateau de jeu contenant TAILLE_PLATEAU cases qui forment un parcours circulaire.
// Les cases des écuries de chaque joueur sont également contenues ici.
typedef struct plateau_t {
    case_t cases[TAILLE_PLATEAU];
    case_t ecuries[NOMBRE_JOUEURS][NOMBRE_CHEVEAUX];
} plateau_t;

// Un jeu contenant un plateau et les cheveaux de chaque joueur.
typedef struct jeu_t {
    plateau_t plateau; // Plateau sur lequel se dérouelera le jeu.
    unsigned char chevaux[NOMBRE_JOUEURS][NOMBRE_CHEVEAUX]; // Les chevaux de chaque joueur.
    unsigned int nbTours; // Le nombre de tours effectués durant cette partie.
} jeu_t;

// Fonction permettant de vider un plateau de jeu.
// Les cases régulières aussi bien que les écuries sont réinitialisées à CS_CASE_VIDE (-1).
void viderPlateau(plateau_t* p);

// Fonction permettant d'indiquer si une case est vide.
// Retourne 1 si la case est vide, 0 sinon.
int caseEstVide(case_t c);

// Fonction retournant un entier aléatoire compris entre min et max.
int entierAleatoire(int min, int max);

// Fonction permettant de lancer un dé à six faces.
// Le résultat est un entier compris entre 1 et 6.
unsigned char lancerDe6(void);

#endif // !__PC_JEU_H__