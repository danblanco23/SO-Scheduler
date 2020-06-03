//
// Created by Dereck Escalante on 5/30/20.
//

#ifndef TP2_OPERATIVOS_CALENDARIZER_H
#define TP2_OPERATIVOS_CALENDARIZER_H
struct Calendarizer {
    int algorithm;
    int operationMode;
    int numberProcess;
    int quantum;
};
typedef struct Calendarizer Calendar ;
void FCFS(Calendar);

#endif //TP2_OPERATIVOS_CALENDARIZER_H
