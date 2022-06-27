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
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "sudoku_c.h"

#define SudokuX N-1
#define SudokuY N-1
#define HARD 60
#define NORMAL 40
#define EASY 20

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
    GtkWidget *statusbar;
    guint id;
    int solution[N*N];
    int puzzle[N*N];
    bool hard;
    bool normal;
    bool easy;
};

#define ent(IDX,IDY) \
	w->entry[IDX] = gtk_entry_new(); \
	gtk_widget_set_size_request(w->entry[IDX],50, 50); \
    gtk_entry_set_width_chars(GTK_ENTRY(w->entry[IDX]),4);\
    gtk_entry_set_alignment(GTK_ENTRY(w->entry[IDX]),0.5);\
    gtk_grid_attach(GTK_GRID(w->grid),w->entry[IDX],IDX,IDY,1,1);


static void quit_callback (GSimpleAction *action, GVariant *parameter, gpointer user_data)
{
	struct widget *w = (struct widget *)user_data;
	g_application_quit (G_APPLICATION (w->app));
}


static void difficulty_callback_hard (GtkWidget *widget, gpointer user_data)
{
	struct widget *w = (struct widget *)user_data;
    w->hard = true;
    w->normal = false;
    w->easy = false;
    printf("Difficulty: Hard %d\n",w->hard);
}

static void difficulty_callback_normal (GtkWidget *widget, gpointer user_data)
{
	struct widget *w = (struct widget *)user_data;
    w->hard = false;
    w->normal = true;
    w->easy = false;
    printf("Difficulty: Normal %d\n",w->normal);
}

static void difficulty_callback_easy (GtkWidget *widget, gpointer user_data)
{
	struct widget *w = (struct widget *)user_data;
    w->hard = false;
    w->normal = false;
    w->easy = true;
    printf("Difficulty: Easy %d\n",w->easy);
}

static void sudoku_build (GtkWidget *widget, gpointer user_data)
{
    struct widget *w = (struct widget *)user_data;  
    char buffer[2]; 
    sudoku_generate(w->solution);
    memcpy(w->puzzle,w->solution,sizeof(w->puzzle));

    if(w->hard == true){sudoku_classic(w->puzzle,HARD);}
    if(w->normal == true){sudoku_classic(w->puzzle,NORMAL);}
    if(w->easy == true){sudoku_classic(w->puzzle,EASY);}

    for(int i = 0; i <= N*N; i++)
    {
        buffer[0] = *(g_ascii_dtostr(buffer,2,(double) w->puzzle[i]));   
        const char *buffer_entry = buffer;
        printf("%i buffer_entry: %s\n",i,buffer_entry);
        printf("%i buffer: %s\n",i,buffer);
        printf("%i puzzle: %d\n\n",i,w->puzzle[i]);

        gtk_entry_set_text(GTK_ENTRY(w->entry[i]),buffer_entry);
        if(w->puzzle[i] == 0)
        {
            gtk_entry_set_text(GTK_ENTRY(w->entry[i]),"");   
        }  
    }

}



static void activate (GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;

    struct widget *w = (struct widget *)user_data;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_application (GTK_WINDOW (window), GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (window), "Sudoku");
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    w->vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
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
    g_signal_connect(G_OBJECT(w->restart_m),"activate",G_CALLBACK(sudoku_build), w);
    g_signal_connect(G_OBJECT(w->hard_m),"activate",G_CALLBACK(difficulty_callback_hard), w);
    g_signal_connect(G_OBJECT(w->normal_m),"activate",G_CALLBACK(difficulty_callback_normal), w);
    g_signal_connect(G_OBJECT(w->easy_m),"activate",G_CALLBACK(difficulty_callback_easy), w);
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


    //ENTRYS@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    w->grid = gtk_grid_new();
    gtk_box_pack_start(GTK_BOX(w->vbox),w->grid, TRUE, FALSE, 0);
    

    for(int i = 0; i <= SudokuX; i++)
    {
        for(int j = 0; j <= SudokuY; j++)
        {
            ent(i,j);
        }
    }
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


    //STATUSBAR@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    
    w->statusbar = gtk_statusbar_new();
    gtk_widget_set_size_request (w->statusbar, 300, 10);
    gtk_box_pack_start (GTK_BOX (w->vbox), w->statusbar, FALSE, FALSE, 0);
    w->id = gtk_statusbar_get_context_id (GTK_STATUSBAR (w->statusbar), "demo");
    // gtk_statusbar_push((GtkStatusbar *)w->statusbar,w->id,"Test");
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



    gtk_widget_show_all (GTK_WIDGET (window));
}

int main (int argc, char **argv)
{
    srand((unsigned int)time(NULL));
	int status;
    struct widget *d = g_malloc (sizeof (struct widget));
    d->hard = false;
    d->normal = true;
    d->easy =  false;

	d->app = gtk_application_new ("org.gtk.minimal", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (d->app, "activate", G_CALLBACK (activate), (gpointer) d);
	status = g_application_run (G_APPLICATION (d->app), argc, argv);
	g_object_unref (d->app);
    g_free (d);
	return status;
} 