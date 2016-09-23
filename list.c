//
// Created by konig on 2016-08-31.
//
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list* new_list(void){

    list* list = malloc(sizeof(list));

    list->first = NULL;
    list->last = NULL;

    return list;
}

bool isEmpty(list* l){

    return(l->first == NULL);
}

node* next(node* n){

    if(n->next != NULL){
        return n->next;
    }
    return NULL;
}

node* prev(node* n){

    if(n->previous != NULL){
        return n->previous;
    }
    return NULL;
}

element* inspect(list* l, int index){
    node* n = l->first;
    for(int i = 1; i <= index; i++){
        if(n->index == index){
            return n->value;
        }
        n = next(n);
    }
    return n->value;
}

int size(list* l){

    return l->last->index;
}

void insert(list* l, element* value){

    int i = 1;
    if(isEmpty(l)) {
        node* n1 = malloc(sizeof(node));
        n1->value = value;
        l->first = n1;
        l->first->index = 1;
        l->last = n1;
        l->last->index = 1;
        return;
    }else{
        node* n = l->first;
        while(n != NULL){
            n = next(n);
            i++;
        }
        node* n2 = malloc(sizeof(node));
        n2->index = i;
        n2->previous = l->last;
        l->last->next = n2;
        n2->next = NULL;
        l->last = n2;
        n2->value = value;
    }
    return;
}

void delete(list* l, int position){
    node* n = l->first;
    for(int i = 1;i < position;i++){
        n = next(n);
    }
    n->previous->next = n->next;
    n->next->previous = n->previous;
    node* nremove = n;
    while(n != NULL) {
        n->index--;
        n = n->next;
    }
    free(nremove);
}

void swapElement(list* l, int a, int b){

    if(!isEmpty(l)){
        node* n1 = l->first;
        node* n2 = l->first;
        element* tmp;
        int i = 1;
        while(i < a){
            n1 = next(n1);
            i++;
        }
        i = 1;
        while(i < b){
            n2 = next(n2);
            i++;
        }
        tmp = n1->value;
        n1->value = n2->value;
        n2->value = tmp;

    }

}