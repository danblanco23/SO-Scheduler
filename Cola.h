

#ifndef TP2_OPERATIVOS_COLA_H
#define TP2_OPERATIVOS_COLA_H
#include "Process.h"
struct Queue
{
    int front, rear, size;
    unsigned capacity;
    Process* array;
};
struct Queue* createQueue(unsigned capacity);
int isFull(struct Queue* queue);
int isEmpty(struct Queue* queue);
//void enqueue(struct Queue* queue, Process *item);
Process* dequeue(struct Queue* queue);
Process* front(struct Queue* queue);
Process* rear(struct Queue* queue);
void print(struct Queue* queue);
#endif //TP2_OPERATIVOS_COLA_H
