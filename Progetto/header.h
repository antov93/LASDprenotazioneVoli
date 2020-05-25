#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct arco
{
    char citta_arrivo[30];
    int distanza;   // peso
    float costo;    // peso
    struct nodo*next_arco;
} arco;

typedef struct vertice
{
    char citta[30];
    struct vertice*next_vertice; // puntatore al prossimo vertice
} vertice;

typedef struct grafo
{
    int nv;        // numero vertici
    vertice*lista; // puntatore al primo vertice
} grafo;


void errore(char messaggio[50])
{
    char testo[60]="Errore : ";
    strcat(testo, messaggio);
    printf("\n%s ", testo);
    exit(0);
}


grafo*nuovo_grafo()  // si alloca un nuovo grafo, senza vertici e senza archi
{
    grafo*g=(grafo*)malloc((sizeof(grafo)));
    if(!g)
        errore("memoria grafo non allocata");
    else
    {
        g->nv=0;
        g->lista=NULL;
    }
    return g;
}

void stampa_grafo(grafo*g)
{
    // da finire
    vertice*tmpV=g->lista;
    while(tmpV)
    {
        printf("\n> %s :", tmpV->citta);
        tmpV=tmpV->next_vertice;
    }
    free(tmpV);
}


//************************************** gestione liste *****************************

//************** vertice *************************
vertice* crea_vertice(char citta[30])
{
    vertice*v=(vertice*)malloc(sizeof(vertice));
    if(!v)
        errore("vertice non creato.");
    else
    {
        v->next_vertice=NULL;
        strcpy(v->citta, citta);
    }
    return v;
}

void inserisci_vertice_in_coda( vertice**testa, vertice*v) // testa<<<<<<
{
    if(!(*testa) )
    {
        *testa=v;
    }
    else
    {
        vertice*tmp=*testa; //<<<<<
        while(tmp->next_vertice)
        {
            tmp=tmp->next_vertice;
        }
        tmp->next_vertice=v;
    }
}

void nuovo_vertice(grafo*g, char citta[30])
{
    vertice*v=crea_vertice(citta);
    if(!v)
        errore("memoria non disponibile.");
    else
    {
        inserisci_vertice_in_coda(&(g->lista) ,v);
        g->nv++;
    }
}


//********************* ARCO ***********************************
arco* crea_arco(char citta_arrivo[30], int distanza, float costo)
{
    arco*a=(arco*)malloc(sizeof(arco));
    if(!a)
        errore("arco non creato.");
    else
    {
        strcpy(a->citta_arrivo, citta_arrivo);
        a->costo=costo;
        a->distanza=distanza;
        a->next_arco=NULL;
    }
    return a;
}

void inserisci_arco_in_coda(arco*n)
{


}


void nuovo_arco(grafo*g,char citta_partenza[30], char citta_arrivo[30], int distanza, float costo)
{

}







