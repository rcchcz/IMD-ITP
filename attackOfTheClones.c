#include <stdio.h>

int main(void) {
    int n, m, l, c, k, b, morto;
    k = b = morto = 0;
    scanf("%d %d", &n, &m); // map size

    #define N n+2 // map rows
    #define M m+2 // map columns
    #define B 2*n // bomb coordinate array

    int mapa[N][M];
    int bombas[B]; // stores the coordinates of the bombs
    scanf("%d %d", &l, &c); // jedi position

    for(int i = 0; i < N; i++) { // receives the values ​​of the bombs
        for(int j = 0; j < M; j++)  {
            if(i == 0 || j == 0 || i == N-1 || j == M-1) mapa[i][j] = 0;
                else scanf("%d", &mapa[i][j]);
        }
    }

    for(int i = 0; i < N; i++) { // radiation analysis
        for(int j = 0; j < M; j++) {
            if(mapa[i][j] > mapa[i-1][j] && mapa[i][j] > mapa[i-1][j+1] && mapa[i][j] > mapa[i][j+1] && mapa[i][j] > mapa[i+1][j+1] && mapa[i][j] > mapa[i+1][j] && mapa[i][j] > mapa[i+1][j-1] && mapa[i][j] > mapa[i][j-1] && mapa[i][j] > mapa[i-1][j-1]) {
                bombas[k] = i;
                k++;
                bombas[k] = j;
                k++;
            }
        }
    }

    for(int q = 0; q < k; q += 2) { // prints the bombing locations
        printf("Local %d: %d %d\n", b + 1, bombas[q], bombas[q+1]);
        if(l == bombas[q] && c == bombas[q+1]) morto = 1; // checks if the jedi has been hit
        b++;
    }

    if(morto) printf("Descanse na Força...");
        else printf("Ao resgate!");

    return 0;
}