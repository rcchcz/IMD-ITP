#include <stdio.h>
#include <string.h>

int youLose = 0;

void imprimeBg(int N, int M, char m[N][M]) {
    for(int i = 0; i < M+2; i++) printf("=");
    printf("\n");
    for(int i = 0; i < N; i++) { 
        for(int j = 0; j < M; j++) {
            printf("%c", m[i][j]);
        }
        printf("\n");
    }
    return;
}

int verifica(int l, int c, int N, int M, int mSistema[N][M]) {
    int nBombas = 0;
    for(int i = l-1; i < l+2; i++) {
        for(int j = c-1; j < c+2; j++) {
            if(i >= 0 && i < N && j >= 0 && j < M) nBombas += mSistema[i][j];
        }
    }
    return nBombas;
}

void clica(int l, int c, int N, int M, int mSistema[N][M], char mUser[N][M]) {
    if(l >= 0 && l < N && c >= 0 && c < M) { // checking if the coordinate is within the perimeter of the matrix
        int nBombas = 0;
        if(mSistema[l][c] == 1) youLose = 1;
        else {
            nBombas = verifica(l, c, N, M, mSistema);
            mUser[l][c] = nBombas + '0';
            if(nBombas == 0) {
                for(int i = l-1; i < l+2; i++) {
                    for(int j = c-1; j < c+2; j++) {
                        if(i >= 0 && i < N && j >= 0 && j < M && mUser[i][j] == '*') clica(i, j, N, M, mSistema, mUser);
                    }
                }
            }
        }
    }
}

void revelaBG(int l, int c, int N, int M, int youLose, int mSistema[N][M], char mUser[N][M]) {
    int nBombas;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            if(mSistema[i][j] == 1) mUser[i][j] = 'B'; // reveals the mines in the user matrix (mUser)
            else {
                nBombas = verifica(i, j, N, M, mSistema);
                mUser[i][j] = nBombas + '0';
            } 
        } 
    }
    if(youLose) mUser[l][c] = 'X';
}

void marca(int l, int c, int N, int M, char mUser[N][M]) {
    mUser[l][c] = 'B'; // the user puts a 'B' in the coordinate when he suspects that there is a mine there
}

int main(void) {
    int N, M, B; 
    scanf("%d %d", &N, &M);
    scanf("%d", &B);

    int mSistema[N][M]; // reference matrix
    char mUser[N][M]; // user matrix

    for(int i = 0; i < N; i++) { // initializes mSystem with 0 and mUser with *
        for(int j = 0; j < M; j++) {
            mSistema[i][j] = 0;
            mUser[i][j] = '*';
        }
    }

    int l, c; 
    for(int i = 0; i < B; i++) {
        scanf("%d %d", &l, &c);
        l--;
        c--;
        mSistema[l][c] = 1;
    }

    int J; 
    char jogada[10];
    scanf("%d", &J);
    for(int i = 0; i < J; i++) {
        scanf(" %s %d %d", jogada, &l, &c); 
        l--;
        c--;
        if(strcmp(jogada, "Clica")) {
            marca(l, c, N, M, mUser);
            imprimeBg(N, M, mUser);
        } else {
            clica(l, c, N, M, mSistema, mUser);
            if(youLose) break;
            imprimeBg(N, M, mUser);   
        }
    }

    if(youLose) {
        printf("CABUUUUM!\nGame Over....\n");
    } else {
        printf("Você sobreviveu!\n");
    }

    revelaBG(l, c, N, M, youLose, mSistema, mUser);
    imprimeBg(N, M, mUser);

    return 0;
}