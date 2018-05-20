#include <stdlib.h>
#include <stdio.h>


int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    int choice = 999;

    while (choice) {
        print_banner();

        scanf("%d", &choice);
    }
}
