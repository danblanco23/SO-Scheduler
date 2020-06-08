#include <stdio.h>
#include <stdlib.h>
#include "Scheduler.h"

struct Process finishedProcess[25];

void FCFS(struct Scheduler scheduler){
    int a = 0;
    while(first != NULL){
        struct Process process = dequeue(); //cabeza

        if(process.jobDone <= process.jobQuantity){ //si el trabajo hecho por el proceso es menor al maximo pedido
            long double x,sum,last;
            x = 1;
            last=process.lastTaylor;
            sum = process.result;
            //int actual=(process.jobDone*50)+1;
            //int limit = scheduler.quantum*50+(process.jobDone*50);
            int limit = process.jobQuantity;
            for(int i = 1;i <= limit;i++) //cede el control de acuerdo al quantum
            {
                last*=((x*x)*(2*i-1)*(2*i-1))/((2*i)*(2*i+1));
                sum+=last;
            }
            process.lastTaylor = last;
            process.result = sum;
            process.jobDone = process.jobDone+1;

            enqueue(process);
        }
        else{
            finishedProcess[a] = process; // si el proceso termino su trabajo
            a++;
        }

    }
}
void SJF(struct Scheduler scheduler){
    int finishedCont = 0;
    if(scheduler.operationMode == 0){
        while(first != NULL){
            struct Process process = dequeue(); //cabeza
            if(process.jobDone <= process.jobQuantity) { //si el trabajo hecho por el proceso es menor al maximo pedido

            }


        }
    }
    if(scheduler.operationMode == 1){
        while(first != NULL){
            struct Process process = dequeue(); //cabeza
            if(process.jobDone <= process.jobQuantity) { //si el trabajo hecho por el proceso es menor al maximo pedido

            }

        }
    }
}
void getShortest(){

}
