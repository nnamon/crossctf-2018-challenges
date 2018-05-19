#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define gline()         while (getchar() != '\n')

struct notebook {
    long long entries;
    struct notebook *next;
};

struct notebook *notebook_list_head = NULL;

void greeter()
{
    printf("\e[31m");
    puts("      ______                             _   __          __       ");
    puts("     / ____/  ____ _   _____   __  __   / | / /  ____   / /_  ___ ");
    puts("    / __/    / __ `/  / ___/  / / / /  /  |/ /  / __ \\ / __/ / _ \\");
    puts("   / /___   / /_/ /  (__  )  / /_/ /  / /|  /  / /_/ // /_  /  __/");
    puts("  /_____/   \\__,_/  /____/   \\__, /  /_/ |_/   \\____/ \\__/  \\___/ ");
    puts("                            /____/                                ");
    puts("\e[0m");
    puts("               \e[3m~ A Modern Editor for a Modern You ~\e[0m");
    puts("");
}

char menu_choice()
{
    puts("0. Create notebook");
    puts("1. Delete notebook");
    puts("2. Read entry");
    puts("3. Edit entry");
    puts("9. Exit");
    printf("Choice: ");
    
    char choice = getchar();
    getchar();

    return choice;
}

void create_notebook()
{
    printf("Entries: ");

    long long n;
    if (1 != scanf(" %lld", &n))
        exit(1);
    getchar();

    if (n < 0)
        exit(1);

    struct notebook *new_book = malloc(n * sizeof(char *) + sizeof(struct notebook));

    if (!new_book)
        exit(1);

    struct notebook **curr = &notebook_list_head;
    for (; *curr; curr = &(*curr)->next);

    *curr = new_book;

    new_book->entries = n;
    new_book->next = NULL;

    memset((char *)new_book + sizeof(struct notebook), 0, n * sizeof(char *));
}

void delete_notebook()
{
    printf("Notebook index: ");

    unsigned long long n;
    if (1 != scanf(" %llu", &n))
        exit(1);
    getchar();

    struct notebook *curr = notebook_list_head;
    struct notebook *prev = NULL;
    unsigned long long count = 0;

    while (count < n)
    {
        if (!curr)
            exit(1);
        prev = curr;
        curr = curr->next;
        count++;
    }

    if (!curr)
        exit(1);

    if (!prev)
        notebook_list_head = curr->next;
    else
        prev->next = curr->next;

    free(curr);
}

void read_entry()
{
    printf("Notebook index: ");
    unsigned long long n;
    if (1 != scanf(" %llu", &n))
        exit(1);
    getchar();

    struct notebook *curr = notebook_list_head;
    unsigned long long count = 0;

    while (count < n)
    {
        if (!curr)
            exit(1);
        curr = curr->next;
        count++;
    }

    if (!curr)
        exit(1);

    printf("Entry index: ");
    long long en;
    if (1 != scanf(" %lld", &en) || en >= curr->entries)
        exit(1);
    getchar();

    char *s = *(char **)((char *)curr + sizeof(struct notebook) + en * sizeof(char *));

    if (!s)
        puts("Entry is empty.");
    else
        printf("%s\n", s);
}

void edit_entry()
{
    printf("Notebook index: ");
    unsigned long long n;
    if (1 != scanf(" %llu", &n))
        exit(1);
    getchar();

    struct notebook *curr = notebook_list_head;
    unsigned long long count = 0;

    while (count < n)
    {
        if (!curr)
            exit(1);
        curr = curr->next;
        count++;
    }

    if (!curr)
        exit(1);

    printf("Entry index: ");
    long long en;
    if (1 != scanf(" %lld", &en) || en >= curr->entries)
        exit(1);
    getchar();

    char **sptr = (char **)((char *)curr + sizeof(struct notebook) + en * sizeof(char *));

    if (!*sptr) {
        *sptr = malloc(256);
        if (!sptr)
            exit(1);
    }

    printf("Enter contents: ");

    if (!fgets(*sptr, 256, stdin))
        exit(1);

    char *c = strchr(*sptr, '\n');

    if (c)
        *c = '\0';
}

int main()
{
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    alarm(30);

    greeter();

    while (1)
    {
        char c = menu_choice();

        switch (c)
        {
            case '0':
                create_notebook();
                break;
            case '1':
                delete_notebook();
                break;
            case '2':
                read_entry();
                break;
            case '3':
                edit_entry();
                break;
            case '9':
                exit(0);
                break;
            default:
                break;
        }
    }

    return 0;
}
