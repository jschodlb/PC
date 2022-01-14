#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#define uchar unsigned char

#define SUCCESS 1
#define FAILURE 0

/**
 * label node
 * Value is the identification of the node
 * next points to the next node
 * equivalence points to the next node in equivalence list
 * pre_equivalence points to the previous node in equivalence list
 */
typedef struct thenode {
    int value;
    struct thenode *next;
    struct thenode *equivalence;
    struct thenode *prev_equivalence;
    int best_equivalence;
} node;

/**
 * Adds node to a linked list
 *
 * @param head head of the linked list
 * @param label value of the node
 */
void add_node(node** head, int *value);

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
void add_equivalence(node *added_to, node *equivalence);

/**
 * Gets the lowest value in the equivalence list of examined_node
 *
 * @param examined_node this node's equivalence list is examined
 * @return value of the best equivalence
 */
int get_equivalence(node *examined_node);

/**
 * Returns node according to its value.
 * Finds node with value from the argument and returns it.
 *
 * @param head head of the linked list
 * @param value searched for value
 * @return node with value value
 */
node *get_node(node *head, int value);

/**
 * Function will set the best equivalence value for every node in the linked list.
 *
 * @param head head of the linked list
 */
void set_best_equivalence(node *head);

/**
 * Prints the node's value and its equivalence list
 *
 * @param printed printed node
 */
void print_node(node *printed);

/**
 * Goes through the whole list and prints every node using print_node function
 *
 * @param head head of the linked list
 */
void print_list(node *head);

/**
 * Frees the linked list
 *
 * @param head head of the linked list
 */
void free_list(node *head);

#endif