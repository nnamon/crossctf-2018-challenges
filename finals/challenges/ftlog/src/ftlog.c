#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include "art.h"

int main() {
    puts(art);
    char * area = malloc(0x200);
    mprotect(area, 0x200, PROT_READ | PROT_WRITE | PROT_EXEC);
    read(0, area, 0x200);
    void (*jump)(void) = (void *) area;
    jump();
}
