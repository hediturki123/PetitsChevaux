#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "../hdr/pc_jeu.h"

#ifndef __PC_UTILS_H__
#define __PC_UTILS_H__

typedef enum statut_t {
    ST_ERREUR = -1,
    ST_DEMANDE = 0,
    ST_OK = 1
} statut_t;

typedef enum info_type_t {
    IT_FIN_PARTIE = 0,
    IT_TOUR_JOUEUR = 1,
    IT_LANCE_DE = 2
} info_type_t;

typedef struct info_t {
    statut_t statut;
    info_type_t type;
    int data;
} info_t;

void interpreteInfo(info_t* info, int numJoueur, int fdJoueur[NOMBRE_JOUEURS][2]);

#endif // !__PC_UTILS_H__