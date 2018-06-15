#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <time.h>
#include <string.h>

#include "art.h"

#define START_ADDRESS 0x700b1000
#define ERROR_MESSAGE "Invalid internal error."

char flag = 0;
char flag_denied = 0;
uint32_t something = 1;

struct can {
    uint64_t version;
    uint64_t serial;
    char title[56];
    char * error_message;
};

void coca() {
    char flagged[256];
    puts(art);
    read(0, flagged, 255);
    if ((uint8_t) flag_denied == 0xc5) {
        read(0, &something, 1);
    }
}

void cola() {
    struct can coke_can;

    coke_can.serial = rand() % 10000000000 + 1;

    if (something) {
        coke_can.version = 0x1337;
        strcpy(coke_can.title, "Limited Edition Coca Cola - Product of Mexico");
        coke_can.error_message = ERROR_MESSAGE;
    }

    printf("Here's your randomly generated coke can!\n");
    printf("Version: V.%lu\n", coke_can.version);
    printf("Serial Number: %lu\n", coke_can.serial);
    printf("Title: %s\n", coke_can.title);

    if (flag == 'D' && coke_can.error_message) {
        printf("Errors were found.\n");
        printf("Error: %s\n", coke_can.error_message);
    }
}

int main() {
    // Disable buffering on stdin, stdout, and stderr
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    // Seed the random generator
    srand(time(NULL));

    // Map the flag into memory
    int fd = open("flag_page", O_RDONLY, (mode_t) 0600);
    struct stat fileInfo = {0};
    void * ptr = (void *) START_ADDRESS;
    if (fstat(fd, &fileInfo) == -1)
    {
        perror("Error getting the file size");
        return -1;
    }
    char * map;
    map = (char *) mmap(ptr, fileInfo.st_size, PROT_READ, MAP_SHARED, fd, 0);

    printf("Do you want to flip the flag switch? (y/n) ");
    scanf("%2s", &flag);

    coca();
    cola();

    puts("Did you get it? If not try again.");
}
