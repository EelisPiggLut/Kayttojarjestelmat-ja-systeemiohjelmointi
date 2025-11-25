#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 50

void print_error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// Read a line from the given file
char *read_line(FILE *fp) {
    size_t size = 50;
    size_t len = 0;
    char *buffer = malloc(size);
    if (!buffer) print_error("malloc failed");
    
    // Reallocating the size if the input is long
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            char *new_buffer = realloc(buffer, size);
            if (!new_buffer) {
                free(buffer);
                print_error("malloc failed");
            }
            buffer = new_buffer;
        }
        buffer[len++] = ch;
        if (ch == '\n') break;
    }

    if (len == 0 && ch == EOF) {
        free(buffer);
        return NULL;
    }

    buffer[len] = '\0';
    return buffer;
}

// Read all lines from the file and store them in array
char **read_lines(FILE *fp, int *count) {
    int capacity = INITIAL_CAPACITY;
    int size = 0;
    char **lines = malloc(capacity * sizeof(char *));
    if (!lines) print_error("malloc failed");
    
    //reallocating the size if the input is long
    char *line;
    while ((line = read_line(fp)) != NULL) {
        if (size >= capacity) {
            capacity *= 2;
            char **new_lines = realloc(lines, capacity * sizeof(char *));
            if (!new_lines) {
                free(line);
                for (int i = 0; i < size; i++) free(lines[i]);
                free(lines);
                print_error("malloc failed");
            }
            lines = new_lines;
        }
        lines[size++] = line;
    }

    *count = size;
    return lines;
}

// Write lines in reverse order to output file
void write_lines(FILE *fp, char **lines, int count) {
    for (int i = count - 1; i >= 0; i--) {
        fputs(lines[i], fp);
    }
}

// Error checks, for different cases
int main(int argc, char *argv[]) {
    FILE *input = stdin;
    FILE *output = stdout;

    if (argc > 3) {
        print_error("usage: reverse <input> <output>");
    }

    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (!input) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }

    if (argc == 3) {
        if (strcmp(argv[1], argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }
        output = fopen(argv[2], "w");
        if (!output) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
    }

    // Read lines from input and write them in reverse to output
    int count;
    char **lines = read_lines(input, &count);
    write_lines(output, lines, count);

    for (int i = 0; i < count; i++) {
        free(lines[i]);
    }
    free(lines);

    if (input != stdin) fclose(input);
    if (output != stdout) fclose(output);

    return 0;
}