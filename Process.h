//
// Created by danblanco on 9/6/20.
//

#ifndef THESCHEDULER_PROCESS_H
#define THESCHEDULER_PROCESS_H

#include "stdbool.h"

typedef struct Process{
    int id;
    int arrivalTime;
    int jobQuantity;
    int jobDone;
    int priority;
    int lastIteration;
    long double lastTaylor;
    long double result;
    int finished;
    int totalJob;

} Process;

struct Process splitProcess(struct Process process, char const *str, char const *delim);

#endif //THE_SCHEDULER_PROCESS_H
