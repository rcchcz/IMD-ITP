// Studying pointers and dynamic memory allocation.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *soma(int *a, int *b, int n) {
    int *c = malloc(n*sizeof(int));
    for(int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
    return c;
}

int vetor(int **a) {
    int x = 0;
    char entrada[100];
    int tamA = 0;
    fgets(entrada,100,stdin);
    char *texto = strtok(entrada, " ");
    while(texto != NULL) {
        sscanf(texto,"%d",&x);
        (*a) = realloc((*a), (tamA + 1)*sizeof(int));
        (*a)[tamA] = x;
        tamA++;
        texto = strtok(NULL, " ");
    }
    return tamA;
}

int main (void) {
    int *a, *b, *c;
    a = b = c = NULL;
    int tamA, tamB;
    tamA = tamB = 0;

    tamA = vetor(&a);
    tamB = vetor(&b);

    if(tamA != tamB) {
        printf("Vetores de tamanhos diferentes!");
        return 1;
    }

    c = soma(a,b,tamA);

    for(int i = 0; i < tamA; i++) {
        printf("%d ", c[i]);
    }

    return 0;
}