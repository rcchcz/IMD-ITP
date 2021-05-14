#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carta.h"

void strPCarta(char cartaStr[MAX_TAM_CARTA_STR], carta *card)
{
    char temp[MAX_TAM_CARTA_STR];
    int ptemp=0;

    for (int i = 0; i < strlen(cartaStr); i++)
    {
        if(cartaStr[i] == -30) //-30: primeiro caractere de ♥ ♦ ♣ ou ♠
        {
            ptemp=0;

            if(!strcmp(temp, "A")) (*card).valor = ca;
            else if(!strcmp(temp, "J")) (*card).valor = cj;
            else if(!strcmp(temp, "Q")) (*card).valor = cq;
            else if(!strcmp(temp, "K")) (*card).valor = ck;
            else (*card).valor = atoi(temp);
        }

        temp[ptemp] = cartaStr[i];
        temp[ptemp+1] = '\0';
        ptemp++;

        if(i == strlen(cartaStr)-1)
        {
            if(!strcmp(temp, "♥")) (*card).naipe = copas;
            else if(!strcmp(temp, "♦")) (*card).naipe = ouro;
            else if(!strcmp(temp, "♣")) (*card).naipe = paus;
            else if(!strcmp(temp, "♠")) (*card).naipe = espada;
        }
    }
}

void cartaPStr(char cartaStr[MAX_TAM_CARTA_STR], carta card)
{
    char valStr[3], naipStr[4];

    if(card.valor == ca) strcpy(valStr, "A");
    else if(card.valor == cj) strcpy(valStr, "J");
    else if(card.valor == cq) strcpy(valStr, "Q");
    else if(card.valor == ck) strcpy(valStr, "K");
    else if(card.valor == cvoid) fprintf(stderr, "Erro: convertendo carta void (valor)\n");
    else sprintf(valStr, "%d", card.valor); //itoa(val, valStr, 3); //converte números inteiros em string

    if(card.naipe == copas) strcpy(naipStr, "♥");
    else if(card.naipe == ouro) strcpy(naipStr, "♦");
    else if(card.naipe == paus) strcpy(naipStr, "♣");
    else if(card.naipe == espada) strcpy(naipStr, "♠");
    else if(card.naipe == nvoid) fprintf(stderr, "Erro: convertendo carta void (naipe)\n");

    sprintf(cartaStr, "%s%s", valStr, naipStr);
}

void trocaCarta(carta *card1, carta *card2)
{
    carta temp;

    temp = *card1;
    *card1 = *card2;
    *card2 = temp;
}