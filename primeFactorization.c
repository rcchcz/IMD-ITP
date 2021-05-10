#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int n;
    int f = 2;
    int i = 0;

    scanf("%d", &n);
    int vetor[n]; //stores all prime factors

    if(n > 1) {
        while(n>1) {
            if(n%f == 0) {
                n = n/f;
                vetor[i] = f;
                i++;
            } else f++;
        }
    } else printf("Erro, número precisa ser maior do que 1!");

    int cont = 0;
    int q = 0;
    int controle = 0;
    f = vetor[0];

    while(q <= i) {
        if(controle == 0) {
            if(f == vetor[q]) {
                cont++;
                q++;
            } else {
                printf("%d^%d", vetor[q-1], cont);
                f = vetor[q];
                cont = 1;
                controle = 1;
                q++;
            }
        } else if(controle == 1) {
            if(f == vetor[q]) {
            cont++;
            q++;
            } else {
            printf("*%d^%d", vetor[q-1], cont);
            f = vetor[q];
            cont = 1;
            q++;
            }
        }
    }   

    return 0;
}