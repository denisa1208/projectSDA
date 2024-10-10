/*CIOBANU Denisa-Cristina - grupa 311CB*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celulaC
{ 
  int info;
  char inf[10];
  struct celulaC *urm, *ant;
} TCelulaC, *TListaC;

typedef struct coada
{ 
  TListaC sf, inc;       /* adresa ultimei celule */
} TCoada;

TCoada* InitQ();
int IntrQ(TCoada *c, int x, char *s);
void AfisareQ(TCoada *c, FILE *o);
int ExtrQ(TCoada *c);
TCoada* Inversare_coada(TCoada *c);
int Eliminare_sf_coada(TCoada *c);

