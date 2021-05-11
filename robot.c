#include <stdio.h>

int main(void) {
    int l, c, i, j, m, cont;
    char d;
    cont = 0;

    scanf("%d %d", &l, &c);
    #define L l
    #define C c

    char mapa[L][C];

    for(int i = 0; i < L; i++) {
        for(int j = 0; j < C; j++) {
            scanf(" %c", &mapa[i][j]);
        }
    }

    scanf("%d %d", &i, &j);
    scanf(" %c", &d);
    scanf("%d", &m);

    i-=1; // equivalence between index and position
    j-=1; // equivalence between index and position

    while(cont < m) {
        if(d=='N') {
            if(mapa[i-1][j] == '.' && i != 0) i-=1;
                else if(mapa[i-1][j] == '*') d = 'O';
                    else if(mapa[i-1][j] == '_' || mapa[i-1][j] == '|' || i == 0) d = 'L';
        } else if(d == 'S') {
            if(mapa[i+1][j] == '.' && i + 1 != l) i+=1;
                else if(mapa[i+1][j] == '*') d = 'L';
                    else if(mapa[i+1][j] == '_' || mapa[i+1][j] == '|' || i + 1 == l) d = 'O';
        } else if(d == 'L') {
            if(mapa[i][j+1] == '.' && j + 1 != c) j += 1;
                else if(mapa[i][j+1] == '*') d = 'N';
                    else if(mapa[i][j+1] == '_' || mapa[i][j+1] == '|' || j + 1 == c) d = 'S';
        }else if(d == 'O') {
            if(mapa[i][j-1] == '.' && j != 0) j -= 1;
                else if(mapa[i][j-1] == '*') d = 'S';
                    else if(mapa[i][j-1] == '_' || mapa[i][j-1] == '|' || j == 0) d = 'N';
        }
        cont++;
    }

    printf("Posição final: %d %d", i + 1, j + 1);

    return 0;
}