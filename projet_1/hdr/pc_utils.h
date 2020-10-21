#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define IT_TOUR_JOUEUR 1
#define IT_LANCE_DE 2

typedef enum TypeInfo {
  LANCE_DE = 2,
  ENDGAME = 0,
  TOURJOUEUR = 1
}TypeInfo;

typedef struct Infos {
  unsigned char validReception;
  TypeInfo infoType;
  int info;
}Infos;
