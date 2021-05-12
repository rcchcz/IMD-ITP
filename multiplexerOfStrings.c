#include <stdio.h>
#include <string.h>

int main(void) {
    char A[41];
    char B[41];
    fgets(A, 41, stdin);
    fgets(B, 41, stdin);

    int tamA = strlen(A);
    int tamB = strlen(B);

    A[--tamA] = 0;
    B[--tamB] = 0;

    int tam = strcmp(A,B); // compares the sizes

    if(tam == 0) { // tamA = tamB
        for(int i = 0; i < tamA; i++) {
            printf("%c%c", A[i], B[i]);
        }
    } else if(tam > 0) { // tamA > tamB
        for(int i = 0; i < tamA; i++) {
            if(i < tamB) printf("%c%c", A[i], B[i]);
                else printf("%c", A[i]);
        }
    } else { // tamB > tamA
        for(int i = 0; i < tamB; i++) {
            if(A[i] != '\0') printf("%c%c", A[i], B[i]);
                else printf("%c", B[i]);
        }
    }
    return 0;
}