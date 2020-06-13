//
// Created by Dereck Escalante on 6/12/20.
//
#include "Interface.h"

void init(int argc, char **argv,struct Interface* i){

    gtk_init(&argc, &argv);


    i->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(i->window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(i->window), 500, 300);
    gtk_window_set_title(GTK_WINDOW(i->window), "GtkTextView");
    i->vbox = gtk_vbox_new(FALSE, 0);
    i->view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(i->vbox), i->view, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(i->window), i->vbox);

    g_signal_connect(G_OBJECT(i->window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(i->window);

    gtk_main();

    return ;
}

void update(struct Interface *i,char *text){
    i->vbox = gtk_vbox_new(FALSE, 0);
    i->view = gtk_text_view_new();
    gtk_box_pack_start(GTK_BOX(i->vbox), i->view, TRUE, TRUE, 0);
    i->buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(i->view));

    gtk_text_buffer_create_tag(i->buffer, "gap",
                               "pixels_above_lines", 30, NULL);
    gtk_text_buffer_get_iter_at_offset(i->buffer, &i->iter, 0);
    gtk_text_buffer_insert(i->buffer, &i->iter,"text", -1);
    gtk_text_buffer_insert(i->buffer, &i->iter, "\n", -1);
    gtk_container_add(GTK_CONTAINER(i->window), i->vbox);
    g_signal_connect(G_OBJECT(i->window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    gtk_widget_show_all(i->window);
    gtk_main();
    return;
}

