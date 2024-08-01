#include "linked_list.h"

const unsigned BRK_NODE_SIZE = sizeof(node_t);

// Function to Insert Node in the Beginning
void push_front(node_t** head, void *data, unsigned data_size){
    // create a new Node using dynamic memory allocation
    node_t* newNode
        = (node_t*)malloc(sizeof(node_t));

    // store the data in the new Node
    newNode->data = malloc(data_size);
    memcpy(newNode->data, data, data_size);

    // the next pointer of new Node will be on current head
    newNode->next = *head;
    // the current head will the new node_t
    *head = newNode;
}

// Function to Insert the Node in the end
void push_back(node_t** head, void *data, unsigned data_size){
    node_t* newNode
        = (node_t*)malloc(sizeof(node_t));

    // store the data in the new Node
    newNode->data = malloc(data_size);
    memcpy(newNode->data, data, data_size);

    // Since the node will be last its next will be NULL
    newNode->next = NULL;
    // in case this is the first node make the newNode as
    // the head of the LinkedList
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Create a pointer to iterate till the last node
    node_t* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    // make the next of the tail to the new Node
    current->next = newNode;
}

void push_back_node(node_t** head, node_t* node){ push_back(head, node, BRK_NODE_SIZE); }

node_t* pop_back(node_t** head){
    //Simply iterate to the end of the list
    node_t* temp = *head;
    node_t* prev = NULL;

    if(temp == NULL)    // If linked list is empty
        return *head;

    // Traverse until the temps next is null
    while(temp->next != NULL){
        prev = temp;
        temp = temp->next;
        if(!temp->next) break;
    }
    prev->next = NULL;
    free(temp);
    return *head;
}

node_t* delete_nth(node_t** head, int pos){
    if(pos < 0) return *head;

    node_t* temp = *head;
    node_t* prev = NULL;

    if(temp == NULL)    // If linked list is empty
        return *head;

    if(pos == 0){   // If head should be deleted
        *head = temp->next;
        free(temp);
        return *head;
    }

    // Node to be deleted is in middle
    //traverse till given position
    for (int i = 0; temp != NULL && i < pos; i++) {
        //Check to see if pos is out of bounds. If so, it will just do a pop_back instead essentially
        if(temp->next == NULL){
            break;
        }
        
        prev = temp;
        temp = temp->next;
    }

    // If given position is found, delete node
    if (temp != NULL) {
        prev->next = temp->next;
        free(temp);
    }

    return *head;
}

//Overloaded function only used internally in this code for recursion
node_t* get_nth_recursively(node_t* node, int index, int pos){ 
    //Base case:
    if(index == pos)
        return node;
    
    if(node == NULL || index > pos){
        return NULL;
    }

    return get_nth_recursively(node->next, index + 1, pos);
}

node_t* get_nth(node_t* head, int pos){
    //Base case:
    if(pos <= 0) return NULL;

    return get_nth_recursively(head, 0, pos);
}

void free_list(node_t** head){
    node_t* current = *head;
    node_t* next;
    
    while (current != NULL) {
        next = current->next;
        free(current->data); // Free the data stored in the node
        free(current);       // Free the node itself
        current = next;
    }
    
    *head = NULL; // Set the head to NULL after freeing the list
}

void free_2d_list(node_t** head) {
    node_t* current_row = *head;
    node_t* next_row;
    
    while (current_row != NULL) {
        next_row = current_row->next;
        free_list((node_t**)&current_row->data); // Free the sub-list
        free(current_row); // Free the row node itself
        current_row = next_row;
    }
    
    *head = NULL; // Set the head to NULL after freeing the list
}