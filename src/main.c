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

#define SudokuX 8
#define SudokuY 8

struct widget
{
    GtkWidget *entry[81]; 
    GtkWidget *grid;
};

#define B(IDX,IDY) \
	w->entry[IDX] = gtk_entry_new(); \
	gtk_widget_set_size_request(w->entry[IDX],50, 50); \
    gtk_entry_set_width_chars(w->entry[IDX],4);\
    gtk_entry_set_alignment(w->entry[IDX],0.5);\
    gtk_grid_attach(GTK_GRID(w->grid),w->entry[IDX],IDX,IDY,1,1);



static void activate (GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;


    struct widget *w = (struct widget *)user_data;

    // create the window and associate a title
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (window), "Sudoku");
    //gtk_window_set_default_size(GTK_WINDOW(window), 300, 400);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    w->grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window),w->grid);
    

    for(int i = 0; i <= SudokuX; i++)
    {
        for(int j = 0; j <= SudokuY; j++)
        {
            B(i,j);
        }
    }


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