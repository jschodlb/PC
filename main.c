#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "error.h"
#include "ccl.h"

#define PGM_SUFFIX ".pgm"
#define SUFFIX_SIZE 5

#define INPUT_FILE_NAME_INDEX 1
#define OUTPUT_FILE_NAME_INDEX 2

#define MAGIC_NUMBER_SIZE 3

/* ____________________________________________________________________________

    Global Variables
   ____________________________________________________________________________
*/
FILE *file = NULL; /* input and output file handle */
uchar *pixels; /* input pgm image */

/**
 * Checks if file name has a .pgm suffix
 *
 * @param file_name name of the file
 * @return SUCCESS if there is a .pgm suffix, FAILURE if not
 */
int check_pgm_suffix(char *file_name) {
    char *dot;

    /* Sanity check */
    if (!file_name) {
        sanity_check("check_pgm_suffix");
        return FAILURE;
    }

    dot = strrchr(file_name, '.'); /* finds the right most dot */
    if (dot && !strcmp(dot, PGM_SUFFIX)) { /* finds out if there is pgm, after the right most dot */
        return SUCCESS;
    }

    return FAILURE;
}

/**
 * Adds .pgm suffix at the end of file_name
 *
 * @param file_name name of the file
 * @return SUCCESS if the suffix was added successfully, FAILURE if not
 */
int add_pgm_suffix(char *file_name) {
    char suffix[SUFFIX_SIZE];

    /* Sanity check */
    if (!file_name) {
        sanity_check("add_pgm_suffix");
        return FAILURE;
    }

    strcpy(suffix, PGM_SUFFIX); /* copies .pgm suffix into suffix variable */
    strcat(file_name, suffix); /* adds suffix at the end of file_name */

    return SUCCESS;
}

/**
 * Reads data from file
 *
 * @param magic_number magic number from the file (P5)
 */
void read_from_file(char *magic_number, int *width, int *height, int *max_value) {
    uchar pixel;
    int index;
    int i, j;

    /* read basic information */
    fscanf(file, "%s", magic_number); /* reads magic number (P5) */
    fscanf(file, "%d %d %d", width, height, max_value);
    fscanf(file, "%c", &pixel); /* reads new line character */

    pixels = (uchar *) calloc((*width) * (*height), sizeof(uchar)); /* assigns memory for pixels array */

    if (!pixels) {
        malloc_fail("read_from_file");
        exit(EXIT_FAILURE);
    }

    /* reads pixels from file into a pixels array and checks if it is only black and white */
    index = FIRST_INDEX;
    for (i = CYCLE_START; i < *height; i++) {
        for (j = CYCLE_START; j < *width; j++) {
            fscanf(file, "%c", &pixel);

            if (!((uchar) pixel == *max_value || (uchar) pixel == BLACK)) {
                printf("Incorrect PGM format.\n");
                fclose(file);
                free(pixels);
                exit(EXIT_FAILURE);
            }

            pixels[index++] = (uchar) pixel;
        }
    }

    fclose(file);
}

/**
 * Handles input from file.
 * @param argc number of arguments
 * @param argv arguments
 */
void load_file(int argc, char *argv[]) {
    char *file_name;

    if (argc != 3) {
        printf("File name not entered.\n");
        exit(EXIT_FAILURE);
    }

    file_name = (char *) malloc(sizeof(char) * (strlen(argv[INPUT_FILE_NAME_INDEX]) + SUFFIX_SIZE));
    strcpy(file_name, argv[INPUT_FILE_NAME_INDEX]); /* copies name of the file from argument to file_name */

    if (!check_pgm_suffix(file_name)) { /* checks for .pgm suffix */
        add_pgm_suffix(file_name); /* adds .pgm suffix */
    }

    file = fopen(file_name, "r"); /* opens file for reading */

    if (!file) {
        printf("Could not open file\n");
        exit(EXIT_FAILURE);
    }

    free(file_name);
}

/**
 * Writes into a file
 *
 * @param argv contains name of the file
 * @param mask data written into the file
 * @param magic_number magic number (eg. P5) written into the file
 * @param width width of the file
 * @param height height of the file
 * @param max_value max value of colours (eg. 255)
 */
void write_into_file(char *argv[], int *mask, char *magic_number, int width, int height, int max_value) {
    char *file_name;
    int i;

    file_name = (char *) malloc(sizeof(char) * (strlen(argv[OUTPUT_FILE_NAME_INDEX]) + SUFFIX_SIZE));
    strcpy(file_name, argv[OUTPUT_FILE_NAME_INDEX]); /* copies name of the file from argument to file_name */

    if (!check_pgm_suffix(file_name)) { /* checks for .pgm suffix */
        add_pgm_suffix(file_name); /* adds .pgm suffix */
    }

    /* opens file */
    file = fopen(file_name, "w");
    if (!file) {
        printf("Could not open file to write in it.\n");
        exit(EXIT_FAILURE);
    }

    /* writes information about the file */
    fprintf(file, "%s\r", magic_number);
    fprintf(file, "%u %u\r", width, height);
    fprintf(file, "%u\r", max_value);

    /* writes data into the file */
    for (i = CYCLE_START; i < width * height; i++) {
            fprintf(file, "%c", (uchar) mask[i]);
    }

    fclose(file);
}

/**
 * Main function.
 */
int main(int argc, char *argv[]) {
    char magic_number[MAGIC_NUMBER_SIZE];
    int *mask = NULL;
    int width, height;
    int max_value; /* max value of a pixel */

    clock_t end;
    clock_t begin = clock();

    printf("Reading from file...\n");
    load_file(argc, argv);
    read_from_file(magic_number, &width, &height, &max_value);

    printf("Running CCL algorithm...\n");
    run(&mask, pixels, width, height, max_value);

    printf("Writing into file...\n");
    write_into_file(argv, mask, magic_number, width, height, max_value);
    printf("Everything is done.\n");

    free(pixels);
    free(mask);

    end = clock();
    printf("Time elapsed: %.3f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);

    return EXIT_SUCCESS;
}