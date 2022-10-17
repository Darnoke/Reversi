#include "logic.h"

char tablica[64];
char tura;
int odbicie[64];
GtkWidget *tab[64];
GtkLabel *licznik;
GtkLabel *powiadomienie;
GtkImage *obrazy[64];
int last = 0;
static char *moj_id, *twoj_id;
bool fresh = true;


void ustaw_id(char *moj_id_A, char *twoj_id_B)
{
    moj_id = moj_id_A;
    twoj_id = twoj_id_B;
}

void wypisz(int s)
{
    gchar tekst[50];
    if(s == 0)
    {
        sprintf(tekst," ");
    }
    if(s == 1)
    {
        sprintf(tekst,"Brak mozliwego ruchu, tracisz ture");
    }
    if(s == 2)
    {
        sprintf(tekst,"Wygrywa gracz czarny");
    }
    if(s == 3)
    {
        sprintf(tekst,"Wygrywa gracz bialy");
    }
    if(s == 4)
    {
        sprintf(tekst,"Remis");
    }
    gtk_label_set_text(powiadomienie, tekst);
}

void koniec_gry()
{
    tura = 'K';
}

void czy_koniec()
{
    int biale = 0;
    int czarne = 0;
    for(int i = 0; i < 64; i++)
    {
        if(tablica[i] == 'b') biale++;
        else if(tablica[i] == 'c') czarne++;
    }
    if(biale == 0)
    {
        wypisz(2);
        koniec_gry();
    }
    if(czarne == 0)
    {
        wypisz(3);
        koniec_gry();
    }
    if(czarne + biale == 64)
    {
        if(czarne > biale) wypisz(2);
        else if(biale > czarne) wypisz(3);
        else wypisz(4);
        koniec_gry();
    }
}

void ustaw_liczniki()
{
    int biale = 0;
    int czarne = 0;
    for(int i = 0; i < 64; i++)
    {
        if(tablica[i] == 'b') biale++;
        else if(tablica[i] == 'c') czarne++;
    }
    gchar tekst[30];
    sprintf(tekst,"Czarne: %d    Biale: %d",czarne, biale);
    gtk_label_set_text(licznik, tekst);
}

void update()
{
    ustaw_liczniki();
    for(int i = 0; i < 64; i++)
    {
        if(tablica[i] == 'c') gtk_image_set_from_file(obrazy[i], "pionek_czarny.jpg");
        else if(tablica[i] == 'b') gtk_image_set_from_file(obrazy[i], "pionek_bialy.jpg");
        else if(tablica[i] == 'n') gtk_image_set_from_file(obrazy[i], "pionek_niebieski.jpg");
        else gtk_image_set_from_file(obrazy[i], "pole.jpg");
    }
}

void show_moves()
{
    char color_good;
    char color_bad;
    int miejsca = 0;
    if(tura == 'B')
    {
        color_good = 'b';
        color_bad = 'c';
    }
    else
    {
        color_good = 'c';
        color_bad = 'b';
    }
    for(int i = 0; i < 64; i++)
    {
        if(tablica[i] == 'p')
        {
            int j = i - 8;
            if(j >= 0 && tablica[j] == color_bad)
            {
                while(j >= 0 && tablica[j] == color_bad) j-= 8;
                if(j >= 0 && tablica[j] == color_good)
                {
                    miejsca++;
                    tablica[i] = 'n';
                }
            }
            j = i + 8;
            if(j <= 63 && tablica[j] == color_bad)
            {
                while(j <= 63 && tablica[j] == color_bad) j+= 8;
                if(j <= 63 && tablica[j] == color_good)
                {
                    miejsca++;
                    tablica[i] = 'n';
                }
            }
            j = i - 1;
            int row = i / 8;
            if(j >= 0 && j / 8 == row && tablica[j] == color_bad)
            {
                while(j >= 0 && j / 8 == row && tablica[j] == color_bad) j -= 1;
                if(j >= 0 && j / 8 == row && tablica[j] == color_good)
                {
                    miejsca++;
                    tablica[i] = 'n';
                }
            }
            j = i + 1;
            if(j < 64 && j / 8 == row && tablica[j] == color_bad)
            {
                while(j < 64 && j / 8 == row && tablica[j] == color_bad) j += 1;
                if(j < 64 && j / 8 == row && tablica[j] == color_good)
                {
                    miejsca++;
                    tablica[i] = 'n';
                }
            }
            j = i + 9;
            if(j < 64 && j % 8 > i % 8 && tablica[j] == color_bad)
            {
                while(j < 64 && j % 8 > i % 8 && tablica[j] == color_bad) j += 9;
                if(j < 64 && j % 8 > i % 8 && tablica[j] == color_good)
                {
                    miejsca++;
                    tablica[i] = 'n';
                }
            }
            j = i - 9;
            if(j >= 0 && j % 8 < i % 8 && tablica[j] == color_bad)
            {
                while(j >= 0 && j % 8 < i % 8 && tablica[j] == color_bad) j -= 9;
                if(j >= 0 && j % 8 < i % 8 && tablica[j] == color_good)
                {
                    miejsca++;
                    tablica[i] = 'n';
                }
            }
            j = i + 7;
            if(j < 64 && j % 8 < i % 8 && tablica[j] == color_bad)
            {
                while(j < 64 && j % 8 < i % 8 && tablica[j] == color_bad) j += 7;
                if(j < 64 && j % 8 < i % 8 && tablica[j] == color_good)
                {
                    miejsca++;
                    tablica[i] = 'n';
                }
            }
            j = i - 7;
            if(j >= 0 && j % 8 > i % 8 && tablica[j] == color_bad)
            {
                while(j >= 0 && j % 8 > i % 8 && tablica[j] == color_bad) j -= 7;
                if(j >= 0 && j % 8 > i % 8 && tablica[j] == color_good)
                {
                    miejsca++;
                    tablica[i] = 'n';
                }
            }
        }
    }
    if(miejsca == 0)
    {
        if(last == -1)
        {
            koniec_gry();
            int biale = 0;
            int czarne = 0;
            for(int i = 0; i < 64; i++)
            {
                if(tablica[i] == 'b') biale++;
                else if(tablica[i] == 'c') czarne++;
            }
            if(biale > czarne) wypisz(3);
            else if(czarne > biale) wypisz(2);
            else wypisz(4);
        }
        else
        {
            if(tura == 'B') tura = 'C';
            else tura = 'B';
            wypisz(1);
        }
        przekaz_tekst(-1);
    }
    update();
}

void zacznij_ture()
{
    if(tura == moj_id[0])
    {
        show_moves();
    }
}

void usun_n()
{
    for(int i = 0; i < 64; i++) if(tablica[i] == 'n') tablica[i] = 'p';
}

void wykonaj_ruch(GtkWidget *widget,gpointer data)
{
    int i = *((int*)data);
    if(tura == moj_id[0] && tablica[i] == 'n')
    {
        char color_good;
        char color_bad;
        if(tura == 'B')
        {
            color_good = 'b';
            color_bad = 'c';
        }
        else
        {
            color_good = 'c';
            color_bad = 'b';
        }
        usun_n();
        int j = i - 8;
        if(j >= 0 && tablica[j] == color_bad)
        {
            while(j >= 0 && tablica[j] == color_bad) j-= 8;
            if(j >= 0 && tablica[j] == color_good)
            {
                while(j <= i)
                {
                    tablica[j] = color_good;
                    j += 8;
                }
            }
        }
        j = i + 8;
        if(j <= 63 && tablica[j] == color_bad)
        {
            while(j <= 63 && tablica[j] == color_bad) j+= 8;
            if(j <= 63 && tablica[j] == color_good)
            {
                while(j >= i)
                {
                    tablica[j] = color_good;
                    j -= 8;
                }
            }
        }
        j = i - 1;
        int row = i / 8;
        if(j >= 0 && j / 8 == row && tablica[j] == color_bad)
        {
            while(j >= 0 && j / 8 == row && tablica[j] == color_bad) j -= 1;
            if(j >= 0 && j / 8 == row && tablica[j] == color_good)
            {
                while(j <= i)
                {
                    tablica[j] = color_good;
                    j += 1;
                }
            }
        }
        j = i + 1;
        if(j < 64 && j / 8 == row && tablica[j] == color_bad)
        {
            while(j < 64 && j / 8 == row && tablica[j] == color_bad) j += 1;
            if(j < 64 && j / 8 == row && tablica[j] == color_good)
            {
                while(j >= i)
                {
                    tablica[j] = color_good;
                    j -= 1;
                }
            }
        }
        j = i + 9;
        if(j < 64 && j % 8 > i % 8 && tablica[j] == color_bad)
        {
            while(j < 64 && j % 8 > i % 8 && tablica[j] == color_bad) j += 9;
            if(j < 64 && j % 8 > i % 8 && tablica[j] == color_good)
            {
                while(j >= i)
                {
                    tablica[j] = color_good;
                    j -= 9;
                }
            }
        }
        j = i - 9;
        if(j >= 0 && j % 8 < i % 8 && tablica[j] == color_bad)
        {
            while(j >= 0 && j % 8 < i % 8 && tablica[j] == color_bad) j -= 9;
            if(j >= 0 && j % 8 < i % 8 && tablica[j] == color_good)
            {
                while(j <= i)
                {
                    tablica[j] = color_good;
                    j += 9;
                }
            }
        }
        j = i + 7;
        if(j < 64 && j % 8 < i % 8 && tablica[j] == color_bad)
        {
            while(j < 64 && j % 8 < i % 8 && tablica[j] == color_bad) j += 7;
            if(j < 64 && j % 8 < i % 8 && tablica[j] == color_good)
            {
                while(j >= i)
                {
                    tablica[j] = color_good;
                    j -= 7;
                }
            }
        }
        j = i - 7;
        if(j >= 0 && j % 8 > i % 8 && tablica[j] == color_bad)
        {
            while(j >= 0 && j % 8 > i % 8 && tablica[j] == color_bad) j -= 7;
            if(j >= 0 && j % 8 > i % 8 && tablica[j] == color_good)
            {
                while(j <= i)
                {
                    tablica[j] = color_good;
                    j += 7;
                }
            }
        }
        set_fresh();
        if(tura == 'B') tura = 'C';
        else tura = 'B';
        przekaz_tekst(i);
        update();
        czy_koniec();
    }
}

void ruch_przeciwnika(int i)
{
    last = i;
    wypisz(0);
    if(i == -1)
    {
        if(tura == 'B') tura = 'C';
        else tura = 'B';
        update();
        zacznij_ture();
        return;
    }
    if(tablica[i] == 'p')
    {
        char color_good;
        char color_bad;
        if(tura == 'B')
        {
            color_good = 'b';
            color_bad = 'c';
        }
        else
        {
            color_good = 'c';
            color_bad = 'b';
        }
        int j = i - 8;
        if(j >= 0 && tablica[j] == color_bad)
        {
            while(j >= 0 && tablica[j] == color_bad) j-= 8;
            if(j >= 0 && tablica[j] == color_good)
            {
                while(j <= i)
                {
                    tablica[j] = color_good;
                    j += 8;
                }
            }
        }
        j = i + 8;
        if(j <= 63 && tablica[j] == color_bad)
        {
            while(j <= 63 && tablica[j] == color_bad) j+= 8;
            if(j <= 63 && tablica[j] == color_good)
            {
                while(j >= i)
                {
                    tablica[j] = color_good;
                    j -= 8;
                }
            }
        }
        j = i - 1;
        int row = i / 8;
        if(j >= 0 && j / 8 == row && tablica[j] == color_bad)
        {
            while(j >= 0 && j / 8 == row && tablica[j] == color_bad) j -= 1;
            if(j >= 0 && j / 8 == row && tablica[j] == color_good)
            {
                while(j <= i)
                {
                    tablica[j] = color_good;
                    j += 1;
                }
            }
        }
        j = i + 1;
        if(j < 64 && j / 8 == row && tablica[j] == color_bad)
        {
            while(j < 64 && j / 8 == row && tablica[j] == color_bad) j += 1;
            if(j < 64 && j / 8 == row && tablica[j] == color_good)
            {
                while(j >= i)
                {
                    tablica[j] = color_good;
                    j -= 1;
                }
            }
        }
        j = i + 9;
        if(j < 64 && j % 8 > i % 8 && tablica[j] == color_bad)
        {
            while(j < 64 && j % 8 > i % 8 && tablica[j] == color_bad) j += 9;
            if(j < 64 && j % 8 > i % 8 && tablica[j] == color_good)
            {
                while(j >= i)
                {
                    tablica[j] = color_good;
                    j -= 9;
                }
            }
        }
        j = i - 9;
        if(j >= 0 && j % 8 < i % 8 && tablica[j] == color_bad)
        {
            while(j >= 0 && j % 8 < i % 8 && tablica[j] == color_bad) j -= 9;
            if(j >= 0 && j % 8 < i % 8 && tablica[j] == color_good)
            {
                while(j <= i)
                {
                    tablica[j] = color_good;
                    j += 9;
                }
            }
        }
        j = i + 7;
        if(j < 64 && j % 8 < i % 8 && tablica[j] == color_bad)
        {
            while(j < 64 && j % 8 < i % 8 && tablica[j] == color_bad) j += 7;
            if(j < 64 && j % 8 < i % 8 && tablica[j] == color_good)
            {
                while(j >= i)
                {
                    tablica[j] = color_good;
                    j -= 7;
                }
            }
        }
        j = i - 7;
        if(j >= 0 && j % 8 > i % 8 && tablica[j] == color_bad)
        {
            while(j >= 0 && j % 8 > i % 8 && tablica[j] == color_bad) j -= 7;
            if(j >= 0 && j % 8 > i % 8 && tablica[j] == color_good)
            {
                while(j <= i)
                {
                    tablica[j] = color_good;
                    j += 7;
                }
            }
        }
        set_fresh();
        if(tura == 'B') tura = 'C';
        else tura = 'B';
        update();
        czy_koniec();
        zacznij_ture();
    }
}

void init_game(GtkWidget *grid)
{
    for(int i = 0; i < 64; i++)
    {
        tablica[i] = 'p';
    }
    tablica[27] = 'b';
    tablica[28] = 'c';
    tablica[35] = 'c';
    tablica[36] = 'b';
    tura = 'C';

    for(int i = 0; i < 64; i++)
    {
        odbicie[i] = i;
        GtkWidget *element;
        GtkWidget *image;
        image = gtk_image_new_from_file("pole.jpg");
        obrazy[i] = GTK_IMAGE(image);
        element = gtk_button_new();
        //element = element.relief = GTK_RELIEF_NONE;
        gtk_button_set_image(GTK_BUTTON(element), image);
        g_signal_connect(G_OBJECT(element), "clicked",G_CALLBACK(wykonaj_ruch), &odbicie[i]);
        tab[i] = element;
        int y = i/8;
        int x = i - y*8;
        gtk_grid_attach(GTK_GRID(grid), element, x, y, 1, 1);
    }
    update();
}

void nowa_gra(GtkWidget *widget)
{
    if(fresh) return;
    for(int i = 0; i < 64; i++) tablica[i] = 'p';
    tablica[27] = 'b';
    tablica[28] = 'c';
    tablica[35] = 'c';
    tablica[36] = 'b';
    tura = 'C';
    update();
    if(get_ostatnia() != -2)przekaz_tekst(-2);
    wyzeruj_ostatnia();
    fresh = true;
    zacznij_ture();
}

void set_fresh()
{
    fresh = false;
}
