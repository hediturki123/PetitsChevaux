#include "../hdr/pc_utils.h"
#include <stdio.h>



Infos readFile(int fd) {
    Infos info;
    read(fd, &info, sizeof(Infos));
    printf("Lecture : buf = %d\n", info.info);
    return info;
}

void writeFile(int fd, Infos i) {
    write(fd, &i, sizeof(Infos));
    printf("Ecriture : buf = %d\n", i.info);
}


Infos interpreteInfo(Infos info, int numJoueur){
  switch(info.infoType){
    case TypeInfo.ENDGAME :
      writeFile(fdJoueur[numJoueur][1], info);
      exit(0);
      break;

    case TypeInfo.TOURJOUEUR :
      if (info.info == numJoueur){
        printf("c'est mon tour, %d\n", numJoueur);
        info.infoType = TypeInfo.OKTOURJOUEUR;
      }
      writeFile(fdJoueur[numJoueur][1], info);
      break;

    case TypeInfo.LANCE_DE :
      if (info.info == numJoueur){
        info.infoType = TypeInfo.OKLANCEDE;
        info.info = lancerDe6();
      }
      writeFile(fdJoueur[numJoueur][1], info);
      break;

    default :
      writeFile(fdJoueur[numJoueur][1], info);
  }
}
