#include "connection.h"

PipesPtr potoki = NULL;
int ostatnia = 0;

void wyzeruj_ostatnia()
{
    ostatnia = 0;
    return;
}

int get_ostatnia()
{
    return ostatnia;
}

bool ustaw_potoki(int argc,char *argv[])
{
    potoki = initPipes(argc,argv);
    if(potoki == NULL) return 1;
    return 0;
}

void przekaz_tekst(int tekst)
{
    //if(tekst == -2 && ostatnia == -2) return;
    //ostatnia = tekst;
    char str[10];
    sprintf(str, "%d", tekst);

    sendStringToPipe(potoki, str);
}

gboolean pobierz_tekst(gpointer data)
{
  gchar wejscie[10];

  if (getStringFromPipe(potoki,wejscie,10))
  {
      int pole = atoi(wejscie);
      ostatnia = pole;
      if(pole == -2)
      {
        set_fresh();
        nowa_gra(NULL);
        return TRUE;
      }
      ruch_przeciwnika(pole);
  }
  return TRUE;
}

void zakoncz(GtkWidget *widget, gpointer data)
{
  closePipes(potoki);
  gtk_main_quit();
}
