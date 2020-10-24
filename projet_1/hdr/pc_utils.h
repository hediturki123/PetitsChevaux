#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "../hdr/pc_jeu.h"

#ifndef __PC_UTILS_H__
#define __PC_UTILS_H__

/**
 * Statut d'une information.
 * Les différents statuts permettent d'attester la validité et d'orienter le comportement du destinataire vis-à-vis de celle-ci.
 */
typedef enum statut_t {
    ST_ERREUR = -1, // L'information est erronée.
    ST_DEMANDE = 0, // L'information est une demande du maître du jeu.
    ST_OK = 1 // L'information est une réponse à une demande.
} statut_t;

/**
 * Type d'une information.
 * Celui-ci permet de distinguer les différentes actions possibles.
 */
typedef enum info_type_t {
    IT_FIN_PARTIE = 0, // Information signifiant la fin d'une partie.
    IT_TOUR_JOUEUR = 1, // Information sur le joueur qui doit jouer.
    IT_LANCE_DE = 2 // Information sur le lancer de dé d'un joueur.
} info_type_t;

/** Une information pouvant circuler entre les joueurs et le maître du jeu. */
typedef struct info_t {
    statut_t statut; // Statut de l'information transmise.
    info_type_t type; // Type d'information transmise.
    int data; // Donnée transmise par l'information.
    signed char source; // Numéro du joueur ayant envoyé l'info ; -1 pour le maître du jeu.
} info_t;

/** Action sur l'information reçue par un joueur. */
info_t actionJoueur(info_t* info, signed char numJoueur, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]);

/**
 * Action sur l'information reçue par le maître du jeu.
 * C'est ici que sont effectués la modification de l'état du jeu et l'affichage du déroulement de la partie.
 * @param info Information à traiter par le maître du jeu.
 * @param jeu Jeu à mettre à jour vis-à-vis de l'information.
 * @param fdJoueur Descripteurs de fichiers des joueurs.
 * @param fdMaitre Descripteurs de fichiers du maître du jeu.
 * @return Type de l'information obtenue après traitement.
 */
info_t actionMaitre(info_t* info, jeu_t* jeu, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]);

#endif // !__PC_UTILS_H__