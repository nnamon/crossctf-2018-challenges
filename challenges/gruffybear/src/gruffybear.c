#include <stdlib.h>
#include <stdio.h>

int admin_enabled = 0;

void print_banner() {
    puts("Forest Fires are Bad!");
    puts("Stop Smoking, We Love You.");
    puts("1. Build a Bear");
    puts("2. Select Favourite Bear");
    puts("3. Delete Bear");


    if (admin_enable) {
        puts("4. Initialize ");
    }

    puts("0. Exit");
}

int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    int choice = 999;

    while (choice) {
        print_banner();

        scanf("%d", &choice);
        switch(choice) {
            case 1:
                puts("Case 1");
            default:
                puts("Nothing to do.");
        }
    }
}
