#include <stdio.h>
#include <stdlib.h>

#include "colour_linked_list.h"

int label_exists(colour_node *head, int label) {
    colour_node *walk;

    if (!head) {
        /* list is empty, thus label does not exist in it */
        return FAILURE;
    }

    walk = head;
    while (walk) {
        if (walk->label == label) {
            return SUCCESS;
        }
        walk = walk->next;
    }

    return FAILURE;
}

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new colour_node at the end  */
int add_colour_node(colour_node **head, int label) {
    /* used for the last colour_node */
    colour_node *last;
    /* new colour_node added to the end of the list */
    colour_node *new_colour_node;

    /* sanity check for head reference */
    if (!head) {
        printf("Head reference in add_colour_node is NULL.\n");
        return FAILURE;
    }

    /* allocate memory for the new colour_node */
    new_colour_node = (colour_node *) malloc(sizeof(colour_node));
    /* if malloc fails */
    if (!new_colour_node) {
        printf("Malloc failed in add_colour_node.\n");
        return FAILURE;
    }

    /* Putting data in the new colour_node  */
    new_colour_node->label = label;
    /* colour_node pointers set to NULL for now */
    new_colour_node->next = NULL;
    /* colour value set to label for now */
    new_colour_node->value = label;

    /* if the linked list is empty, we assign new colour_node to head */
    if (*head == NULL) {
        *head = new_colour_node;

        return SUCCESS;
    }

    /* if the linked list is not empty, we from head to the last colour_node */
    last = *head;
    while (last->next != NULL) {
        last = last->next;
    }

    /* we add new colour_node next to last colour_node */
    last->next = new_colour_node;

    return SUCCESS;
}

int get_colour(colour_node *head, int label) {
    colour_node* walk;

    /* Sanity check */
    if (!head) {
        printf("Sanity check failed in get_node. List may be empty.\n");
        return FAILURE;
    }

    walk = head;
    while (walk != NULL) {
        if (walk->label == label) {
            return walk->value;
        }
        walk = walk->next;
    }

    return FAILURE;
}

int set_colours(colour_node *head, int unique_colours) {
    int interval;
    int index;
    colour_node *walk;

    /* Sanity check */
    if (!head) {
        printf("Sanity check failed in set_colours.\n");
        return FAILURE;
    }

    interval = UCHAR_MAX / unique_colours;

    index = 0;
    walk = head;
    while (walk) {
        index++;
        walk->value = interval * index;
        walk = walk->next;
    }

    walk = head;
    while (walk) {
        walk = walk->next;
    }

    return SUCCESS;
}

int print_colour_list(colour_node *head) {
    colour_node *walk;

    /* Sanity check */
    if (!head) {
        printf("Sanity check failed in print_colour_list.\n");
        return FAILURE;
    }

    walk = head;
    while (walk) {
        printf("Label: %d, Value: %d\n", walk->label, walk->value);
        walk = walk->next;
    }

    return SUCCESS;
}

int free_colour_list(colour_node *head) {
    colour_node *temp;

    /* Sanity check */
    if (!head) {
        printf("Sanity check failed in free_colour_list.\n");
        return FAILURE;
    }

    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return SUCCESS;
}