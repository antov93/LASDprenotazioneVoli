#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//************************ tipi*********************************
typedef struct arco
{
    char citta_arrivo[30];
    int distanza;   // peso
    float costo;    // peso
    struct arco*next_arco;
} arco;

typedef struct vertice
{
    char citta[30];
    struct vertice*next_vertice; // puntatore al prossimo vertice
    struct arco*next_arco;
} vertice;

typedef struct grafo
{
    int nv;        // numero vertici
    vertice*lista; // puntatore al primo vertice
} grafo;

typedef struct utente
{
    char username[20];
    char password[20];
    int punti;
    char nome[20];
    char cognome[20];

} utente;


//***************************** PROTOTIPI   *****************************************



void nuovo_arco(grafo*g,char citta_partenza[30], char citta_arrivo[30], int distanza, float costo);





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
    vertice*tmpV=g->lista;
    arco*tmpA;
    printf("\nPartenze:\t\t\tDestinazioni\n\n");
    while(tmpV)
    {
        printf("\n %-30s ", tmpV->citta);
        tmpA=tmpV->next_arco;
        while(tmpA)
        {
            printf("> %s ", tmpA->citta_arrivo);
            tmpA=tmpA->next_arco;
        }
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
        v->next_arco=NULL;
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
        vertice*tmp=*testa;     //<<<<<
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
        inserisci_vertice_in_coda(&(g->lista),v);
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

void inserisci_arco_in_coda(vertice*vert, arco*a)
{
    if(vert->next_arco == NULL )
    {
        vert->next_arco=a;
    }
    else
    {
        arco*tmp=vert->next_arco;
        while(tmp->next_arco)
        {
            tmp=tmp->next_arco;
        }
        tmp->next_arco=a;
    }

}

vertice* cerca_vertice(vertice*lista, char citta[30])
{
    vertice*v=lista;
    if(v != NULL && strcmp(v->citta, citta) != 0  ) // non trovato
    {
        v = cerca_vertice(lista->next_vertice, citta);
    }
    return v;
}

void nuovo_arco(grafo*g,char citta_partenza[30], char citta_arrivo[30], int distanza, float costo)
{
    // FARE CONTROLLI
    arco*a=crea_arco(citta_arrivo, distanza, costo);
    if(!a)
    {
        errore("memoria non disponibile.");
    }
    else
    {
        vertice*vert=cerca_vertice(g->lista, citta_partenza);
        inserisci_arco_in_coda( vert, a );
    }

}
<<<<<<< HEAD

//TRATTA ECONOMICA
grafo* tratta_economica(grafo* g, char citta_partenza[])
{

}



//******************************* FILE *******************************

void leggi_file_vertici(grafo*g)
{
    char citta[30];
    FILE*fp=fopen("Vertici.txt", "r");
    if(!fp)
        errore("impossibile aprire il file vertici.");

    while(!feof(fp))
    {
        fscanf(fp, "%30s\n", &citta);
        nuovo_vertice(g, citta);
    }
    fclose(fp);
=======

//TRATTA ECONOMICA
char* meta_economica(grafo* g, char citta_partenza[], char* p){

    int minimo = 1000.0;
    vertice*tmpV=g->lista;

    tmpV=cerca_vertice(g->lista,citta_partenza);
    if(tmpV != NULL){
        arco*tmpA;
        tmpA=tmpV->next_arco;
            while(tmpA)
            {
                if(minimo > tmpA->costo){
                    minimo = tmpA->costo;
                    strcpy(p, tmpA->citta_arrivo);
                }
                tmpA=tmpA->next_arco;
            }

            return p;
    }
>>>>>>> 297c391fe0b2717eec63c3ffa26d4d82fd820ce1
}


void leggi_file_archi(grafo*g)
{
    int distanza;
    float costo;
    char citta_partenza[30], citta_arrivo[30];
    FILE*fp=fopen("Archi.txt", "r");
    if(!fp)
        errore("impossibile aprire il file archi.");
    while(!feof(fp))
    {
        fscanf(fp, "%30s %30s %f %d\n", citta_partenza ,citta_arrivo, &costo, &distanza );
        nuovo_arco(g, citta_partenza, citta_arrivo, distanza, costo );
    }
    fclose(fp);
}

void leggi_file_utenti(char username[], char password[])
{

}



