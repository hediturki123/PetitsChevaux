#include "../hdr/pc_utils.h"
#include <stdio.h>



Infos readFile(int fd, int nj) {
    Infos info;
    read(fd, &info, sizeof(Infos));
    printf("Lecture : buf = %d nj = %d\n", info.info, nj);
    return info;
}

void writeFile(int fd, int nj, Infos i) {
    write(fd, &i, sizeof(Infos));
    printf("Ecriture : buf = %d nj = %d\n", i.info, nj);
}
