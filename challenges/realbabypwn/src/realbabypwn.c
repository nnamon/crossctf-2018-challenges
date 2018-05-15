#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 0x100

void babymode() {
    system("/bin/sh");
}

void fibonacci() {
    char notes[BUFFER_SIZE];
    int choice;
    char letter;
    unsigned long buffer[BUFFER_SIZE];
    buffer[0] = 0;
    buffer[1] = 1;
    for (int i = 2; i < BUFFER_SIZE; i++) {
        buffer[i] = buffer[i-1] + buffer[i-2];
    }
    while (letter != 'n') {
        printf("Which fibbonacci offset did you want to look up? ");
        scanf("%d", &choice);
        printf("Fibbonaci Number %d: %lu\n", choice, buffer[choice]);
        printf("Want to learn another Fibbonaci number? (y/n) ");
        scanf("%s", &letter);
    }
    printf("Did you learn anything? ");
    read(0, notes, BUFFER_SIZE + 0x100);
}

int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    fibonacci();
}
