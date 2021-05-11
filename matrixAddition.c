#include <stdio.h>

int main(void) {
    int l, c;
    scanf("%d %d", &l, &c);

    #define L l
    #define C c
    int A[L][C];
    int B[L][C];
    int soma[L][C];

    for(int i = 0; i < L; i++) {
        for(int j = 0; j < C; j++) {
            scanf("%d", &A[i][j]);
        }
    }

    for(int i = 0; i < L; i++) {
        for(int j = 0; j < C; j++) {
            scanf("%d", &B[i][j]);
        }
    }

    for(int i = 0; i < L; i++) {
        for(int j = 0; j < C; j++) {
            soma[i][j] = A[i][j] + B[i][j];
        }
    }

    for(int i = 0; i < L; i++) {
        for(int j = 0; j < C; j++) {
            printf("%d ", soma[i][j]);
        }
        printf("\n");
    }

    return 0;
}