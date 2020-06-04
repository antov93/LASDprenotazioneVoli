#include"header.h"

//il progetto

void main()
{
    int utilizzatore, scelta;

    utente*albero_utenti=NULL;
    prenotazione*lista_prenotazioni=NULL;
    grafo*g=nuovo_grafo();
    utente* utenteAttivo=NULL;

    leggi_file_utenti(&albero_utenti);
    leggi_file_prenotazioni(&lista_prenotazioni);
    inizializza(g);

    while(1)
    {
        pulisci_schermo();
        stampa_menu_iniziale();
        utilizzatore=richiedi_intero();

        if(utilizzatore == ADMIN) //--------------------------------------------------------------------
        {
            do
            {
                pulisci_schermo();
                stampa_menu_amministratore();
                scelta=richiedi_intero();
                switch(scelta)
                {
                case 1:
                    pulisci_schermo();
                    stampa_grafo(g);
                    break;
                case 2:
                    nuova_citta(g);
                    scrivi_file_vertici(g);
                    break;
                case 3:
                    nuova_tratta(g);
                    scrivi_file_archi(g);
                    break;
                case 4:
                    stampa_tutti_gli_utenti(albero_utenti);
                    break;
                case 5:
                    stampa_prenotazioni(lista_prenotazioni);
                    break;
                case 6:
                    rimuovi_citta(g);
                    scrivi_file_vertici(g);
                    scrivi_file_archi(g);
                    break;
                case 7:
                    rimuovi_tratta(g);
                    scrivi_file_archi(g);
                    break;
                case 0:
                    break; // esci
                default:
                    printf("\nScelta non valida.");
                    break;
                }
                attendi();
            }
            while(scelta !=0 );
        }
        else if(utilizzatore== USER) //--------------------------------------------------------------------
        {
            utenteAttivo = effettua_log_in(albero_utenti);
            if ( utenteAttivo== NULL )
                continue;
            while(1)
            {
                pulisci_schermo();
                stampa_menu_utente(utenteAttivo);
                scelta=richiedi_intero();
                switch(scelta)
                {
                case 1:
                    visualizza_opzioni_voli(g, utenteAttivo, &lista_prenotazioni);
                    scrivi_file_utenti(albero_utenti);
                    scrivi_file_prenotazioni(lista_prenotazioni);
                    attendi();
                    continue;
                case 2:
                    leggi_prenotazioni_utente(&lista_prenotazioni, utenteAttivo);
                    stampa_prenotazioni(utenteAttivo->lista_prenotazioni);
                    attendi();
                    continue;
                case 0: // ESCI
                    break;
                default:
                    printf("\nScelta non valida.\n");
                    attendi();
                    continue;
                }
                break;
            }
            utenteAttivo=NULL;
        }
        else if( utilizzatore== SIGN_IN)//--------------------------------------------------------------------
        {
            registra_utente(&albero_utenti);
            scrivi_file_utenti(albero_utenti);
            attendi();
            continue;
        }
        else if( utilizzatore == 0)//--------------------------------------------------------------------
        {
            printf("\nArrivederci ! ");
            break;
        }
        else
        {
            printf("\nScelta non valida.");
            attendi();
        }

    }// fine WHILE(1)
} // fine main()
