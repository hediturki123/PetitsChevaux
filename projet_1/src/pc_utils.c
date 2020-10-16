#include "../hdr/pc_utils.h"

int redirect(int oldFd, int newFd) {
    close(oldFd);
    dup(newFd);
    close(newFd);
}