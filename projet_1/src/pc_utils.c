#include "../hdr/pc_utils.h"

int redirectInput(int fdin) {
    close(0);
    dup(fdin);
    close(fdin);
}

int redirectOutput(int fdout) {
    close(1);
    dup(fdout);
    close(fdout);
}