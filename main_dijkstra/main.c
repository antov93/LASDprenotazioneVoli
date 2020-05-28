#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"header.h"



void stampa_menu()
{
    printf("\nSELEZIONA UN OPZIONE\n");
    printf("\n1.Visualizza i voli");
    printf("\n2.Visualizza le prenotazioni attive");
    printf("\n3.Effettua una nuova prenotazione");
    printf("\n4.ESCI\n");
}

void inizializza(grafo* g)
{
    leggi_file_vertici(g);
    leggi_file_archi(g);
}

void continua()
{
    char tasto;
    printf("\n\nPremere un tasto per continuare...\n");
    scanf("%s",&tasto);
    system("cls");
}

char* normalizza_parola(char* p)
{

    p[0] = toupper(p[0]);
    for(int i=1; i<strlen(p); i++)
    {
        p[i] = tolower(p[i]);
    }

    return p;
}





int richiedi_intero()
{
    int valore;
    while(scanf("%d", &valore)!= 1)
    {
        printf("\nValore non valido. Inserirne un altro.");
        fflush(stdin);
    }
    return valore;
}

void richiedi_nome_citta(char nome[])
{
    printf("\n> ");
    scanf("%29s",nome );
    normalizza_parola(nome);
}

char richiedi_Y_N()
{
    char scelta;
    do
    {
        fflush(stdin);
        printf("\n\nY=yes\nN=no\n> ");
        scelta=getchar();
        scelta=toupper(scelta);
        if(scelta!='Y' && scelta!='N')
            printf("Non valido.");

    }
    while(scelta!='Y' && scelta!='N');

    return scelta;
}

//************************************************************************+
vertice* cerca_vertice_con_indice(grafo*g, int index)
{
    vertice*v=NULL;
    vertice*tmp=g->lista;
    while(tmp)
    {
        if(tmp->indice_vertice==index)
        {
            v=tmp;
            break;
        }
        tmp=tmp->next_vertice;
    }
    return v;
}



vertice* cerca_vertice_con_indice_ricorsiva(vertice*lista, int index)
{
    vertice*v=lista;
    if(v != NULL && v->indice_vertice!=index  ) // non trovato
    {
        v = cerca_vertice_con_indice_ricorsiva(lista->next_vertice, index);
    }
    return v;
}


//**********************************************************
void stampa_array(int array[], int lungh)  // OK
{
    printf("\n -> ");
    for(int i=0; i<lungh; i++)
    {
        printf("%d ", array[i]);
    }
}
//**************************************************************+


int get_indice_prox_vertice(int pesi[], int visitati[],  int lunghezza_array)  //*** trova indce pross vert
{
    int min_index=-1;
    for(int i=0; i<lunghezza_array; i++)
    {
        if(visitati[i] == 0)
        {
            if(min_index == -1 )
            {
                min_index=i;
                continue;
            }
            if(pesi[i] < pesi[min_index])
            {
                min_index=i;
            }
        }
    }
    printf("\nProssimo Indice : %d ", min_index);
    return min_index;
}

void minimizza_adiacenti(grafo*g, vertice* v, int pesi[], int visitati[]) // OK FUNZIONA
{
    printf("\n****** MINIMIZZA **************\nNome citta : %s ", v->citta);
    arco*tmpA=v->next_arco;
    visitati[v->indice_vertice]=1;
    vertice*tmpV;

    printf("\nARRAY -VISITATI ");
    stampa_array(visitati,g->nv);
    while(tmpA)
    {
        tmpV=cerca_vertice(g->lista,tmpA->citta_arrivo );
        if(  pesi[tmpV->indice_vertice]  > tmpA->costo + pesi[v->indice_vertice])
        {
            pesi[tmpV->indice_vertice]  = tmpA->costo + pesi[v->indice_vertice];
        }
        tmpA=tmpA->next_arco;
    }

    printf("\n-PESI -");
    stampa_array(pesi, g->nv);
    system("PAUSE");

    int index=get_indice_prox_vertice(pesi, visitati, g->nv);
    if(index<0)
    {
        printf("\n index < 0 ");
        return;
    }
    vertice*prox_vert=cerca_vertice_con_indice_ricorsiva(g->lista, index);
    minimizza_adiacenti(g, prox_vert, pesi, visitati);


}


int prova_dijkstra(grafo*g, char citta_partenza[], char citta_arrivo[])
{
#define INFINITO 999999
    vertice*v_part=cerca_vertice(g->lista, citta_partenza);
    vertice*v_arr=cerca_vertice(g->lista, citta_arrivo);

    if(!v_part)
    {
        printf("\nLa citta di destinazione non e' presente.");
        return -2;
    }
    if(!v_arr)
    {
        printf("\nLa citta di destinazione non e' presente.");
        return -2;
    }

    int pesi[g->nv];
    int visitati[g->nv];
    int costo=0;

    for(int i=0; i<g->nv; i++)
    {
        pesi[i]=INFINITO;
        visitati[i]=0;
    }
    pesi[v_part->indice_vertice]=0;
    visitati[v_part->indice_vertice]=1;


    minimizza_adiacenti(g, v_part, pesi, visitati);
    printf("\n * * * FINE DIJKSRTRA * * * \n");
    system("PAUSE");

    int result;

    if(pesi[v_arr->indice_vertice] == INFINITO)
    {
        printf("\n* Nessuna tratta disponibile");
        result= -1;
    }
    else
    {
        result=pesi[v_arr->indice_vertice];
    }

    return result;

}
//**************************
void main()
{
    int scelta;
    char scelta_Y_N;
    char citta_partenza[30];
    char citta_arrivo[30];
    char citta_economica[30]; // ???
    char* p;   // ????

    grafo*g=nuovo_grafo();
    inizializza(g);

    stampa_grafo(g);

    printf("\n... calcolo ...\n");


    int peso=prova_dijkstra(g, "Napoli", "York");
    printf("\n********************** risultato ***********************\n");
    switch(peso)
    {
    case(-2):
        printf("\n* * * Errore nell inserire i nomi o citta inesistenti");
        break;
    case -1:
        printf("\n> > >Nessuna tratta disponibile verso destinazione ");
        break;
    default:
        printf("\n-> Il costo minimo per la tratta e' : %d ", peso);
    }

    printf("\n\n*********************************************************\n");



}

