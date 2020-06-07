#include <stdio.h>
#include <stdlib.h>
#include "Scheduler.h"

struct Process finishedProcess[25];

void FCFS(struct Scheduler scheduler){
    //struct Queue* cola = createQueue(1000);
    //struct Queue* terminado = createQueue(1000);
    int cont = 0;
    int a = 0;

    /*
    while(cont < scheduler.processQuantity){        //llenamos cola de procesos
        Process proceso;
        proceso.id = cont+1;
        proceso.lastTaylor = 1;
        proceso.result = 1;
        proceso.jobDone = 0;
        enqueue(cola, &proceso);
        cont = cont+1;
    }*/

    while(first != NULL){


        struct Process process = dequeue(); //cabeza

        if(process.jobDone <= process.jobQuantity){ //si el trabajo hecho por el proceso es menor al maximo pedido
            long double x,sum,last;
            x = 1;
            last=process.lastTaylor;
            sum = process.result;
            int actual=(process.jobDone*50)+1;
            int limit = scheduler.quantum*50+(process.jobDone*50);
            for(int i = actual;i <= limit;i++) //cede el control de acuerdo al quantum
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
