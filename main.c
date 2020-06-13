#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include "Process.c"
#include "Scheduler.c"
#include "Queue.c"
#include "Interface.h"
#include <pthread.h>


struct Scheduler scheduler1;
struct Process listProcess[25];  //Como el maximo son 25 procesos
struct Interface interface;
void readFile(){
    FILE *inputFile;
    char line[50];
    struct Process process;

    inputFile = fopen("input.txt","r");

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
                listProcess[j] = process; // Se insertan los procesos en la lista
                j++;
            }
            i++;
        }
    }
    printf( "\nalgorithm: %s", scheduler1.algorithm);
    printf( "\nopMode: %d", scheduler1.operationMode);
    printf( "\nproce: %d", scheduler1.processQuantity);
    printf( "\nquantum: %d", scheduler1.quantum);

    int smallestArrivalTime = 25;
    struct Process aux;

    for(int i=0; i <= scheduler1.processQuantity - 1; i++){
        printf("\nid %d", listProcess[i].id);

        if(listProcess[i].arrivalTime <= smallestArrivalTime){
            smallestArrivalTime = listProcess[i].arrivalTime;
            aux = listProcess[i];
        }
    }
    enqueue(aux);
    fclose(inputFile);
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;

    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 400);
    gtk_widget_show_all(window);
}
void char_at_a_time( const char * str ) { while( *str!= '\0' ) {
        putchar( *str++ );
        fflush( stdout );
        usleep(50);
    }
}


int main(int argc, char **argv) {


   /* if (forkStatus == 0) {
        init(&argc,&argv,&interface);
        update(&interface,"Hola");
    }*/


    //update(interface,"Dereck");
    readFile();
    showQueue();

    long double x,sum,last;
    x = 1;
    last=1;
    sum = 1;
    int limit = 400*50;
    int i;
    for(i = 1;i <= limit;i++) //cede el control de acuerdo al quantum
    {
        last*=((x*x)*(2*i-1)*(2*i-1))/((2*i)*(2*i+1));
        sum+=last;
    }
    //printf("\nResultadoooooo: %LF\n",2*sum);


    if(strcmp(scheduler1.algorithm, "FCFS") == 0){

        if(scheduler1.operationMode != 0){
            printf("El algoritmo FCFS es NO EXPROPIATIVO");
            return 0;
        }
        else{
            FCFS(scheduler1, listProcess);
        }

    } else if (strcmp(scheduler1.algorithm, "SJF") == 0){
        dequeue();
        for(int i=0; i <= scheduler1.processQuantity - 1; i++){
            enqueue(listProcess[i]);  //Se llena la cola
        }
        showQueue();
        SJF(scheduler1);

    } else if (strcmp(scheduler1.algorithm, "RR") == 0){
        if(scheduler1.operationMode != 1){
            printf("El algoritmo RR es EXPROPIATIVO");
            return 0;
        }
        else{
            RR(scheduler1, listProcess);
        }
    }
    else if (strcmp(scheduler1.algorithm, "MQS") == 0){

        dequeue();
        for(int i=0; i <= scheduler1.processQuantity - 1; i++){
            enqueue(listProcess[i]);  //Se llena la cola
        }
        MQS(scheduler1,listProcess);

    }else if (strcmp(scheduler1.algorithm, "PS") == 0) {

        if (scheduler1.operationMode == 0) {
            dequeue();
            for (int i = 0; i <= scheduler1.processQuantity - 1; i++) {
                enqueue(listProcess[i]);  //Se llena la cola
            }
            PS(scheduler1, listProcess);
        } else if (scheduler1.operationMode == 1){
            PSPreemptive(scheduler1, listProcess);
        }
    } else if (strcmp(scheduler1.algorithm, "PSRR") == 0){

        int len = scheduler1.processQuantity;
        struct Process p;

        for (int i = 0; i < (len - 1); i++)
        {
            for (int j = i + 1; j < len; j++)
            {
                if (listProcess[j].priority < listProcess[i].priority)
                {
                    p = listProcess[j];
                    listProcess[j] = listProcess[i];
                    listProcess[i] = p;
                }
            }
        }
        for (int i = 0;i < len; i++)
        {
            printf(" \n%ddasda", listProcess[i].priority);
        }

        dequeue();
        for(int i=0; i <= scheduler1.processQuantity - 1; i++){
            enqueue(listProcess[i]);  //Se llena la cola
        }
        PSRR(scheduler1, listProcess);
    }

    for(int i = 0; i <= scheduler1.processQuantity-1; i++){
        //printf("\nId: %d Res: %LF", finishedProcess[i].id, finishedProcess[i].result);
    }

    /*GtkApplication *app;
    int status;

    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);*/
    //showQueue();
    /*-- Declare the GTK Widgets used in the program --*/
    for(int i = 0; i <= scheduler1.processQuantity-1; i++){
        printf("\nId: %d Res: %LF", finishedProcess[i].id, finishedProcess[i].result);
    }

    return 0;
}
