//
// Created by Dereck Escalante on 5/30/20.
//

#ifndef THESCHEDULER_SCHEDULER_H
#define THESCHEDULER_SCHEDULER_H

#include "Queue.h"

typedef struct Scheduler{
    char algorithm[50];
    int operationMode;
    int processQuantity;
    int quantum;
} Scheduler;

void FCFS(struct Scheduler scheduler);
void SJF(struct Scheduler scheduler);

#endif //THESCHEDULER_SCHEDULER_H
