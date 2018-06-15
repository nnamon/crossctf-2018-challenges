#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define BUF_SIZE 1024
#define MOD (1 << 16)

uint32_t h(char *input, size_t len);
uint32_t f(uint32_t x);

uint32_t h(char *input, size_t len) {
    uint32_t res = 0;

    for(size_t i = 0; i < len; i++) {
        uint8_t c = input[i];
        res += c;
        res = f(res);
    }
    return res % MOD;
}

//LCG: f(x)
uint32_t f(uint32_t x) {
    return 0x43726f73 * x + 0x73435446;
}

void flag1(){
	FILE *f = fopen("flag1", "r");
	char flag[48];

	if (f == NULL){
		puts("Couldn't open flag file.");
		exit(1);
	}

	if ((fgets(flag, 48, f)) == NULL){
		puts("Couldn't read flag file.");
		exit(1);
	};

	puts(flag);
	fclose(f); 
}

void flag2(){
    FILE *f = fopen("flag2", "r");
    char flag[48];

    if (f == NULL){
        puts("Couldn't open flag file.");
        exit(1);
    }

    if ((fgets(flag, 48, f)) == NULL){
        puts("Couldn't read flag file.");
        exit(1);
    };

    puts(flag);
    fclose(f); 
}


void flag3(){
    FILE *f = fopen("flag3", "r");
    char flag[48];

    if (f == NULL){
        puts("Couldn't open flag file.");
        exit(1);
    }

    if ((fgets(flag, 48, f)) == NULL){
        puts("Couldn't read flag file.");
        exit(1);
    };

    puts(flag);
    fclose(f); 
}

//reverse and collide LCG hash 
bool rochefort6(){
    char buf[BUF_SIZE];

    //randomly generate number
    srand(time(NULL));
    uint32_t r = rand() % MOD;

    puts("Bet you can't produce the same output :P");
    printf("%d\n", r);
    
    puts("Your turn: ");
    //probably will change to allow buffer overflow
    if(fgets(buf, BUF_SIZE, stdin) != NULL) {
        buf[BUF_SIZE - 1] = '\0';

        uint32_t ans = h(buf, strlen(buf));
        printf("Your output is %d\n", ans);

        if(ans == r) {
            flag1();
            return true;
        } else {
            puts("FAIL");
            exit(2);
        }
    } else {
        puts("Couldn't read your input.");
        exit(1);
    }
}

//crazy struct reversing
uint32_t rochefort8(){
    return 0;
}


//bad character shellcoding
uint32_t rochefort10(){
    return 0;
}

uint32_t westvleteren12(){
    puts("But wait... there's one more level! I wonder how you get to it...");
}

int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    rochefort6();
    rochefort8();
    rochefort10();
    westvleteren12();

    return 0;
}
