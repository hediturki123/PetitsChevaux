#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "../hdr/pc_jeu.h"

#ifndef __PC_UTILS_H__
#define __PC_UTILS_H__

/** @brief Enumération servant à désambiguïser la lecture et l'écriture dans les pipes. */
enum {LIRE, ECRIRE};

// Macros pour les descripteurs du maître.
#define FD_M_J0 fdMaitre[0] /** @brief Descripteurs de fichiers pour l'interaction du maître vers le joueur 0. */
#define FD_J0_M fdMaitre[1] /** @brief Descripteurs de fichiers pour l'interaction du joueur 0 vers le maître. */

/**
 * @brief Statut d'une information.
 * Les différents statuts permettent d'attester la validité et d'orienter le comportement du destinataire vis-à-vis de celle-ci.
 */
typedef enum statut_t {
    ST_ERREUR, // L'information est erronée.
    ST_DEMANDE, // L'information est une demande du maître du jeu.
    ST_OK // L'information est une réponse à une demande.
} statut_t;

/** @brief Type d'une information. Celui-ci permet de distinguer les différentes actions possibles. */
typedef enum info_type_t {
    IT_FIN_PARTIE, // Information signifiant la fin d'une partie.
    IT_TOUR_JOUEUR, // Information sur le joueur qui doit jouer.
    IT_LANCE_DE // Information sur le lancer de dé d'un joueur.
} info_type_t;

/** @brief Une information pouvant circuler entre les joueurs et le maître du jeu. */
typedef struct info_t {
    info_type_t type; // Type d'information transmise.
    statut_t statut; // Statut de l'information transmise.
    int data; // Donnée transmise par l'information.
    int source; // Numéro du joueur ayant envoyé l'info ; -1 pour le maître du jeu.
} info_t;

// TODO: Corriger header `actionJoueur`.
/** Action sur l'information reçue par un joueur. */
info_t actionJoueur(info_t* info, int numJoueur, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]);

/**
 * @brief Action sur l'information reçue par le maître du jeu.
 * C'est ici que sont effectués la modification de l'état du jeu et l'affichage du déroulement de la partie.
 * @param info Information à traiter par le maître du jeu.
 * @param jeu Jeu à mettre à jour vis-à-vis de l'information.
 * @param fdJoueur Descripteurs de fichiers des joueurs.
 * @param fdMaitre Descripteurs de fichiers du maître du jeu.
 * @return Type de l'information obtenue après traitement.
 */
info_t actionMaitre(info_t* info, jeu_t* jeu, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]);

// TODO: Commenter header `printInfo`.
void printInfo(info_t i, int numJoueur);

/**
 * @brief Modulo mathématique d'un entier par un autre.
 * @param n Entier positif ou négatif.
 * @param m Modulo ; entier positif.
 * @return Modulo m de l'entier n.
 */
int mathMod(int n, int m);

/**
 * @brief Fonction de fermeture des descripteurs inutiles du programme.
 * @param numJoueur Numéro du joueur ayant des descripteurs à fermer.
 * @param fdJoueur Adresse de la structure des descripteurs de joueurs.
 * @param fdMaitre Adresse de la structure des descripteurs du maître du jeu.
 */
void fermDescInut(int numJoueur, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]);

#endif // !__PC_UTILS_H__