/*CIOBANU Denisa-Cristina - grupa 311CB*/
#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
    char info;
    struct celula *ant, *urm;

}TCelula, *TLista;

typedef struct sant_mec {
    TLista s;
    TLista p;

}TTren;

TLista InitL();
void Afiseaza(TTren *T, FILE *o);
void Constr_vagon1(TTren *T);
void Scrie(TTren *T, char x);
TLista Inserare_vagon(TTren *T, char x);
void Muta_stanga(TTren *T);
void Muta_dreapta(TTren *T);
void Inserare_stanga(TTren *T, char x, FILE *O);
void Inserare_dreapta(TTren *T, char x);
void Afiseaza_mecanic(TTren *T, FILE *o);
int Cauta(TTren *T, char *s, FILE *o);
int Cauta_dreapta(TTren *T, char *s, FILE *o);
int nr_vagoane(TTren *T);
int Cauta_stanga(TTren *T, char *s, FILE *O);
void Sterge_vagoane(TTren **T);
int Comparare(char *s, char *c);
void Sterge_vagon(TTren *T);

