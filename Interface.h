//
// Created by Dereck Escalante on 6/12/20.
//

#ifndef THESCHEDULER_INTERFACE_H
#define THESCHEDULER_INTERFACE_H
#include <gtk/gtk.h>

struct Interface{
    GtkWidget *window;
    GtkWidget *view;
    GtkWidget *vbox;
    GtkTextBuffer *buffer;
    GtkTextIter iter;
    int argc;
    char **argv;
};

void init(int argc, char **argv,struct Interface*);
void update(struct Interface*,char* text);


#endif //THESCHEDULER_INTERFACE_H
