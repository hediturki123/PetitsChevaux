#include "../hdr/pc_utils.h"

void interpreteInfo(info_t *info, int numJoueur, int fdJoueur[NOMBRE_JOUEURS][2]) {
    switch (info->type) {
        case IT_FIN_PARTIE:
            write(fdJoueur[numJoueur][1], &info, sizeof(info_t));
            exit(0);

        case IT_TOUR_JOUEUR:
            if (info->data == numJoueur) {
                printf("Joueur %d : c'est mon tour !\n", numJoueur);
                info->statut = ST_OK;
            }
            else if (info->statut == ST_DEMANDE && numJoueur > info->data) {
                info->statut = ST_ERREUR;
            }
            write(fdJoueur[numJoueur][1], &info, sizeof(info_t));
            break;

        case IT_LANCE_DE:
            if (info->data == numJoueur) {
                info->statut = ST_OK;
                info->data = lancerDe6();
            }
            write(fdJoueur[numJoueur][1], &info, sizeof(info_t));
            break;

        default:
            write(fdJoueur[numJoueur][1], &info, sizeof(info_t));
        }
}