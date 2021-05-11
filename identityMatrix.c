#include <stdio.h>

int main(void) {
    int n;
    scanf("%d", &n);

    #define ordem n
    int id[ordem][ordem];

    for(int i = 0; i < ordem; i++) {
        for(int j = 0; j < ordem; j++) {
            if(i == j) id[i][j] = 1;
                else id[i][j] = 0;
        }
    }

    for(int i = 0; i < ordem; i++) {
        for(int j = 0; j < ordem; j++) {
            printf("%d ", id[i][j]);
        }
        printf("\n");
    }

    return 0;
}