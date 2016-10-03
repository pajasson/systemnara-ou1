//
// Created by konig on 2016-08-31.
//
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list* new_list(void){

    list* l = calloc(1, sizeof(list));

    l->first = NULL;
    l->last = NULL;

    return l;
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
    if(!isEmpty(l)){
        node* n = l->first;
        for(int i = 1; i <= index; i++){
            if(n->index == index){
                return n->value;
            }
            n = next(n);
        }
    }
    return NULL;
}

int size(list* l){
    if(!isEmpty(l)){
        return l->last->index;
    }
    return 0;
}

void insert(list* l, element* value){

    int i = 1;
    if(isEmpty(l)) {
        node* n1 = calloc(1, sizeof(node));
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
        node* n2 = calloc(1, sizeof(node));
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
    free(n->value);
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
void clearList(list* l){

    if(!isEmpty(l)){
        node* n1 = l->first;
        node* n2 = NULL;
        while(n1->next != NULL){
            n2 = n1->next;
            free(n1->value);
            free(n1);
            n1 = n2;
        }
        free(n1->value);
        free(n1);

    }
}