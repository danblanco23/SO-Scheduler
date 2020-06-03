//
// Created by Dereck Escalante on 5/30/20.
//

#ifndef TP2_OPERATIVOS_PROCESS_H
#define TP2_OPERATIVOS_PROCESS_H
struct Process{
    int processNumber;
    int jobDone;
    int iteration;
    long double lastTaylor;
    long double result;
    int processArrival;
    int totalJob;

};
typedef struct Process Process ;

#endif //TP2_OPERATIVOS_PROCESS_H
