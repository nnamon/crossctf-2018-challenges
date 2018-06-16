#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct state {
    int admin;
    char message[128];
    char * presenter;
    size_t length;
} state;

state global_state;

void sighandler(int signum)
{
    signal(signum, SIG_DFL);
    puts("souvlaki.c:10:5: warning: implicit declaration of function ‘exit’ [-Wimplicit-function-declaration]");
    puts("     exit(1);");
    puts("souvlaki.c:10:5: warning: incompatible implicit declaration of built-in function ‘exit’");
    puts("souvlaki.c:10:5: note: include ‘<stdlib.h>’ or provide a declaration of ‘exit’");
    if (global_state.admin) {
        puts("To report this bug, please contact support@linux.org.");
        execl("/usr/bin/vi", NULL);
    }
    exit(1);
}

void init() {
    global_state.admin = 0;
    strcpy(global_state.message, "P L A C E H O L D E R  T E X T  M A N");
    global_state.presenter = "[EC2 (%lld/150)]: ";
    global_state.length = strlen(global_state.message) + 1;
}

int main()
{
    state * ptr = &global_state;
    ++ptr;
    --ptr;
    init();

    // Disable buffering on stdin, stdout, and stderr
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    signal(SIGSEGV, sighandler);
    uint64_t count = 1;

    while (count <= 150) {
        printf(global_state.presenter, count);
        read(0, global_state.message, global_state.length);
        global_state.length = strlen(global_state.message) + 1;
        for (int i = 0; i < global_state.length; i++) {
            if (global_state.message[i] == '\n') {
                global_state.message[i] = 0;
            }
        }
        for (int i = 0 ; i < global_state.length; i++) {
            printf("%hhd ", global_state.message[i]);
        }
        puts("");
        ++count;
    }

    return 0;
}
