#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "art.h"
#include "art2.h"
#include <unistd.h>

typedef struct bear {
    char name[32];
    uint32_t id;
    uint32_t age;
    char description[128];
    void (*deallocator)(void *);
    void (*self_destruct)(int);
} bear;

int admin_enabled = 0;
bear * selected_bear = NULL;
bear * bears[13];
uint32_t num_bears = 0;
char * comment = NULL;

void print_banner() {
    puts("Forest Fires are Bad!");
    puts("Stop Smoking, We Love You.");
    puts("1. Build a Bear");
    puts("2. Select Favourite Bear");
    puts("3. Delete Bear");
    puts("4. Print Bear");
    puts("5. Add Comment");
    puts("6. Print Comment");

    if (admin_enabled) {
        puts("7. Initialize Self-Destruction Sequence");
    }

    puts("0. Exit");
}

void self_destruct_device(int x) {
    for (int i = 0; i < x; i++) {
        sleep(1);
        puts(art2);
    }
    exit(0);
}

void build_bear() {
    if (num_bears < 13) {
        bears[num_bears] = calloc(1, sizeof(bear));
        bear * current_bear = bears[num_bears];
        printf("Bear Name: ");
        read(0, current_bear->name, 31);
        printf("Bear ID: ");
        scanf("%x", &current_bear->id);
        printf("Bear Age: ");
        scanf("%d", &current_bear->age);
        printf("Bear Description: ");
        read(0, current_bear->description, 128);
        current_bear->deallocator = free;
        current_bear->self_destruct = self_destruct_device;
        puts("Bear created!");
        ++num_bears;
    }
    else {
        printf("Here we are now... ");
        char * slts = "SUNIATRETNE";
        char x;
        for (int i = 10; i >= 0; i--) {
            read(0, &x, 1);
            if (slts[i] != x) {
                return;
            }
        }
        read(0, &x, 1);
        admin_enabled = 1;
    }
}

void select_bear() {
    int selection = 0;
    printf("Selection: ");
    scanf("%d", &selection);
    if (selection >= 0 && selection < num_bears) {
        selected_bear = bears[selection];
    }
    else {
        puts("Not enough bears.");
    }
}

void delete_bear() {
    if (selected_bear) {
        printf("Deleting [%s]...\n", selected_bear->name);
        if (selected_bear->deallocator == free) {
            selected_bear->deallocator(selected_bear);
        }
        puts("Deleted!");
    }
    else {
        puts("No bear selected!");
    }
}

void print_bear() {
    if (selected_bear) {
        puts(art);
        printf("You have selected: [%s]\n", selected_bear->name);
        printf("It's ID is %x\n", selected_bear->id);
        printf("It's AGE is %d\n", selected_bear->age);
        printf("It's DESCRIPTION is %s\n", selected_bear->description);
    }
    else {
        puts("No bear selected!");
    }
}

void add_comment() {
    uint32_t length;
    printf("How long should the comment be: ");
    scanf("%d", &length);
    comment = calloc(length + 1, sizeof(char));
    printf("Comment: ");
    read(0, comment, length);
}

void print_comment() {
    if (comment) {
        puts(comment);
    }
    else {
        puts("No");
    }
}

void destruction() {
    if (!admin_enabled) {
        puts("Nothing to do");
        return;
    }
    else {
        if (selected_bear) {
            selected_bear->self_destruct(num_bears);
        }
    }
}

int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    int choice = 999;

    alarm(60);

    while (choice) {
        print_banner();

        scanf("%d", &choice);
        switch(choice) {
            case 1:
                build_bear();
                break;
            case 2:
                select_bear();
                break;
            case 3:
                delete_bear();
                break;
            case 4:
                print_bear();
                break;
            case 5:
                add_comment();
                break;
            case 6:
                print_comment();
                break;
            case 7:
                destruction();
                break;
            default:
                puts("Nothing to do.");
        }
    }
}
