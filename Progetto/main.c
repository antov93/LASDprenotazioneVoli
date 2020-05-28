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
    char destinazione;
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
    printf("\nLOGIN");
    printf("\n1.Effettua il login");
    printf("\n2.Registrati");
    printf("\n3.Entra come visitatore\n");
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
} //fine if-else
}


/*

int conferma_login(char utente[]){

	int i=0,j=0;
	FILE *fp;
	char lettura[20][20];
	int dim;

	fp=fopen("utenti.txt","r"); //apro il file in lettura
	if(fp){
		while(!feof(fp)){

			fscanf(fp, "%s", lettura[i]);
			i++;

		}//fine while della lettura file

	}else{
		printf("Errore apertura file!");
	 }//fine controllo esistenza file

	fclose(fp);


	int res = 0;
	dim = i;
	for (i = 0; i < dim; i++) //controllo riga per riga se i dati sono presenti nel file
		if (strcmp(utente, lettura[i]) == 0){
            res = 1;
            return res;
        }

	  return res;

}

void registra_utente(char utente[]){
    FILE *fp;
    fp=fopen("utenti.txt","a"); //apro il file
    if(fp){
            fprintf(fp, "%s %d\n", utente, 0);
    }else{
        printf("\nErrore nella scrittura del file utenti.txt!\n");
    }
    fclose(fp);
}

void registra_prenotazione(char utente[], char citta_partenza[], char citta_arrivo[]){
    FILE *fp;
    fp=fopen("prenotazioni.txt","a"); //apro il file
    if(fp){
            fprintf(fp, "%s %s %s\n", utente, citta_partenza, citta_arrivo);
    }else{
        printf("\nErrore nella scrittura del file prenotazioni.txt!\n");
    }
    fclose(fp);
}

prenotazioni* attive(char utente[], prenotazioni* p){

	int i=0,j=0;
	FILE *fp;
	char lettura[20][20];
	int dim;

	fp=fopen("prenotazioni.txt","r"); //apro il file in lettura
	if(fp){
		while(!feof(fp)){

			fscanf(fp, "%s", lettura[i]);
			i++;

		}//fine while della lettura file

	}else{
		printf("Errore apertura file!");
	 }//fine controllo esistenza file

	fclose(fp);


	int res = 0;
	dim = i;
	for (i = 0; i < dim; i++){ //controllo riga per riga se i dati sono presenti nel file
		if (strcmp(utente, lettura[i]) == 0){
            p = aggiungi_prenotazione(p,lettura[i+1],lettura[i+2]);
        }
	}

    return p;
}

*/
