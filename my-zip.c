#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("my-zip: file1 [file2 ...]\n");
        return 1;
    }
    // Check all the files provided
    for (int i = 1; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (fp == NULL) {
            printf("my-zip: cannot open file\n");
            return 1;
        }

        int count = 0;
        int current = fgetc(fp);
        if (current == EOF) {
            fclose(fp);
            continue;
        }

        count = 1;
        int next;
        // Reads and writes all the characters one by one
        while ((next = fgetc(fp)) != EOF) {
            if (next == current) {
                count++;
            } else {
                fwrite(&count, sizeof(int), 1, stdout);
                fwrite(&current, sizeof(char), 1, stdout);
                current = next;
                count = 1;
            }
        }

        fwrite(&count, sizeof(int), 1, stdout);
        fwrite(&current, sizeof(char), 1, stdout);

        fclose(fp);
    }

    return 0;
}