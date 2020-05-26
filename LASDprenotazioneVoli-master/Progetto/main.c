#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"header.h"



void main()
{
    printf("\n*** INIZIO ***\n");
    grafo*g=nuovo_grafo();
    nuovo_vertice(g, "Napoli");
    nuovo_vertice(g, "Roma");
    nuovo_vertice(g, "Milano");

    nuovo_arco(g, "Napoli", "Roma",   200, 50);
    nuovo_arco(g, "Napoli", "Milano", 700, 150);
    nuovo_arco(g, "Milano", "Napoli", 700, 150);


    stampa_grafo(g);

    printf("\n\n*** FINE ***");
}
