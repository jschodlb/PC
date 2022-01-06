#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "linked_list.h"
#include "colour_linked_list.h"

int get_index(int x, int y, int width) {
    return y * width + x;
}

int get_lowest_not_black_value(const int *array, int n) {
    // index of the lowest value
    int lowest = INT_MAX;
    int i;

    /* Sanity check */
    if (!array) {
        printf("Sanity check failed in get_lowest_not_black_value.\n");
        return FAILURE;
    }

    /* getting lowest value in the array except of 0 */
    for (i = 0; i < n; i++) {
        if (array[i] != 0){
            if (array[i] < lowest) {
                lowest = array[i];
            }
        }
    }

    return lowest;
}

int get_highest(int *array, int n) {
    int highest;
    int i;

    if (!array) {
        printf("Sanity check failed in get_highest.\n");
        return FAILURE;
    }

    highest = array[0];

    for (i = 1; i < n; i++) {
        if (array[i] > highest) {
            highest = array[i];
        }
    }

    return highest;
}

int is_all_black(int *array, int n) {
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

int first_pixel_value(int *mask, int x, int y, int width, node **head, int *value) {
    int n = 2;
    int output;
    int *array = (int *) malloc(n * sizeof(int));

    // assign every neighboring pixel that we have to examine
    // up right
    array[0] = mask[get_index(x+1, y-1, width)];
    // up
    array[1] = mask[get_index(x, y-1, width)];

    // if all pixels are black
    if (is_all_black(array, n)) {
        output = 0;
    } else {
        output = get_lowest_not_black_value(array, n);
    }

    if (output == 0) {
        add_node(head, value);
        mask[get_index(x, y, width)] = *value;
    } else {
        mask[get_index(x, y, width)] = output;
        add_equivalence(get_node(*head, output), get_node(*head, get_highest(array, n)));
    }

    free(array);

    return output;
}

int middle_pixel_value(int *mask, int x, int y, int width, node **head, int *value) {
    int n = 4;
    int output;
    int *array;

    /* Sanity check */
    if (!mask || !head || !value) {
        printf("Sanity check failed in middle_pixel_value.\n");
        return FAILURE;
    }

    array = (int *) malloc(n * sizeof(int));

    if (!array) {
        printf("Malloc failed in middle_pixel_value.\n");
        return FAILURE;
    }


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
        output = get_lowest_not_black_value(array, n);
    }

    if (output == 0) {
        add_node(head, value);
        mask[get_index(x, y, width)] = *value;
    } else {
        mask[get_index(x, y, width)] = output;
        add_equivalence(get_node(*head, output), get_node(*head, get_highest(array, n)));
    }

    free(array);

    return SUCCESS;
}

int last_pixel_value(int *mask, int x, int y, int width, node **head, int *value) {
    int n = 3;
    int output;
    int *array = (int *) malloc(n * sizeof(int));

    // assign every neighboring pixel that we have to examine
    array[0] = mask[get_index(x-1, y, width)];
    array[1] = mask[get_index(x-1, y-1, width)];
    array[2] = mask[get_index(x, y-1, width)];

    // if all pixels are black
    if (is_all_black(array, n)) {
        output = 0;
    } else {
        output = get_lowest_not_black_value(array, n);
    }

    if (output == 0) {
        add_node(head, value);
        mask[get_index(x, y, width)] = *value;
    } else {
        mask[get_index(x, y, width)] = output;
        add_equivalence(get_node(*head, output), get_node(*head, get_highest(array, n)));
    }

    free(array);

    return output;
}

int fix_mask(int *mask, node *head, int width, int height) {
    int i;
    int j;

    /* Sanity check */
    if (!mask) {
        printf("Failed sanity check for mask in fix_mask.\n");
        return 0;
    }

    if (!head) {
        printf("Failed sanity check for head in fix_mask.\n");
        return 0;
    }

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (mask[get_index(j, i, width)]) {
                mask[get_index(j, i, width)] = get_equivalence(get_node(head, mask[get_index(j, i, width)]));
            }
        }
    }

    return SUCCESS;
}

int paint_mask(int *mask, int width, int height, colour_node *head) {
    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (mask[get_index(j, i, width)] != 0) {
                mask[get_index(j, i, width)] = get_colour(head, mask[get_index(j, i, width)]);
            }
        }
    }
}

int paint(int *mask, int width, int height, node *head) {
    colour_node *colours;
    node *walk;
    int num_of_colours = 0;

    /* Sanity check */
    if (!mask || !head) {
        printf("Sanity check failed in pain_mask.\n");
        return FAILURE;
    }

    colours = NULL;

    walk = head;
    while (walk) {
        if (walk->value == get_equivalence(walk)) {
            num_of_colours++;
            add_colour_node(&colours, walk->value);
        }
        walk = walk->next;
    }

    set_colours(colours, num_of_colours);

    paint_mask(mask, width, height, colours);

    print_colour_list(colours);

    free(colours);

    return SUCCESS;
}

int main(int argc, char *argv[]) {
    FILE *file;
    char file_name[255];
    char magic_number[3];
    int width, height, max_value;
    int i, j, index;
    uchar pixel;
    uchar *pixels;
    int *mask;
    int *value;
    node *head = NULL;

    value = (int *) malloc(sizeof(int));

    /* sanity check */
    if (!value) {
        printf("Malloc for uchar failed.\n");
        return EXIT_FAILURE;
    }

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
    pixels = (uchar *) calloc(width * height, sizeof(uchar));
    mask = (int *) calloc(width * height, sizeof(int));

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

    *value = 0;
    // for the first pixel we only compare if it is white or black
    // if white we assign a new value, we ignore if black, because it stays 0
    // if pixel is not black
    if (pixels[0] > 0) {
        add_node(&head, value);
        mask[0] = *value;
    } else {
        mask[0] = 0;
    }

    // first line
    for (j = 1; j < width; j++) {
        if (pixels[j] != 0) {
            if (mask[j-1] == 0) {
                add_node(&head, value);
                mask[j] = *value;
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
            first_pixel_value(mask, 0, i, width, &head, value);
        }

        // middle pixels
        for (j = 1; j < width - 1; j++) {
            if (pixels[get_index(j, i, width)] != 0) {
                middle_pixel_value(mask, j, i, width, &head, value);
            }
        }

        // last pixels
        if (pixels[get_index(width-1, i, width)] != 0) {
            last_pixel_value(mask, width-1, i, width, &head, value);
        }
    }

    /*
    printf("\nMask after first walk-through:\n");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            printf("%*d", 3, mask[get_index(j, i, width)]);
        }
        printf("\n");
    }
    */

    fix_mask(mask, head, width, height);
    printf("Value = %d\n", *value);
    //print_list(head);


    printf("\nMask after second walk-through:\n");
    /*
    for (i = 0; i < 50; i++) {
        for (j = 85; j < 124; j++) {
            printf("%*d", 3, mask[get_index(j, i, width)]);
        }
        printf("\n");
    }
     */



    strcpy(file_name, "..\\tests\\");
    strcat(file_name, argv[2]);
    file = fopen(file_name, "w+");

    if (!file) {
        printf("Could not open file to write in it.\n");
        return EXIT_FAILURE;
    }

    paint(mask, width, height, head);

    fprintf(file, "%s\r", magic_number);
    fprintf(file, "%u %u\r", width, height);
    fprintf(file, "%u\r", max_value);

    printf("\nMask after paint walk-through:\n");
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            fprintf(file, "%c", mask[get_index(j, i, width)]);
        }
    }

    /*
    for (i = 6; i < 79; i++) {
        for (j = 85; j < 124; j++) {
            printf("%*d", 3, mask[get_index(j, i, width)]);
        }
        printf("\n");
    }
     */

    fclose(file);

    free(pixels);
    free(mask);
    free(value);
    free_list(head);

    return EXIT_SUCCESS;
}