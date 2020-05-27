#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"header.h"




//int richiedi_intero();
//void stampa_menu();
//void inizializza(grafo* g);
//void continua();
//char* normalizza_parola(char* p);

//***********************************************************++


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



/* void main()  // main da eliminare
{
    int scelta; //scelta dal menù
    char destinazione;
    char citta_partenza[20];
    char citta_economica[20];
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
*/


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
            break;
        case 2:
            break;
        case 3:
            printf("\nInserire la citta' di partenza: ");
            richiedi_nome_citta(citta_partenza);
            if(cerca_vertice(g->lista, citta_partenza)==NULL)
                errore("la citta non esiste.");

            printf("\nVuoi inserire una destinazione ? ");
            scelta_Y_N=richiedi_Y_N();
            if(scelta_Y_N == 'Y')
            {
                richiedi_nome_citta(citta_arrivo);
                if(!cerca_vertice(g->lista, citta_arrivo))
                {
                    printf("\nCitta' non trovata.");
                }

                // continua...

            } // FINE YES
            else if(scelta_Y_N == 'N')
            {
                do
                {
                    printf("\nCosa vuoi sapere : \n1->meta piu' econimica\n2->meta piu' gettonata\n0->annulla\n> ");
                    scelta=richiedi_intero();
                    switch(scelta)
                    {
                    case 0:
                        break;
                    case 1:
                        meta_piu_econimica(g, citta_partenza);
                        break;
                    case 2:
                        //meta_piu_gettonata()
                        break;
                    default:
                        printf("\nScelta non valida ! ");
                        continue;
                    }
                    break;
                }
                while (1);
            }

            continua();
            break;
        case 4:
            printf("\nArrivederci!");
            exit(0);
            break;
        }
    }

    printf("\n\n*** FINE ***");
    return;
}

