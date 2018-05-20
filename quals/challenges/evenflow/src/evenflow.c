#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

size_t get_file_size(char * filename) {
    struct stat st;
    stat(filename, &st);
    return st.st_size;
}

int main(int argc, char ** argv) {
    FILE * fd = fopen("flag", "r");
    size_t file_size = get_file_size("flag");
    char * buffer = malloc(file_size);
    fread(buffer, 1, file_size, fd);
    return strcmp(buffer, argv[1]);
}
