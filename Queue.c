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
            printf("\nProceso: %d ,Trabajo hecho: %d, Trabajo total: %d Valor: %LF\n\n", pivot->process.id,pivot->process.jobDone,pivot->process.jobQuantity,2*pivot->process.result);
            pivot = pivot->next;
        }
    } else{
        printf("No hay cola");
    }
}

struct Process *getShortest(int currentTime){        //recibe el tiempo actual en la iteracion
    Node* aux = (Node*) malloc(sizeof(Node));
    aux = first;    //puntero copia de procesos
    int SJ =0;
    int firstTime = 1;
    struct Process *shortestProcess;
    if(currentTime==0){             //tiempo 1 retorne primer proceso
        return &aux->process;
    }
    else{                       //tiempo 2 o mas busque el menor de los procesos
        while(aux != NULL){

            if(aux->process.arrivalTime<=currentTime){   //si el arribo del proceso coincide con el tiempo solicitado
                int currentJob;
                currentJob = aux->process.jobQuantity;
                if(firstTime && currentJob !=0){
                    SJ = aux->process.jobQuantity;
                    firstTime = 0;
                    shortestProcess = &aux->process;
                }
                if(currentJob < SJ && currentJob !=0){           //verifica si el proceso viene con trabajo menor
                    SJ = currentJob;            //guarda el menor
                    shortestProcess = &aux->process;
                    aux = aux->next;
                }
                else{
                    aux = aux->next;        //siguiente
                }
            }
            else{
                aux = aux->next;
            }

        }

        return shortestProcess;
    }

}

int checkFinished(){
    Node* aux = (Node*) malloc(sizeof(Node));
    aux = first;
    struct Process process;
    int finished= 0;
    while(aux != NULL) {
        process = aux->process;
        if(process.jobQuantity>0)
            finished = 1;

        aux = aux->next;
    }
    return finished;
}

