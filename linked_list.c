#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
int add_node(node** head, int *value) {
    /* used for the last node */
    node *last;
    /* new node added to the end of the list */
    node *new_node;
    
    /* sanity check for head reference */
    if (!head) {
        printf("Head reference in add_node is NULL.\n");
        return FAILURE;
    }

    /* allocate memory for the new node */
    new_node = (node *) malloc(sizeof(node));
    /* if malloc fails */
    if (!new_node) {
        printf("Malloc failed in add_node.\n");
        return FAILURE;
    }

    /* Putting data in the new node  */
    *value = *value + 1;
    new_node->value  = *value;
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

int add_equivalence(node *added_to, node *new_equivalence) {
    node *walk;
    uchar *added_to_array;
    uchar *new_equivalence_array;
    int index;
    int new_equivalence_size;
    int added_to_size;
    int i, j;

    /* sanity check */
    if (!added_to || !new_equivalence) {
        printf("Failed sanity check in add_equivalence.\n");
        return FAILURE;
    }

    if (added_to->value == 1) {
        if (new_equivalence->value == 7) {
            printf("###############################################");
        }
    }

    if (added_to->value == 7) {
        if (new_equivalence->value == 1) {
            printf("###############################################");
        }
    }

    // number of nodes in added_to equivalency list
    added_to_size = 0;
    walk = added_to;
    while (walk) {
        walk = walk->equivalence;
        added_to_size++;
    }

    walk = added_to;
    while (walk->prev_equivalence) {
        added_to_size++;
        walk = walk->prev_equivalence;
    }

    added_to_array = (uchar *) malloc(added_to_size * sizeof(uchar));

    // get number of node in new equivalence equivalence list
    new_equivalence_size = 0;
    walk = new_equivalence;
    while (walk) {
        walk = walk->equivalence;
        new_equivalence_size++;
    }

    walk = new_equivalence;
    while (walk->prev_equivalence) {
        new_equivalence_size++;
        walk = walk->prev_equivalence;
    }

    new_equivalence_array = (uchar *) malloc(new_equivalence_size * sizeof(uchar));

    index = 0;
    walk = added_to;
    while (walk) {
        added_to_array[index] = walk->value;
        index++;
        walk = walk->equivalence;
    }

    walk = added_to;
    while (walk->prev_equivalence) {
        added_to_array[index] = walk->prev_equivalence->value;
        index++;
        walk = walk->prev_equivalence;
    }

    index = 0;
    walk = new_equivalence;
    while (walk) {
        new_equivalence_array[index] = walk->value;
        index++;
        walk = walk->equivalence;
    }

    walk = new_equivalence;
    while (walk->prev_equivalence) {
        new_equivalence_array[index] = walk->prev_equivalence->value;
        index++;
        walk = walk->prev_equivalence;
    }

    for (i = 0; i < added_to_size; i++) {
        for (j = 0; j < new_equivalence_size; j++) {
            if (new_equivalence_array[j] == added_to_array[i]) {
                return SUCCESS;
            }
        }
    }

    /* when there is no equivalence for added_to node */
    if (added_to->equivalence == NULL) {
        added_to->equivalence = new_equivalence;
        new_equivalence->prev_equivalence = added_to;

        return SUCCESS;
    }
        /* if there is equivalence for added_to node */
    else {
        /* going to the end of equivalence linked list */
        walk = added_to;

        while (walk->equivalence != NULL) {
            walk = walk->equivalence;
        }

        /* adding equivalence */
        walk->equivalence = new_equivalence;
        new_equivalence->prev_equivalence = walk;

        return SUCCESS;
    }
}

uchar get_equivalence(node *examined_node) {
    uchar min;
    node *walk;

    /* sanity check */
    if (!examined_node) {
        printf("Failed sanity check in get_equivalence.\n");
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
    node *walk;

    /* Sanity check */
    if (!printed) {
        printf("Sanity check failed in print_node.\n");
        return FAILURE;
    }

    printf("Node: %d Equivalence: ", printed->value);
    walk = printed;
    while (walk->next) {
        walk = walk->next;
        printf("%d ", walk->value);
    }
    walk = printed;
    while (walk->prev_equivalence) {
        walk = walk->prev_equivalence;
        printf("%d ", walk->value);
    }
    printf("\n");

    return SUCCESS;
}

int print_list(node *head) {
    node *walk;

    /* Sanity check */
    if (!head) {
        printf("Sanity check failed in print_list.\n");
        return FAILURE;
    }

    walk = head;
    while (walk != NULL) {
        print_node(walk);
        walk = walk->next;
    }

    return SUCCESS;
}

node *get_node(node *head, uchar value) {
    node* walk;

    /* Sanity check */
    if (!head) {
        printf("Sanity check failed in get_node. List may be empty.\n");
        return NULL;
    }

    walk = head;
    while (walk != NULL) {
        if (walk->value == value) {
            return walk;
        }
        walk = walk->next;
    }

    return NULL;
}

int free_list(node *head) {
    /* goes through list */
    node *walk;
    /* help variable for free */
    node *temp;

    /* Sanity check */
    if (!head) {
        printf("Sanity check failed in free_list.\n");
        return FAILURE;
    }

    /* going through the list */
    walk = head;
    while (walk) {
        temp = walk;
        walk = walk->next;
        /* freeing nodes */
        free(temp);
    }

    return SUCCESS;
}