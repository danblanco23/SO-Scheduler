//
// Created by danblanco on 3/6/20.
//
#include "Queue.h"

void enqueue(Process process){
    Node* newNode = (Node*) malloc(sizeof(Node));
    newNode->process = process;

    if(first == NULL){
        first = newNode;
        first->next = NULL;
        last = newNode;
    } else{
        last->next = newNode;
        newNode->next = NULL;
        last = newNode;
    }
}

struct Process dequeue(){
    Node* aux = (Node*) malloc(sizeof(Node));
    aux = first;
    struct Process process;

    if(aux != NULL){
        if(aux->next == NULL){
            first = NULL;
            last = NULL;
            process = aux->process;
            return process;
        }
        else{
            first = aux->next;
            process = aux->process;
            //free(aux);
            return process;
        }

    } else{
        printf("no hay colaaaa");
    }
}


void showQueue(){
    Node* pivot = (Node*) malloc(sizeof(Node));
    pivot = first;

    if(first != NULL){
        while (pivot != NULL){
            printf("\n %d", pivot->process.id);
            pivot = pivot->next;
        }
    } else{
        printf("No hay cola");
    }
}

