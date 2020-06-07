#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Process.c"
#include "Scheduler.c"
#include "Queue.c"


struct Scheduler scheduler1;
struct Process listProcess[25];  //Como el maximo son 25 procesos


void readFile(){
    FILE *inputFile;
    char line[50];
    struct Process process;

    inputFile = fopen("/home/danblanco/SO-Scheduler/input.txt","r");

    if (inputFile == NULL)
        exit(1);
    else
    {
        int i = 0;
        int j = 0;
        while (feof(inputFile) == 0)
        {
            fgets(line,50,inputFile);

            if (i == 0){
                int len = strlen(line);
                if(line[len-1] == '\n'){
                    line[len-1] = '\0';
                    strcpy(scheduler1.algorithm, line);
                }
            }
            else if (i==1){
                scheduler1.operationMode = atoi(line);
            }
            else if (i==2){
                scheduler1.processQuantity = atoi(line);
            }
            else if (i==3){
                scheduler1.quantum =atoi(line);
            }
            else if(i>=4){

                process = splitProcess(process, line, ",");
                //strcpy(process.id, line);
                listProcess[j] = process;
                j++;
            }
            i++;
        }
    }
    printf( "\nalgorithm: %s", scheduler1.algorithm);
    printf( "\nopMode: %d", scheduler1.operationMode);
    printf( "\nproce: %d", scheduler1.processQuantity);
    printf( "\nquantum: %d", scheduler1.quantum);
    for(int i=0; i <= scheduler1.processQuantity - 1; i++){
        printf("\nid %d", listProcess[i].id);
        enqueue(listProcess[i]);  //Se llena la cola
    }

    fclose(inputFile);
}

int main() {
    readFile();
    showQueue();
    FCFS(scheduler1);
    showQueue();
    for(int i = 0; i < scheduler1.processQuantity; i++){
        printf("id: %d, Result: %Le\n", finishedProcess[i].id,finishedProcess[i].result);
    }
    printf("%Le",finishedProcess[0].result * finishedProcess[1].result);
    return 0;
}
