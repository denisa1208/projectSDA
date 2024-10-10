/*CIOBANU Denisa-Cristina - grupa 311CB*/
#include <stdio.h>
#include <stdlib.h>
#include "functii_trenulet.h"
#include "functii_coada.h"
#include <string.h>
int main() 
{
    FILE *f;
    f = fopen("tema1.in", "r");
    FILE *o;
    o = fopen("tema1.out", "w");
    if(f == NULL) {
        return 0;
    }
    /*initializare coada*/
    TCoada *c;
    //c = malloc(sizeof(TListaC));
    //if (!c) return 0;
    c = InitQ();
    if (!c) return 0;
    TTren *T;
    T = malloc(sizeof(TLista));
    if (!T) return 0;
    T->s = InitL();

    /*alocare spatiu mecanic*/
    // T->p = (TLista)malloc(sizeof(TCelula));

    Constr_vagon1(T);
    int n;
    fscanf(f, "%d\n", &n);
    char s[256];
    int  i = 0;
    for (i = 0; i < n; i++) {
        fscanf(f, "%s", s);
        if (s[0] == 'W') {
            /*comanda WRITE*/
            char x = ' ';
            fscanf(f, "%c", &x);
            char *y;
            y = malloc(10 * sizeof(char));
            fscanf(f, "%s", y);
            int a = IntrQ(c, 10, y);
            (void) a;
            free(y);
        } else if (s[0] == 'M' && s[5] == 'R') {
            /*comanda MOVE_RIGHT*/
            int a = IntrQ(c, 2, " ");
            (void) a;
        } else if (s[0] == 'M' && s[5] == 'L') {
            /*comanda MOVE_LEFT*/
            int a = IntrQ(c, 1, " ");
            (void) a;
        } else if (s[0] == 'I' && s[7] == 'R') {
            /*comanda INSERT_RIGHT*/
            char x = ' ';
            fscanf(f, "%c", &x);
            char *y;
            y = malloc(10 * sizeof(char));
            fscanf(f, "%s", y);
            int a = IntrQ(c, 4, y);
            (void) a;
            free(y);
        } else if (s[0] == 'I' && s[7] == 'L') {
            char x = ' ';
            fscanf(f, "%c", &x);
            char *y;
            y = malloc(10 * sizeof(char));
            fscanf(f, "%s", y);
            int a = IntrQ(c, 3, y);
            (void) a;
            free(y);
        } else if (s[0] == 'S' && strlen(s) == 6 && s[1] == 'E') {
            /*comanda SEARCH*/
            char x = ' ';
            fscanf(f, "%c", &x);
            char *y;
            y = malloc(10 * sizeof(char));
            fscanf(f, "%s", y);
            int a = IntrQ(c, 7, y);
            (void) a;
            free(y);
        } else if (s[0] == 'S' && strlen(s) == 11 && s[7] == 'L') {
            /*comanda SEARCH_LEFT*/
            char x = ' ';
            fscanf(f, "%c", &x);
            char *y;
            y = malloc(10 * sizeof(char));
            fscanf(f, "%s", y);
            int a = IntrQ(c, 8, y);
            (void) a;
            free(y);

        } else if (s[0] == 'S' && strlen(s) == 12 && s[7] == 'R' && s[6] == '_') {
            /*comanda SEARCH_RIGHT*/
            char x = ' ';
            fscanf(f, "%c", &x);
            char *y;
            y = malloc(10 * sizeof(char));
            fscanf(f, "%s", y);
            int a = IntrQ(c, 9, y);
            (void) a;
            free(y);
        } else if (s[0] == 'C' && strlen(s) == 9) {
            /*comanda CLEAR_ALL*/
            int a = IntrQ(c, 6, " ");
            (void) a;
        } else if (s[0] == 'C' && strlen(s) == 10) {
            /*comanda CLEAR_CELL*/
            int a = IntrQ(c, 5, " ");
            (void) a;
        } else if (s[0] == 'E') {
            /*comanda EXECUTE*/
            if (c->inc->info == 10) {
               char x = c->inc->inf[0];
               Scrie(T, x);
               int e = ExtrQ(c);
               (void) e;
            } else if (c->inc->info == 2) {
                Muta_dreapta(T);
                int e = ExtrQ(c);
                (void) e;
            } else if (c->inc->info == 1) {
                Muta_stanga(T);
                int e = ExtrQ(c);
                (void) e;
            } else if (c->inc->info == 4) {
                char x = c->inc->inf[0];
                Inserare_dreapta(T, x);
                int e = ExtrQ(c);
                (void) e;
            } else if (c->inc->info == 3) {
                char x = c->inc->inf[0];
                Inserare_stanga(T, x, o);
                int e = ExtrQ(c);
                (void) e;
            } else if (c->inc->info == 7) {
                char *s;
                s = malloc(10 * sizeof(char));
                strcpy(s, c->inc->inf);
                Cauta(T, s, o);
                int e = ExtrQ(c);
                (void) e;
            } else if (c->inc->info == 8) {
                /*comanda SEARCH_LEFT*/
                char *s;
                s = malloc(10 * sizeof(char));
                int i = 0;
                while (c->inc->inf[i] != '\0') {
                    s[i] = c->inc->inf[i];
                    i++;
                }
                s[i] = '\0';
                Cauta_stanga(T, s, o);
                int e = ExtrQ(c);
                (void) e;

            }  else if (c->inc->info == 9) {
                /*comanda SEARCH_RIGHT*/
                char *s;
                s = malloc(10 * sizeof(char));
                int i = 0;
                while (c->inc->inf[i] != '\0') {
                    s[i] = c->inc->inf[i];
                    i++;
                }
                s[i] = '\0';
                Cauta_dreapta(T, s, o);
                int e = ExtrQ(c);
                (void) e;
                free(s);

            } else if (c->inc->info == 6) {
                /*comanda CLEAR_ALL*/
                Sterge_vagoane(&T);
                int e = ExtrQ(c);
                (void) e;
            } else if (c->inc->info == 5) {
                /*comanda CLEAR_CELL*/
                Sterge_vagon(T);
                int e = ExtrQ(c);
                (void) e;
            }

        } else if (s[0] == 'S' && strlen(s) == 4) {
            Afiseaza(T, o);
        } else if (s[0]== 'S' && s[4] == '_' && s[11] == 'T') {
            /*comanda SHOW_CURRENT*/
            Afiseaza_mecanic(T, o);
        } else if (strcmp(s, "SWITCH") == 0) {
            /*comanda SWITCH*/
            TCoada *aux = Inversare_coada(c);
            c = InitQ();
            c = aux;
        }
    }
    //Afiseaza_mecanic(T);
    //Afiseaza(T);
    // free(c);
    fclose(f);
    fclose(o);


    return 0;
}