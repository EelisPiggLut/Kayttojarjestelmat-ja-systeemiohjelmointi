#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-unzip: file1 [file2 ...]\n");
        return 1;
    }
    // Checks all the files provided
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "rb");
        if (fp == NULL) {
            printf("my-unzip: cannot open file\n");
            return 1;
        }

        int count;
        char ch;
        while (fread(&count, sizeof(int), 1, fp) == 1 &&
               fread(&ch, sizeof(char), 1, fp) == 1) {
            for (int j = 0; j < count; j++) {
                printf("%c", ch);
            }
        }

        fclose(fp);
    }

    return 0;
}