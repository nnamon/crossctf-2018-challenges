#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char moon[] = "moon.ascii";

void print_banner() {
    char path[255] = {0};
    strcpy(path, "/home/quietmoon/");
    strcat(path, moon);
    FILE * moon_file = fopen(path, "r");
    char banner[100000] = {0};
    fread(banner, 81115, 1, moon_file);
    puts(banner);
}

int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    alarm(5);

    char buffer[256] = {0};

    while (1) {
        print_banner();
        read(0, buffer, 255);
        printf(buffer);
    }
}
