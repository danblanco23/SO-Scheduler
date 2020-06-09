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
            printf("Proceso: %d ,Trabajo hecho: %d, Trabajo total: %d Valor: %LF\n\n", pivot->process.id,pivot->process.jobDone,pivot->process.jobQuantity,pivot->process.result);
            pivot = pivot->next;
        }
    } else{
        printf("No hay cola");
    }
}

struct Process getShortest(int currentTime){        //recibe el tiempo actual en la iteracion
    Node* aux = (Node*) malloc(sizeof(Node));
    aux = first;    //puntero copia de procesos
    int SJ =0;
    int firstTime = 1;
    int shortestID;
    struct Process process;
    while(aux != NULL){
        process = aux->process;

        if(process.arrivalTime<=currentTime){   //si el arribo del proceso coincide con el tiempo solicitado
            int currentJob;
            process = aux->process;
            currentJob = process.jobQuantity;
            if(firstTime){
                SJ = process.jobQuantity;
                firstTime = 0;
                shortestID = process.id;
            }
            if(currentJob < SJ ){           //verifica si el proceso viene con trabajo menor
                SJ = currentJob;            //guarda el menor
                shortestID = process.id;    //guarda el id del menor
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
    Process p = search_and_destroy(shortestID);
    showQueue();
    return p;
}

struct Process search_and_destroy(int processId){       //busca un nodo por id y lo elimina(un dequeue dirigido)
    Node* aux = (Node*) malloc(sizeof(Node));
    Node* prev = (Node*) malloc(sizeof(Node));
    aux = first;
    prev = first;
    struct Process process;
    int found =0;
    while(aux != NULL || found == 0){
        process = aux->process;
        if(process.id == processId){
            if(aux == first){
                first = first->next;
            }
            else{
                prev->next = aux->next;
            }
            found = 1;
        }
        else{
            prev = aux;
            aux = aux->next;
        }
    }

    return process;


}

