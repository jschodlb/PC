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

int add_equivalence(node *node1, node *node2) {
    node *last_node1;
    node *first_node2;
    node *walk1;
    node *walk2;

    /* Sanity check */
    if (!node1 || !node2) {
        printf("Sanity check failed in add_equivalence.\n");
        return FAILURE;
    }

    /* get to the end of added_to equivalence list */
    last_node1 = node1;
    while (last_node1->equivalence) {
        last_node1 = last_node1->equivalence;
    }

    /* get to the beginning of new_equivalence equivalence list */
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
                return SUCCESS;
            }
            walk1 = walk1->prev_equivalence;
        }
        walk2 = walk2->equivalence;
    }

    /* adding equivalence
       added_to->new_equivalence
       added_to<-new_equivalence */
    last_node1->equivalence = first_node2;
    first_node2->prev_equivalence = last_node1;

    return SUCCESS;
}

// TODO delete this function:
int add_equivalence_deprecated(node *added_to, node *new_equivalence) {
    node *walk;
    node *walk_e;
    int *added_to_array;
    int *new_equivalence_array;
    int index;
    int new_equivalence_size;
    int added_to_size;
    int i, j;

    /* sanity check */
    if (!added_to || !new_equivalence) {
        printf("Failed sanity check in add_equivalence.\n");
        return FAILURE;
    }

    // number of nodes in added_to equivalency list
    added_to_size = 0;
    walk = added_to;
    while (walk) {
        added_to_size++;
        walk = walk->equivalence;
    }

    walk = added_to->prev_equivalence;
    while (walk) {
        added_to_size++;
        walk = walk->prev_equivalence;
    }

    added_to_array = (int *) malloc(added_to_size * sizeof(int));

    // get number of node in new equivalence equivalence list
    new_equivalence_size = 0;
    walk = new_equivalence;
    while (walk) {
        walk = walk->equivalence;
        new_equivalence_size++;
    }

    walk = new_equivalence->prev_equivalence;
    while (walk) {
        new_equivalence_size++;
        walk = walk->prev_equivalence;
    }

    new_equivalence_array = (int *) malloc(new_equivalence_size * sizeof(int));

    index = 0;
    walk = added_to;
    while (walk) {
        added_to_array[index] = walk->value;
        index++;
        walk = walk->equivalence;
    }

    walk = added_to->prev_equivalence;
    while (walk) {
        added_to_array[index] = walk->value;
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

    walk = new_equivalence->prev_equivalence;
    while (walk) {
        new_equivalence_array[index] = walk->value;
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
    // ################################################################################################################
    // we need start of new_equivalence equivalence list
    walk_e = new_equivalence;
    while (walk_e->prev_equivalence) {
        walk_e = walk_e->prev_equivalence;
    }

    /* when there is no equivalence for added_to node */
    if (added_to->equivalence == NULL) {
        added_to->equivalence = walk_e;
        walk_e->prev_equivalence = added_to;

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
        walk->equivalence = walk_e;
        walk_e->prev_equivalence = walk;

        return SUCCESS;
    }
}


int get_equivalence(node *examined_node) {
    int min;
    node *walk;

    /* sanity check */
    if (!examined_node) {
        printf("Failed sanity check in get_equivalence.\n");
        return FAILURE;
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

int print_node(node *printed) {
    node *walk;

    /* Sanity check */
    if (!printed) {
        printf("Sanity check failed in print_node.\n");
        return FAILURE;
    }

    printf("Value: %d\n", printed->value);

    walk = printed;
    while (walk->prev_equivalence) {
        walk = walk->prev_equivalence;
    }

    printf("Equivalence:");
    while (walk) {
        printf(" %d", walk->value);
        walk = walk->equivalence;
    }

    printf("\n");

    return SUCCESS;
}

int print_node_deprecated(node *printed) {
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

node *get_node(node *head, int value) {
    node* walk;

    /* Sanity check */
    if (!head) {
        printf("Sanity check failed in get_node. List may be empty.\n");
        return NULL;
    }

    walk = head;
    while (walk) {
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