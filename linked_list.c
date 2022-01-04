#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
int add_node(node** head, int new_data) {
    /* used for the last node */
    node *last;
    /* new node added to the end of the list */
    node *new_node;
    
    /* sanity check for head reference */
    if (!head || !*head) {
        printf("Head reference in add_node is NULL.");
        return FAILURE;
    }

    /* allocate memory for the new node */
    new_node = (node *) malloc(sizeof(node));
    /* if malloc failes */
    if (!new_node) {
        printf("Malloc failed in add_node.");
        return FAILURE;
    }

    /* Putting data in the new node  */
    new_node->value  = new_data;
    /* node pointers set to NULL for now */
    new_node->next = NULL;
    new_node->equivalence = NULL;
    new_node->prev_equivalence =NULL;

    /* if the linked list is empty, we assign new node to head */
    if (*head == NULL) {
        *head = new_node;
        return SUCCESS;
    }

    /* if the linked list is not empty, we from head to the last node */
    last = *head;
    while (last->next != NULL) {
        last = last->next;
    }

    /* we add new node next to last node */
    last->next = new_node;

    return SUCCESS;
}

int add_equivalence(node *added_to, node *equivalence) {
    node *walk;

    /* sanity check */
    if (!added_to || !equivalence) {
        printf("Failed sanity check in add_equivalence.");
        return FAILURE;
    }

    /* when there is no equivalence for added_to node */
    if (added_to->equivalence == NULL) {
        added_to->equivalence = equivalence;
        equivalence->prev_equivalence = added_to;

        return SUCCESS;
    }
    /* if there is equivalence for added_to node */
    else {
        /* going to the end of equivalence linked list */
        walk = added_to->equivalence;

        while (walk->equivalence != NULL) {
            walk = walk->equivalence;
        }

        /* adding equivalence */
        walk->equivalence = equivalence;
        equivalence->prev_equivalence = walk;

        return SUCCESS;
    }
}

int get_equivalence(node *examined_node) {
    int min;
    node *walk;

    /* sanity check */
    if (!examined_node) {
        printf("Failed sanity check in get_equivalence.");
        return FAILURE;
    }

    /* walk is used to go through linked list of equivalence */
    walk = examined_node;
    /* min value is the examined node's value in case it does not have equivalency to other values */
    min = walk->value;

    /* going on the right side of equivalence linked list */
    while (walk->equivalence !=NULL) {
        walk = walk->equivalence;
        if (walk->value < min) {
            min = walk->value;
        }
    }

    /* go back to examined node */
    walk = examined_node;

    /* go on the left side of equivalence linked list */
    while (walk->prev_equivalence != NULL) {
        walk = walk->prev_equivalence;
        if (walk->value < min) {
            min = walk->value;
        }
    }

    return min;
}

int print_node(node *printed) {
    /* Sanity check */
    if (!printed) {
        printf("Sanity check failed in print_node.");
        return FAILURE;
    }

    printf("Value: %d Equivalency: %d\n", printed->value, get_equivalence(printed));
    return SUCCESS;
}

int print_list(node *head) {
    node *walk;

    /* Sanity check */
    if (!head) {
        printf("Sanity check failed in print_list.");
        return FAILURE;
    }

    walk = head;
    while (walk != NULL) {
        print_node(walk);
        walk = walk->next;
    }

    return SUCCESS;
}