#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linked_list.h"

int get_index(int x, int y, int width) {
    return y * width + x;
}

uchar get_lowest_notblack_value(uchar *array, int n) {
    // index of the lowest value
    // 255 should be the highest possible unsigned char
    int lowest = 255;
    int i;

    // from lowest to the end of array
    for (i = 0; i < n; i++) {
        printf("lowest fce: %d\n", array[i]);
        if (array[i] != 0){
            if (array[i] < lowest) {
                lowest = array[i];
            }
        }
    }

    printf("lowest: %d\n", array[lowest]);
    return lowest;
}

int is_all_black(uchar *array, int n) {
    int i;

    // if at least one pixel is not black return 0
    for (i = 0; i < n; i++) {
        if (array[i] > 0) {
            return 0;
        }
    }

    // if all pixels are black
    return 1;
}

uchar first_pixel_value(uchar *mask, int x, int y, int width) {
    int n = 2;
    uchar output;
    uchar *array = (uchar *) malloc(n * sizeof(uchar));

    // assign every neighboring pixel that we have to examine
    // up right
    array[0] = mask[get_index(x+1, y-1, width)];
    // up
    array[1] = mask[get_index(x, y-1, width)];

    // if all pixels are black
    if (is_all_black(array, n)) {
        output = 0;
    } else {
        output = get_lowest_notblack_value(array, n);
    }

    free(array);

    return output;
}

int middle_pixel_value(uchar *mask, int x, int y, int width) {
    int n = 4;
    int output;
    uchar *array = (uchar *) malloc(n * sizeof(uchar));

    // assign every neighboring pixel that we have to examine
    // left
    array[0] = mask[get_index(x-1, y, width)];
    // up left
    array[1] = mask[get_index(x-1, y-1, width)];
    // up
    array[2] = mask[get_index(x, y-1, width)];
    // up right
    array[3] = mask[get_index(x+1, y-1, width)];

    // if all pixels are black
    if (is_all_black(array, n)) {
        output = 0;
    } else {
        output = get_lowest_notblack_value(array, n);
    }

    free(array);

    return output;
}

int last_pixel_value(uchar *mask, int x, int y, int width) {
    int n = 3;
    uchar *array = (uchar *) malloc(n * sizeof(uchar));
    int output;

    // assign every neighboring pixel that we have to examine
    array[0] = mask[get_index(x-1, y, width)];
    array[1] = mask[get_index(x-1, y-1, width)];
    array[2] = mask[get_index(x, y-1, width)];

    // if all pixels are black
    if (is_all_black(array, n)) {
        output = 0;
    } else {
        output = get_lowest_notblack_value(array, n);
    }

    free(array);

    return output;
}

int main(int argc, char *argv[]) {
    FILE *file;
    char file_name[255];
    char magic_number[2];
    int width, height, max_value;
    int i, j, index;
    uchar pixel;
    uchar *pixels;
    uchar *mask;
    node n;
    int value;
    int label;
    node *head = NULL;

    strcpy(file_name, "..\\tests\\");
    strcat(file_name, argv[1]);

    file = fopen(file_name, "r");

    if (!file) {
        printf("File not found.");
        return EXIT_FAILURE;
    }

    fscanf(file, "%s", magic_number);

    fscanf(file, "%d %d", &width, &height);
    fscanf(file, "%d", &max_value);
    // reading new line symbol, so it does not end up in pixels array
    fscanf(file, "%c", &pixel);

    // basic info about pgm file
    printf("buff %s\nwidth %d\nheight %d\nmax value %d\n", magic_number, width, height, max_value);

    // assigns memory for pixels array and for mask array
    pixels = calloc(width * height, sizeof(uchar));
    mask = calloc(width * height, sizeof(uchar));

    index = 0;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            fscanf(file, "%c", &pixel);

            if (!((uchar) pixel == max_value || (uchar) pixel == 0)) {
                printf("Incorrect PGM format.");
                fclose(file);
                free(pixels);
                return EXIT_FAILURE;
            }

            pixels[index++] = (uchar) pixel;
        }
    }
    fclose(file);

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%*d", 3, pixels[get_index(j, i, width)] == 255 ? 1 : 0);
        }
        printf("\n");
    }

    value = 0;
    // first line of the mask
    // for the first pixel we only compare if it is white or black
    // if white we assign a new value, we ignore if black, because it stays 0
    // if pixel is not black
    if (pixels[0] != 0) {
        value++;
        mask[0] = value;
        add_node(&head, value);
    }

    // first line
    for (j = 1; j < width; j++) {
        if (pixels[j] != 0) {
            if (mask[j-1] == 0) {
                value++;
                mask[j] = value;
                add_node(&head, value);
            } else {
                mask[j] = mask[j-1];
            }
        }
    }

    // first line is done so we start on i = 1
    // i is y in the mask, and j is x in the mask
    for (i = 1; i < height; i++) {
        // for the first pixel in line we do not have to check left neighbor, because there is nothing
        if (pixels[get_index(0, i, width)] != 0) {
            label = first_pixel_value(mask, 0, i, width);
            if (label == 0) {
                value++;
                mask[get_index(0, i, width)] = value;
                add_node(&head, value);
            } else {
                mask[get_index(0, i, width)] = label;
            }
        }

        // middle pixels
        for (j = 1; j < width - 1; j++) {
            if (pixels[get_index(j, i, width)] != 0) {
                label = middle_pixel_value(mask, j, i, width);
                if (label == 0) {
                    value++;
                    mask[get_index(j, i, width)] = value;
                    add_node(&head, value);
                } else {
                    mask[get_index(j, i, width)] = label;
                }
            }
        }

        // last pixels
        if (pixels[get_index(width-1, i, width)] != 0) {
            label = last_pixel_value(mask, width-1, i, width);
            if (label == 0) {
                value++;
                mask[get_index(width-1, i, width)] = value;
                add_node(&head, value);
            } else {
                mask[get_index(width-1, i, width)] = label;
            }
        }
    }

    printf("Mask:\n");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%*d", 3, mask[get_index(j, i, width)]);
        }
        printf("\n");
    }

    free(pixels);
    free(mask);

    return EXIT_SUCCESS;
}