#include <stdio.h>

int main(void) {
    int s, n, m, v;
    scanf("%d %d", &s, &n);

    #define S s

    int simbolos[S-1];

    for(int i = 0; i < S; i++) {
        simbolos[i] = i; //creates the array with all the symbols
    }

    for(int i=0; i<n; i++) {
        scanf("%d", &m);
        for(int j = 0; j < m; j++) {
            scanf("%d", &v);
            for(int k = 0; k < S; k++) {
                if(simbolos[k] == v) simbolos[k] = -1; //invalidates collected values
            }
        }
    }

    //prints the array
    int controle = 0;
    for(int i = 0; i < S; i++) {
        if(simbolos[i] != -1) controle = 1;
    }
    if(controle) {
        printf("[ ");
        for(int i = 0; i < S; i++) {
            if(simbolos[i] != -1) {
                printf("%d", simbolos[i]);
                if(simbolos[i] != S-1) printf(", ");
            }
        }
        printf(" ]");
    } else {
        printf("[ ]");
    }

    return 0;
}