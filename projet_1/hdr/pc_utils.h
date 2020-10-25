/**
 * \file pc_utils.h
 * \brief Entête du module utilitaire du projet Petits Chevaux.
 * \author Hedi TURKI SANEKLI, Alexis YVON
 * \version 1.0
 * \date Octobre 2020
 *
 * Ce fichier constitue l'entête du module utilitaire du projet Petits Chevaux.
 * On y retrouve toutes les structures utiles à la transmission et la réception
 * d'informations entre le processus père et ses fils, ainsi que les entêtes
 * des fonctions d'actions correspondantes.
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "../hdr/pc_jeu.h"

#ifndef __PC_UTILS_H__
#define __PC_UTILS_H__

/**
 * \enum "LIRE & ECRIRE"
 * \brief 0 pour LIRE ; 1 pour ECRIRE.
 *
 * Enumération servant à désambiguïser la lecture et l'écriture dans les pipes.
 */
enum {LIRE, ECRIRE};

/// Macros pour les descripteurs du maître.
/**
 * \def FD_M_J0
 * \brief Descripteurs de fichiers pour l'interaction du maître vers le joueur 0.
 */
#define FD_M_J0 fdMaitre[0]
/**
 * \def FD_J0_M
 * \brief Descripteurs de fichiers pour l'interaction du joueur 0 vers le maître.
 */
#define FD_J0_M fdMaitre[1]

/**
 * \enum "Statut"
 * \brief Statut d'une information.
 *
 * Les différents statuts permettent d'attester la validité et d'orienter le comportement du destinataire vis-à-vis de celle-ci.
 */
typedef enum statut_e {
    ST_ERREUR,  // L'information est erronée.
    ST_DEMANDE, // L'information est une demande du maître du jeu.
    ST_OK       // L'information est une réponse à une demande.
} statut_e;

/**
 * \enum "Type d'information"
 * \brief Type d'une information permettant de distinguer les différentes actions possibles vis-à-vis de celle-ci.
 *
 * Une information peut concerner le joueur à qui c'est le tour, le lancer de dé d'un joueur ou si c'est la fin d'une partie.
 */
typedef enum info_type_e {
    IT_FIN_PARTIE,  // Information signifiant la fin d'une partie.
    IT_TOUR_JOUEUR, // Information sur le joueur qui doit jouer.
    IT_LANCE_DE     // Information sur le lancer de dé d'un joueur.
} info_type_e;

/**
 * \struct info_t pc_utils.h "Information"
 * \brief Une information pouvant circuler entre les joueurs et le maître du jeu.
 */
typedef struct info_t {
    info_type_e type; // Type d'information transmise.
    statut_e statut;  // Statut de l'information transmise.
    int data;         // Donnée transmise par l'information.
    int source;       // Numéro du joueur ayant envoyé l'info ; -1 pour le maître du jeu.
} info_t;

/**
 * \fn info_t actionJoueur (info_t*, int, int[NOMBRE_JOUEURS][2], int[2][2])
 * \brief Action sur l'information reçue par un joueur.
 * Dans cette fonction, un joueur traite l'information transmise par le joueur précédent.
 * Si l'information concerne le joueur, ce dernier envoie une réponse appropriée par rapport à celle-ci. Sinon, il se
 * contente de la transmettre au joueur suivant.
 *
 * \param[in, out] info Information à traiter par le joueur.
 * \param[in] numJoueur Numéro du joueur effectuant l'action.
 * \param[in, out] fdJoueur Descripteurs de fichiers des joueurs.
 * \param[in] fdMaitre Descripteurs de fichiers du maître du jeu.
 * \return Type de l'information obtenue après traitement.
 */
info_t actionJoueur(info_t* info, int numJoueur, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]);

/**
 * \fn info_t actionMaitre (info_t*, jeu_t*, int[NOMBRE_JOUEURS][2], int[2][2])
 * \brief Action sur l'information reçue par le maître du jeu.
 * C'est ici que sont effectués la modification de l'état du jeu et l'affichage du déroulement de la partie.
 *
 * \param[in, out] info Information à traiter par le maître du jeu.
 * \param[in, out] jeu Jeu à mettre à jour vis-à-vis de l'information.
 * \param[in] fdJoueur Descripteurs de fichiers des joueurs.
 * \param[in, out] fdMaitre Descripteurs de fichiers du maître du jeu.
 * \return Type de l'information obtenue après traitement.
 */
info_t actionMaitre(info_t* info, jeu_t* jeu, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]);

/**
 * \fn void printInfo (info_t, int);
 * \brief Fonction utilitaire de débugging permettant l'affichage propre d'une information.
 * \param[in] i Une information.
 * \param[in] numJoueur Numéro du joueur traitant l'information.
 */
void printInfo(info_t i, int numJoueur);

/**
 * \fn int mathMod (int, int)
 * \brief Modulo mathématique d'un entier par un autre.
 * \param[in] n Entier positif ou négatif.
 * \param[in] m Modulo ; entier positif.
 * \return Modulo m de l'entier n.
 */
int mathMod(int n, int m);

/**
 * \fn void fermDescInut (int, int[NOMBRE_JOUEURS][2], int[2][2])
 * \brief Fonction de fermeture des descripteurs inutiles du programme.
 * Cette fonction permet la fermeture des descripteurs de fichiers inutiles au maître du jeu ainsi
 * qu'aux joueurs, afin d'éviter de rester en attente de ceux-ci à la fin du programme.
 *
 * \param[in] numJoueur Numéro du joueur ayant des descripteurs à fermer.
 * \param[in, out] fdJoueur Structure des descripteurs de joueurs.
 * \param[in, out] fdMaitre Structure des descripteurs du maître du jeu.
 */
void fermDescInut(int numJoueur, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]);

#endif // !__PC_UTILS_H__