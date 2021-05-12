// This program receives from the user 2 strings, A and B, of up to
// 30 characters each and analyzes whether A is a substring of B. The
// program prints the position of the beginning of A in B. If A is not
// a substring of B, the program prints 0.

#include <stdio.h>
#include <string.h>

int main(void) {
    char A[31];
    char B[31];

    fgets(A, 31, stdin);
    fgets(B, 31, stdin);

    int sizeA = strlen(A);
    int sizeB = strlen(B);

    A[--sizeA] = '\0';
    B[--sizeB] = '\0';

    int controle = 1;
    int contador;
    int pos;
    for(int i = 0; i < sizeA; i++) {
        for(int j = 0; j < sizeB; j++) {
            if(A[i] == B[j]) {
                pos = j + 1;
                int k = 0;
                while(k < sizeA) {
                    while(j < sizeB) {
                        if(A[k] == B[j]) {
                            contador++;
                            j++;
                        } else break;
                    }
                    k++;
                }
                if(contador == sizeA) {
                    printf("%i", pos);
                    return 0;
                } else contador = 0;
                
            }
        }
    }

    if(controle) printf("%i", 0);

    return 0;
}