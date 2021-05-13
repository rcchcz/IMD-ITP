#include <stdio.h>

void bubbleSort(int vetor[], int tamanho) { 
    int aux; 
    for(int j = tamanho - 1; j >= 1; j--) { 
        for(int i = 0; i < j; i++) { 
            if(vetor[i] < vetor[i+1]) { 
                aux = vetor[i]; 
                vetor[i] = vetor[i+1]; 
                vetor[i+1] = aux; 
            } 
        } 
    } 
}

void insertionSort(int hand[]) {    
    int j, aux;  

    for(int i = 0; i < 5; i++) { 
        j = i; 

        while((j != 0) && (hand[j] > hand[j-1])) { 
            aux = hand[j]; 
            hand[j] = hand[j-1]; 
            hand[j-1] = aux; 
            j--;     
        } 
    } 
}

int main(void) {
    int hand[5] = {0,-2,-900,12,7};
    //insertionSort(hand);
    bubbleSort(hand, 5);
    for(int i = 0; i < 5; i++) {
        printf("%d ", hand[i]);
    }
    return 0;
}