#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
@brief gera um número aleatório no intervalo [min,max]
@param min o número minimo no range
@param max o número máximo no range
@return um número aleatório no intervalo [min,max]
*/

// generates pseudo-random integers for the values array
int rand_int_range(int min, int max) {
    int range = max - min + 1;
    return min + rand()%range;
}

// creates the values ​​(valores) array
int *criarVetorAleatorio(int tamanho, int minimo, int maximo) {
    int tamanhoRealVetor = tamanho + 3;
    int *valores = malloc(tamanhoRealVetor*sizeof(int));
    valores[0] = tamanho;
    valores[1] = minimo;
    valores[2] = maximo;
    for(int i = 3; i < tamanhoRealVetor; i++) {
        valores[i] = rand_int_range(minimo, maximo);
    }
    return valores;
}

int *criarHistograma(int *vetor) {
    int tamanhoVetor = 3 + vetor[0];
    int minimo = vetor[1];
    int maximo = vetor[2];
    int tamanhoHist = maximo - minimo + 3; // creates a histogram as follows: [min, max, valorMin, valorMin+1, valorMin+2...valorMax]
    int *histograma = calloc(tamanhoHist,sizeof(int));
    histograma[0] = minimo; // minimum
    histograma[1] = maximo; // maximum

    // inserts values ​​in the histogram
    int index = 2;
    for(int aux = minimo; aux <= maximo; aux++) {
        for(int i = 3; i < tamanhoVetor; i++) {
            if(vetor[i] == aux) histograma[index]++;
        }
        index++;
    } 
    return histograma;
}

float *criarPorcentagens(int *vetorHist) {
    int minimo = vetorHist[0];
    int maximo = vetorHist[1];
    int totalElementos = 1;
    int somaElementos = 0;
    // counts elements
    for(int i = minimo; i < maximo; i++) {
        totalElementos++;
    }
    // counts the total occurrences
    int tamanhoHist = 2 + totalElementos;
    for(int i = 2; i < tamanhoHist; i++) {
        somaElementos += vetorHist[i];
    }
    // creates the percentage array
    float *porcentagens = calloc(totalElementos,sizeof(float));
    int index = 0;
    for(int i = 2; i < tamanhoHist; i++) {
        porcentagens[index] = (vetorHist[i]*100.0)/somaElementos;
        index++;
    }
    return porcentagens;
}

void imprimePorcentagens(float *porcentagens, int *histograma) {
    int minimo = histograma[0];
    int maximo = histograma[1];
    int index = 0;
    printf("Valor |Qtdade |Porcent\n");
    while(minimo <= maximo) {
        printf("%d |%d |%.2f%%\n", minimo, histograma[index+2], porcentagens[index]);
        minimo++;
        index++;
    }
}

void liberar(int *valores, float *porcentagens, int *histograma) {
    free(valores);
    free(porcentagens);
    free(histograma);
}

int main() {
    int tamanho, maximo, minimo;
    scanf("%d", &tamanho);
    scanf("%d %d", &minimo, &maximo);
    int *valores = criarVetorAleatorio(tamanho, minimo, maximo);
    int *histograma = criarHistograma(valores);
    float *porcentagens = criarPorcentagens(histograma);
    imprimePorcentagens(porcentagens, histograma);
    liberar(valores, porcentagens, histograma);

    return 0;
}