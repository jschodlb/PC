#ifndef __COLOUR_LINKED_LIST_H__
#define __COLOUR_LINKED_LIST_H__

#define SUCCESS 1
#define FAILURE 0

typedef struct thecolour_node {
    int label;
    int value;
    struct thecolour_node *next;
} colour_node;

int label_exists(colour_node *head, int label);

int add_colour_node(colour_node **head, int value);

int get_colour(colour_node *head, int label);

int set_colours(colour_node *head, int unique_colours);

int free_colour_list(colour_node *head);

#endif