#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"
#include "error.h"

/**
 * Adds node to a linked list
 *
 * @param head head of the linked list
 * @param label value of the node
 */
void add_node(node **head, int *value) {
    /* new node added to the list */
    node *new_node;
    
    /* sanity check for head reference */
    if (!head) {
        sanity_check("add_node");
        exit(EXIT_FAILURE);
    }

    /* allocate memory for the new node */
    new_node = (node *) malloc(sizeof(node));
    /* if malloc fails */
    if (!new_node) {
        malloc_fail("add_node");
        exit(EXIT_FAILURE);
    }

    *value = *value + 1; /* next value added to the node */
    new_node->value  = *value; /* saves value into the node */
    /* node pointers set to NULL for now */
    new_node->next = NULL;
    new_node->equivalence = NULL;
    new_node->prev_equivalence = NULL;
    /* for now set the best equivalence to the new node's value */
    new_node->best_equivalence = *value;

    /* if the linked list is empty, we assign new node to head */
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    /* adding node to the start of the linked list */
    new_node->next = *head;
    *head = new_node;
}

/**
 * Adds equivalence of node1 and node2
 * To node1, equivalence is added at the end
 * To node2, equivalence is added at the beginning
 * node1->node2
 * node1<-node2
 *
 * @param node1 node added equivalency to
 * @param node2 node added equivalency to
 */
void add_equivalence(node *node1, node *node2) {
    node *last_node1;
    node *first_node2;
    node *walk1;
    node *walk2;

    /* Sanity check */
    if (!node1 || !node2) {
        sanity_check("add_equivalence");
        exit(EXIT_FAILURE);
    }

    /* get to the end of node1 equivalence list */
    last_node1 = node1;
    while (last_node1->equivalence) {
        last_node1 = last_node1->equivalence;
    }

    /* get to the beginning of node2 equivalence list */
    first_node2 = node2;
    while (first_node2->prev_equivalence) {
        first_node2 = first_node2->prev_equivalence;
    }


    /* check for duplicates */
    walk2 = first_node2;
    while (walk2) {
        walk1 = last_node1;
        while (walk1) {
            if (walk1->value == walk2->value) {
                return;
            }
            walk1 = walk1->prev_equivalence;
        }
        walk2 = walk2->equivalence;
    }

    /* adding equivalence
       node1->node2
       node1<-node2 */
    last_node1->equivalence = first_node2;
    first_node2->prev_equivalence = last_node1;
}

/**
 * Gets the lowest value in the equivalence list of examined_node
 *
 * @param examined_node this node's equivalence list is examined
 * @return value of the best equivalence
 */
int get_equivalence(node *examined_node) {
    int min;
    node *walk;

    /* sanity check */
    if (!examined_node) {
        sanity_check("get_equivalence");
        exit(EXIT_FAILURE);
    }

    /* walk is used to go through linked list of equivalence */
    walk = examined_node->equivalence;
    /* min value is the examined node's value in case it does not have equivalency to other values */
    min = examined_node->value;

    /* going on the right side of equivalence linked list */
    while (walk) {
        if (walk->value < min) {
            min = walk->value;
        }
        walk = walk->equivalence;
    }

    /* go back to examined node */
    walk = examined_node->prev_equivalence;

    /* go on the left side of equivalence linked list */
    while (walk) {
        if (walk->value < min) {
            min = walk->value;
        }
        walk = walk->prev_equivalence;
    }

    return min;
}

/**
 * Returns node according to its value.
 * Finds node with value from the argument and returns it.
 *
 * @param head head of the linked list
 * @param value searched for value
 * @return node with value value or NULL
 */
node *get_node(node *head, int value) {
    node* walk;

    /* Sanity check */
    if (!head) {
        printf("Sanity check failed in get_node. List may be empty.\n");
        return NULL;
    }

    /* walks through list the whole list and when finds node with value it returns it */
    walk = head;
    while (walk) {
        if (walk->value == value) {
            return walk;
        }
        walk = walk->next;
    }

    printf("get_node: Node not found!\n");

    return NULL;
}

/**
 * Function will set the best equivalence value for every node in the linked list.
 *
 * @param head head of the linked list
 */
void set_best_equivalence(node *head) {
    node *walk;
    int best_equivalence;

    /* Sanity check */
    if (!head) {
        sanity_check("set_best_equivalence");
        exit(EXIT_FAILURE);
    }

    walk = head;
    while (walk) {
        best_equivalence = get_equivalence(walk);
        walk->best_equivalence = best_equivalence;

        walk = walk->next;
    }
}

/**
 * Prints the node's value and its equivalence list
 *
 * @param printed printed node
 */
void print_node(node *printed) {
    node *walk;

    /* Sanity check */
    if (!printed) {
        sanity_check("print_node");
        exit(EXIT_FAILURE);
    }

    printf("Value: %d\n", printed->value);

    /* getting to the beginning of the equivalence list */
    walk = printed;
    while (walk->prev_equivalence) {
        walk = walk->prev_equivalence;
    }

    /* printing equivalence from the beginning to the end */
    printf("Equivalence:");
    while (walk) {
        printf(" %d", walk->value);
        walk = walk->equivalence;
    }

    printf("\n");
}

/**
 * Goes through the whole list and prints every node using print_node function
 *
 * @param head head of the linked list
 */
void print_list(node *head) {
    node *walk;

    /* Sanity check */
    if (!head) {
        sanity_check("print_list");
        exit(EXIT_FAILURE);
    }

    walk = head;
    while (walk != NULL) {
        print_node(walk);
        walk = walk->next;
    }
}

/**
 * Frees the linked list
 *
 * @param head head of the linked list
 */
void free_list(node *head) {
    /* goes through list */
    node *walk;
    /* help variable for free */
    node *temp;

    /* going through the list */
    walk = head;
    while (walk) {
        temp = walk;
        walk = walk->next;
        /* freeing nodes */
        free(temp);
    }
}