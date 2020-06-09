//
// Created by danblanco on 3/6/20.
//

#ifndef THESCHEDULER_QUEUE_H
#define THESCHEDULER_QUEUE_H

#include "Process.h"

typedef struct Node{
    Process process;
    struct Node *next;
} Node;

Node* first = NULL;
Node* last = NULL;

void enqueue(Process process);
struct Process dequeue();
void showQueue();
struct Process getShortest(int);
struct Process search_and_destroy(int);

#endif //THESCHEDULER_QUEUE_H
