#include <string.h>
#include <math.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include "fifo.h"
#include "logic.h"
#include "connection.h"

static GtkWidget *window;
static char *moj_id, *twoj_id;

int main(int argc,char *argv[])
{
    if(ustaw_potoki(argc, argv)) return 1;
    if (argc == 2 && strcmp(argv[1],"A") == 0) { twoj_id="Bialy"; moj_id="Czarny"; }
    else { moj_id="Bialy"; twoj_id="Czarny"; }
    ustaw_id(moj_id, twoj_id);
    gtk_init(&argc, &argv);

    gchar naglowek[25];
    sprintf(naglowek,"Plansza gracza %s",moj_id);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),naglowek);
    g_signal_connect(G_OBJECT(window), "destroy",G_CALLBACK(zakoncz), NULL);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);

    GtkWidget *box1 =gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box1);

    licznik= GTK_LABEL(gtk_label_new("Czarne:     Biale:"));
    powiadomienie = GTK_LABEL(gtk_label_new(""));
    gtk_box_pack_start(GTK_BOX(box1), GTK_WIDGET(licznik), TRUE, TRUE, 3);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 0);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 0);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_box_pack_start(GTK_BOX(box1), grid, TRUE, TRUE, 0);
    GtkWidget *reset_button = gtk_button_new_with_label ("Nowa gra");
    gtk_box_pack_end(GTK_BOX(box1), reset_button, TRUE, TRUE, 3);
    g_signal_connect(G_OBJECT(reset_button), "clicked",G_CALLBACK(nowa_gra), NULL);
    gtk_box_pack_end(GTK_BOX(box1), GTK_WIDGET(powiadomienie), TRUE, TRUE, 3);

    GtkSettings *default_settings = gtk_settings_get_default();
    g_object_set(default_settings, "gtk-button-images", TRUE, NULL);

    init_game(grid);

    g_timeout_add(100,pobierz_tekst,NULL);
    zacznij_ture();
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
