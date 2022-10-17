#ifndef CONNECTION_H_INCLUDED
#define CONNECTION_H_INCLUDED

#include "logic.h"
#include "fifo.h"
#include <gtk/gtk.h>
#include <stddef.h>
#include <stdio.h>


bool ustaw_potoki(int argc,char *argv[]);
//void ruch_przeciwnika(int i);
void przekaz_tekst(int tekst);
int get_ostatnia();
void wyzeruj_ostatnia();
gboolean pobierz_tekst(gpointer data);
void zakoncz(GtkWidget *widget, gpointer data);

#endif // CONNECTION_H_INCLUDED
