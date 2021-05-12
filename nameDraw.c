// studying pointers and dynamic memory allocation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sorteado(int x, int *nomesSorteados, int N) {
    for(int i = 0; i < N; i++) {
        if(x == nomesSorteados[i]) return 1;
    }
    return 0;
}

int main() {
    char **PARTICIPANTES = NULL;
    char entrada[100];
    char *nome;
    int N = 0;
    int S;

    // names input
    while(1) {
        fgets(entrada,100,stdin);
        if(strcmp(entrada, "acabou\n") == 0) break;
        int tamEntrada = strlen(entrada);
        entrada[--tamEntrada] = '\0';
        nome = malloc(tamEntrada*sizeof(char));
        strcpy(nome,entrada);
        PARTICIPANTES = realloc(PARTICIPANTES,(N+1)*sizeof(char*));
        PARTICIPANTES[N] = nome;
        N++;
    }

    // seed
    scanf("%d", &S);
    srand(S);

    // stores the order of the names drawn
    int *nomesSorteados = calloc(N,sizeof(int));

    // name order draw
    for(int i = 0; i < N; i++) {
        int x;
        do {
            x = 1+rand()%N;
        } while(sorteado(x,nomesSorteados,N));
        nomesSorteados[i] = x;
    }

    // prints names in the order they were drawn
    for(int i = 0; i < N;i++) {
        printf ("%s\n", PARTICIPANTES[nomesSorteados[i]-1]);
    }

    // freeing the memory allocated to each string
    for(int i = 0; i < N; i++) free(PARTICIPANTES[i]);

    // freeing the memory allocated to the array of pointers
    free(PARTICIPANTES);

    return 0;
}