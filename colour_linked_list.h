#ifndef __COLOUR_LINKED_LIST_H__
#define __COLOUR_LINKED_LIST_H__

#define SUCCESS 1
#define FAILURE 0

/**
 * colour node
 * Label is used for identification in the mask.
 * Value is the colour.
 * next points to the next colour
 */
typedef struct the_colour_node {
    int label;
    int value;
    struct the_colour_node *next;
} colour_node;

/**
 * Adds node to a colour linked list
 *
 * @param head head of the colour linked list
 * @param label label saved into the node for identification
 */
void add_colour_node(colour_node **head, int value);

/**
 * Gets colours on node in accordance with label
 *
 * @param head head of the colour list
 * @param label label saved into the node for identification
 * @return colour value or FAILURE
 */
int get_colour(colour_node *head, int label);

/**
 * Sets colours in the linked list.
 *
 * @param head head of the colour list
 * @param unique_colours how many different colours are there
 * @param max_value max value of a colour (eg 255)
 * @return
 */
void set_colours(colour_node *head, int unique_colours, int max_value);

/**
 * Prints the whole colour linked list
 *
 * @param head head of the colour list
 */
void print_colour_list(colour_node *head);

/**
 * Frees the colour linked list for the memory
 *
 * @param head head of the colour list
 */
void free_colour_list(colour_node *head);

#endif