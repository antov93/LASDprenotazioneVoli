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



    stampa_grafo(g);

    printf("\n\n*** FINE ***");
}
