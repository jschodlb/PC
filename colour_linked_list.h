#ifndef __COLOUR_LINKED_LIST_H__
#define __COLOUR_LINKED_LIST_H__

#define uchar unsigned char

#define SUCCESS 1
#define FAILURE 0

typedef struct thecolour_node {
    uchar label;
    uchar value;
    struct thecolour_node *next;
} colour_node;

int add_colour_node(colour_node **head, uchar value);

uchar get_colour(colour_node *head, uchar label);

int is_label_in_list(colour_node *head, uchar label);

int set_colours(colour_node *head, int unique_colours);

int free_colour_list(colour_node *head);

#endif