#include <stdio.h>
#include <stdlib.h>

#include "colour_linked_list.h"
#include "error.h"


/**
 * Adds node to a colour linked list
 *
 * @param head head of the colour linked list
 * @param label label saved into the node for identification
 */
void add_colour_node(colour_node **head, int label) {
    colour_node *new_colour_node; /* new colour_node added to the list */

    /* sanity check for head reference */
    if (!head) {
        sanity_check("add_colour_node");
        exit(EXIT_FAILURE);
    }

    /* allocate memory for the new colour_node */
    new_colour_node = (colour_node *) malloc(sizeof(colour_node));
    /* if malloc fails */
    if (!new_colour_node) {
        malloc_fail("add_colour_node");
        exit(EXIT_FAILURE);
    }

    new_colour_node->label = label; /* label used to identify the node */
    new_colour_node->next = NULL; /* colour_node pointers set to NULL for now */
    new_colour_node->value = label; /* colour value set to label for now */

    /* if the linked list is empty, we assign new colour_node to head */
    if (*head == NULL) {
        *head = new_colour_node;
        return;
    }

    /* adding node to the start of the linked list */
    new_colour_node->next = *head;
    *head = new_colour_node;
}

/**
 * Gets colours on node in accordance with label
 *
 * @param head head of the colour list
 * @param label label saved into the node for identification
 * @return colour value or FAILURE
 */
int get_colour(colour_node *head, int label) {
    colour_node *walk;

    /* Sanity check */
    if (!head) {
        sanity_check("get_node");
        exit(EXIT_FAILURE);
    }

    /* walks through colour list,
     * if the label equals to the label in node,
     * it returns the colour value in it */
    walk = head;
    while (walk != NULL) {
        if (walk->label == label) {
            return walk->value;
        }
        walk = walk->next;
    }

    printf("get_colour: Label not found!\n");

    return FAILURE;
}

/**
 * Sets colours in the linked list.
 *
 * @param head head of the colour list
 * @param unique_colours how many different colours are there
 * @param max_value max value of a colour (eg 255)
 * @return
 */
void set_colours(colour_node *head, int unique_colours, int max_value) {
    int interval;
    int index;
    colour_node *walk;

    /* Sanity check */
    if (!head) {
        sanity_check("set_colours");
        exit(EXIT_FAILURE);
    }

    /* distance between 2 numbers */
    interval = max_value / unique_colours;

    /* assigns colours to individual nodes */
    index = FIRST_INDEX;
    walk = head;
    while (walk) {
        index++;
        walk->value = interval * index;
        walk = walk->next;
    }
}

/**
 * Prints the whole colour linked list
 *
 * @param head head of the colour list
 */
void print_colour_list(colour_node *head) {
    colour_node *walk;

    /* Sanity check */
    if (!head) {
        sanity_check("print_colour_list");
        exit(EXIT_FAILURE);
    }

    walk = head;
    while (walk) {
        printf("Label: %d, Value: %d\n", walk->label, walk->value);
        walk = walk->next;
    }
}

/**
 * Frees the colour linked list for the memory
 *
 * @param head head of the colour list
 */
void free_colour_list(colour_node *head) {
    colour_node *temp;

    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}