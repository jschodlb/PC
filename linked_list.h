#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

#define uchar unsigned char

#define SUCCESS 1
#define FAILURE 0

typedef struct thenode {
    uchar value;
    struct thenode *next;
    struct thenode *equivalence;
    struct thenode *prev_equivalence;
} node;

int add_node(node** head_ref, int new_data);

int add_equivalence(node *added_to, node *equivalence);

int get_equivalence(node *examined_node);

int print_node(node *printed);

int print_list(node *head);

#endif