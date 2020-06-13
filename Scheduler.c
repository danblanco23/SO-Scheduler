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

void MQS(struct Scheduler scheduler, struct Process listProcess[25]){
    //Node* aux = (Node*) malloc(sizeof(Node));
    //aux = first;    //puntero copia de procesos
    struct Process priority[25][25];        //Array multidimensional de 25 x 25
    for(int m = 0 ; m < 25 ; m++){          //LLena array de procesos nulos
        for(int n = 0; n < 25 ; n ++){
            Process p;
            p.id = -1;
            priority[m][n] = p;
        }
    }
    int x ;
    while(first!=NULL){
        Process proceso = dequeue();
        int i = 0;
        x = proceso.priority;          //coloca el proceso en su cola de prioridad donde filas( x )son prioridad
        while(i < 25 ){       // y las columnas ( i ) son donde se colocan los procesos en la celda
            if(priority[x][i].id == -1){
                priority[x][i] = proceso;
                break;

            }
            i++;

        }

    }
    for(int y = 0; y < 25 ; y++){       //Recorre todas las prioridades
        struct Process list[25];
        int z;
        int entered = 0;
        for(z = 0; z < 25 ; z++){
            if(priority[y][z].id != -1 ){
                list[z] = priority[y][z];
                entered = 1;

            }

        }
        if(entered){
            enqueue(list[0]);
            RR(scheduler,list);
            printf("Prioridad %d:\n", y);
            showQueue();
        }

    }
}


void PS(struct Scheduler scheduler, struct Process listProcess[25]){
    timer = 0;
    int a = 0;
    while(first != NULL){
        showQueue();
        printf("----------------\n");

        //struct Process process = dequeue(); //cabeza
        struct Process *process = findHighestPriority(timer, scheduler.operationMode);

        if(process->jobQuantity > 0){ //si el trabajo hecho por el proceso es menor al maximo pedido
            long double x,sum,last;
            x = 1;
            last=process->lastTaylor;
            sum = process->result;
            //int actual=(process.jobDone*50)+1;
            //int limit = scheduler.quantum*50+(process.jobDone*50);
            int limit = process->jobQuantity*50;
            for(int i = 1;i <= limit;i++)
            {
                last*=((x*x)*(2*i-1)*(2*i-1))/((2*i)*(2*i+1));
                sum+=last;
            }
            process->lastTaylor = last;
            process->result = sum;
            process->jobQuantity = process->jobQuantity*0;

            process->result = 2*process->result;
            finishedProcess[a] = *process; // si el proceso termino su trabajo
            a++;
            printf("\nid %d, ress: %LF", process->id, process->result);

        }
//        for(int i = 0; i <= scheduler.processQuantity; i++){
//            if(listProcess[i].arrivalTime == timer){
//                enqueue(listProcess[i]);
//            }
//        }
        if(first != NULL && first->process.arrivalTime > timer){
            timer = first->process.arrivalTime;
        } else{
            timer++;
        }
    }
}

void PSPreemptive(struct Scheduler scheduler, struct Process listProcess[25]){
    int a = 0;

    while(first != NULL) {
        showQueue();
        printf("----------------88\n");

        struct Process *process = findHighestPriority(timer, scheduler.operationMode);
        printf("pid %d \n", process->id);

        if (process->jobQuantity > 0) { //si el trabajo hecho por el proceso es menor al maximo pedido
            long double x, sum, last;
            x = 1;
            last = process->lastTaylor;
            sum = process->result;
            int actual = (process->jobQuantity * 50);
            int limit = 50;
            //int limit = process.jobQuantity;
            int i = process->lastIteration;
            int limit2 = i - 1;

            for (i; i <= limit + limit2 && i <= actual + limit2; i++) {
                last *= ((x * x) * (2 * i - 1) * (2 * i - 1)) / ((2 * i) * (2 * i + 1));
                sum += last;
                process->lastIteration = i + 1;
            }
            process->lastTaylor = last;
            process->result = sum;
            process->jobDone = process->jobDone + 1;
            process->jobQuantity = process->jobQuantity-1;
            if (process->jobQuantity > 0) {
                enqueue(*process);

            } else{
                process->result = 2 * process->result;
                finishedProcess[a] = *process; // si el proceso termino su trabajo
                a++;
            }

            for (int i = 1; i <= scheduler.processQuantity-1; i++) {
                if (listProcess[i].arrivalTime == timer) {
                    enqueue(listProcess[i]);
                }
            }
        }
        timer++;
    }
}

void PSRR(struct Scheduler scheduler, struct Process listProcess[25]){
    int a = 0;
    while(first != NULL) {
        showQueue();
        printf("----------------\n");

        //struct Process process = dequeue(); //cabeza
        struct Node *highestPriorityNode = findHighestPriorityPS(timer, scheduler.operationMode);

        if (highestPriorityNode->next != NULL){
            if(highestPriorityNode->process.priority == highestPriorityNode->next->process.priority){

                //Round Robin
                if(highestPriorityNode->process.jobQuantity > 0){ //si el trabajo hecho por el proceso es menor al maximo pedido
                    long double x,sum,last;
                    x = 1;
                    last = highestPriorityNode->process.lastTaylor;
                    sum = highestPriorityNode->process.result;
                    int actual = (highestPriorityNode->process.jobQuantity*50);
                    int limit = scheduler.quantum*50;
                    //int limit = process.jobQuantity;
                    int i = highestPriorityNode->process.lastIteration;
                    int limit2 = i-1;

                    if(limit >= actual){ //Si el quantum es mayor a la carga de trabajo
                        for(i; i <= limit+limit2 && i <= actual+limit2; i++) //cede el control de acuerdo al quantum
                        {
                            last*=((x*x)*(2*i-1)*(2*i-1))/((2*i)*(2*i+1));
                            sum+=last;
                            highestPriorityNode->process.lastIteration = i+1;
                        }
                        highestPriorityNode->process.lastTaylor = last;
                        highestPriorityNode->process.result = sum;
                        highestPriorityNode->process.jobQuantity = highestPriorityNode->process.jobQuantity*0; //Como la carga es menor al quantum, entonces termina de una vez


                    }else{
                        for(i; i <= limit+limit2 && i <= actual+limit2; i++) //cede el control de acuerdo al quantum
                        {
                            last*=((x*x)*(2*i-1)*(2*i-1))/((2*i)*(2*i+1));
                            sum+=last;
                            highestPriorityNode->process.lastIteration = i+1;
                        }

                        highestPriorityNode->process.lastTaylor = last;
                        highestPriorityNode->process.result = sum;
                        highestPriorityNode->process.jobQuantity = highestPriorityNode->process.jobQuantity-scheduler.quantum; //Se le resta a la cantidad de trabajo las unidades que el quantum le permitio hacer
                    }

                    if (highestPriorityNode->process.jobQuantity > 0){
                        enqueue(highestPriorityNode->process);

                    } else{
                        highestPriorityNode->process.result = 2*highestPriorityNode->process.result;
                        finishedProcess[a] = highestPriorityNode->process; // si el proceso termino su trabajo
                        a++;
                    }

                }

            }
            else {  //PriorityScheduling
                if (highestPriorityNode->process.jobQuantity >
                    0) { //si el trabajo hecho por el proceso es menor al maximo pedido
                    long double x, sum, last;
                    x = 1;
                    last = highestPriorityNode->process.lastTaylor;
                    sum = highestPriorityNode->process.result;
                    //int actual=(process.jobDone*50)+1;
                    //int limit = scheduler.quantum*50+(process.jobDone*50);
                    int i = highestPriorityNode->process.lastIteration;
                    int limit2 = i - 1;
                    int limit = highestPriorityNode->process.jobQuantity * 50;
                    for (i; i <= limit + limit2; i++) {
                        last *= ((x * x) * (2 * i - 1) * (2 * i - 1)) / ((2 * i) * (2 * i + 1));
                        sum += last;
                    }
                    highestPriorityNode->process.lastTaylor = last;
                    highestPriorityNode->process.result = sum;
                    highestPriorityNode->process.jobQuantity = highestPriorityNode->process.jobQuantity * 0;

                    highestPriorityNode->process.result = 2 * highestPriorityNode->process.result;
                    finishedProcess[a] = highestPriorityNode->process; // si el proceso termino su trabajo
                    a++;
                    printf("\nid %d, ress: %LF", highestPriorityNode->process.id, highestPriorityNode->process.result);
                }
            }
        }
        else{ //PriorityScheduling
            if(highestPriorityNode->process.jobQuantity > 0){ //si el trabajo hecho por el proceso es menor al maximo pedido
                long double x,sum,last;
                x = 1;
                last= highestPriorityNode->process.lastTaylor;
                sum = highestPriorityNode->process.result;
                //int actual=(process.jobDone*50)+1;
                //int limit = scheduler.quantum*50+(process.jobDone*50);
                int i = highestPriorityNode->process.lastIteration;
                int limit2 = i-1;
                int limit = highestPriorityNode->process.jobQuantity*50;
                for(i; i <= limit+limit2  ;i++)
                {
                    last*=((x*x)*(2*i-1)*(2*i-1))/((2*i)*(2*i+1));
                    sum+=last;
                }
                highestPriorityNode->process.lastTaylor = last;
                highestPriorityNode->process.result = sum;
                highestPriorityNode->process.jobQuantity = highestPriorityNode->process.jobQuantity*0;

                highestPriorityNode->process.result = 2*highestPriorityNode->process.result;
                finishedProcess[a] = highestPriorityNode->process; // si el proceso termino su trabajo
                a++;
                printf("\nid %d, ress: %LF", highestPriorityNode->process.id, highestPriorityNode->process.result);
            }
        }

    }

}

