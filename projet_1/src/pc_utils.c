#include "../hdr/pc_utils.h"

// TODO: commenter la fonction
void actionJoueur(info_t *info, int numJoueur, int fdJoueur[NOMBRE_JOUEURS][2]) {
    switch (info->type) {
        case IT_FIN_PARTIE:
            if (info->source != (NOMBRE_JOUEURS-1)) // Pas besoin d'envoyer l'info, le premier fils est déjà mort.
                write(fdJoueur[numJoueur][1], &info, sizeof(info_t));
            // TODO: nettoyer le jeu et le processus (fermer les pipes, etc)
            exit(EXIT_SUCCESS);

        case IT_TOUR_JOUEUR:
            if (info->data == numJoueur) {
                printf("Joueur %d : c'est mon tour !\n", numJoueur);
                info->statut = ST_OK;
            } else if (info->statut == ST_DEMANDE && numJoueur > info->data) {
                info->statut = ST_ERREUR;
            }
            if (info->source == (NOMBRE_JOUEURS-1))
                {} // TODO: écrire la sortie vers le maitre
            else
                write(fdJoueur[numJoueur][1], &info, sizeof(info_t));
            break;

        case IT_LANCE_DE:
            if (info->data == numJoueur) {
                info->statut = ST_OK;
                info->data = lancerDe6();
            }
            if (info->source == (NOMBRE_JOUEURS-1))
                {} // TODO: écrire la sortie vers le maitre
            else
                write(fdJoueur[numJoueur][1], &info, sizeof(info_t));
            break;

        default:
            exit(EXIT_FAILURE);
        }
}

// TODO: écrire la fonction d'interprétation du maître + commentaire
// C'est ici qu'auront lieu les modifications de l'état du jeu et l'affichage du retour.
void actionMaitre() {}