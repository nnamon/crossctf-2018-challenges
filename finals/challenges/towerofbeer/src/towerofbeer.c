#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/ptrace.h>
#include <limits.h>

#define BUF_SIZE 1024
#define MOD (1 << 16)

uint32_t h(char *input, size_t len);
uint32_t f(uint32_t x);
void read_12_numbers(long* arr);
void rochefort6();
void rochefort8();
void rochefort10();
void westvleteren12();
void flag1();
void flag2();
void flag3();

void read_10_numbers(long* arr){
    size_t num_read = scanf("%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", 
        arr, arr+1, arr+2, arr+3, arr+4, arr+5, arr+6, arr+7, arr+8, arr+9);
    if (num_read < 10) {
        puts("FAIL");
        exit(1);
    }
}

#pragma GCC push_options
#pragma GCC optimize ("O3")

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


//reverse and collide LCG hash 
void rochefort6(){
    char buf[BUF_SIZE];
    uint32_t r;
    //randomly generate number
    srand(time(NULL));
    for(size_t i = 0; i < 20; i++){
        r = rand() % MOD;

        puts("Bet you can't produce the same output :P");
        printf("%d\n", r);
        
        puts("Your turn: ");
        if(fgets(buf, BUF_SIZE, stdin) != NULL) {
            uint32_t ans = h(buf, strlen(buf));
            printf("Your output is %d\n", ans);

            if(ans == r) {
                //do nothing
            } else {
                puts("FAIL");
                exit(2);
            }
        } else {
            puts("Couldn't read your input.");
            exit(1);
        }
    }
    flag1();

}

#pragma GCC pop_options

void flag1(){
	FILE *f = fopen("/home/towerofbeeruser/flag1", "r");
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
    FILE *f = fopen("/home/towerofbeeruser/flag2", "r");
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

typedef union Data {
    long v;
    char* p;
} data;

typedef struct Node {
    int type;
    data d1; // 1:v1, 2:v2, 3:p1, 4:p2, 5:v1, 6:v2
    data d2; // 1:v2, 2:p1, 3:p2, 4:v1, 5:p1, 6:p2
    data d3; // 1:p1, 2:p2, 3:v1, 4:v2, 5:p2, 6:p1
    data d4; // 1:p2, 2:v1, 3:v2, 4:p1, 5:v2, 6:v1
} node;

node* get_left_ptr(node* n) {
    if(n == NULL) return NULL;
    int type = n->type;
    switch(type){
        case 1:
            return (node*) n->d3.p; 
        case 2:
            return (node*) n->d2.p;
        case 3:
            return (node*) n->d1.p;
        case 4:
            return (node*) n->d4.p;
        case 5:
            return (node*) n->d2.p;
        case 6:
            return (node*) n->d3.p;
        default:
            return NULL;
    }
}

node* get_right_ptr(node* n) {
    if(n == NULL) return NULL;
    int type = n->type;
    switch(type){
        case 1:
            return (node*) n->d4.p; 
        case 2:
            return (node*) n->d3.p;
        case 3:
            return (node*) n->d2.p;
        case 4:
            return (node*) n->d1.p;
        case 5:
            return (node*) n->d3.p;
        case 6:
            return (node*) n->d2.p;
        default:
            return NULL;
    }
}

long get_first_value(node* n) { 
    if(n == NULL) return 0;
    int type = n->type;
    switch(type){
        case 1:
            return n->d1.v; 
        case 2:
            return n->d4.v;
        case 3:
            return n->d3.v;
        case 4:
            return n->d2.v;
        case 5:
            return n->d1.v;
        case 6:
            return n->d4.v;
        default:
            return 0;
    }
}

long get_second_value(node* n) { 
    if(n == NULL) return 0;
    int type = n->type;
    switch(type){
        case 1:
            return n->d2.v; 
        case 2:
            return n->d1.v;
        case 3:
            return n->d4.v;
        case 4:
            return n->d3.v;
        case 5:
            return n->d4.v;
        case 6:
            return n->d1.v;
        default:
            return 0;
    }
}


bool check_node(node* curr, node* to_traverse, long val1, long val2, bool left) {
    //check first val first
    long curr_val_1 = get_first_value(curr);
    long tra_val_1 = get_first_value(to_traverse);
    node* nleft_ptr;
    node* nright_ptr;
    
    if(left) {
        //all items to the left subtree are strictly less than current node
        if(curr_val_1 <= val1) return false;
    } else {
        //all items to the right subtree are strictly more than current node
        if(curr_val_1 >= val1) return false;
    }

    //don't allow duplicates traversal values
    if(val1 == tra_val_1) {
        return false;
    }
    nleft_ptr = get_left_ptr(to_traverse);
    nright_ptr = get_right_ptr(to_traverse);

    if(nleft_ptr != NULL) {
        long left_val = get_first_value(nleft_ptr);
        if(left_val >= val1) return false;
    }

    if(nright_ptr != NULL) {
        long right_val = get_first_value(nright_ptr);
        if(right_val <= val1) return false;
    }

    //do the same for the second val
    long curr_val_2 = get_second_value(curr);
    long tra_val_2 = get_second_value(to_traverse);
    
    if(left) {
        //all items to the left subtree are strictly less than current node
        if(curr_val_2 <= val2) return false;
    } else {
        //all items to the right subtree are strictly more than current node
        if(curr_val_2 >= val2) return false;
    }

    //don't allow duplicates traversal values
    if(val2 == tra_val_2) {
        return false;
    }

    if(nleft_ptr != NULL) {
        long left_val = get_second_value(nleft_ptr);
        if(left_val >= val2) return false;
    }

    if(nright_ptr != NULL) {
        long right_val = get_second_value(nright_ptr);
        if(right_val <= val2) return false;
    }

    return true;
}

void check(node* head, long* inputs, size_t* checked) {
    node* left_ptr;
    node* right_ptr;
    left_ptr = get_left_ptr(head);
    right_ptr = get_right_ptr(head);

    if(left_ptr != NULL) {
        bool correct = check_node(head, left_ptr, inputs[*checked], inputs[*checked + 5], true);
        if(correct) {
            *checked = *checked + 1;    
        }
        check(left_ptr, inputs, checked);
    }

    if(right_ptr != NULL) {
        bool correct = check_node(head, right_ptr, inputs[*checked], inputs[*checked + 5], false);
        if(correct) {
            *checked = *checked + 1;
        }
        check(right_ptr, inputs, checked);
    }

}

//crazy struct reversing
void rochefort8(){
    if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) {
        puts("Something bad happened!");
        exit(1);
    }

    // make structs
    node nodes[6];

    printf("This address may be interesting...\n0x%lx\n", (long) &nodes);

    // assign types
    nodes[0].type = 3;
    nodes[1].type = 5;
    nodes[2].type = 1;
    nodes[3].type = 6;
    nodes[4].type = 2;
    nodes[5].type = 4;

    //type 3 done
    nodes[0].d1.p = &nodes[1];
    nodes[0].d2.p = &nodes[2];
    nodes[0].d3.v = 0;
    nodes[0].d4.v = &nodes[1];
 
    //type 5 done
    nodes[1].d1.v = -3;
    nodes[1].d2.p = &nodes[3];
    nodes[1].d3.p = &nodes[4];
    nodes[1].d4.v = (long)&nodes[0] - sizeof(node); 

    //type 1 done
    nodes[2].d1.v = LONG_MAX;
    nodes[2].d2.v = &nodes[4];
    nodes[2].d3.p = &nodes[5];
    nodes[2].d4.p = 0; 

    //type 6 done
    nodes[3].d1.v = nodes[1].d4.v - 8;
    nodes[3].d2.p = 0;
    nodes[3].d3.p = 0;
    nodes[3].d4.v = -0xcafebabeL; 
    
    //type 2
    nodes[4].d1.v = (long)&nodes[0] - 8;
    nodes[4].d2.p = 0;
    nodes[4].d3.p = 0;
    nodes[4].d4.v = -1;  
    
    //type 4
    nodes[5].d1.p = 0;
    nodes[5].d2.v = ~nodes[4].d4.v + 1;
    nodes[5].d3.v = &nodes[3];
    nodes[5].d4.p = 0; 
    
    puts("Now let's see if you can read my mind. Give me 10 numbers!");
    long inputs[10];
    read_10_numbers(inputs);
    
    // compare against target implementation
    //ties are not allowed
    size_t checked = 0;
    check(nodes, inputs, &checked);
    
    if (checked == 5) {
        // print flag if it succeeds
        flag2();
    } else {
        puts("FAIL");
        exit(1);
    } 
}


int main() {
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    puts("Welcome to the Tower of Beer!");
    puts("6: Rochefort 6");
    puts("8: Rochefort 8");
    puts("Tell me which beer you would like:");
    puts("Or send any number to have both ;)");

    int choice = 0;

    char buf[BUF_SIZE];
    fgets(buf, BUF_SIZE, stdin);

    sscanf(buf, "%d", &choice);


    switch(choice) {
        case 6:
            rochefort6();
            break;
        case 8:
            rochefort8();
            break;
        default:
            rochefort6();
            rochefort8();
            break;
    }
    return 0;
}
