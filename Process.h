//
// Created by Dereck Escalante on 5/30/20.
//

#ifndef THESCHEDULER_PROCESS_H
#define THESCHEDULER_PROCESS_H

typedef struct Process{
    int id;
    int arrivalTime;
    int jobQuantity;
    int jobDone;
    int iteration;
    long double lastTaylor;
    long double result;
} Process;

struct Process splitProcess(struct Process process, char const *str, char const *delim);

#endif //THESCHEDULER_PROCESS_H
