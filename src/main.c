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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sudoku_c.h"

#define SudokuX N-1
#define SudokuY N-1

struct widget
{
    GtkWidget *vbox;
    GtkWidget *entry[81]; 
    GtkWidget *grid;
    GtkWidget *menu;
    GtkWidget *menubar;
    GtkWidget *restart_m;
    GtkWidget *difficulty_m;
    GtkWidget *highscore_m;
    GtkWidget *check_m;
    GtkWidget *quit_m;
    GtkWidget *hard_m;
    GtkWidget *normal_m;
    GtkWidget *easy_m;
    GtkWidget *difficultymenu;
    GtkApplication *app;
};

#define ent(IDX,IDY) \
	w->entry[IDX] = gtk_entry_new(); \
	gtk_widget_set_size_request(w->entry[IDX],50, 50); \
    gtk_entry_set_width_chars(w->entry[IDX],4);\
    gtk_entry_set_alignment(w->entry[IDX],0.5);\
    gtk_grid_attach(GTK_GRID(w->grid),w->entry[IDX],IDX,IDY,1,1);


void quit_callback (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	struct widget *w = (struct widget *)user_data;
	g_application_quit (G_APPLICATION (w->app));
}


static void activate (GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;

    struct widget *w = (struct widget *)user_data;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (window), "Sudoku");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    w->vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), w->vbox);

    //MENU@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    w->menubar = gtk_menu_bar_new();
    w->difficultymenu = gtk_menu_new();

    w->restart_m = gtk_menu_item_new_with_label("Restart");
    w->difficulty_m = gtk_menu_item_new_with_label("Difficulty");
    w->highscore_m = gtk_menu_item_new_with_label("Highscore");
    w->check_m = gtk_menu_item_new_with_label("Check");
    w->quit_m = gtk_menu_item_new_with_label("Quit");
    w->hard_m = gtk_menu_item_new_with_label("Hard");
    w->normal_m = gtk_menu_item_new_with_label("Normal");
    w->easy_m = gtk_menu_item_new_with_label("Easy");

    gtk_menu_shell_append(GTK_MENU_SHELL(w->menubar), w->check_m);
    gtk_menu_shell_append(GTK_MENU_SHELL(w->menubar), w->restart_m);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(w->difficulty_m), w->difficultymenu);
    gtk_menu_shell_append(GTK_MENU_SHELL(w->difficultymenu), w->hard_m);
    gtk_menu_shell_append(GTK_MENU_SHELL(w->difficultymenu), w->normal_m);
    gtk_menu_shell_append(GTK_MENU_SHELL(w->difficultymenu), w->easy_m);
    gtk_menu_shell_append(GTK_MENU_SHELL(w->menubar), w->difficulty_m);
    gtk_menu_shell_append(GTK_MENU_SHELL(w->menubar), w->highscore_m);
    gtk_menu_shell_append(GTK_MENU_SHELL(w->menubar), w->quit_m);

    gtk_box_pack_start(GTK_BOX(w->vbox), w->menubar, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(w->quit_m),"activate",G_CALLBACK(quit_callback), NULL);
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

    w->grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(w->vbox),w->grid, TRUE, FALSE, 0);
    

    for(int i = 0; i <= SudokuX; i++)
    {
        for(int j = 0; j <= SudokuY; j++)
        {
            ent(i,j);
        }
    }


    gtk_widget_show_all (GTK_WIDGET (window));
}

int main (int argc, char **argv)
{

	int status;
    struct widget *d = g_malloc (sizeof (struct widget));

	d->app = gtk_application_new ("org.gtk.minimal", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (d->app, "activate", G_CALLBACK (activate), (gpointer) d);
	status = g_application_run (G_APPLICATION (d->app), argc, argv);
	g_object_unref (d->app);
    g_free (d);
	return status;
} 