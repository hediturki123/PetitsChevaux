#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../hdr/pc_jeu.h"

#define IT_TOUR_JOUEUR 1
#define IT_LANCE_DE 2

typedef enum TypeInfo {
  LANCE_DE = 20,
  ENDGAME = 00,
  TOURJOUEUR = 10,
  OKTOURJOUEUR = 11,
  OKLANCEDE = 21
}TypeInfo;

typedef struct Infos {
  unsigned char validReception;
  TypeInfo infoType;
  int info;
}Infos;
