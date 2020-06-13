#include "Queue.h"
#include <stdio.h>
#include <math.h>

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

    if(aux != NULL){                    //Si solo tiene un elemento
        if(aux->next == NULL){
            first = NULL;
            last = NULL;
            process = aux->process;
            return process;
        }
        else{                          //Si hay mas de un elemento
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
void progressBar(){
    Node* pivot = (Node*) malloc(sizeof(Node));
    pivot = first;
    int progressQuantity;
    char bar[100]="";
    if(first != NULL){
        while (pivot != NULL){
            progressQuantity = round((pivot->process.jobDone*30)/pivot->process.totalJob);
            if(progressQuantity != 0){
                for(int i =0 ; i<progressQuantity; i++){
                    strcat(bar,"*");
                }
            }
            else{
                strcat(bar,"");
            }


            printf("Proceso: %d ,Progreso | %s |\n",pivot->process.id, bar);
            pivot = pivot->next;
        }
    }
    else{
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

struct Process *findHighestPriority(int timer, int preemptive){
    Node* pivot = (Node*) malloc(sizeof(Node));
    pivot = first;
    Node *highest = (Node*) malloc(sizeof(Node));
    highest = first;

    if(preemptive == 0) {
        int highestPriority = findShortestArrivalTime(), foundNode; //poner con el tiempo (3)
        if (first != NULL) {
            while (pivot != NULL) {
                if (pivot->process.priority <= highestPriority && pivot->process.arrivalTime <= timer) {
                    highestPriority = pivot->process.priority;
                    highest = pivot;
                }
                if (pivot->next == NULL) {
                    break;

                } else pivot = pivot->next;
            }
            deleteNode(highest->process.id);

        } else {
            printf("No hay cola");
        }


    } else{
        int highestPriority = 25;
        if (first != NULL) {
            while (pivot != NULL) {
                if (pivot->process.priority <= highestPriority) {
                    highestPriority = pivot->process.priority;
                    highest = pivot;
                }
                if (pivot->next == NULL) {
                    break;

                } else pivot = pivot->next;
            }
            deleteNode(highest->process.id);

        } else {
            printf("No hay cola");
        }
    }
    printf("\nid: %d, PRIORIDAD: %d", highest->process.id, highest->process.priority);
    return &highest->process;  //Quede en que devuelve el proceso
}

void deleteNode(int id){
    Node* pivot = (Node*) malloc(sizeof(Node));
    pivot = first;
    Node* previous = NULL;
    previous = NULL;

    int foundNode = 0;

    if(first != NULL) {
        while (pivot != NULL && foundNode != 1) {
            if (pivot->process.id == id) {
                if (pivot == first) {
                    first = first->next;
                } else if (pivot == last) {
                    previous->next = NULL;
                    last = previous;
                } else {
                    previous->next = pivot->next;
                }
                foundNode = 1;
            }
            previous = pivot;
            pivot = pivot->next;
        }
        if (foundNode == 0) {
            printf("Nodo no encontrado");
        } else {
            printf("se borro");
        }
    } else printf("la cola no existe");
}

int findShortestArrivalTime(){
    Node* pivot = (Node*) malloc(sizeof(Node));
    pivot = first;
    Node* shortest = (Node*) malloc(sizeof(Node));
    shortest = first;

    int shortestArrivalTime = first->process.arrivalTime, foundNode;

    if(first != NULL){
        while (pivot != NULL){
            if(pivot->process.arrivalTime <= shortestArrivalTime){ //&& pivot->process.arrivalTime == timer){
                shortestArrivalTime = pivot->process.arrivalTime;
                shortest = pivot;
            }
            if(pivot->next == NULL){
                break;

            } else pivot = pivot->next;
        }
        //deleteNode(highest->process.id);

    } else{
        printf("No hay cola");
    }
    //printf("\nid: %d, PRIORIDAD: %d", highest->process.id, highest->process.priority);
    return shortest->process.priority;  //Quede en que devuelve el proceso
}



struct Node *findHighestPriorityPS(int timer, int preemptive){
    Node* pivot = (Node*) malloc(sizeof(Node));
    pivot = first;
    Node *highest = (Node*) malloc(sizeof(Node));
    highest = first;
    Node *next = (Node*) malloc(sizeof(Node));

    int highestPriority = 25;
    if (first != NULL) {
        while (pivot != NULL) {
            if (pivot->process.priority < highestPriority) {
                highestPriority = pivot->process.priority;
                highest = pivot;
            }
            if (pivot->next == NULL) {
                break;

            } else pivot = pivot->next;
        }
        next = deleteNodePS(highest->process.id);

    } else {
        printf("No hay cola");
    }
    highest->next = next;
    printf("\nid: %d, PRIORIDAD: %d", highest->process.id, highest->process.priority);
    return highest;  //Quede en que devuelve el proceso
}

struct Node* deleteNodePS(int id){
    Node* pivot = (Node*) malloc(sizeof(Node));
    pivot = first;
    Node* previous = NULL;
    previous = NULL;
    Node* next = NULL;
    next = NULL;

    int foundNode = 0;

    if(first != NULL) {
        while (pivot != NULL && foundNode != 1) {
            if (pivot->process.id == id) {
                if (pivot == first) { //Si es la cabeza
                    next = first->next;
                    first = first->next;

                } else if (pivot == last) {//Si es el ultimo
                    previous->next = NULL;
                    last = previous;
                } else {
                    next = pivot->next;
                    previous->next = pivot->next;
                }
                foundNode = 1;
            }
            previous = pivot;
            pivot = pivot->next;
        }
        if (foundNode == 0) {
            printf("Nodo no encontrado");
        } else {
            printf("se borro");
        }
    } else printf("la cola no existe");

    return next;
}

int findShortestArrivalTimePS(){
    Node* pivot = (Node*) malloc(sizeof(Node));
    pivot = first;
    Node* shortest = (Node*) malloc(sizeof(Node));
    shortest = first;

    int shortestArrivalTime = first->process.arrivalTime, foundNode;

    if(first != NULL){
        while (pivot != NULL){
            if(pivot->process.arrivalTime <= shortestArrivalTime){ //&& pivot->process.arrivalTime == timer){
                shortestArrivalTime = pivot->process.arrivalTime;
                shortest = pivot;
            }
            if(pivot->next == NULL){
                break;

            } else pivot = pivot->next;
        }
        //deleteNode(highest->process.id);

    } else{
        printf("No hay cola");
    }
    //printf("\nid: %d, PRIORIDAD: %d", highest->process.id, highest->process.priority);
    return shortest->process.priority;  //Quede en que devuelve el proceso
}


