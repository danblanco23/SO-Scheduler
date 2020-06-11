#include <stdio.h>
#include <stdlib.h>
#include "Scheduler.h"

struct Process finishedProcess[25];
int timer = 1;

void FCFS(struct Scheduler scheduler, struct Process listProcess[25]){
    int a = 0;
    while(first != NULL){
        showQueue();
        printf("----------------\n");

        struct Process process = dequeue(); //cabeza

        if(process.jobQuantity > 0){ //si el trabajo hecho por el proceso es menor al maximo pedido
            long double x,sum,last;
            x = 1;
            last=process.lastTaylor;
            sum = process.result;
            //int actual=(process.jobDone*50)+1;
            //int limit = scheduler.quantum*50+(process.jobDone*50);
            int limit = process.jobQuantity*50;
            for(int i = 1;i <= limit;i++)
            {
                last*=((x*x)*(2*i-1)*(2*i-1))/((2*i)*(2*i+1));
                sum+=last;
            }
            process.lastTaylor = last;
            process.result = sum;
            process.jobQuantity = process.jobQuantity*0;

            process.result = 2*process.result;
            finishedProcess[a] = process; // si el proceso termino su trabajo
            a++;

        }
        for(int i = 0; i <= scheduler.processQuantity; i++){
            if(listProcess[i].arrivalTime == timer){
                enqueue(listProcess[i]);
            }
        }
        timer++;
    }
}


void SJF(struct Scheduler scheduler) {
    int arrival = 0;
    if (scheduler.operationMode == 1) {       //Expropiativo
        while (checkFinished()) {
            struct Process *process;
            process = getShortest(arrival); //si es tiempo uno o mas, tome el del trabajo mas corto
            if (process->jobQuantity > 0) { //si el trabajo aun es mayor a cero
                int limit = process->jobQuantity * 50;
                long double x, sum, last;
                x = 1;
                last = process->lastTaylor;
                sum = process->result;
                for (int i = 1; i <= limit && i <= 50; i++) {
                    last *= ((x * x) * (2 * i - 1) * (2 * i - 1)) / ((2 * i) * (2 * i + 1));
                    sum += last;
                }
                process->lastTaylor = last;
                process->result = sum;
                process->jobDone = process->jobDone + 1;
                process->jobQuantity = process->jobQuantity - 1;
                arrival = arrival + 1;
            }

        }
        //showQueue();

    }
    if (scheduler.operationMode == 0) {       //No Expropiativo
        while (checkFinished()) {
            struct Process *process;
            process = getShortest(arrival); //si es tiempo uno o mas, tome el del trabajo mas corto
            if (process->jobQuantity > 0) { //si el trabajo aun es mayor a cero
                int limit = process->jobQuantity * 50;
                long double x, sum, last;
                x = 1;
                last = process->lastTaylor;
                sum = process->result;
                for (int i = 1; i <= limit; i++) {
                    last *= ((x * x) * (2 * i - 1) * (2 * i - 1)) / ((2 * i) * (2 * i + 1));
                    sum += last;
                }
                process->lastTaylor = last;
                process->result = sum;
                process->jobDone = process->jobQuantity;
                process->jobQuantity = 0;
                arrival = arrival + 1;
            }
        }
    }
}


void RR(struct Scheduler scheduler, struct Process listProcess[25]){
    int a = 0;

    while(first != NULL){
        showQueue();
        printf("----------------\n");

        struct Process process = dequeue(); //cabeza

        if(process.jobQuantity > 0){ //si el trabajo hecho por el proceso es menor al maximo pedido
            long double x,sum,last;
            x = 1;
            last = process.lastTaylor;
            sum = process.result;
            int actual = (process.jobQuantity*50);
            int limit = scheduler.quantum*50;
            //int limit = process.jobQuantity;
            int i = process.lastIteration;
            int limit2 = i-1;

            if(limit >= actual){ //Si el quantum es mayor a la carga de trabajo
                for(i; i <= limit+limit2 && i <= actual+limit2; i++) //cede el control de acuerdo al quantum
                {
                    last*=((x*x)*(2*i-1)*(2*i-1))/((2*i)*(2*i+1));
                    sum+=last;
                    process.lastIteration = i+1;
                }
                process.lastTaylor = last;
                process.result = sum;
                process.jobQuantity = process.jobQuantity*0; //Como la carga es menor al quantum, entonces termina de una vez


            }else{
                for(i; i <= limit+limit2 && i <= actual+limit2; i++) //cede el control de acuerdo al quantum
                {
                    last*=((x*x)*(2*i-1)*(2*i-1))/((2*i)*(2*i+1));
                    sum+=last;
                    process.lastIteration = i+1;
                }

                process.lastTaylor = last;
                process.result = sum;
                process.jobQuantity = process.jobQuantity-scheduler.quantum; //Se le resta a la cantidad de trabajo las unidades que el quantum le permitio hacer
            }

            if (process.jobQuantity > 0){
                enqueue(process);

            } else{
                process.result = 2*process.result;
                finishedProcess[a] = process; // si el proceso termino su trabajo
                a++;
            }

        }

        for(int i = 0; i <= scheduler.processQuantity; i++){
            if(listProcess[i].arrivalTime == timer){
                enqueue(listProcess[i]);
            }
        }
        timer++;
    }
}

