#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile();



typedef struct process{
    int id;
    int arrivalTime;
    int jobQuantity;
} process;

typedef struct scheduler{
    char algorithm[50];
    int operationMode;
    int processes;
    int quantum;

} scheduler;

struct scheduler scheduler1;


struct process listProcess[25];  //Como el maximo son 25 procesos

/*
 * Entrada: Un proceso, y dos strings, el primero es la linea de texto donde viene los datos del proceso y la segunda el
 * separador.
 * Salida: Un proceso con los valores asignados.
 */
struct process splitProcess(struct process process, char const *str, char const *delim){
    char *ptr = strtok(str, delim);

    int i = 0;
    while(ptr != NULL)
    {
        if(i == 0){
            process.id = atoi(ptr);
        }
        else if(i == 1){
            process.arrivalTime = atoi(ptr);
        }
        else if(i == 2){
            process.jobQuantity = atoi(ptr);
        }
        ptr = strtok(NULL, delim);
        i++;
    }
    return process;
}

void readFile(){
    FILE *inputFile;
    char line[50];
    struct process process;

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
                scheduler1.processes = atoi(line);
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
    printf( "\nproce: %d", scheduler1.processes);
    printf( "\nquantum: %d", scheduler1.quantum);
    for(int i=0; i <= scheduler1.processes - 1; i++){
        printf("\nid %d", listProcess[i].id);
    }

    fclose(inputFile);
}

int main() {
    readFile();
    return 0;
}