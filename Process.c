#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "Process.h"


/*
 * Entrada: Un proceso, y dos strings, el primero es la linea de texto donde viene los datos del proceso y la segunda el
 * separador.
 * Salida: Un proceso con los valores asignados.
 */
struct Process splitProcess(struct Process process, char const *str, char const *delim){
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
    process.lastTaylor = 1;
    process.jobDone = 0;
    process.result = 1;
    process.finished = 0;
    return process;
}