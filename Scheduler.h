//
// Created by danblanco on 9/6/20.
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

void FCFS(struct Scheduler scheduler, struct Process listProcess[25]);
void SJF(struct Scheduler scheduler);
void RR(struct Scheduler scheduler, struct Process listProcess[25]);
void MQS(struct Scheduler scheduler, struct Process listProcess[25]);
void PS(struct Scheduler scheduler, struct Process listProcess[25]);
void PSPreemptive(struct Scheduler scheduler, struct Process listProcess[25]);
void PSRR(struct Scheduler scheduler, struct Process listProcess[]);


#endif //THE_SCHEDULER_SCHEDULER_H
