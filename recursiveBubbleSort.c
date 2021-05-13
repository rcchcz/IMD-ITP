#include <stdlib.h>
#include <stdio.h>

void copiaVetor(int v[], int v_o[], int t) {
    for(int i = 0; i < t; i++) {
        v_o[i] = v[i];
    }
}

void bubbleSortRecursivo(int v[], int v_o[], int t) { // descending order
    if(t == 1) return;
    int aux;
    for(int i = 0; i < t-1; i++) {
        if(v_o[i] < v_o[i+1]) {
            aux = v_o[i];
            v_o[i] = v_o[i+1];
            v_o[i+1] = aux;                
        }
    }
    bubbleSortRecursivo(v, v_o, t-1); 
}

/*
void bubbleSortRecursivo(int v[], int v_o[], int t) { // ascending order
    if(t == 1) return;
    int aux;
    for(int i = 0; i < t-1; i++) {
        if(v_o[i] > v_o[i+1]) {
            aux = v_o[i];
            v_o[i] = v_o[i+1];
            v_o[i+1] = aux;                
        }
    }
    bubbleSortRecursivo(v, v_o, t-1); 
}
*/

int main() {
    int N;
    scanf("%d", &N);
    int v[N];
    int v_ord[N];
    srand(1); // uses the default seed for the rand function
    for(int i = 0; i < N; i++) {
        int rand_num = rand()%100; // generates a random number between 0 and 99
        v[i] = rand_num;
    }
    copiaVetor(v, v_ord, N);
    bubbleSortRecursivo(v, v_ord, N);
    for(int i = 0; i < N; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
    for(int i = 0; i < N; i++) {
        printf("%d ", v_ord[i]);
    }
}