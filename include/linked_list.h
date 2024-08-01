#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node{
    void *data;
    struct Node* next;
};

typedef struct Node node_t;

extern const unsigned BRK_NODE_SIZE;

void push_front(node_t** head, void *data, unsigned data_size);

void push_back(node_t** head, void * data, unsigned data_size);

void push_back_node(node_t** head, node_t* node);

node_t* pop_back(node_t** head);

node_t* delete_nth(node_t** head, int pos);

node_t* get_nth(node_t* head, int pos);

void free_list(node_t** head);

void free_2d_list(node_t** head);

#endif