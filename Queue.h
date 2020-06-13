//
// Created by danblanco on 9/6/20.
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
struct Process *getShortest(int);
int checkFinished();
void progressBar();
struct Process *findHighestPriority(int, int);
void deleteNode(int id);
int findShortestArrivalTime();
struct Node *findHighestPriorityPS(int, int);
Node *deleteNodePS(int id);
int findShortestArrivalTimePS();


#endif //THESCHEDULER_QUEUE_H
