#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(FILE *fp, const char *search_term) {
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, fp) != -1) {
        if (strstr(line, search_term) != NULL) {
            printf("%s", line); 
        }
    }

    free(line);
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-grep: searchterm [file ...]\n");
        return 1;
    }

    const char *search_term = argv[1];

    // Use stdin if only search term is given
    if (argc == 2) {
        return search(stdin, search_term);
    }

    // Expected case, read from file
    for (int i = 2; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("my-grep: cannot open file\n");
            return 1;
        }

        search(fp, search_term);
        fclose(fp);
    }

    return 0;
}