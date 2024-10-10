/*CIOBANU Denisa-Cristina - grupa 311CB*/
#include "functii_trenulet.h"
#include <string.h>
/*construire lista vida cu santinela*/
TLista InitL() 
{
    TLista s;
    s = (TLista)malloc(sizeof(TCelula));
    if (!s) return NULL;
    s->info = '0';
    s->urm = s;
    s->ant = s;
    return s;
}

TLista Inserare_vagon(TTren *T, char x) 
{
    TLista vagon;
    vagon = (TLista)malloc(sizeof(TCelula));
    if (vagon) {
        vagon->info = x;
        vagon->ant = NULL;
        vagon->urm = NULL;
        vagon->urm = T->p->urm;
        T->p->urm->ant = vagon;
        vagon->ant = T->p;
        T->p->urm = vagon;
    }
    return vagon;
}

void Constr_vagon1(TTren *T)
{
        TLista vagon;
        vagon = (TLista)malloc(sizeof(TCelula));
        if (vagon) {
            vagon->ant = NULL;
            vagon->urm = NULL;
            vagon->info = '#';
            vagon->urm = T->s->urm;
            T->s->urm->ant = vagon;
            vagon->ant = T->s;
            T->s->urm = vagon;
        }
        T->p = vagon;
        //return vagon;
}

void Muta_stanga(TTren *T)
{
    /*daca mecanicul e in primul vagon, il mutam in ultimul*/
    if (T->p == T->s->urm) {
        T->p = T->s->ant;
    } else {
        T->p = T->p->ant;
    }
}

void Muta_dreapta(TTren *T) 
{
    /*daca mecanicul e in ultimul vagon, mai cuplam inca unul*/
    if (T->p == T->s->ant) {
        T->p = Inserare_vagon(T, '#');
        //T->p = T->s->ant;
    } else {
        T->p = T->p->urm;
    }
}

// scriem x in celula MECANICULUI
void Scrie(TTren *T, char x)
{
    T->p->info = x;
}

void Inserare_stanga(TTren *T, char x, FILE *o) 
{
    /*daca mecanicul se afla in primul vagon, eroare*/
    if (T->p == T->s->urm) {
        fprintf(o, "ERROR\n");
    } else {
        TLista vagon;
        vagon = (TLista)malloc(sizeof(TCelula));
        TLista aux;
        aux = T->p->ant;
        if (vagon) {
            vagon->info = x;
            vagon->ant = NULL;
            vagon->urm = NULL;
            vagon->urm = aux->urm;
            aux->urm->ant = vagon;
            vagon->ant = aux;
            aux->urm = vagon;
        }
        T->p = T->p->ant;
    }
}

void Inserare_dreapta(TTren *T, char x) 
{
    Inserare_vagon(T, x);
    T->p = T->p->urm;
}

int nr_vagoane(TTren *T)
{
    TLista aux = T->s->urm;
    int nr = 0;
    while (aux != T->s) {
        nr++;
        aux = aux->urm;
    }
    return nr;
}

int Cauta(TTren *T, char *s, FILE *o) 
{
/*returneaza 1 daca a gasit, respectiv 0 daca nu a gasit sirul*/
    TLista aux = T->p;
    int nr_vag = nr_vagoane(T);
    int nr = 1;
    while (nr <= nr_vag) {
        if (aux->info != s[0]) {
            aux = aux->urm;
            if (aux == T->s) {
                aux = aux->urm;
            }
        } else {
            TLista aux1 = aux;
            int i = 0;
            int n = strlen(s);
            int cp_nr = nr;
            while (aux->info == s[i] && cp_nr <= nr_vag && i <= n) {
                cp_nr++;
                i++;
                aux = aux->urm;
                if (aux == T->s) {
                    aux = aux->urm;
                }
            }
            if (i == n) {
                T->p = aux1;
                return 1;
            } else {
                aux = aux1->urm;
            }
        }
        if (aux == T->s) {
            aux = aux->urm;
        }
        nr++;
    }
    fprintf(o, "ERROR\n");
    return 0;
}

int Cauta_dreapta(TTren *T, char *s, FILE *o) 
{
    
    TLista aux = T->p;
    while (aux != T->s) {
        if (aux->info != s[0]) {
            aux = aux->urm;
        } else {
            int i = 0;
            int n = strlen(s);
            while (aux->info == s[i] && aux != T->s) {
                i++;
                aux = aux->urm;
            }
            if (i == n) {
                T->p = aux->ant;
                return 1;
            } else {
                if  (aux == T->s) {
                    fprintf(o, "ERROR\n");
                    return 0;
                } else {
                    aux = aux->urm;
                }
            }
        }
    }
    fprintf(o, "ERROR\n");
    return 0;
}

int Cauta_stanga(TTren *T, char *s, FILE *O) 
{
    TLista aux = T->p;
    int n = strlen(s);
    while (aux != T->s) {
        if (aux->info != s[0]) {
            aux = aux->ant;
        } else {
            int i = 0;
            while (aux->info == s[i] && aux != T->s) {
                i++;
                aux = aux->ant;
            }
            if (i == n) {
                T->p = aux->urm;
                return 1;
            } else {
                if (aux == T->s) {
                    fprintf(O, "ERROR\n");
                    return 0;
                } else {
                    aux = aux->ant;
                }
            }
        }
    }
    fprintf(O, "ERROR\n");
    return 0;
}

void Sterge_vagoane(TTren **T) /* decuplarea tuturor vagoanelor */
{
    TLista ant = (*T)->s->urm;
    while(ant != (*T)->s) {
        (*T)->s->urm = ant->urm;
        free(ant);
        ant = (*T)->s->urm;
    }
    free(ant);

    (*T)->s = InitL();
    (*T)->p = malloc(sizeof(TCelula));
    Constr_vagon1(*T);
    // printf("%c\n", (*T)->p->info);
}

void Sterge_vagon(TTren *T) {

    TLista aux = T->p;
    if (nr_vagoane(T) > 1) {
        /*daca mecanicul nu se afla in primul vagon al trenului*/
        if (T->p->ant != T->s) {
            T->p = T->p->ant;
        } else {
            /*mutam mecanicul in ultimul vagon*/
            T->p = T->s->ant;
        }
        aux->ant->urm = aux->urm;
        aux->urm->ant = aux->ant;
        free(aux);
    } else {
        /*daca avem un singur vagon, initializam trenul*/
            Sterge_vagoane(&T);
        }

}

void Afiseaza(TTren *T, FILE *O)
{
    // daca lista e vida
    TLista p;
    // if (!p) return;
    p = T->s;
    while (p->urm != T->s) {
        if (p != T->s) {
            if (p != T->p) {
                fprintf(O, "%c", p->info);
                p = p->urm;
            } else {
                fprintf(O, "|%c|", p->info);
                p = p->urm;
            }

        } else p = p->urm;

    }
    if (p != T->s) {
        if (p != T->p) {
            fprintf(O, "%c", p->info);
        } else {
            fprintf(O, "|%c|", p->info);
        }
    }
    //fprintf(o, "\n");
    fprintf(O, "\n");

}

void Afiseaza_mecanic(TTren *T, FILE *o) 
{
    fprintf(o, "%c\n", T->p->info);
}

int Comparare(char *s, char *c) 
{
/*return 0 daca sunt egale si 1 daca nu 0*/
    int i = 0;
    while (s[i] == c[i] && i < strlen(s)) {
        i++;
    }
    if (i == strlen(s) - 1) return 0;
    return 1;
}