#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // If statement to check correct input
    if (argc == 1) {
        return 0;
    }

    // Checks all the files provided in the command line
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("my-cat: cannot open file\n");
            return 1;
        }

        char buffer[4096];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) {
            printf("%s", buffer); 
        }

        fclose(fp);
    }

    return 0;
}