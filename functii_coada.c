/*CIOBANU Denisa-Cristina - grupa 311CB*/
#include <string.h>
#include "functii_coada.h"


TCoada* InitQ ()  /* creeaza coada vida */
{
  TCoada* c;          /* spatiu pentru descriptor coada */
  c = (TCoada*)malloc(sizeof(TCoada));
  if ( ! c ) return NULL;     /* nu exista spatiu -> "esec" */

  c->sf = NULL;
  c->inc = NULL;
  return c;   /* intoarce adresa descriptorului cozii */
}

int IntrQ(TCoada *c, int x, char *s)  /* adauga element la sfarsitul cozii */
 /* intoarce 1: operatie reusita, 0: in caz contrar */
{
  TListaC aux = (TListaC)malloc(sizeof(TCelulaC));
  if (!aux) return 0;

  if (c->inc == NULL) {
    aux->info = x;
    //printf("%s", aux->info);
    int i = 0;
    while(s[i] != '\0') {
      aux->inf[i] = s[i];
      i++;
    }
    aux->inf[i] = '\0';
    aux->urm = NULL;
    c->inc = aux;
    c->sf = aux;
  } else {
    aux->info = x;
    int i = 0;
    while (s[i] != '\0') {
      aux->inf[i] = s[i];
      i++;
    }
    aux->inf[i] = '\0';
    aux->urm = NULL;
    aux->ant = c->sf;
    c->sf->urm = aux;
    c->sf = aux;
  }

  return 1;             
}

void AfisareQ(TCoada *c, FILE *o)  /* afisare elementele cozii */
{ 
  if (c->sf == NULL) {
    return;
  } 
  TListaC p;
  p = c->inc;
  while(p != c->sf) {
    fprintf(o, "%d", p->info);
    p = p->urm;
  }
  fprintf(o, "%d", p->info);
}

int ExtrQ(TCoada *c)  /* extrage primul element din coada la adresa ae */
/* intoarce 1: operatie reusita, 0: in caz contrar */
{
  TListaC aux = NULL;
  if (c->sf == NULL) return 0;
  aux = c->inc;
  if (c->inc != c->sf) {
    c->inc = aux->urm;
    aux->urm = NULL;
    free(aux);
  } else {
    c->inc = NULL;
    c->sf = NULL;
    free(aux);
  }

  return 1;                   
}

int Eliminare_sf_coada(TCoada *c) 
{
  TListaC aux = NULL;
  if (c->inc == NULL) return 0;
  aux = c->sf;
  if (aux != c->inc) {
    c->sf = aux->ant;
    aux->ant = NULL;
    free(aux);
  } else {
    c->inc = NULL;
    c->sf = NULL;
    free(aux);
  }
  return 1;
}

TCoada* Inversare_coada(TCoada *c) {
  TCoada* coada_inversata;
  coada_inversata= InitQ();
  if (!coada_inversata) return 0;

  while (c->sf != NULL) {
    IntrQ(coada_inversata, c->sf->info, c->sf->inf);
    int d = Eliminare_sf_coada(c);
    (void) d;
  }
  return coada_inversata;
}