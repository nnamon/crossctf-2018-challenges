#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>

void skipping_rope() {
    char * region = mmap(0, 0x2000, PROT_READ|PROT_WRITE|PROT_EXEC, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    for (int i = 0; i < 0x1000/16; i++) {
        read(0, region + (i*16), 6);
    }
    (*(void(*)()) region)();
}

int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    skipping_rope();
}
