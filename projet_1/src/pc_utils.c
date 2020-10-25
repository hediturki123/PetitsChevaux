/**
 * \file pc_utils.c
 * \brief Module utilitaire du projet Petits Chevaux.
 * \author Hedi TURKI SANEKLI, Alexis YVON
 * \version 1.0
 * \date Octobre 2020
 *
 * Ce fichier contient les fonctions utilitaires du projet Petits Chevaux.
 * Ces fonctions permettent notamment la mise en place du protocole de communication
 * entre le processus père (maître du jeu) et ses fils (joueurs).
 * Il y a également diverses fonctions d'affichage et de calcul.
 */

#include "../hdr/pc_utils.h"

info_t actionJoueur(info_t *info, int numJoueur, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]) {
    info_t reponse;
    reponse.type = info->type;
    reponse.source = numJoueur;
    switch (info->type) {
        case IT_FIN_PARTIE:
            reponse.statut = info->statut;
            reponse.data = 42;
            close(fdJoueur[mathMod(numJoueur-1,NOMBRE_JOUEURS)][LIRE]);
            close(fdJoueur[numJoueur][ECRIRE]);
            exit(EXIT_SUCCESS);

        case IT_TOUR_JOUEUR:
            if (info->statut == ST_DEMANDE) {
                if (info->data == numJoueur) {
                    reponse.statut = ST_OK;
                } else if (numJoueur > info->data) {
                    reponse.statut = ST_ERREUR;
                }
            } else {
                reponse.statut = info->statut;
            }
            reponse.data = info->data;
            break;

        case IT_LANCE_DE:
            if (info->data == numJoueur) {
                reponse.statut = ST_OK;
                reponse.data = lancerDe6() + 10*numJoueur;
            } else {
                reponse.statut = info->statut;
                reponse.data = info->data;
            }
            break;

        default:
            // TODO: gestion de l'erreur
            break;
        }
        if (info->source == (NOMBRE_JOUEURS-1))
            write(FD_J0_M[ECRIRE], &reponse, sizeof(info_t));
        else if (!(numJoueur == NOMBRE_JOUEURS-1 && reponse.type == IT_FIN_PARTIE))
            write(fdJoueur[numJoueur][ECRIRE], &reponse, sizeof(info_t));
        return reponse;
}

info_t actionMaitre(info_t* info, jeu_t* jeu, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]) {
    info_t reponse;
    int numJoueur;
    switch (info->type) {
        case IT_LANCE_DE:
            if (info->statut == ST_OK) {
                numJoueur = info->data/10;
                int de6 = info->data - 10*numJoueur;
                printf("> \033[0;3%dmJoueur %d\033[0;0m a fait un \033[0;3m%d\033[0;0m à son lancé.\n", numJoueur+1, numJoueur, de6);
                // TODO: Mettre à jour la structure de jeu.
                reponse.source = -1;
                reponse.statut = ST_DEMANDE;
                if (jeu->nbTours > 4) { // FIXME: Mettre la bonne condition de fin de jeu.
                    reponse.type = IT_FIN_PARTIE;
                    reponse.data = 0;
                } else {
                    if (de6 == 6) { // Dans le cas d'un 6, le joueur peut rejouer.
                        reponse.type = IT_LANCE_DE;
                        printf("> \033[0;3%dmJoueur %d\033[0;0m peut rejouer !\n", numJoueur+1, numJoueur);
                    } else { // Sinon, c'est au joueur suivant.
                        if (numJoueur == NOMBRE_JOUEURS-1) (jeu->nbTours)++; // On incrémente le nombre de tours si c'est le dernier joueur.
                        reponse.type = IT_TOUR_JOUEUR;
                        numJoueur = mathMod(numJoueur+1,NOMBRE_JOUEURS);
                        printf("> Au tour de \033[0;3%dmJoueur %d\033[0;0m !\n", numJoueur+1, numJoueur);
                    }
                    reponse.data = numJoueur;
                }
            }
            break;

        case IT_TOUR_JOUEUR:
            if (info->statut == ST_OK) {
                numJoueur = info->data;
                reponse.source = -1;
                reponse.type = IT_LANCE_DE;
                reponse.statut = ST_DEMANDE;
                reponse.data = numJoueur;
            }
            break;

        default:
            break;
        }
        write(FD_M_J0[1], &reponse, sizeof(info_t));
        return reponse;
}

void printInfo(info_t i, int numJoueur) {
    printf(
        "---- INFO ----\n%d> Type : %d\n%d> Statut : %d\n%d> Data : %d\n%d> Source : %d\n--------------\n",
        numJoueur, i.type,
        numJoueur, i.statut,
        numJoueur, i.data,
        numJoueur, i.source
    );
}

int mathMod(int n, int m) {
    n %= m;
    return n < 0 ? n+m : n;
}

void fermDescInut(int numJoueur, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]) {
    switch (numJoueur) {
        case -1:
            for (int i = 0; i < NOMBRE_JOUEURS; i++) {
                close(fdJoueur[i][LIRE]);
                close(fdJoueur[i][ECRIRE]);
            }
            close(FD_J0_M[ECRIRE]);
            close(FD_M_J0[LIRE]);
            break;
        case 0:
            close(FD_J0_M[LIRE]);
            close(FD_M_J0[ECRIRE]);
            close(fdJoueur[0][LIRE]);
            close(fdJoueur[1][ECRIRE]);
            if (NOMBRE_JOUEURS <= 3) {
                close(fdJoueur[1][LIRE]);
                close(fdJoueur[2][ECRIRE]);
            }
            if (NOMBRE_JOUEURS <= 4) {
                close(fdJoueur[2][LIRE]);
                close(fdJoueur[3][ECRIRE]);
            }
            break;
        case 1:
            close(FD_M_J0[ECRIRE]);
            close(FD_M_J0[LIRE]);
            close(FD_J0_M[ECRIRE]);
            close(FD_J0_M[LIRE]);
            close(fdJoueur[0][ECRIRE]);
            close(fdJoueur[1][LIRE]);
            if (NOMBRE_JOUEURS <= 3) {
                close(fdJoueur[2][ECRIRE]);
                close(fdJoueur[2][LIRE]);
            }
            if (NOMBRE_JOUEURS <= 4) {
                close(fdJoueur[3][ECRIRE]);
                close(fdJoueur[3][LIRE]);
            }
            break;
        case 2:
            close(FD_M_J0[ECRIRE]);
            close(FD_M_J0[LIRE]);
            close(FD_J0_M[ECRIRE]);
            close(FD_J0_M[LIRE]);
            close(fdJoueur[1][ECRIRE]);
            close(fdJoueur[2][LIRE]);
            if (NOMBRE_JOUEURS <= 4) {
                close(fdJoueur[3][ECRIRE]);
                close(fdJoueur[3][LIRE]);
            }
            break;
        case 3:
            close(FD_M_J0[ECRIRE]);
            close(FD_M_J0[LIRE]);
            close(FD_J0_M[ECRIRE]);
            close(FD_J0_M[LIRE]);
            close(fdJoueur[0][ECRIRE]);
            close(fdJoueur[0][LIRE]);
            close(fdJoueur[1][ECRIRE]);
            close(fdJoueur[1][LIRE]);
            close(fdJoueur[2][ECRIRE]);
            close(fdJoueur[3][LIRE]);
            break;
    }
}