#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#ifndef __PC_JEU_H__
#define __PC_JEU_H__

/**
 * Définition des constantes de l'environnement de jeu.
 * Ces contantes peuvent être redéfinies lors de la compilation pour moduler le jeu.
 */
#define NOMBRE_JOUEURS 4 /** @brief Nombre de joueurs dans une partie ; par défaut 4, minimum 2, maximum 4. */
#define NOMBRE_CHEVEAUX 4 /** @brief Nombre de cheveaux par joueurs ; par défaut 4, minimum 1. */
#define TAILLE_PLATEAU 56 /** @brief Taille du plateau de jeu en nombre de cases ; par défaut 56, minimum 4 (doit être un multiple de 4). */

/**
 * @brief L'entier -1 (CS_CASE_VIDE) correspond à une case vide.
 * Un entier n (n allant de 0 à 3) correspond à un cheval du joueur n (CS_CVL_Jn).
 */
typedef enum case_t {
    CS_CASE_VIDE = -1, // Une case vide.
    CS_CVL_J0 = 0, // Un cheval du joueur 0.
    CS_CVL_J1 = 1, // Un cheval du joueur 1.
    CS_CVL_J2 = 2, // Un cheval du joueur 2.
    CS_CVL_J3 = 3 // Un cheval du joueur 3.
} case_t;

/**
 * @brief Un plateau de jeu contenant TAILLE_PLATEAU cases qui forment un parcours circulaire.
 * Les cases des écuries de chaque joueur sont également contenues ici.
 */
typedef struct plateau_t {
    case_t cases[TAILLE_PLATEAU];
    case_t ecuries[NOMBRE_JOUEURS][NOMBRE_CHEVEAUX];
} plateau_t;

/** @brief Un jeu contenant un plateau et les cheveaux de chaque joueur. */
typedef struct jeu_t {
    plateau_t plateau; // Plateau sur lequel se dérouelera le jeu.
    int chevaux[NOMBRE_JOUEURS][NOMBRE_CHEVEAUX]; // Les chevaux de chaque joueur.
    int nbTours; // Le nombre de tours effectués durant cette partie.
} jeu_t;

/**
 * @brief Fonction permettant de vider un plateau de jeu.
 * Les cases régulières aussi bien que les écuries sont réinitialisées à CS_CASE_VIDE (-1).
 * @param p Adresse du plateau de jeu à vider.
 */
void viderPlateau(plateau_t* p);

/**
 * @brief Fonction permettant d'indiquer si une case est vide.
 * @param c Une case de plateau ou d'écurie.
 * @return 1 si la case est vide, 0 sinon.
 */
int caseEstVide(case_t c);

/**
 * @brief Fonction retournant un entier aléatoire compris entre min et max.
 * @param min Borne inférieure (incluse) de la plage des nombres possibles.
 * @param max Borne supérieure (incluse) de la plage des nombres possibles.
 * @return Un entier aléatoire compris entre min inclus et max inclus.
 */
int entierAleatoire(int min, int max);

/**
 * @brief Fonction permettant de lancer un dé à six faces.
 * @return Un résultat de dé (entier) compris entre 1 et 6.
 */
int lancerDe6(void);

#endif // !__PC_JEU_H__