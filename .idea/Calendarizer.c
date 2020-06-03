#include <stdio.h>
#include <stdlib.h>
#include "Calendarizer.h"
#include "Cola.h"



void FCFS(Calendar calendar){
    struct Queue* cola = createQueue(1000);
    struct Queue* terminado = createQueue(1000);
    int cont = 0;

    while(cont< calendar.numberProcess){        //llenamos cola de procesos
        Process proceso;
        proceso.processNumber = cont+1;
        proceso.iteration = 1;
        proceso.lastTaylor = 1;
        proceso.result = 1;
        proceso.jobDone = 0;
        enqueue(cola, &proceso);
        cont = cont+1;
    }

    while(!isEmpty(cola)){
        Process *p = dequeue(cola);

        if(p->jobDone <= p->totalJob){ //si el trabajo hecho por el proceso es menor al maximo pedido
            long double x,sum,last;
            x = 1;
            last=p->lastTaylor;
            sum = p->result;
            int actual=(p->jobDone*50)+1;
            int limit = calendar.quantum*50+(p->jobDone*50);
            for(int i = actual;i <= limit;i++) //cede el control de acuerdo al quantum
            {
                last*=((x*x)*(2*i-1)*(2*i-1))/((2*i)*(2*i+1));
                sum+=last;
            }
            p->lastTaylor = last;
            p->result = sum;
            p->jobDone= p->jobDone+1;
            print(&p);
            enqueue(cola,&p);

        }
        else{
            enqueue(terminado,&p);   // si el proceso termino su trabajo

        }


    }
    print(terminado);




}
