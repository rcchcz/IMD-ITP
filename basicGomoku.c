// The objective of the gomoku game is to place five stones of the same color 
// consecutively in a vertical, horizontal or diagonal sequence. This program 
// considers only vertical or horizontal sequences. It reads from the data 
// entry the state of a 15x15 board and prints 1 if the player with the black 
// stones won, 2 if the player with the white stones won or 0 if there is still 
// no winner. On the board, 1 indicates a black stone, 2 indicates a white stone 
// and 0 indicates that there is no stone in that position. Consider that a board 
// does not have two simultaneous winners (there will be a maximum of one).

#include <stdio.h>

int main(void) {
    int tabuleiro[15][15];
    int cont1, cont2;
    cont1 = cont2 = 0;

    for(int i = 0; i < 15; i++) { //receives board
        for(int j = 0; j < 15; j++) {
            scanf("%d", &tabuleiro[i][j]);
        }
    }

    for(int i = 0; i < 15; i++) { //analyze lines
        for(int j = 0; j < 15; j++) {
            if(tabuleiro[i][j] == tabuleiro[i][j+1]) {
                if(tabuleiro[i][j] == 1 && tabuleiro[i][j+1] == 1 && tabuleiro[i][j+2] == 1 && tabuleiro[i][j+3] == 1 && tabuleiro[i][j+4] == 1) cont1 = 1;
                if(tabuleiro[i][j] == 2 && tabuleiro[i][j+1] == 2 && tabuleiro[i][j+2] == 2 && tabuleiro[i][j+3] == 2 && tabuleiro[i][j+4] == 2) cont2 = 1;
            }
        }
    }

    for(int i = 0; i < 15; i++) { //analyze columns
        for(int j = 0; j < 15; j++) {
            if(tabuleiro[i][j] == tabuleiro[i+1][j]) {
                if(tabuleiro[i][j] == 1 && tabuleiro[i+1][j] == 1 && tabuleiro[i+2][j] == 1 && tabuleiro[i+3][j] == 1 && tabuleiro[i+4][j] == 1) cont1 = 1;
                if(tabuleiro[i][j] == 2 && tabuleiro[i+1][j] == 2 && tabuleiro[i+2][j] == 2 && tabuleiro[i+3][j] == 2 && tabuleiro[i+4][j] == 2) cont2 = 1;
            }
        }
    }

    if(cont1) printf("1");
    if(cont2) printf("2");
    if(cont1 == 0 && cont2 == 0) printf("0");

    return 0;
}