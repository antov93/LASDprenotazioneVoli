#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"

#include<ctype.h>


void inizializza(grafo*g); //riempe il grafo
void continua(); //chiede di premere un tasto per continuare
char* normalizza_parola(char* p); //rende la prima lettera maiuscola e le restanti minuscole

void stampa_menu()
{
    printf("\nSELEZIONA UN OPZIONE\n");
    printf("\n1.Visualizza i voli");
    printf("\n2.Visualizza le prenotazioni attive");
    printf("\n3.Effettua una nuova prenotazione");
    printf("\n4.ESCI\n");
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


void pulisci_schermo()
{
    system("cls");
}

void main()
{
    int scelta; //scelta dal menù
    char destinazione;
    char citta_partenza[20];
    char* p;
    grafo*g=nuovo_grafo();
    inizializza(g);
    printf("*****");
   stampa_grafo(g);

    while(1)
    {
        stampa_menu();
        scelta=richiedi_intero();

        system("cls");

        switch (scelta)
        {
        case 1:
            stampa_grafo(g);
            continua();
            system("cls");
            break;
        case 2:
            break;
        case 3:
            printf("\nInserire la citta' di partenza: ");
            scanf("%s", citta_partenza);
            p=normalizza_parola(citta_partenza);
            printf("\nVuoi inserire la destinazione? S/N");
            scanf("%c", &destinazione);
            if(destinazione == 'S')
            {

            }
            else if(destinazione =='N')
            {
                printf("\nDa %s la tratta piu' economica e' %s, approfittane!", citta_partenza, tratta_economica(g, citta_partenza));
            }
            continua();
            system("cls");
            break;
        case 4:
            printf("\nArrivederci!");
            exit(0);
            break;
        }
    }


//    stampa_grafo(g);
//    printf("\n\n*** FINE ***");
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
    // system("PAUSE");
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
