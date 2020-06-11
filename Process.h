//
// Created by danblanco on 9/6/20.
//

#ifndef THE_SCHEDULER_PROCESS_H
#define THE_SCHEDULER_PROCESS_H

#include "stdbool.h"

typedef struct Process{
    int id;
    int arrivalTime;
    int jobQuantity;
    int jobDone;
    int lastIteration;
    long double lastTaylor;
    long double result;
    int finished;
} Process;

struct Process splitProcess(struct Process process, char const *str, char const *delim);

#endif //THE_SCHEDULER_PROCESS_H
