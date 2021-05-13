#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[300];
    int totalPartidas;
    int vitorias;
    int empates;
    int derrotas;
    int golsFeitos;
    int golsSofridos;
    int saldoGols;
    int pontos;
} Time;

void leituraTime(Time *vTime) {
    scanf("%[^;]; %d %d %d %d %d", vTime->nome, &vTime->vitorias, &vTime->empates, &vTime->derrotas, &vTime->golsFeitos, &vTime->golsSofridos);
    vTime->saldoGols = vTime->golsFeitos - vTime->golsSofridos;
    vTime->pontos = (3*vTime->vitorias) + vTime->empates;
    vTime->totalPartidas = vTime->vitorias + vTime->derrotas + vTime->empates; 
}

void ordenaTimes(int T, Time *vTimes) {
    Time aux; 
    for(int j = T-1; j >= 1; j--) { 
        for(int i = 0; i < j; i++) { 
            if(vTimes[i].pontos < vTimes[i+1].pontos) { 
                aux = vTimes[i]; 
                vTimes[i] = vTimes[i+1]; 
                vTimes[i+1] = aux; 
            } else if(vTimes[i].pontos == vTimes[i+1].pontos) {
                if(vTimes[i].vitorias < vTimes[i+1].vitorias) {
                    aux = vTimes[i]; 
                    vTimes[i] = vTimes[i+1]; 
                    vTimes[i+1] = aux;
                } else if(vTimes[i].vitorias == vTimes[i+1].vitorias) {
                    if(vTimes[i].saldoGols < vTimes[i+1].saldoGols) {
                        aux = vTimes[i]; 
                        vTimes[i] = vTimes[i+1]; 
                        vTimes[i+1] = aux;
                    }
                }
            } 
        } 
    } 
}

void imprimeTabelaTimes(int T, Time *vTime) {
    ordenaTimes(T, vTime);
    printf("Tabela do campeonato:\n");
    printf("Nome| Pontos| Jogos| Vitorias| Empates| Derrotas| Gols Pro| Gols Contra| Saldo de Gols");
    for(int i = 0; i < T; i++) {
        printf("%s| %d| %d| %d| %d| %d| %d| %d| %d", vTime[i].nome, vTime[i].pontos, vTime[i].totalPartidas, vTime[i].vitorias, vTime[i].empates, vTime[i].derrotas, vTime[i].golsFeitos, vTime[i].golsSofridos, vTime[i].saldoGols);
    }
    printf("\n\n");
    printf("Times na zona da libertadores:");
    for(int i = 0; i < 6; i++) {
        printf("%s", vTime[i].nome);
    }
    printf("\n\n");
    printf("Times rebaixados:");
    for(int i = T-1; i > T-5; i--) {
        printf("%s", vTime[i].nome);
    }
}

int main(void) {
    int T;
    scanf("%d", &T);
    Time times[T];
    for(int i = 0; i < T; i++) {
        leituraTime(&times[i]);
    }
    imprimeTabelaTimes(T, times);
    return 0;
}