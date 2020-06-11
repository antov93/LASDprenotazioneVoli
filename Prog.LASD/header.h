#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define INFINITO 999999
#define ADMIN 1
#define USER 2
#define SIGN_IN 3

//********************************* TIPI **************************************
typedef struct prenotazione
{
    char username[30];
    char citta_partenza[30];
    char citta_arrivo[30];
    struct prenotazione* next;
} prenotazione;

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

typedef struct utente
{
    char username[20];
    char password[20];
    int punti;
    struct utente*dx, *sx;
    struct prenotazione*lista_prenotazioni;
} utente;

//***************************************  PROTOTIPI  *************************************

void stampa_vettore(int*v, int lungh);
void stampa_menu_amministratore();
void stampa_menu_utente(utente*u);
void stampa_menu_iniziale();
void errore(char messaggio[50]);
void continua();
void normalizza_parola(char* p);
int richiedi_intero();
float richiedi_float();
void richiedi_nome_citta(char nome[]);
void pulisci_schermo();
void attendi();

grafo*nuovo_grafo();
void stampa_grafo(grafo*g);
void inizializza(grafo* g);

vertice* crea_vertice(char citta[30]);
void inserisci_vertice_in_coda( vertice**testa, vertice*v);
void nuovo_vertice(grafo*g, char citta[30]);
vertice* cerca_vertice(vertice*lista, char citta[30]);
vertice* cerca_vertice_con_indice(vertice*lista, int index);
void decrementa_indici(vertice*lista_vertici);
int rimuovi_vertice(vertice**lista, char nome_citta[]);

arco* crea_arco(char citta_arrivo[30], int distanza, float costo);
void inserisci_arco_in_coda(vertice*vert, arco*a);
void nuovo_arco(grafo*g,char citta_partenza[30], char citta_arrivo[30], int distanza, float costo);
char*cerca_arco(arco*lista_archi, char citta[]);
void rimuovi_arco(arco**lista_archi, char nome_citta[]);

int grado_vertice(grafo*g, char citta[]);
arco* meta_piu_econimica(grafo*g, char citta_partenza[]);
char*meta_piu_gettonata(grafo*g, prenotazione*lista_prenotazioni);

int get_indice_prossimo_vertice_per_costo(float pesi[], int visitati[],  int lunghezza_array);
void rilassa_adiacenti_per_costo(grafo*g, vertice* v, float pesi[], int visitati[]);
float dijkstra_sp_costo(grafo*g, char citta_partenza[], char citta_arrivo[]);
int get_indice_prossimo_vertice_per_distanza(int pesi[], int visitati[],  int lunghezza_array);
void rilassa_adiacenti_per_distanza(grafo*g, vertice* v, int pesi[], int visitati[], float prezzi[]);
int dijkstra_sp_distanza(grafo*g, char citta_partenza[], char citta_arrivo[], float* prezzo_per_distanza);

void nuova_tratta(grafo*g);
void nuova_citta(grafo*g);
void rimuovi_citta(grafo*g);
void rimuovi_tratta(grafo*g);
void stampa_tutti_gli_utenti(utente*albero_utenti);

utente*crea_utente(char username[], char password[], int punti);
void inserisci_utente_albero(utente**treePtr, utente*u);
void nuovo_utente(utente**albero_utenti, char username[], char password[], int punti);
void stampa_albero_utenti(utente*treePtr);
utente*cerca_utente(utente*treePtr, char username[], char password[]);
utente* effettua_log_in(utente*albero_utenti);
void libera_lista_prenotazioni(prenotazione**lista_prenotazioni);
void leggi_prenotazioni_utente( prenotazione**lista_prenotazioni, utente*u);
int controlla_username(utente*treePtr, char username[]);
void registra_utente(utente**albero_utenti);

prenotazione*crea_prenotazione(char partenza[], char arrivo[], char username[]);
void inserisci_prenotazione_in_coda( prenotazione **lista, prenotazione *p);
void nuova_prenotazione(prenotazione**lista_prenotazioni, char partenza[], char destinazione[], char username[]);
void stampa_prenotazioni(prenotazione*lista);

void visualizza_opzioni_voli(grafo*g, utente*u, prenotazione**lista_prenotazioni);
void acquista_biglietto(utente*u, prenotazione**lista_prenotazioni, char citta_partenza[], char citta_destinazione[], float costo);

void leggi_file_vertici(grafo*g);
void leggi_file_archi(grafo*g);
void leggi_file_utenti(utente**albero_utenti);
void leggi_file_prenotazioni(prenotazione** lista_prenotazioni);

void scrivi_file_vertici(grafo*g);
void scrivi_file_archi(grafo*g);
void util_scrivi_file_utenti(FILE*fp, utente*albero_utenti);
void scrivi_file_utenti(utente*albero_utenti);
void scrivi_file_prenotazioni(prenotazione*lista_prenotazioni);


//********************************* FUNZIONI UTILI **********************************************
void stampa_vettore(int*v, int lungh)
{
    printf("\n**************\n");
    for(int i=0; i<lungh; i++)
    {
        printf("> %d ", v[i]);
    }
    printf("\n**************\n");
}

void stampa_menu_amministratore()
{
    printf("\n 1 -> Stampa tutti i voli ");
    printf("\n---------------------------------------");
    printf("\n 2 -> Aggiungi citta' ");
    printf("\n 3 -> Aggiungi tratta ");
    printf("\n---------------------------------------");
    printf("\n 4 -> Visualizza tutti gli utenti ");
    printf("\n 5 -> Visualizza tutte le prenotazioni ");
    printf("\n---------------------------------------");
    printf("\n 6 -> Rimuovi citta'");
    printf("\n 7 -> Rimuovi tratta");
    printf("\n---------------------------------------");
    printf("\n 0 -> Esci ");
    printf("\n---------------------------------------");

}

void stampa_menu_utente(utente*u)
{
    printf("Benvenuto %s  PUNTI :  %d ", u->username, u->punti);
    printf("\n\n 1 -> Nuova prenotazione");
    printf("\n 2 -> Stampa prenotazioni ");
    printf("\n 0 -> Esci");

}

void stampa_menu_iniziale()
{
    printf("Scegli : \n 1 -> AMMINISTRATORE \n 2 -> UTENTE \n 3 -> REGISTRATI \n 0 -> ESCI ");
}

void errore(char messaggio[50])
{
    char testo[60]="Errore : ";
    strcat(testo, messaggio);
    printf("\n%s ", testo);
    exit(0);
}

void continua()
{
    printf("\n\n");
    system("PAUSE");
    system("cls");
}

void normalizza_parola(char* p)
{

    p[0] = toupper(p[0]);
    for(int i=1; i<strlen(p); i++)
    {
        p[i] = tolower(p[i]);
    }

    //return p;
}

int richiedi_intero()
{
    int valore;
    printf("\n > ");
    while(scanf("%d", &valore)!= 1)
    {
        printf("\nValore non valido. Inserirne un altro.\n > ");
        fflush(stdin);
    }
    return valore;
}

float richiedi_float()
{
    float valore;
    printf("\n > ");
    while(scanf("%f", &valore)!= 1)
    {
        printf("\nValore non valido. Inserirne un altro.\n > ");
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

void pulisci_schermo()
{
    system("cls");
}

void attendi()
{
    printf("\n");
    system("PAUSE");
}

//************************************  GRAFO  *******************************************************

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
    printf("Partenze:\t\t\tDestinazioni\n");
    while(tmpV)
    {
        printf("\n %-30s [index: %d] ", tmpV->citta, tmpV->indice_vertice);
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

void inizializza(grafo* g) // riempie il grafo con vertici e archi
{
    leggi_file_vertici(g);
    leggi_file_archi(g);
}


//************************************* VERTICE ********************************************************
vertice* crea_vertice(char citta[30])  //alloca memoria per un vertice
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

void inserisci_vertice_in_coda( vertice**testa, vertice*v)
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

void nuovo_vertice(grafo*g, char citta[30])  // crea il vertice e lo aggiunge al grafo
{
    vertice*v=crea_vertice(citta);
    v->indice_vertice=g->nv;
    if(!v)
        errore("memoria non disponibile.");
    else if (cerca_vertice(g->lista, citta) != NULL )// vertice gia presente
    {
        printf("\nGia' esistente !");
    }
    else
    {
        inserisci_vertice_in_coda(&(g->lista),v);
        g->nv++;
    }
}

vertice* cerca_vertice(vertice*lista, char citta[30]) // restituisce un puntatore al vertice cercato tramite nome
{
    vertice*v=lista;
    if(v != NULL && strcmp(v->citta, citta) != 0  ) // non trovato
    {
        v = cerca_vertice(lista->next_vertice, citta);
    }
    return v;
}

vertice* cerca_vertice_con_indice(vertice*lista, int index) // restituisce un puntatore al vertice cercato tramite indice
{
    vertice*v=lista;
    if(v != NULL && v->indice_vertice!=index  ) // non trovato
    {
        v = cerca_vertice_con_indice(lista->next_vertice, index);
    }
    return v;
}

void decrementa_indici(vertice*lista_vertici)
{
    if(lista_vertici==NULL)
        return ;
    lista_vertici->indice_vertice--;
    decrementa_indici(lista_vertici->next_vertice);
}

int rimuovi_vertice(vertice**lista, char nome_citta[])
{
    int controllo=0;
    if(*lista==NULL)  // fine lista_vertici
        return controllo;
    if(strcmp( (*lista)->citta, nome_citta) == 0   )  // rimuove il vertice e tutti isuoi archi
    {
        printf("<<<<trovato**");
        vertice*del=*lista;
        while(del->next_arco)
            rimuovi_arco(&del->next_arco, del->next_arco->citta_arrivo);
        (*lista) = del->next_vertice;
        free(del);
        decrementa_indici(*lista);
        controllo=1;
        if(*lista==NULL)
            return controllo;
    }
    rimuovi_arco( &(*lista)->next_arco, nome_citta); // rimuove da ogni vertice l'arco verso il vertice da eliminare
    return controllo + rimuovi_vertice(&(**lista).next_vertice, nome_citta );
}

//******************************** ARCO ************************************************
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
        if(vert)
            inserisci_arco_in_coda( vert, a );
        else
        {
            printf("\nErrore. Arco con vertice inesistente.");
            attendi();
        }
    }

}

char*cerca_arco(arco*lista_archi, char citta[])
{
    char *res;
    if(lista_archi==NULL)
        res = NULL;
    else if(strcmp(lista_archi->citta_arrivo, citta)==0)
        res = lista_archi->citta_arrivo;
    else
        res = cerca_arco(lista_archi->next_arco, citta);

    return res;
}

void rimuovi_arco(arco**lista_archi, char nome_citta[])
{
    if(*lista_archi==NULL)
        return;

    if( strcmp( (*lista_archi)->citta_arrivo, nome_citta)==0 )
    {
        arco*del=(*lista_archi);
        (*lista_archi)=del->next_arco;
        free(del);
        return;
    }
    rimuovi_arco( &(**lista_archi).next_arco, nome_citta  );
}

//********************************** METE ******************************************+++

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

arco* meta_piu_econimica(grafo*g, char citta_partenza[])
{
    vertice*vert=cerca_vertice(g->lista, citta_partenza);
    if(!g || g->nv==0)
        return NULL;
    if(!vert)
        return NULL;
    if(vert->next_arco==NULL)
        return NULL;

    arco*minimo=vert->next_arco;
    arco*tmp=vert->next_arco;

    while(tmp)
    {
        if(tmp->costo < minimo->costo)
            minimo=tmp;
        tmp=tmp->next_arco;
    }
    return minimo;
}

char*meta_piu_gettonata(grafo*g, prenotazione*lista_prenotazioni)
{
    int num_prenotazioni[g->nv];
    int max=0; // indice della citta più gettonata
    prenotazione*tmp = lista_prenotazioni;
    vertice*v;

    if(lista_prenotazioni==NULL)
    {
        printf("\nMeta piu' gettonata non disponibile. Nessuna prenotazione.\n");//<<<<<<<<<<<<<<<<<<<
        return NULL;
    }

    for(int i=0; i<g->nv; i++) // inizializza le celle del vettore a 0
        num_prenotazioni[i]=0;

    while(tmp) // scorre tutte le prenotazioni e in base all'indice di ogni città destinazione aumenta di uno la cella del vettore
    {
        v=cerca_vertice(g->lista, tmp->citta_arrivo);
        num_prenotazioni[v->indice_vertice]++;
        tmp=tmp->next;
    }

    for(int i=0; i<g->nv; i++)
    {
        if( num_prenotazioni[i] > num_prenotazioni[max])
            max=i;
    }

    v=cerca_vertice_con_indice(g->lista, max);
    //printf("\nLa meta piu' gettonata e' \"%s\" \n", v->citta);  //<<<<<<<<<<<<<<<<<<<
    return  v->citta;
}

// *************************  FUNZIONI PERCORSO MINIMO ********************************
//************************** S.P. per il COSTO ****************************************
int get_indice_prossimo_vertice_per_costo(float pesi[], int visitati[],  int lunghezza_array)
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

void rilassa_adiacenti_per_costo(grafo*g, vertice* v, float pesi[], int visitati[])
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

//*************************** S.P. per la DISTANZA  ********************************************

int get_indice_prossimo_vertice_per_distanza(int pesi[], int visitati[],  int lunghezza_array)
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

void rilassa_adiacenti_per_distanza(grafo*g, vertice* v, int pesi[], int visitati[], float prezzi[])
{
    int index;
    arco*tmpA=v->next_arco;
    visitati[v->indice_vertice]=1;
    vertice*tmpV;

    while(tmpA)
    {
        tmpV=cerca_vertice(g->lista,tmpA->citta_arrivo );
        if(  pesi[tmpV->indice_vertice]  > tmpA->distanza + pesi[v->indice_vertice])
        {
            pesi[tmpV->indice_vertice]  = tmpA->distanza + pesi[v->indice_vertice];
            prezzi[tmpV->indice_vertice] = tmpA->costo + prezzi[v->indice_vertice];
        }

        tmpA=tmpA->next_arco;
    }

    index=get_indice_prossimo_vertice_per_distanza(pesi, visitati, g->nv);
    if(index<0)
        return;

    vertice*prox_vert=cerca_vertice_con_indice(g->lista, index);
    rilassa_adiacenti_per_distanza(g, prox_vert, pesi, visitati, prezzi);
}

int dijkstra_sp_distanza(grafo*g, char citta_partenza[], char citta_arrivo[], float* prezzo_per_distanza)
{
    int pesi[g->nv];
    int visitati[g->nv];
    float prezzi[g->nv];
    int risultato;

    vertice*v_part=cerca_vertice(g->lista, citta_partenza);
    vertice*v_arr=cerca_vertice(g->lista, citta_arrivo);

    if(!v_part || !v_arr)
        return -2;

    for(int i=0; i<g->nv; i++)
    {
        pesi[i]=INFINITO;
        visitati[i]=0;
        prezzi[i]=0;
    }
    pesi[v_part->indice_vertice]=0;
    visitati[v_part->indice_vertice]=1;

    rilassa_adiacenti_per_distanza(g, v_part, pesi, visitati, prezzi);

    if(pesi[v_arr->indice_vertice] == INFINITO)
        risultato = -1;
    else
    {
        risultato = pesi[v_arr->indice_vertice];
        *prezzo_per_distanza=prezzi[v_arr->indice_vertice];
    }

    return risultato;
}

//*************************  AMMINISTRATORE ************************************

void nuova_tratta(grafo*g)
{
    char citta_1[30], citta_2[30];
    int distanza;
    float costo;
    vertice*v_1=NULL;
    vertice*v_2=NULL;

    printf("\nInserire nome prima citta' : ");
    richiedi_nome_citta(citta_1);
    v_1=cerca_vertice(g->lista, citta_1);
    if(!v_1)
    {
        printf("\nCitta inesistente.");
        return;
    }

    printf("\nInserire nome seconda citta' : ");
    richiedi_nome_citta(citta_2);
    v_2=cerca_vertice(g->lista, citta_2);
    if(!v_2)
    {
        printf("\nCitta  inesistente.");
        return;
    }

    char*tmp=cerca_arco(v_1->next_arco, citta_2);
    if(tmp)
    {
        printf("\nTratta gia' esistente  [1]");
        return;
    }
//superfluo
    tmp=cerca_arco(v_2->next_arco, citta_1);
    if(tmp)
    {
        printf("\nTratta gia' esistente  [2]");
        return;
    }
//<<<<<<<<<<<<<<<<<<<<<<<<<
    printf("\nInserire distanza : ");
    distanza=richiedi_intero();
    printf("\nInserire costo : ");
    costo=richiedi_float();

    nuovo_arco(g, citta_1, citta_2, distanza, costo);
    nuovo_arco(g, citta_2, citta_1, distanza, costo);
    printf("\nNuova tratta aggiunta !");
}

void nuova_citta(grafo*g)
{
    char nome_citta[30];
    printf("\nInserire nome citta' : ");
    richiedi_nome_citta(nome_citta);

    nuovo_vertice(g, nome_citta);
}

void rimuovi_citta(grafo*g)
{
    char nome_citta[30];
    printf("\nQuale citta' vuoi rimuovere ? ");
    richiedi_nome_citta(nome_citta);
    if(rimuovi_vertice(&g->lista, nome_citta) == 1)
    {
        g->nv--;
        printf("\nLa citta' e' stata rimossa ! ");
    }
    else
    {
        printf("\nCitta' non rimossa !");
    }
}

void rimuovi_tratta(grafo*g)
{
    char citta_1[30], citta_2[30];
    vertice*vert_1, *vert_2;
    printf("\nLa seguente operazione rimuovera' tratte da e verso entrambe le citta' ");

    printf("\nInserisci nome prima citta : ");
    richiedi_nome_citta(citta_1);
    printf("\nInserisci nome seconda citta : ");
    richiedi_nome_citta(citta_2);

    vert_1=cerca_vertice(g->lista, citta_1);
    vert_2=cerca_vertice(g->lista, citta_2);
    if(!vert_1)
        printf("\nNome prima citta' non valido");
    else if(!vert_2)
        printf("\nNome seconda citta' non valido");
    else
    {
        // controllo se arco non esiste >>>><<<<<
        if(cerca_arco(vert_1->next_arco, citta_2)==NULL) // se arco v1 -> v2 non esiste
        {
            printf("\nTratta inesistente ");
        }
        else
        {
            rimuovi_arco(&vert_1->next_arco, citta_2 );
            rimuovi_arco(&vert_2->next_arco, citta_1 );
            printf("\nLa tratta e' stata rimossa.");
        }

    }
}

void stampa_tutti_gli_utenti(utente*albero_utenti)
{
    if(albero_utenti==NULL)
        printf("\nNessun utente.");
    else
        stampa_albero_utenti(albero_utenti);
}

//******************************* UTENTE *********************************************

utente*crea_utente(char username[], char password[], int punti) // alloca memoria
{
    utente*u=(utente*)malloc(sizeof(utente));
    if(!u)
        errore("impossibile creare utente.");

    strcpy(u->username, username);
    strcpy(u->password, password);
    u->punti=punti;
    u->dx=NULL;
    u->sx=NULL;
    u->lista_prenotazioni=NULL;

    return u;
}

void inserisci_utente_albero(utente**treePtr, utente*u) // inserisce nodo nell'albero
{
    if(*treePtr==NULL)
    {
        *treePtr=u;
    }
    else
    {
        if( strcmp((*treePtr)->username, u->username)  > 0  )
            inserisci_utente_albero( &(*treePtr)->sx, u);

        else if( strcmp( (*treePtr)->username, u->username)  < 0  )
            inserisci_utente_albero( &(*treePtr)->dx, u);

        else
            printf("\nUtente e' gia registrato !");
    }

}

void nuovo_utente(utente**albero_utenti, char username[], char password[], int punti)//alloca memoria per un utente e lo inserisce nell'albero
{
    utente*nuovo=crea_utente(username, password, punti);
    if(nuovo)
    {
        inserisci_utente_albero(albero_utenti, nuovo);
    }
}

void stampa_albero_utenti(utente*treePtr)
{
    if(treePtr!=NULL)
    {
        stampa_albero_utenti(treePtr->sx);
        printf("\n> %-30s |%-30s  | %d  ", treePtr->username, treePtr->password, treePtr->punti);
        stampa_albero_utenti(treePtr->dx);
    }
}

utente*cerca_utente(utente*treePtr, char username[], char password[])
{
    utente*risultato=NULL;
    if(treePtr==NULL)//non trovato
    {
        printf("\nUsername non valido !");
    }
    else
    {
        if(strcmp( username, treePtr->username) > 0)
            risultato = cerca_utente(treePtr->dx, username, password);
        else if( strcmp(username, treePtr->username) < 0)
            risultato = cerca_utente(treePtr->sx, username, password);
        else
        {
            if(strcmp(username, treePtr->username)==0 && strcmp(password, treePtr->password)==0)
                risultato = treePtr;
            else
                printf("\nPassword non valida !");
        }
    }
    return risultato;
}

utente* effettua_log_in(utente*albero_utenti)
{
    char username[20],password[20];
    utente*u;
    int continua=1;
    do
    {
        pulisci_schermo();

        printf("Username : ");
        scanf("%s", username);

        printf("Password : ");
        scanf("%s", password);

        u=cerca_utente(albero_utenti, username, password);
        if(u==NULL) // non trovato
        {
            printf("\nRiprovare ?\n 1->si \n 0-> no ");
            continua=richiedi_intero();
        }
    }
    while(u==NULL && continua!=0);
    return u;
}

void libera_lista_prenotazioni(prenotazione**lista_prenotazioni)
{
    prenotazione*del;

    while(*lista_prenotazioni!=NULL)
    {
        del=*lista_prenotazioni;
        (*lista_prenotazioni)=del->next;
        free(del);
    }
}

void leggi_prenotazioni_utente( prenotazione**lista_prenotazioni, utente*u) // carica dalla lista_prenotazioni quelle dell'utenteAttivo
{
    libera_lista_prenotazioni(&u->lista_prenotazioni);
    prenotazione*tmp=*lista_prenotazioni;
    prenotazione*p;
    while(tmp)
    {
        if(strcmp(u->username, tmp->username )==0)
        {
            p=crea_prenotazione(tmp->citta_partenza, tmp->citta_arrivo, tmp->username);
            inserisci_prenotazione_in_coda(&u->lista_prenotazioni, p);
        }
        tmp=tmp->next;
    }
}

int controlla_username(utente*treePtr, char username[]) // restituiscec 1 se non esiste utente con username = username[]
{
    int risultato=0;
    if(treePtr==NULL) // username valido
    {
        risultato= 1;
    }
    else
    {
        if(strcmp( username, treePtr->username) > 0)
            risultato = controlla_username(treePtr->dx, username);
        else if( strcmp(username, treePtr->username) < 0)
            risultato = controlla_username(treePtr->sx, username);
        else
            risultato = 0; // username gia' utilizzato
    }
    return risultato;

}

void registra_utente(utente**albero_utenti)
{
    char username[20], password[20];
    int continua=1;
    do
    {
        pulisci_schermo();
        printf("\n********************* REGISTRAZIONE *********************\n");
        printf("\nInserisci un username e una password.\n");
        printf("\nUsername : \n > ");
        scanf("%s", username);
        printf("Password : \n > ");
        scanf("%s", password);

        if(controlla_username(*albero_utenti, username)==1)
        {
            nuovo_utente(albero_utenti, username, password, 0);
            continua=0;
            printf("\nNuovo utente salvato !\n");
        }
        else
        {
            printf("\nUsername gia' utilizzato. \nRiprovare 1-> si / 0-> no ");
            continua=richiedi_intero();
        }
    }
    while(continua!=0);

}

//************************************ PRENOTAZIONI *************************************************

prenotazione*crea_prenotazione(char partenza[], char arrivo[], char username[])
{
    prenotazione*p=(prenotazione*)malloc(sizeof(prenotazione));
    if(!p)
        errore("impossibile salvare prenotazione");
    p->next=NULL;

    strcpy(p->citta_partenza, partenza);
    strcpy(p->citta_arrivo, arrivo);
    strcpy(p->username, username);

    return p;
}

void inserisci_prenotazione_in_coda( prenotazione **lista, prenotazione *p)
{
    if((*lista)==NULL)
    {
        (*lista)=p;
    }
    else
        inserisci_prenotazione_in_coda( &(*lista)->next,  p);
}

void nuova_prenotazione(prenotazione**lista_prenotazioni, char partenza[], char destinazione[], char username[])
{
    printf("\n************** ACQUISTA BIGLIETTO ***************\n");
    prenotazione*p=crea_prenotazione(partenza, destinazione, username);
    if(!p)
    {
        printf("\nImpossibile allocare memoria per la prenotazione.");
        return;
    }
    inserisci_prenotazione_in_coda(lista_prenotazioni,p);
}

void stampa_prenotazioni(prenotazione*lista)
{
    prenotazione*tmp=lista;
    if(lista==NULL)
    {
        printf("\nNessuna prenotazione !\n");
        return;
    }
    while(tmp)
    {
        printf("\n> %-30s | %-30s | %s", tmp->citta_partenza, tmp->citta_arrivo, tmp->username);
        tmp=tmp->next;
    }
}

//********************************** OPEZIONI PER UTENTE ********************************************************************

void visualizza_opzioni_voli(grafo*g, utente*u, prenotazione**lista_prenotazioni)
{
    char partenza[30], arrivo[30];
    int scelta,distanza,acquista ;
    float costo, costo_per_distanza;
    arco*meta_economica;
    char *meta_gettonata;


    pulisci_schermo();
    printf("Inserire citta' partenza : ");
    richiedi_nome_citta(partenza);
    if(cerca_vertice(g->lista, partenza)==NULL)
    {
        printf("\nCitta' non trovata");
        return;
    }
    do
    {
        pulisci_schermo();
        printf("Vuoi inserire una destinazione  ? \n 1 -> si \n 0 -> no ");
        scelta=richiedi_intero();
    }
    while(scelta!=0 && scelta!=1);

    pulisci_schermo();
    switch(scelta)
    {
    case 1: /**---------------------------------------- partenza e destinazione -------------------------------------------- */
    {
        printf("Partenza : %s ", partenza);
        printf("\nInserire destinazione :  ");
        richiedi_nome_citta(arrivo);
        if(cerca_vertice(g->lista, arrivo)==NULL)
        {
            printf("\nCitta' non trovata.");
            break;
        }

        distanza = dijkstra_sp_distanza(g, partenza, arrivo, &costo_per_distanza);
        costo = dijkstra_sp_costo(g, partenza, arrivo);

        if(costo == -1 || distanza == -1)
        {
            printf("\nNessuna tratta disponibile ! ");
            break;
        }
        else if (costo == -2 || distanza == -2 )
        {
            printf("\nCitta' non valide.");
            break;
        }
        else // se le tratte esistono
        {
            while(1)
            {
                pulisci_schermo();
                printf("La tratta piu' ECONOMICA da \"%s\" a \"%s\" ha un costo di : %.2f euro ", partenza, arrivo, costo);
                printf("\nLa tratta piu' BREVE da \"%s\" a \"%s\" ha una distanza di : %d KM con un costo di %.2f", partenza, arrivo, distanza, costo_per_distanza);
                printf("\n\nQuale vuoi acquistare?\n 1-> Economica\n 2-> Breve\n 0-> Annulla");
                acquista=richiedi_intero();
                switch(acquista)
                {
                case 1:
                    acquista_biglietto(u, lista_prenotazioni, partenza, arrivo, costo);
                    break;
                case 2:
                    acquista_biglietto(u, lista_prenotazioni, partenza, arrivo, costo_per_distanza);
                    break;
                case 0:
                    break;
                default:
                    printf("\nScelta non valida ! ");
                    attendi();
                    continue;
                }
                break;
            }
        }
        break;
    }
    case 0:  /**-------------------------------------------------- solo partenza ------------------------------------------------------------------------*/
    {
        meta_economica=meta_piu_econimica(g, partenza);
        meta_gettonata=meta_piu_gettonata(g, *lista_prenotazioni);
        while(1)
        {
            pulisci_schermo();
            if(meta_economica)
                printf("La meta piu' ECONOMICA raggiungibile da \"%s\" e' \"%s\", con un costo di %.2f euro. ", partenza, meta_economica->citta_arrivo , meta_economica->costo  );
            else
                printf("\nMeta piu' ECONOMICA non disponibile.");

            if(meta_gettonata==NULL )
                printf("\nMeta piu' GETTONATA non disponibile.");
            else if( strcmp(meta_gettonata, partenza)==0)
                printf("\nLa meta piu' GETTONATA e' proprio \"%s\" ", meta_gettonata);
            else
                printf("\nLa meta piu' GETTONATA e' \"%s\". ", meta_gettonata);

            printf("\n\nVuoi acquistare un biglietto ? \n 1-> meta econimica \n 2-> meta gettonata \n 0-> esci ");
            scelta=richiedi_intero();
            switch(scelta)
            {
            case 1: // se utente seleziona economica
            {
                if(meta_economica)
                    acquista_biglietto(u, lista_prenotazioni, partenza, meta_economica->citta_arrivo, meta_economica->costo);
                else
                {
                    printf("\n\nMeta economica non disponibile ! \n");
                    attendi();
                    continue;
                }
                break;
            }
            case 2: // se utente seleziona gettonata
            {
                if(meta_gettonata==NULL || strcmp(meta_gettonata, partenza)==0)
                {
                    printf("\nMeta gettonata non disponibile ! \n");
                    attendi();
                    continue;
                }
                distanza = dijkstra_sp_distanza(g, partenza, meta_gettonata, &costo_per_distanza);
                costo = dijkstra_sp_costo(g, partenza, meta_gettonata);
                if(costo == -1 || distanza == -1)
                {
                    printf("\nNessuna tratta disponibile per la meta piu' gettonata ! ");
                    attendi();
                    continue;
                    //break
                }
                while(1)
                {
                    pulisci_schermo();
                    printf("La tratta piu' econimica da \"%s\" a \"%s\" ha un costo di : %.2f euro ", partenza, meta_gettonata, costo);
                    printf("\nLa tratta piu' breve da \"%s\" a \"%s\" ha una distanza di : %d KM con un costo di %.2f euro", partenza, meta_gettonata, distanza, costo_per_distanza);
                    printf("\n\nQuale vuoi acquistare?  \n 1-> Economica \n 2-> Gettonata \n 0-> Annulla \n");
                    acquista=richiedi_intero();
                    switch(acquista)
                    {
                    case 1:
                        acquista_biglietto(u, lista_prenotazioni, partenza, meta_gettonata, costo);
                        break;
                    case 2:
                        acquista_biglietto(u, lista_prenotazioni, partenza, meta_gettonata, costo_per_distanza);
                        break;
                    case 0:
                        break;
                    default:
                        printf("\nScelta non valida ! ");
                        attendi();
                        continue;
                    }
                    break;
                }
                break;  // fine case 2
            }
            case 0: // esci
                break;
            default:
                printf("\nScelta non valida.");
                attendi();
                continue;
            }
            break;
        }
        break;
    }//fine solo partenza
    }
}

void acquista_biglietto(utente*u, prenotazione**lista_prenotazioni, char citta_partenza[], char citta_destinazione[], float costo)
{
    int scelta;

    pulisci_schermo();
    printf("Partenza : %s     Destinazione : %s     Prezzo : %.2f \n", citta_partenza, citta_destinazione, costo);
    if(u->punti > 10)
    {
        printf("\nHai punti %d inutilizzati. Li vuoi spendere ora per ottenere uno sconto sul biglietto ?", u->punti);
        printf("\nOgni 10 punti hai uno sconto di 1 euro !");
        do
        {
            printf("\n 1-> si \n 0-> no ");
            scelta=richiedi_intero();
        }
        while(scelta!=0 && scelta !=1);

        if(scelta==1)
        {
            while (costo>0 && u->punti>10)
            {
                u->punti-=10;
                costo-=1;
            }

        }
    }
    nuova_prenotazione(lista_prenotazioni, citta_partenza, citta_destinazione, u->username);
    printf("\nPrenotazione effettuata ! ");
    printf("\nImporto totale : %.2f euro \n", costo );
    u->punti+=(int)costo;
    return;
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

void leggi_file_utenti(utente**albero_utenti)
{
    char username[20], password[20];
    int punti;
    FILE*fp=fopen("Utenti.txt", "r+");
    if(!fp)
        errore("impossibile aprire file utenti.");

    while(!feof(fp))
    {
        if(fscanf(fp, " %s %s %d\n", username, password, &punti) == 3   )
            nuovo_utente(albero_utenti, username,password,punti);
    }
}

void leggi_file_prenotazioni(prenotazione** lista_prenotazioni)
{
    FILE*fp=fopen("Prenotazioni.txt", "r+");
    if(!fp)
        errore("impossibile aprire il file prenotazioni.");

    char partenza[30], arrivo[30], username[30];
    while(!feof(fp))
    {
        if(fscanf(fp, " %s %s %s", username, partenza, arrivo) ==3  )
        {
            prenotazione*p=crea_prenotazione(partenza, arrivo, username);
            inserisci_prenotazione_in_coda(lista_prenotazioni, p);
        }
    }
    fclose(fp);
}

void scrivi_file_vertici(grafo*g)
{
    FILE*fp=fopen("Vertici.txt", "w+");
    if(!fp)
    {
        printf("\nImpossibile aprire file vertici.");
        return;
    }
    printf("\n*** salvo file vertici***\n");
    vertice*tmp=g->lista;
    while(tmp)
    {
        fprintf(fp,"%s\n", tmp->citta);
        tmp=tmp->next_vertice;
    }
    free(tmp);
    fclose(fp);
}

void scrivi_file_archi(grafo*g)
{
    FILE*fp=fopen("Archi.txt", "w+");
    if(!fp)
    {
        printf("\nImpossibile aprire file vertici.");
        return;
    }
    printf("\n*** salvo file archi***\n");  //<<<<<<<<<<<<<<<
    vertice*tmpV=g->lista;
    arco*tmpA=tmpV->next_arco;
    while(tmpV)
    {
        tmpA=tmpV->next_arco;
        while(tmpA)
        {
            fprintf(fp, "%-30s %-30s %5d \t%.2f\n", tmpV->citta, tmpA->citta_arrivo, tmpA->distanza, tmpA->costo);
            tmpA=tmpA->next_arco;
        }
        tmpV=tmpV->next_vertice;
    }

    free(tmpV);
    free(tmpA);
    fclose(fp);
}

void util_scrivi_file_utenti(FILE*fp, utente*albero_utenti)
{
    if(albero_utenti)
    {
        fprintf(fp, "%-30s %-30s %6d\n",albero_utenti->username, albero_utenti->password, albero_utenti->punti);
        util_scrivi_file_utenti(fp,albero_utenti->sx);
        util_scrivi_file_utenti(fp,albero_utenti->dx);
    }
}

void scrivi_file_utenti(utente*albero_utenti)
{
    FILE*fp=fopen("Utenti.txt", "w");

    if(!fp)
    {
        errore("impossibile scrivere file utenti.");
    }
    util_scrivi_file_utenti(fp, albero_utenti);
    fclose(fp);
}

void scrivi_file_prenotazioni(prenotazione*lista_prenotazioni)
{
    prenotazione*tmp=lista_prenotazioni;
    FILE*fp=fopen("Prenotazioni.txt", "w");

    if(!fp)
        errore("impossibile aprire file prenotazioni.");

    while(tmp)
    {
        fprintf(fp,"%s \t%s \t%s \n", tmp->username, tmp->citta_partenza, tmp->citta_arrivo);
        tmp=tmp->next;
    }
    fclose(fp);
}


//***************************************  FINE  *********************************************************
