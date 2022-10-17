#ifndef LOGIC_H_INCLUDED
#define LOGIC_H_INCLUDED

#include "connection.h"
#include <stdbool.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <stddef.h>

extern GtkLabel *licznik;
extern GtkLabel *powiadomienie;

void init_game(GtkWidget *grid);
void ruch_przeciwnika(int i);
void wykonaj_ruch(GtkWidget *widget,gpointer data);
void usun_n();
void zacznij_ture();
void show_moves();
void update();
void ustaw_liczniki();
void czy_koniec();
void koniec_gry();
void wypisz(int s);
void nowa_gra(GtkWidget *widget);
void set_fresh();
void ustaw_id(char *moj_id_A, char *twoj_id_B);

#endif // LOGIC_H_INCLUDED
