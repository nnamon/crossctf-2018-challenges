#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

char * hidden_message = "If you can see this hidden message, you are on the right track.";

char moon[] = "moon.ascii";

char * flag = "The flag is not in this binary, please get a shell.";

void print_banner() {
    char path[255] = {0};
    strcpy(path, "/home/moonmoon/");
    strcat(path, moon);
    FILE * moon_file = fopen(path, "r");
    char banner[100000] = {0};
    fread(banner, 81115, 1, moon_file);
    puts(banner);
}

void do_nothing() {
    int z = strlen(hidden_message);
    int k = strlen(flag);
    int a = 1;
    int b = 2;
    int c = 3;
    int d = a * a * b * c * d;
    c = a << b;
    return;
}

int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    alarm(420);

    char buffer[256] = {0};
    char results[4196] = {0};

    while (1) {
        print_banner();
        do_nothing();
        do_nothing();
        read(0, buffer, 255);
        sprintf(results, buffer);
        for (int i = 0; i < 4196; i++) {
            results[i] ^= 0x42;
        }
        write(1, results, 4196);
    }
}
