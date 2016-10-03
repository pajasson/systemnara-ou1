//
// Created by konig on 2016-08-31.
//

#ifndef OU1_LIST_H
#define OU1_LIST_H


#include <stdbool.h>

typedef void* element;

typedef struct node{
    struct node* next;
    struct node* previous;
    element value;
    int index;
}node;

typedef struct {
    struct node* first;
    struct node* last;
}list;

/*
 * Creates a new list
 */
list* new_list(void);

/*
 * Returns the size of a list
 */
int size(list* l);

/*
 * returns the element in the list at the specified index-nr
 */
element* inspect(list* l, int index);

/*
 * returns the node next in in the list from a given node
 */
node* next(node* n);

/*
 * Returns the node previous in the list from a given node
 */
node* prev(node* n);

/*
 * Removes the node and its element at the given index
 */
void delete(list* l, int position);

/*
 * Returns a boolean value. true if the list is empty and false if its not.
 */
bool isEmpty(list* l);

/*
 * inserts the given element in the list. The list creates a new node for the element
 * and inserts in last in the list
 */
void insert(list* l, element* value);

/*
 * Swaps the elements between the two given indexnumbers in the list
 */
void swapElement(list* l, int a, int b);

/*
 * CLears the entire list of nodes and their elements
 */
void clearList(list* l);

#endif //OU1_LIST_H