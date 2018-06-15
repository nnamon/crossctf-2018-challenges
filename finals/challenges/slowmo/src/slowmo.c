#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

int happy = 0;

void (*indirection)();

char tape[256];

void dis() {
    system("/bin/date");
}

void dos() {
    system("/bin/sh");
}

int main() {
    indirection = dis;
    char * ptr = tape + 128;
    alarm(30);
    char inst;
    while (1) {
        if (happy) {
            for (int i = 0; i < 256; i++) {
                printf("/%02x", tape[i]);
            }
            printf("/\n");
        }
        read(0, &inst, 1);
        switch (inst) {
            case '<':
                ++ptr;
                break;
            case '>':
                --ptr;
                break;
            case '^':
                *ptr += 1;
                break;
            case 'v':
                *ptr -= 1;
                break;
            case '!':
                indirection();
                return 0;
            case '`':
                happy = 1;
        }
    }
}
