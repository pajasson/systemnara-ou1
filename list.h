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

list* new_list(void);
int size(list* l);
element* inspect(list* l, int index);
void delete(list* l, int position);
bool isEmpty(list* l);
void insert(list* l, element* value);

#endif //OU1_LIST_H