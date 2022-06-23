/*
* Author: Stundner Maroc
* Filename: main.c
* Task: GTK3 GUI Sudoku
* https://github.com/DevMarcoStundner/GUI_Sudoku.git
* Date 23.06.22
* Build instructions:
* clang main.c $(pkg-config --cflags --libs gtk+-3.0) -Wall -I. sudoku_c.c -lm
*/

#include <gtk/gtk.h>

struct widget
{

};

static void activate (GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *box;

    // create the window and associate a title
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (window), "Sudoku");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_container_set_border_width(GTK_CONTAINER(window), 5);

    // Create a box and add it to the window 
    box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);





    gtk_widget_show_all (GTK_WIDGET (window));
}

int main (int argc, char **argv)
{
	GtkApplication *app;
	int status;
    struct widget *d = g_malloc (sizeof (struct widget));

	app = gtk_application_new ("org.gtk.minimal", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), (gpointer) d);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
    g_free (d);
	return status;
}