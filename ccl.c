#include <stdio.h>
#include <stdlib.h>

#include "ccl.h"
#include "error.h"
#include "linked_list.h"
#include "colour_linked_list.h"

/* ____________________________________________________________________________

    Global Variables
   ____________________________________________________________________________
*/
int width, height; /* dimensions the files */

/**
 * Gets index of 2D array format into 1D format
 *
 * @param x x-coordinate
 * @param y y-coordinate
 * @return 1D index
 */
int get_index(int x, int y) {
    return y * width + x;
}

/* ____________________________________________________________________________

    first walk through functions
   ____________________________________________________________________________
*/
/**
 * Gets lowest not black value from surrounding pixels
 *
 * @param array array of surrounding pixels
 * @param n size of array
 * @return lowest value from surrounding pixels
 */
int get_lowest_not_black_value(const int *array, int n) {
    int lowest;
    int i;

    /* Sanity check */
    if (!array) {
        sanity_check("get_lowest_not_black_value");
        exit(0);
    }

    /* get first not black value */
    for (i = 0; i < n; i++) {
        if (array[i] != 0) {
            lowest = array[i];
            break;
        }
    }

    /* getting lowest value in the array except of 0 */
    for (; i < n; i++) {
        if (array[i] != 0){
            if (array[i] < lowest) {
                lowest = array[i];
            }
        }
    }

    return lowest;
}

/**
 * Gets highest value from surrounding pixels. Used for equivalence
 *
 * @param array surrounding pixels
 * @param n size of array
 * @return highest value from surrounding pixels
 */
int get_highest(const int *array, int n) {
    int highest;
    int i;

    /* Sanity check */
    if (!array) {
        sanity_check("get_highest");
        exit(0);
    }

    /* getting highest value */
    highest = array[0];
    for (i = 1; i < n; i++) {
        if (array[i] > highest) {
            highest = array[i];
        }
    }

    return highest;
}

/**
 * Checks if surrounding pixels are all black.
 *
 * @param array surrounding pixels
 * @param n size of array
 * @return SUCCESS if all pixels are black, FAILURE otherwise
 */
int is_all_black(const int *array, int n) {
    int i;

    /* Sanity check */
    if (!array) {
        sanity_check("is_all_black");
        exit(0);
    }

    /* if at least one pixel is not black return 0 */
    for (i = 0; i < n; i++) {
        if (array[i] > 0) {
            return FAILURE;
        }
    }

    /* if all pixels are black */
    return SUCCESS;
}

/**
 * Gets label of the first column pixels and adds equivalence
 *
 * @param x x-coordinate
 * @param y y-coordinate
 * @param head head reference of linked list of values and equivalencies
 * @param value value of the next added value
 * @param mask array of labels
 */
void first_pixel_value(int x, int y, node **head, int *value, int *mask) {
    int n = 2;
    int output;
    int *array;
    int highest;

    /* Sanity check */
    if (!mask || !head || !value) {
        sanity_check("first_pixel_value");
        exit(0);
    }

    array = (int *) malloc(n * sizeof(int));

    if (!array) {
        printf("Malloc failed in first_pixel_value.\n");
        exit(0);
    }

    /* assign every neighboring pixel that has to be examined */
    /* above to the right */
    array[0] = mask[get_index(x+1, y-1)];
    /* straight above */
    array[1] = mask[get_index(x, y-1)];

    /* if all pixels are black */
    if (is_all_black(array, n)) {
        output = 0;
    } else {
        output = get_lowest_not_black_value(array, n);
    }

    /* if all pixels are black add node */
    if (output == 0) {
        add_node(head, value);
        mask[get_index(x, y)] = *value;
    }
    /* if surrounding pixels can be equivalent, add the equivalence */
    else {
        mask[get_index(x, y)] = output;
        highest = get_highest(array, n);
        if (highest != output) {
            add_equivalence(get_node(*head, output), get_node(*head, highest));
        }
    }

    free(array);
}

/**
 * Gets label of the middle column pixels and adds equivalence
 *
 * @param x x-coordinate
 * @param y y-coordinate
 * @param head head reference of linked list of values and equivalencies
 * @param value value of the next added value
 * @param mask array of labels
 */
void middle_pixel_value(int x, int y, node **head, int *value, int *mask) {
    int n = 4;
    int output;
    int *array;
    int highest;

    /* Sanity check */
    if (!mask || !head || !value) {
        sanity_check("middle_pixel_value");
        exit(0);
    }

    array = (int *) malloc(n * sizeof(int));

    if (!array) {
        printf("Malloc failed in middle_pixel_value.\n");
        exit(0);
    }


    /* assign every neighboring pixel that has to be examined */
    /* to the left */
    array[0] = mask[get_index(x-1, y)];
    /* above to the left */
    array[1] = mask[get_index(x-1, y-1)];
    /* straight above */
    array[2] = mask[get_index(x, y-1)];
    /* above to the right */
    array[3] = mask[get_index(x+1, y-1)];

    /* if all pixels are black */
    if (is_all_black(array, n)) {
        output = 0;
    } else {
        output = get_lowest_not_black_value(array, n);
    }

    /* if all pixels are black add node */
    if (output == 0) {
        add_node(head, value);
        mask[get_index(x, y)] = *value;
    }
    /* if surrounding pixels can be equivalent, add the equivalence */
    else {
        mask[get_index(x, y)] = output;
        highest = get_highest(array, n);
        if (highest != output) {
            add_equivalence(get_node(*head, output), get_node(*head, highest));
        }
    }

    free(array);
}

/**
 * Gets label of the last column pixels and adds equivalence
 *
 * @param x x-coordinate
 * @param y y-coordinate
 * @param head head reference of linked list of values and equivalencies
 * @param value value of the next added value
 * @param mask array of labels
 */
void last_pixel_value(int x, int y, node **head, int *value, int *mask) {
    int n = 3;
    int output;
    int *array;
    int highest;

    /* Sanity check */
    if (!mask || !head || !value) {
        sanity_check("last_pixel_value");
        exit(0);
    }

    array = (int *) malloc(n * sizeof(int));

    if (!array) {
        printf("Malloc failed in last_pixel_value.\n");
        exit(0);
    }

    /* assign every neighboring pixel that we have to examine */
    /* to the left */
    array[0] = mask[get_index(x-1, y)];
    /* above to the left */
    array[1] = mask[get_index(x-1, y-1)];
    /* straight above */
    array[2] = mask[get_index(x, y-1)];

    /* if all pixels are black */
    if (is_all_black(array, n)) {
        output = 0;
    } else {
        output = get_lowest_not_black_value(array, n);
    }

    /* if all pixels are black add node */
    if (output == 0) {
        add_node(head, value);
        mask[get_index(x, y)] = *value;
    }
    /* if surrounding pixels can be equivalent, add the equivalence */
    else {
        mask[get_index(x, y)] = output;
        highest = get_highest(array, n);
        if (highest != output) {
            add_equivalence(get_node(*head, output), get_node(*head, highest));
        }
    }

    free(array);
}

/**
 * Labels first line of pixels
 *
 * @param pixels input pgm image pixels
 * @param head head reference of linked list of values and equivalencies
 * @param value value of the next added value
 * @param mask array of labels
 */
void first_line(const uchar *pixels, node **head, int *value, int *mask) {
    int j;

    /* Sanity check */
    /* no need to check node *head here, it should be NULL here, because it is an empty linked list */
    if (!pixels || !value || !head) {
        sanity_check("first_line");
        exit(1);
    }

    /* for the first pixel only compare if it is white or black */
    /* if white then assign a new value */
    if (pixels[0] > 0) {
        add_node(head, value);
        mask[0] = *value;
    } else {
        mask[0] = 0;
    }

    /* rest of the first line */
    /* only checking pixels on the left */
    for (j = 1; j < width; j++) {
        if (pixels[j] != 0) {
            if (mask[j-1] == 0) {
                add_node(head, value);
                mask[j] = *value;
            } else {
                mask[j] = mask[j-1];
            }
        }
    }
}

/**
 * First walk through of the ccl algorithm
 *
 * @param pixels input pgm image
 * @param head head reference of linked list of values and equivalencies
 * @param mask array of labels
 */
void first_walk_through(uchar *pixels, node **head, int *mask) {
    int *value;
    int i, j;

    /* Sanity check */
    /* no need to check node *head here, it should be NULL here, because it is an empty linked list */
    if (!pixels) {
        sanity_check("first_walk_through");
        exit(1);
    }

    value = (int *) malloc(sizeof(int));

    if (!value) {
        malloc_fail("first_walk_through");
        exit(1);
    }

    *value = 0;

    first_line(pixels, head, value, mask);

    /* starting on i = 1 because first line is done */
    for (i = 1; i < height; i++) {
        /* check first pixel in the row */
        /* if pixel is black, dont check */
        if (pixels[get_index(0, i)] != 0) {
            first_pixel_value(0, i, head, value, mask);
        }

        /* middle pixels */
        for (j = 1; j < width - 1; j++) {
            if (pixels[get_index(j, i)] != 0) {
                middle_pixel_value(j, i, head, value, mask);
            }
        }

        /* last pixels */
        if (pixels[get_index(width-1, i)] != 0) {
            last_pixel_value(width-1, i, head, value, mask);
        }
    }

    free(value);
}
/* ____________________________________________________________________________

    end of first walk through functions
   ____________________________________________________________________________
*/

/* ____________________________________________________________________________

    second walk through functions
   ____________________________________________________________________________
*/
/**
 * Using equivalence to fix the mask.
 * @param head head reference of linked list of values and equivalencies
 * @param mask array of labels
 */
void second_walk_through(node **head, int *mask) {
    int i, j;

    /* Sanity check */
    if (!mask || !head) {
        sanity_check("second_walk_through");
        exit(1);
    }

    /* cycle where the fix is done */
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (mask[get_index(j, i)]) {
                mask[get_index(j, i)] = get_equivalence(get_node(*head, mask[get_index(j, i)]));
            }
        }
    }
}

/* ____________________________________________________________________________

    painting mask
   ____________________________________________________________________________
*/
/**
 * Gives mask colour values
 *
 * @param head reference to colours
 * @param mask array of labels, turned into colours
 */
void paint_mask(colour_node *head, int *mask) {
    int i, j;

    /* Sanity check */
    if (!mask || !head) {
        sanity_check("paint_mask");
        exit(1);
    }

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            /* if not black */
            if (mask[get_index(j, i)] != 0) {
                mask[get_index(j, i)] = get_colour(head, mask[get_index(j, i)]); /* assign colour from colour linked list to mask */
            }
        }
    }
}

/**
 * Paints the mask with gray colours
 *
 * @param head head reference of linked list of values and equivalencies
 * @param max_value max value of colours, eg 255
 * @param mask array of labels, turned into colours
 */
void paint(node **head, int max_value, int *mask) {
    colour_node *colours;
    node *walk;
    int num_of_colours = 0;

    /* Sanity check */
    if (!mask || !head) {
        sanity_check("paint");
        exit(1);
    }

    colours = NULL;

    /* adds colours into the colour linked list and counts how many colours there are */
    walk = *head;
    while (walk) {
        if (walk->value == get_equivalence(walk)) {
            num_of_colours++;
            add_colour_node(&colours, walk->value);
        }
        walk = walk->next;
    }

    /* sets value for colour nodes */
    set_colours(colours, num_of_colours, max_value);

    paint_mask(colours, mask);

    free_colour_list(colours);
}

/**
 * Runs CLL algorithm
 *
 * @param mask array of labels, turned into colours
 * @param pixels input pgm image
 * @param width_ref width of the image
 * @param height_ref width of the image
 * @param max_value max value of colours, eg 255
 */
void run(int **mask, uchar *pixels, int width_ref, int height_ref, int max_value) {
    node *head = NULL;

    /* Sanity check */
    if (!pixels) {
        sanity_check("run");
        exit(1);
    }

    width = width_ref;
    height = height_ref;

    *mask = (int *) calloc(width * height, sizeof(int));

    if (!*mask) {
        malloc_fail("run");
        exit(1);
    }

    printf("First walk through...\n");
    first_walk_through(pixels, &head, *mask);

    printf("Second walk through...\n");
    second_walk_through(&head, *mask);

    printf("Painting...\n");
    paint(&head, max_value, *mask);

    free_list(head);
}