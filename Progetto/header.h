#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>


typedef struct prenotazioni
{
    char citta_partenza[20];
    char citta_arrivo[20];
    struct prenotazioni* next;
} prenotazioni;

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
    int indice_vertice;
    struct vertice*next_vertice; // puntatore al prossimo vertice
    struct arco*next_arco;
} vertice;

typedef struct grafo
{
    int nv;        // numero vertici
    vertice*lista; // puntatore al primo vertice
} grafo;



//*******************************************************************************


void errore(char messaggio[50])
{
    char testo[60]="Errore : ";
    strcat(testo, messaggio);
    printf("\n%s ", testo);
    exit(0);
}

//*******************************************************************************

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
    arco*tmpA;
    printf("\nPartenze:\t\t\tDestinazioni\n\n");
    while(tmpV)
    {
        printf("\n %s :\t\t\t", tmpV->citta);
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
        v->indice_vertice=0;
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
    v->indice_vertice=g->nv;
    if(!v)
        errore("memoria non disponibile.");
    else
    {
        inserisci_vertice_in_coda(&(g->lista),v);
        g->nv++;
    }
}

vertice* cerca_vertice(vertice*lista, char citta[30])  // ?????
{
    vertice*v=lista;
    if(v != NULL && strcmp(v->citta, citta) != 0  ) // non trovato
    {
        v = cerca_vertice(lista->next_vertice, citta);
    }
    return v;
}

vertice* cerca_vertice_con_indice(vertice*lista, int index)
{
    vertice*v=lista;
    if(v != NULL && v->indice_vertice!=index  ) // non trovato
    {
        v = cerca_vertice_con_indice(lista->next_vertice, index);
    }
    return v;
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

void inserisci_arco_in_coda(vertice*vert, arco*a)  //  <<<<<< FUNZIONE SBAGLIATA <<<<<
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

arco* cerca_arco(vertice* v, char citta[])
{
    arco*tmpA;

    if(v)
    {
        tmpA=v->next_arco;
        while(tmpA)
        {
            if(strcmp(tmpA->citta_arrivo,citta)==0)
            {
                return tmpA;
            }
            tmpA=tmpA->next_arco;
        }
    }
}

//******************************************************************************+++

//TRATTA ECONOMICA
char* meta_economica(grafo* g, char citta_partenza[], char* p)
{

    int minimo = 1000.0;
    vertice*tmpV=g->lista;

    tmpV=cerca_vertice(g->lista,citta_partenza);
    if(tmpV != NULL)
    {
        arco*tmpA;
        tmpA=tmpV->next_arco;
        while(tmpA)
        {
            if(minimo > tmpA->costo)
            {
                minimo = tmpA->costo;
                strcpy(p, tmpA->citta_arrivo);
            }
            tmpA=tmpA->next_arco;
        }

        return p;
    }
}

int grado_vertice(grafo*g, char citta[])
{
    vertice*tmpV=g->lista;
    arco*tmpA;
    int occorrenze = 0;
    while(tmpV)
    {
        tmpA=tmpV->next_arco;
        while(tmpA)
        {
            if(strcmp(tmpA->citta_arrivo,citta) == 0)
            {
                occorrenze++;
            }
            tmpA=tmpA->next_arco;
        }
        tmpV=tmpV->next_vertice;
    }
    free(tmpV);
    return occorrenze;
}

/* **********************PRENOTAZIONI***********************************************/
prenotazioni* inizializza_prenotazioni(char citta_partenza[], char citta_arrivo[])
{
    prenotazioni* p = malloc(sizeof(struct prenotazioni));
    strcpy(p->citta_partenza, citta_partenza);
    strcpy(p->citta_arrivo, citta_arrivo);
    p->next = NULL;
    return p;
}

prenotazioni* aggiungi_prenotazione(prenotazioni* p, char citta_partenza[], char citta_arrivo[])
{

    if(p != NULL)
    {
        if (strcmp(p->citta_partenza, citta_partenza) != 0 || strcmp(p->citta_arrivo, citta_arrivo) != 0)
        {
            p->next = aggiungi_prenotazione(p->next, citta_partenza, citta_arrivo);
        }
    }
    else
    {
        p=inizializza_prenotazioni(citta_partenza, citta_arrivo);
    }
    return p;
}

prenotazioni* testa(prenotazioni* p, char citta_partenza[], char citta_arrivo[])
{
    if (p != NULL)
    {
        prenotazioni* G = malloc(sizeof(struct prenotazioni));
        strcpy(p->citta_partenza, citta_partenza);
        strcpy(p->citta_arrivo, citta_arrivo);
        G->next = p;
        return G;
    }
    return inizializza_prenotazioni(citta_partenza, citta_arrivo);
}

prenotazioni* rimuovi_prenotazione(prenotazioni* p, char citta_partenza[], char citta_arrivo[])
{
    if (p != NULL)
    {
        if (strcmp(p->citta_partenza, citta_partenza) != 0 || strcmp(p->citta_arrivo, citta_arrivo) != 0)
        {
            prenotazioni* tmp = p->next;
            free(p);
            return tmp;
        }
        p->next = rimuovi_prenotazione(p,citta_partenza,citta_arrivo);
    }
    return p;
}

void stampa_prenotazioni(prenotazioni* p)
{
    if (p != NULL)
    {
        printf("\ncitta' di partenza: %s\ncitta di arrivo: %s\n", p->citta_partenza, p->citta_arrivo);
        stampa_prenotazioni(p->next);
    }
}

//*****************************PRENOTAZIONI******************************************

int conferma_login(char utente[])
{

    int i=0,j=0;
    FILE *fp;
    char lettura[20][20];
    int dim;

    fp=fopen("Utenti.txt","r"); //apro il file in lettura
    if(fp)
    {
        while(!feof(fp))
        {

            fscanf(fp, "%s", lettura[i]);
            i++;

        }//fine while della lettura file

    }
    else
    {
        printf("Errore apertura file!");
    }//fine controllo esistenza file

    fclose(fp);


    int res = 0;
    dim = i;
    for (i = 0; i < dim; i++) //controllo riga per riga se i dati sono presenti nel file
        if (strcmp(utente, lettura[i]) == 0)
        {
            res = 1;
            return res;
        }

    return res;

}

int conferma_amministratore(char utente[])
{

    int i=0,j=0;
    FILE *fp;
    char lettura[20][20];
    int dim;

    fp=fopen("Amministratori.txt","r"); //apro il file in lettura
    if(fp)
    {
        while(!feof(fp))
        {

            fscanf(fp, "%s", lettura[i]);
            i++;

        }//fine while della lettura file

    }
    else
    {
        printf("Errore apertura file!");
    }//fine controllo esistenza file

    fclose(fp);


    int res = 0;
    dim = i;
    for (i = 0; i < dim; i++) //controllo riga per riga se i dati sono presenti nel file
        if (strcmp(utente, lettura[i]) == 0)
        {
            res = 1;
            return res;
        }

    return res;

}

void registra_utente(char utente[])
{
    FILE *fp;
    fp=fopen("Utenti.txt","a+t"); //apro il file
    if(fp)
    {
        fprintf(fp, "%s %d\n", utente, 0);
    }
    else
    {
        printf("\nErrore nella scrittura del file Utenti.txt!\n");
    }
    fclose(fp);
}


void registra_prenotazione(char utente[], char citta_partenza[], char citta_arrivo[])
{
    FILE *fp;
    fp=fopen("prenotazioni.txt","a"); //apro il file
    if(fp)
    {
        fprintf(fp, "%s %s %s\n", utente, citta_partenza, citta_arrivo);
    }
    else
    {
        printf("\nErrore nella scrittura del file prenotazioni.txt!\n");
    }
    fclose(fp);
}

prenotazioni* attive(char utente[], prenotazioni* p)
{

    int i=0,j=0;
    FILE *fp;
    char lettura[20][20];
    int dim;

    fp=fopen("prenotazioni.txt","r"); //apro il file in lettura
    if(fp)
    {
        while(!feof(fp))
        {
            fscanf(fp, "%s", lettura[i]);
            i++;

        }//fine while della lettura file

    }
    else
    {
        printf("Errore apertura file!");
    }//fine controllo esistenza file

    fclose(fp);

    int res = 0;
    dim = i-1;
    for (i = 0; i < dim; i++)  //controllo riga per riga se i dati sono presenti nel file
    {
        if (strcmp(utente, lettura[i]) == 0)
        {
            p = aggiungi_prenotazione(p,lettura[i+1],lettura[i+2]);
        }
    }

    return p;
}


//**************************************************************************************
// *************************  FUNZIONI PERCORSO MINIMO ********************************

#define INFINITO 999999

//**************************  per il COSTO ***************************************

int get_indice_prossimo_vertice_per_costo(float pesi[], int visitati[],  int lunghezza_array)  //*** trova indce pross vert
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
    return min_index;
}

void rilassa_adiacenti_per_costo(grafo*g, vertice* v, float pesi[], int visitati[]) // OK FUNZIONA
{
    arco*tmpA=v->next_arco;
    visitati[v->indice_vertice]=1;
    vertice*tmpV;

    while(tmpA)
    {
        tmpV=cerca_vertice(g->lista,tmpA->citta_arrivo );
        if(  pesi[tmpV->indice_vertice]  > tmpA->costo + pesi[v->indice_vertice])
            pesi[tmpV->indice_vertice]  = tmpA->costo + pesi[v->indice_vertice];

        tmpA=tmpA->next_arco;
    }

    int index=get_indice_prossimo_vertice_per_costo(pesi, visitati, g->nv);
    if(index<0)
        return;

    vertice*prox_vert=cerca_vertice_con_indice(g->lista, index);
    rilassa_adiacenti_per_costo(g, prox_vert, pesi, visitati);
}


float dijkstra_sp_costo(grafo*g, char citta_partenza[], char citta_arrivo[])
{
    float pesi[g->nv];
    int visitati[g->nv];
    float risultato;
    vertice*v_part=cerca_vertice(g->lista, citta_partenza);
    vertice*v_arr=cerca_vertice(g->lista, citta_arrivo);

    if(!v_part || !v_arr)
        return -2;

    for(int i=0; i<g->nv; i++)
    {
        pesi[i]=INFINITO;
        visitati[i]=0;
    }
    pesi[v_part->indice_vertice]=0;
    visitati[v_part->indice_vertice]=1;

    rilassa_adiacenti_per_costo(g, v_part, pesi, visitati);

    if(pesi[v_arr->indice_vertice] == INFINITO)
        risultato = -1;
    else
        risultato = pesi[v_arr->indice_vertice];

    return risultato;
}

//*************************** per la DISTANZA  ********************************************

int get_indice_prossimo_vertice_per_distanza(int pesi[], int visitati[],  int lunghezza_array)  //*** trova indce pross vert
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
    return min_index;
}


void rilassa_adiacenti_per_distanza(grafo*g, vertice* v, int pesi[], int visitati[]) // OK FUNZIONA
{
    arco*tmpA=v->next_arco;
    visitati[v->indice_vertice]=1;
    vertice*tmpV;

    while(tmpA)
    {
        tmpV=cerca_vertice(g->lista,tmpA->citta_arrivo );
        if(  pesi[tmpV->indice_vertice]  > tmpA->distanza + pesi[v->indice_vertice])
            pesi[tmpV->indice_vertice]  = tmpA->distanza + pesi[v->indice_vertice];

        tmpA=tmpA->next_arco;
    }

    int index=get_indice_prossimo_vertice_per_distanza(pesi, visitati, g->nv);
    if(index<0)
        return;

    vertice*prox_vert=cerca_vertice_con_indice(g->lista, index);
    rilassa_adiacenti_per_distanza(g, prox_vert, pesi, visitati);
}


int dijkstra_sp_distanza(grafo*g, char citta_partenza[], char citta_arrivo[])
{
    int pesi[g->nv];
    int visitati[g->nv];
    int risultato;
    vertice*v_part=cerca_vertice(g->lista, citta_partenza);
    vertice*v_arr=cerca_vertice(g->lista, citta_arrivo);

    if(!v_part || !v_arr)
        return -2;

    for(int i=0; i<g->nv; i++)
    {
        pesi[i]=INFINITO;
        visitati[i]=0;
    }
    pesi[v_part->indice_vertice]=0;
    visitati[v_part->indice_vertice]=1;

    rilassa_adiacenti_per_distanza(g, v_part, pesi, visitati);

    if(pesi[v_arr->indice_vertice] == INFINITO)
        risultato = -1;
    else
        risultato = pesi[v_arr->indice_vertice];

    return risultato;
}


//********************************* FILE ***************************************
void leggi_file_vertici(grafo*g)
{
    char citta[30];
    FILE*fp=fopen("Vertici.txt", "r");
    if(!fp)
        errore("impossibile aprire il file vertici.");

    while(!feof(fp))
    {
        fscanf(fp, "%s\n", &citta);
        nuovo_vertice(g, citta);
    }
    fclose(fp);
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
        fscanf(fp, "%30s %30s %d %f\n", citta_partenza,citta_arrivo, &distanza, &costo  );
        nuovo_arco(g, citta_partenza, citta_arrivo, distanza, costo );
    }
    fclose(fp);
}


//******************************* FUNZIONI UTILI  *********************************

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
    printf("\n\n");
    system("PAUSE");
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


float richiedi_float()
{
    float valore;
    while(scanf("%f", &valore)!= 1)
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

//***********************************************************************************
//*************************  lato amministratore ************************************

void nuova_tratta(grafo*g)
{
    char citta_partenza[30], citta_arrivo[30];
    int distanza;
    float costo;

    printf("\nInserire citta' di partenza : ");
    richiedi_nome_citta(citta_partenza);
    printf("\nInserire citta' di arrivo : ");
    richiedi_nome_citta(citta_arrivo);
    printf("\nInserire distanza : ");
    distanza=richiedi_intero();
    printf("\nInserire costo : ");
    costo=richiedi_float();

    nuovo_arco(g, citta_partenza, citta_arrivo, distanza, costo);

}

void nuova_citta(grafo*g)
{
    char nome_citta[30];
    printf("\nInserire nome citta' : ");
    richiedi_nome_citta(nome_citta);

    nuovo_vertice(g, nome_citta);
}

//**************************************************************************************

void incrementa_punteggio(char username[], float costo)
{
    int i=0;
    FILE *fp;
    char lettura[20][20];
    int dim; //dimensione file


    fp=fopen("Utenti.txt","r"); //apro il file in lettura
    if(fp)
    {
        while(!feof(fp))
        {

            fscanf(fp, "%s", lettura[i]);
            i++;
        }//fine while della lettura file

    }
    else
    {
        printf("Errore apertura file!");
    }//fine controllo esistenza file

    fclose(fp);

    dim = i-1;
    fp=fopen("Utenti.txt","w"); //apro il file
    if(fp)
    {
        for(i=0; i<dim; i=i+2)
        {
            if(strcmp(username,lettura[i])==0)
            {
                fprintf(fp, "%s %d\n", lettura[i], (atoi(lettura[i+1])) + (int)costo);
            }
            else
            {
                fprintf(fp, "%s %s\n", lettura[i], lettura[i+1]);
            }
        }
    }
    else
    {
        printf("\nErrore nella scrittura del file Utenti.txt!\n");
    }
    fclose(fp);
}

void decrementa_punteggio(char username[], float costo)
{
    int i=0;
    FILE *fp;
    char lettura[20][20];
    int dim; //dimensione file

    fp=fopen("Utenti.txt","r"); //apro il file in lettura
    if(fp)
    {
        while(!feof(fp))
        {

            fscanf(fp, "%s", lettura[i]);
            i++;
        }//fine while della lettura file

    }
    else
    {
        printf("Errore apertura file!");
    }//fine controllo esistenza file

    fclose(fp);

    dim = i-1;
    fp=fopen("Utenti.txt","w"); //apro il file
    if(fp)
    {
        for(i=0; i<dim; i=i+2)
        {
            if(strcmp(username,lettura[i])==0)
            {
                fprintf(fp, "%s %d\n", lettura[i], (atoi(lettura[i+1])) - (int)costo);
            }
            else
            {
                fprintf(fp, "%s %s\n", lettura[i], lettura[i+1]);
            }
        }
    }
    else
    {
        printf("\nErrore nella scrittura del file Utenti.txt!\n");
    }
    fclose(fp);
}

int punteggio_corrente(char utente[])
{
    int i=0;
    FILE *fp;
    char lettura[20][20];
    int dim; //dimensione file

    fp=fopen("Utenti.txt","r"); //apro il file in lettura
    if(fp)
    {
        while(!feof(fp))
        {

            fscanf(fp, "%s", lettura[i]);
            i++;
        }//fine while della lettura file

    }
    else
    {
        printf("Errore apertura file!");
    }//fine controllo esistenza file

    fclose(fp);

    dim = i-1;
    for(i=0; i<dim; i=i+2)
    {
        if(strcmp(utente,lettura[i])==0)
        {
            return atoi(lettura[i+1]);
        }
    }
}


//******************************************************************************************************
//******************************************************************************************************
