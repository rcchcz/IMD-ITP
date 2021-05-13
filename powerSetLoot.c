#include <stdio.h>
#include <stdlib.h>

int *melhorLoot;

typedef struct {
    char nome[20];
    int valor;
    int peso;
} Item;

void leLoot(Item *v) {
    scanf("%s %d %d", v->nome, &v->valor, &v->peso);
}

void combinaLoot(Item lootInicial[], int sacola[], int q, int p) {
    for(int i = 0; i < q; i++) {
        if(sacola[1] + lootInicial[i].peso <= p && sacola[i+2] == 0) {
        sacola[0] += lootInicial[i].valor;
        sacola[1] += lootInicial[i].peso;
        sacola[i+2] = 1;
        combinaLoot(lootInicial, sacola, q, p);
        sacola[0] -= lootInicial[i].valor;
        sacola[1] -= lootInicial[i].peso;
        sacola[i+2] = 0;
        }
    }
    if(sacola[0] > melhorLoot[0]) {
        for(int i = 0; i < q+2; i++) {
            melhorLoot[i] = sacola[i];
        }
    }
}

void printLoot(Item lootInicial[], int melhorLoot[], int q) {
    if(melhorLoot[0] == 0) printf("Nada para carregar...");
    else {
        printf("Inventario final:\n");
        for(int i = 0; i < q; i++) {
            if(melhorLoot[i+2] == 1) printf("Item: %s\n", lootInicial[i].nome);
        }
        printf("Valor total: %d\n", melhorLoot[0]);
    }
}

int main(void) { 
    int Q, P;
    int *sacola;
    scanf("%d %d", &Q, &P);

    melhorLoot = calloc((Q+2),sizeof(int));
    sacola = calloc((Q+2),sizeof(int));

    Item lootInicial[Q];
    for(int i = 0; i < Q; i++) {
        leLoot(&lootInicial[i]);
    }
    combinaLoot(lootInicial, sacola, Q, P);
    printLoot(lootInicial, melhorLoot, Q);
    return 0;
}