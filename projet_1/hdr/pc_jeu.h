/**
 * \file pc_jeu.h
 * \brief Entête du module de jeu du projet Petits Chevaux.
 * \author Hedi TURKI SANEKLI, Alexis YVON
 * \version 1.0
 * \date Octobre 2020
 *
 * Ce fichier constitue l'entête du module de jeu du projet Petits Chevaux.
 * C'est ici que sont déclarées toutes les structures nécéssaires au bon
 * fonctionnement du jeu ainsi que les entêtes des fonctions permettant de jouer (par
 * exemple les lancers de dé, le déplacement des pions, etc).
 */

#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#ifndef __PC_JEU_H__
#define __PC_JEU_H__

/// Définition des constantes de l'environnement de jeu.
/// Ces contantes peuvent être redéfinies lors de la compilation pour moduler le jeu.
#ifndef NOMBRE_JOUEURS
    #define NOMBRE_JOUEURS 4 /** \def Nombre de joueurs dans une partie ; par défaut 4, minimum 2, maximum 4. */
#endif // !NOMBRE_JOUEURS
#ifndef NOMBRE_CHEVAUX
    #define NOMBRE_CHEVAUX 4 /** \def Nombre de chevaux par joueurs ; par défaut 4, minimum 1. */
#endif // !NOMBRE_CHEVAUX
#ifndef TAILLE_PLATEAU
    #define TAILLE_PLATEAU 56 /** \def Taille du plateau de jeu en nombre de cases ; par défaut 56, minimum 4 (doit être un multiple de 4). */
#endif // !TAILLE_PLATEAU

/**
 * \enum "Case"
 * \brief Une case de plateau.
 *
 * L'entier -1 (CS_CASE_VIDE) correspond à une case vide.
 * Un entier n (n allant de 0 à 3) correspond à un cheval du joueur n (CS_CVL_Jn).
 */
typedef enum case_e {
    CS_CASE_VIDE = -1,  // Une case vide.
    CS_CVL_J0 = 0,      // Un cheval du joueur 0.
    CS_CVL_J1 = 1,      // Un cheval du joueur 1.
    CS_CVL_J2 = 2,      // Un cheval du joueur 2.
    CS_CVL_J3 = 3       // Un cheval du joueur 3.
} case_e;

/**
 * \struct plateau_t pc_jeu.h "Plateau de jeu"
 * \brief Plateau de jeu contenant TAILLE_PLATEAU cases.
 *
 * Un plateau de jeu qui contient TAILLE_PLATEAU cases formant un parcours circulaire.
 * Les cases des écuries de chaque joueur sont également contenues ici.
 */
typedef struct plateau_t {
    case_e cases[TAILLE_PLATEAU];                   // Cases formant le tour du plateau.
    case_e ecuries[NOMBRE_JOUEURS][NOMBRE_CHEVAUX]; // Cases spéciales sur lesquelles chaque joueur doit mettre ses chevaux pour gagner.
} plateau_t;

/**
 * \struct jeu_t pc_jeu.h "Jeu de Petits Chevaux"
 * \brief Structure simulant un jeu de Petits Chevaux.
 *
 * Un jeu contient un plateau et les chevaux de chaque joueur.
 */
typedef struct jeu_t {
    plateau_t plateau;                           // Plateau sur lequel se dérouelera le jeu.
    int chevaux[NOMBRE_JOUEURS][NOMBRE_CHEVAUX]; // Les chevaux de chaque joueur.
    int nbTours;                                 // Le nombre de tours effectués durant cette partie.
} jeu_t;

/**
 * \fn void viderPlateau (plateau_t*);
 * \brief Fonction permettant de vider un plateau de jeu.
 * \param p Adresse du plateau de jeu à vider.
 *
 * Les cases régulières aussi bien que les écuries sont réinitialisées à CS_CASE_VIDE (-1).
 */
void viderPlateau(plateau_t* p);

/**
 * \fn int caseEstVide (case_e)
 * \brief Fonction permettant d'indiquer si une case est vide.
 * \param c Une case de plateau ou d'écurie.
 * \return 1 si la case est vide, 0 sinon.
 */
int caseEstVide(case_e c);

/**
 * \fn int entierAleatoire (int, int);
 * \brief Fonction retournant un entier aléatoire compris entre min et max.
 * \param min Borne inférieure (incluse) de la plage des nombres possibles.
 * \param max Borne supérieure (incluse) de la plage des nombres possibles.
 * \return Un entier aléatoire compris entre min inclus et max inclus.
 */
int entierAleatoire(int min, int max);

/**
 * \fn int lancerDe6 (void)
 * \brief Fonction permettant de lancer un dé à six faces.
 * \return Un résultat de dé (entier) compris entre 1 et 6.
 */
int lancerDe6(void);

#endif // !__PC_JEU_H__