#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"

grafo* inizializza(grafo*g); //riempe il grafo
void continua(); //chiede di premere un tasto per continuare
char* normalizza_parola(char* p); //rende la prima lettera maiuscola e le restanti minuscole

void main()
{
    int scelta; //scelta dal menù
    char destinazione;
    char citta_partenza[20];
    char* p;
    grafo*g=nuovo_grafo();
    g=inizializza(g);

    while(1){

        printf("\nSELEZIONA UN OPZIONE\n");
        printf("\n1.Visualizza i voli");
        printf("\n2.Visualizza le prenotazioni attive");
        printf("\n3.Effettua una nuova prenotazione");
        printf("\n4.ESCI\n");

        scanf("%d", &scelta);
        system("cls");

         switch (scelta){
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
                    if(destinazione == 'S'){

                    }else if(destinazione =='N'){
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


    stampa_grafo(g);

    printf("\n\n*** FINE ***");
}

grafo* inizializza(grafo* g){
    nuovo_vertice(g, "Napoli");
    nuovo_vertice(g, "Roma");
    nuovo_vertice(g, "Milano");
    nuovo_vertice(g, "Verona");
    nuovo_vertice(g, "Barcellona");
    nuovo_vertice(g, "Madrid");
    nuovo_vertice(g, "Amsterdam");
    nuovo_vertice(g, "Pisa");
    nuovo_vertice(g, "Parigi");
    nuovo_vertice(g, "Londra");
    nuovo_vertice(g, "Bari");
    nuovo_vertice(g, "Piacenza");
    nuovo_vertice(g, "Mosca");
    nuovo_vertice(g, "Bruxelles");
    nuovo_vertice(g, "Helsinki");
    nuovo_vertice(g, "Tokyo");
    nuovo_vertice(g, "Montecarlo");
    nuovo_vertice(g, "Edimburgo");
    nuovo_vertice(g, "Stoccolma");
    nuovo_vertice(g, "Dublino");

    nuovo_arco(g, "Napoli", "Roma",   200, 20.0);
    nuovo_arco(g, "Roma", "Napoli",   200, 20.0);
    nuovo_arco(g, "Napoli", "Milano", 700, 50.0);
    nuovo_arco(g, "Milano", "Napoli",   700, 20.0);
    nuovo_arco(g, "Verona", "Barcellona", 1100, 100.0);
    nuovo_arco(g, "Barcellona", "Verona", 1100, 100.0);
    nuovo_arco(g, "Helsinki", "Montecarlo",   2800, 200.0);
    nuovo_arco(g, "Montecarlo", "Helsinki",   2800, 200.0);
    nuovo_arco(g, "Bruxelles", "Helsinki", 700, 50.0);
    nuovo_arco(g, "Helsinki", "Bruxelles", 700, 50.0);
    nuovo_arco(g, "Mosca", "Tokyo", 7500, 100.0);
    nuovo_arco(g, "Tokyo", "Mosca", 7500, 100.0);
    nuovo_arco(g, "Napoli", "Barcellona",   1500, 80.0);
    nuovo_arco(g, "Barcellona", "Napoli",   1500, 80.0);
    nuovo_arco(g, "Amsterdam", "Milano", 1070, 90.0);
    nuovo_arco(g, "Milano", "Amsterdam", 1070, 90.0);
    nuovo_arco(g, "Milano", "Bruxelles", 800, 50.0);
    nuovo_arco(g, "Bruxelles", "Milano", 800, 50.0);
    nuovo_arco(g, "Napoli", "Dublino", 2600, 150.0);
    nuovo_arco(g, "Dublino", "Napoli", 2600, 150.0);
    nuovo_arco(g, "Stoccolma", "Edimburgo", 2500, 180.0);
    nuovo_arco(g, "Edimburgo", "Stoccolma", 2500, 180.0);
    nuovo_arco(g, "Londra", "Parigi", 470, 50.0);
    nuovo_arco(g, "Parigi", "Londra", 470, 50.0);
    nuovo_arco(g, "Londra", "Napoli", 2000, 100.0);
    nuovo_arco(g, "Napoli", "Londra", 2000, 100.0);

    return g;
}

void continua(){
    char tasto;
    printf("\n\nPremere un tasto per continuare...\n");
    scanf("%s",&tasto);
}

char* normalizza_parola(char* p){

    p[0] = toupper(p[0]);
    for(int i=1; i<strlen(p); i++){
        p[i] = tolower(p[i]);
    }

    return p;
}
