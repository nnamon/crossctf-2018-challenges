#include<stdio.h>

void loc000();
void loc001();
void loc002();
void loc010();
void loc012();
void loc020();
void loc030();
void loc100();
void loc101();
void loc110();
void loc112();
void loc130();
void loc200();
void loc210();
void loc220();
void loc221();
void loc230();
void loc300();
void loc310();
void loc330();

int scan(){
    int n;
    scanf("%d", &n);
    printf("\n");
    return n;
}

void printmovement(int n){
    char strings[6][20] = {"North", "South", "East", "West", "Up", "Down"};
    printf ("Where would you like to move?\n");
    int count = 1;
    while (n){
        if (n % 10){
            printf ("%d -- %s\n", count, strings[count-1]);
        }
        count++;
        n /= 10;
    }
    printf ("9 -- Quit\n");
}

void scribble(int n, int k){
    printf ("Scribbled into the wall is the number %d.\n", n);
    printf ("Below in red, the number %d was written.\n", k);
}

void scribbles(int m, int n, int k){
    printf ("Scribbled into the wall are the numbers %d and %d.\n", m, n);
    printf ("Below in red, the number %d was written\n", k);
}

void scribbled(int m, int n, int o, int k){
    printf ("Scribbled into the wall are the numbers %d, %d and %d.\n", m, n, o);
    printf ("Below in red, the number %d was written\n", k);
}

void loc000(){
    printf("00 00 00, Score: 00\n");
    printf("The room is just empty space. It is a void.\n");
    scribbles(9, 12, 0);
    printmovement(10110);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (2):
            loc010();
            break;
        case (3):
            loc001();
            break;
        case (5):
            loc100();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc001(){
    printf("00 00 01, Score: 03\n");
    printf("An Egyptian statue stands in the middle of the room. A pungent smell covering it.\n");
    scribble (14, 3);
    printmovement(11100);

    int k = scan();
    switch (k){
        case (9):
            return;
        case (3):
            loc002();
            break;
        case (4):
            loc000();
            break;
        case (5):
            loc101();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc002(){
    printf("00 00 02, Score: 00\n");
    printf("Even though you are breathing normally, this room is suffocating.\n");
    scribbled(5, 7, 10, 1);
    printmovement(1010);
    int k = scan();
    switch(k){
        case (9):
            return;
        case (2):
            loc012();
            break;
        case (4):
            loc001();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc010(){
    printf("00 01 00, Score: 02\n");
    printf("A think blanket of fog covers this room.\n");
    scribble(15, 4);
    printmovement(10011);
    int k = scan();
    switch(k){
        case (9):
            return;
        case (1):
            loc000();
            break;
        case (2):
            loc020();
            break;
        case (5):
            loc110();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc012(){
    printf("00 01 02, Score: 00\n");
    printf("Even though the room is empty, you chuckled at the absurdity as you entered it.\n");
    scribble(3, 6);
    printmovement(10001);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (1):
            loc002();
            break;
        case(5):
            loc112();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc020(){
    printf("00 02 00, Score: 02\n");
    printf("Your skin burns as you waddled in the puddle in this room. However, you feel cleaner.\n");
    printmovement(11);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (1):
            loc010();
            break;
        case (2):
            loc030();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc030(){
    printf("00 03 00, Score: 00\n");
    printf("The heat from the deep blue tube lights doesn't seem that apparent in this room.\n");
    scribbles(8, 11, 3);
    printmovement(10001);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (1):
            loc020();
            break;
        case (5):
            loc130();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc100(){
    printf("01 00 00, Score: 04\n");
    printf("A large poster on the wall read 'No naked flames'. You wonder why there is a cow in the middle of the room.\n");
    scribble(16, 0);
    printmovement(110110);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (2):
            loc110();
            break;
        case (3):
            loc101();
            break;
        case (5):
            loc200();
            break;
        case (6):
            loc000();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc101(){
    printf("01 00 01, Score: 01\n");
    printf("Someone seemed to have spilled some almond powder in this room.\n");
    printmovement(101000);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (4):
            loc100();
            break;
        case (6):
            loc001();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc110(){
    printf("01 01 00, Score: 02\n");
    printf("Taxidermized animals line this room.\n");
    scribble(13, 0);
    printmovement(110001);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (1):
            loc100();
            break;
        case (5):
            loc210();
            break;
        case (6):
            loc010();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc112(){
    printf("01 01 02, Score: 04\n");
    printf("You contribute to the puddle of urine in the corner of this room.\n");
    scribble(17, 0);
    printmovement(100000);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (6):
            loc012();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc130(){
    printf("01 03 00, Score: 02\n");
    printf("Soft drinks erupt from holes in the wall.\n");
    printmovement(110000);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (5):
            loc230();
            break;
        case (6):
            loc030();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc200(){
    printf("02 00 00, Score: 04\n");
    printf("The sweet smell of rotting fruits permeates the room.\n");
    printmovement(110010);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (2):
            loc210();
            break;
        case (5):
            loc300();
            break;
        case (6):
            loc100();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc210(){
    printf("02 01 00, Score: 06\n");
    printf("You believe the deserted pub in this room has never been used, but your dizzy mind cannot be sure.\n");
    printmovement(100011);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (1):
            loc200();
            break;
        case (2):
            loc220();
            break;
        case (6):
            loc110();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc220(){
    printf("02 02 00, Score: 04\n");
    printf("A mildly sour smell lingers in the air. It smells like gyoza.\n");
    scribbled(1, 4, 19, 0);
    printmovement(111);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (1):
            loc210();
            break;
        case (2):
            loc230();
            break;
        case (3):
            loc221();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc221(){
    printf("02 02 01, Score: 05\n");
    printf("You sense microscopic creatures trying to thrive.\n");
    printmovement(1000);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (4):
            loc220();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc230(){
    printf("02 03 00, Score: 02\n");
    printf("You see a gradient of lard and starch on the ground; An arrow points towards the starch.\n");
    printmovement(110001);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (1):
            loc220();
            break;
        case (5):
            loc330();
            break;
        case (6):
            loc130();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc300(){
    printf("03 00 00, Score: 06\n");
    printf("You see pipes running out of the salt cavern room, as well as large gas canisters on the ground.\n");
    scribble(2, 0);
    printmovement(100010);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (2):
            loc310();
            break;
        case (6):
            loc200();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc310(){
    printf("03 01 00, Score: 06\n");
    printf("The paint on the drips down slowly, as if the walls are crying.\n");
    scribbles(0, 6, 1);
    printmovement(1);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (1):
            loc300();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

void loc330(){
    printf("03 03 00, Score: 08\n");
    printf("The room is packed with bottles of hair gel and vape juice.\n");
    scribble(18, 1);
    printmovement(100000);
    int k = scan();
    switch (k){
        case (9):
            return;
        case (6):
            loc230();
            break;
        default:
            printf("Invalid Choice\n");
    }
}

int main(){
    setvbuf(stdin, NULL, _IONBF,0);
    setvbuf(stdout, NULL, _IONBF,0);

    printf("After a long time of trying to will yourself, you are finally in the maze.\n");
    printf("You take a deep breath. The clue to the flag is in here somewhere.\n");
    printf("Non standard flag format.\n\n");
    loc000();
    printf("You close your eyes and will yourself back to your world.\n");
    printf("Goodbye, you're welcomed back again.\n");
    return 0;
}
