#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int *fromJsonString_int(char str[], int *t) {
    int index = 0;
    int numero;
    int *vetorInteiro = NULL;
    char *token = strtok(str, "[, ]");
    while(token != NULL) { 
        numero = atoi(token);
        if(index) {
            vetorInteiro = realloc(vetorInteiro,(index+1)*sizeof(int));
            vetorInteiro[index] = numero;
        } else {
            vetorInteiro = malloc(1*sizeof(int));
            vetorInteiro[index] = numero;
        }    
        index++;
        token=strtok(NULL, "[, ]"); 
    }
    *t = index;
    return vetorInteiro;
}

double *fromJsonString_double(char str[], int *t) {
    int index = 0;
    double numero;
    double *vetorDouble = NULL;
    char *token = strtok(str, "[, ]");
    while(token != NULL) { 
        numero = atof(token);
        if(index) {
            vetorDouble=realloc(vetorDouble,(index+1)*sizeof(double));
            vetorDouble[index]=numero;
        } else {
            vetorDouble = malloc(1*sizeof(double));
            vetorDouble[index] = numero;
        }    
        index++;
        token = strtok(NULL, "[, ]"); 
    }
    *t = index;
    return vetorDouble;
}

int main(void) {
    int tam;
    int *vetorInteiro = NULL;
    double *vetorDouble = NULL;
    int N;
    scanf("%d\n",&N);
    int auxN = 0;
    char entrada[200];
    int tamEntradaAux;
    int valorInteiro;

    while(1) {
        if(auxN == N) break;
        valorInteiro = 1;
        fgets(entrada,200,stdin);
        tamEntradaAux = strlen(entrada);
        entrada[--tamEntradaAux] = '\0';
        auxN++;
        for(int i = 0; i < tamEntradaAux; i++) {
            if(entrada[i] == '.'){
                valorInteiro = 0;
                break;
            }
        }

        if(valorInteiro) {
            vetorInteiro = fromJsonString_int(entrada, &tam);
            if(tam) {
                for(int i = 0; i < tam; i++) {
                    printf("%d ", vetorInteiro[i]);
                }
                printf("\n");
                free(vetorInteiro);
            } else {
                printf("vetor vazio\n");
            }
        } else {
            vetorDouble = fromJsonString_double(entrada, &tam);
            if(tam) {
                for(int i = 0; i < tam; i++) {
                    printf("%f ", vetorDouble[i]);
                }
                printf("\n");
                free(vetorDouble);
            } else {
                printf("vetor vazio\n");
            }
        }
    }    
    return 0;
}