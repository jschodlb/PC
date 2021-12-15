#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAILURE 0
#define SUCCESS 1

int read_file(char *output[], char *file_name) {
    char prefix[] = "..\\tests\\";
    FILE *file;
    size_t size = 0;
    int i;

    if (!file_name || !output)
    {
        printf("Failure when reading from file.");
        return FAILURE;
    }

    strcat(prefix, file_name);
    printf("%s\n", prefix);
    file = fopen(prefix, "r");

    if (!file)
    {
        printf("Failure when opening file.");
        return FAILURE;
    }

    /* Get output size */
    fseek(file, 0L, SEEK_END); // goes to the end of file
    size = ftell(file); // how many bytes did it got through

    rewind(file); // go to the beginning of file

    output = calloc(1, (size+1) * sizeof(char)); // size + 1 for \0

    fread(output, size, 1, file); // reads 1 times sizes of byte from file into output

    output[size] = '\0';

    printf("%s\n", output);


    fclose(file);

    return SUCCESS;
}

int number_of_lines(char *file_name) {
    FILE *file;
    char prefix[] = "..\\tests\\";
    int lines = 0;
    char character;

    // Sanity check
    if (!file_name)
    {
        printf("Failure when reading from file.");
        return FAILURE;
    }

    strcat(prefix, file_name);
    printf("%s\n", prefix);
    file = fopen(prefix, "r");

    // Cycle until end of file is found
    while(!feof(file))
    {
        /* gets a character */
        character = fgetc(file);
        /* if a end of line is found, increment variable lines */
        if(character == '\n')
        {
            lines++;
        }
    }

    return lines;
}

int main(int argc, char *argv[]) {
    char *x[] = { 0 };
    // koment

    // read_file(x, argv[1]);

    printf("Number of lines: %d", number_of_lines(argv[1]));

    return EXIT_SUCCESS;
}