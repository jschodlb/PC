#ifndef __CCL_H__
#define __CCL_H__

#define FAILURE 0
#define SUCCESS 1

#define CYCLE_START 0

#define BLACK 0

#define FIRST_INDEX 0

#define NUMBER_OF_NEIGHBOHRS_FIRST_COLUMN 2
#define NUMBER_OF_NEIGHBOHRS_MIDDLE_COLUMN 4
#define NUMBER_OF_NEIGHBOHRS_LAST_COLUMN 3

#define uchar unsigned char

/**
 * Gets index of 2D array format into 1D format
 *
 * @param x x-coordinate
 * @param y y-coordinate
 * @return 1D index
 */
int get_index(int x, int y);

/**
 * Runs all the functions needed to run CLL algorithm
 * and to paint the mask afterwards.
 *
 * @param mask array of labels, turned into colours
 * @param pixels input pgm image
 * @param width_ref width of the image
 * @param height_ref width of the image
 * @param max_value max value of colours, eg 255
 */
void run(int **mask, uchar *pixels, int width_ref, int height_ref, int max_value);

#endif