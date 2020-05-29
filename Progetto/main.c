#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"header.h"

//grafo* inizializza(grafo*g); //riempe il grafo
//void continua(); //chiede di premere un tasto per continuare
//char* normalizza_parola(char* p); //rende la prima lettera maiuscola e le restanti minuscole
//prenotazioni* attive(char utente[], prenotazioni* p);

void main()
{

    int scelta; //scelta dal menù
    int scelta_login;
    int distanza;
    float costo;
    char destinazione;
    char sconto;
    char citta_partenza[20];
    char citta_economica[20];
    char citta_arrivo[20];
    char* p;
    char username[20];
    char password[20] = {"nulla"};
    char confronto_password[20] = {"niente"}; //stringa di confronto password
    char utente[40];
    int confermato;
    int k; //indice stringa username
    grafo*g=nuovo_grafo();
    prenotazioni* lista_prenotazioni = NULL;

    inizializza(g);

while(confermato != 1){
    printf("LOGIN");
    printf("\n1.Effettua il login");
    printf("\n2.Registrati");
    printf("\n3.Entra come visitatore");
    printf("\n4.Entra come amministratore");
    printf("\n5.ESCI\n");
    scanf("%d", &scelta_login);

    if(scelta_login == 1){
        printf("\nInserire username: \n");
        scanf("%s", username);
        k = strlen(username);
        username[k] = '-';
        username[k+1] = '\0';
        printf("\nInserire password: \n");
        scanf("%s", password);
        strcat(username,password);
        confermato = conferma_login(username);
        if(confermato == 0){
            printf("\nDati errati, riprova!");
        }else{
            printf("\nDati corretti!");
        }
    }else if(scelta_login == 2){
        while(strcmp(password, confronto_password) != 0){
            printf("\nScegliere l'username: \n");
            scanf("%s", username);
            k=strlen(username);
            username[k] = '-';
            username[k+1] = '\0';
            printf("\nScegliere una password: \n");
            scanf("%s", password);
            printf("\nRipetere password: \n");
            scanf("%s", confronto_password);

            if(strcmp(password,confronto_password) == 0){
                strcat(username,password);
                registra_utente(username);
                strcpy(password, confronto_password);
            }else{
                printf("\nConfronto password errato, ripetere!\n");
            }
        } //fine while
    }else if(scelta_login == 3){
        confermato = 1;
    }else if(scelta_login == 4){
        printf("\nInserire username: \n");
        scanf("%s", username);
        k = strlen(username);
        username[k] = '-';
        username[k+1] = '\0';
        printf("\nInserire password: \n");
        scanf("%s", password);
        strcat(username,password);
        confermato = conferma_amministratore(username);
        if(confermato == 0){
            printf("\nDati errati, riprova!");
        }else{
            printf("\nDati corretti!");
        }
    }else if(scelta_login == 5){
        system("cls");
        printf("\nArrivederci!");
        exit(0);
    }

    continua();
} //fine while

/*OPZIONI DI MENU' A SECONDA DELL'UTENTE*/
if(scelta_login == 3){
    while(1){
        printf("\nSELEZIONA UN OPZIONE\n");
        printf("\n1.Visualizza i voli");
        printf("\n2.ESCI\n");

        scanf("%d", &scelta);
        system("cls");

         switch (scelta){
            case 1:
                 stampa_grafo(g);
                 continua();
                 break;
            case 2:
                printf("\nArrivederci!");
                exit(0);
                break;
        }
    }
}else if(scelta_login == 1){
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
                 break;
            case 2:
                 lista_prenotazioni=attive(username,lista_prenotazioni);
                 printf("\nPRENOTAZIONI ATTIVE:\n");
                 stampa_prenotazioni(lista_prenotazioni);
                 continua();
                 break;
            case 3:
                printf("\nInserire la citta' di partenza: ");
                scanf("%s", citta_partenza);
                normalizza_parola(citta_partenza);
                    if(cerca_vertice(g->lista,citta_partenza)){ // se la città è presente...
                        /*chiediamo all'utente se vuole inserire destinazioni*/
                        while(destinazione != 'N' && destinazione != 'Y'){
                            printf("\nVuoi inserire la destinazione? Y/N\n");
                            scanf(" %c", &destinazione);
                            destinazione = toupper(destinazione);
                        }

                        if(destinazione == 'N'){
                            meta_economica(g, citta_partenza, citta_economica);
                            printf("\nDa %s la meta piu' economica e' %s, approfittane!", citta_partenza,citta_economica);
                        }

                        printf("\nInserisci la destinazione: ");
                        scanf("%s", citta_arrivo);
                        normalizza_parola(citta_arrivo);
                        if(cerca_arco(cerca_vertice(g->lista,citta_partenza),citta_arrivo)){
                            printf("\nIl costo del biglietto e' %.2f€", cerca_arco(cerca_vertice(g->lista,citta_partenza),citta_arrivo)->costo);
                            if(punteggio_corrente(username) > 0){
                                printf("\nHai %d crediti bonus, vuoi utilizzarli per avere uno sconto sul biglietto? Y/N\n", punteggio_corrente(username));
                                scanf(" %c", &sconto);
                                sconto = toupper(sconto);

                                if(sconto == 'Y'){
                                    decrementa_punteggio(username,cerca_arco(cerca_vertice(g->lista,citta_partenza),citta_arrivo)->costo);
                                }else if(sconto == 'N'){
                                    incrementa_punteggio(username,cerca_arco(cerca_vertice(g->lista,citta_partenza),citta_arrivo)->costo);
                                }
                            }else{
                                incrementa_punteggio(username,cerca_arco(cerca_vertice(g->lista,citta_partenza),citta_arrivo)->costo);
                            }

                            registra_prenotazione(username, citta_partenza,citta_arrivo);
                        }else{
                            printf("\nNon esistono voli da %s a %s!", citta_partenza, citta_arrivo);
                        }

                        destinazione = 'Z'; //rinizializziamo la variabile destinazione
                    }else{//...altrimenti
                        printf("\nNon esistono partenze da %s", citta_partenza);
                    }
                continua();
                break;
            case 4:
                printf("\nArrivederci!");
                exit(0);
                break;
        }
    }
}else if(scelta_login == 4){
        while(1){
            printf("\nSELEZIONA UN OPZIONE\n");
            printf("\n1.Visualizza i voli");
            printf("\n2.Aggiungi sito");
            printf("\n3.Aggiungi volo a sito");
            printf("\n4.ESCI\n");

            scanf("%d", &scelta);
            system("cls");

             switch (scelta){
                case 1:
                     stampa_grafo(g);
                     continua();
                     break;
                case 2:
                     printf("\nInserire nome di citta': ");
                     scanf("%s", citta_partenza);
                     normalizza_parola(citta_partenza);
                     nuovo_vertice(g,citta_partenza);
                     continua();
                     break;
                case 3:
                     printf("\nInserire nome di citta' di partenza: ");
                     scanf("%s", citta_partenza);
                     normalizza_parola(citta_partenza);
                     if(cerca_vertice(g->lista,citta_partenza)){
                        printf("\nInserire citta' di arrivo: ");
                        scanf("%s", citta_arrivo);
                        normalizza_parola(citta_arrivo);
                        printf("\nInserire costo biglietto da %s a %s: ", citta_partenza, citta_arrivo);
                        scanf("%f", &costo);
                        printf("\nInserire distanza in chilometri tra %s e %s: ", citta_partenza, citta_arrivo);
                        scanf("%d", &distanza);
                        nuovo_arco(g,citta_partenza,citta_arrivo,distanza,costo);
                     }else{
                        printf("\nLa citta' %s non e' registrata nel database!", citta_partenza);
                     }
                     continua();
                     break;
                case 4:
                    printf("\nArrivederci!");
                    exit(0);
                    break;
            }
        }
    } //fine if-else
} //fine main()
