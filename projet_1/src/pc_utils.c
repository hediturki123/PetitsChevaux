#include "../hdr/pc_utils.h"

info_t actionJoueur(info_t *info, signed char numJoueur, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]) {
    switch (info->type) {
        case IT_FIN_PARTIE:
            if (info->source != (NOMBRE_JOUEURS-1)) // Pas besoin d'envoyer l'info, le premier fils est déjà mort.
                write(fdJoueur[numJoueur][1], &info, sizeof(info_t));
            // TODO: nettoyer le jeu et le processus (fermer les pipes, etc)

        case IT_TOUR_JOUEUR:
            if (info->statut == ST_DEMANDE) {
                if (info->data == numJoueur) {
                    info->statut = ST_OK;
                } else if (numJoueur > info->data) {
                    info->statut = ST_ERREUR;
                }
            } else {
                // TODO: gestion de l'erreur
            }
            break;

        case IT_LANCE_DE:
            if (info->data == numJoueur) {
                info->statut = ST_OK;
                info->data = numJoueur + (lancerDe6() << sizeof(char));
                info->source = numJoueur;
            }
            break;

        default:
            // TODO: gestion de l'erreur
            break;
        }
        if (info->source == (NOMBRE_JOUEURS-1)) {
            info->source = numJoueur;
            write(FD_J0_M[1], &info, sizeof(info_t));
        } else {
            info->source = numJoueur;
            write(fdJoueur[numJoueur][1], &info, sizeof(info_t));
        }
        return *info;
}

info_t actionMaitre(info_t* info, jeu_t* jeu, int fdJoueur[NOMBRE_JOUEURS][2], int fdMaitre[2][2]) {
    signed char numJoueur;
    switch (info->type) {
        case IT_LANCE_DE:
            if (info->statut == ST_OK) {
                numJoueur = (signed char) (info->data & 0xf);
                unsigned char de6 = info->data >> sizeof(char);
                printf("> Joueur %d a fait un %d à son lancé.\n", numJoueur, de6);
                // TODO: mettre à jour le jeu.
                info->source = -1;
                if (jeu->nbTours > 4) { // FIXME: mettre la bonne condition de fin de jeu.
                    info->type = IT_FIN_PARTIE;
                    info->statut = ST_DEMANDE;
                    info->data = 0;
                } else {
                    if (de6 == 6) { // Dans le cas d'un 6, le joueur peut rejouer.
                        info->type = IT_LANCE_DE;
                        printf("> Le joueur %d peut rejouer !\n", numJoueur);
                    } else { // Sinon, c'est au joueur suivant.
                        info->type = IT_TOUR_JOUEUR;
                        numJoueur = (numJoueur+1)%NOMBRE_JOUEURS;
                        printf("> Au tour du joueur %d !\n", numJoueur);
                    }
                    info->data = numJoueur;
                    info->statut = ST_DEMANDE;
                }
            } else {
                // TODO: gestion de l'erreur
            }

        case IT_TOUR_JOUEUR:
            if (info->statut == ST_OK) {
                numJoueur = (signed char) info->data;
                info->source = -1;
                info->type = IT_LANCE_DE;
                info->statut = ST_DEMANDE;
                info->data = numJoueur;
            } else {
                // TODO: gestion de l'erreur
            }

        default:
            // TODO: gestion de l'erreur
            break;
        }
        write(FD_M_J0[1], &info, sizeof(info_t));
        return *info;
}