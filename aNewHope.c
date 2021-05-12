#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char decode(char k[], char p[], int sizeK, int sizeP) {
    const char S[] =
    {'0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z','.',',','?',' '};
    int index = 0;
    for(int i = 0; i < sizeP; i++) {
        for(int j = 0; j < 40; j++) {
            if(index == sizeK && p[i] != '\0') index = 0;
            if(S[j] == p[i]) {
                if(k[index] - 48 + j > 39) {
                    printf("%c", S[(k[index] - 48) - (39 - j) - 1]);
                    index++;
                } else {
                    printf("%c", S[j + (k[index] - 48)]);
                    index++;
                }
            }
        }   
    }
}

int validaK(char k[], int tamK) {
    if(tamK == 4) {
        for(int i = 0; i < tamK; i++) {
            if(k[i] < 48 || k[i] > 57) return 0;
        }
    } else if(tamK != 4) return 0;
    return 1;
}

int validaP(char p[], int tamP) {
    int valido = 1;
    for(int i = 0; i < tamP; i++) {
        if(!(((p[i] >= 48 && p[i] <= 57) || (p[i] >= 65 && p[i] <= 90)) || ((p[i] == 44 || p[i] == 46) || (p[i] == 63 || p[i] == 32)))) return 0;
    }
    return 1;
}

int main(void) {
    char K[7];
    char P[203];
    fgets(K, 7, stdin);
    fgets(P, 203, stdin);

    int tamK = strlen(K);
    int tamP = strlen(P);

    K[--tamK] = 0;
    P[--tamP] = 0;

    if(validaK(K, tamK)) {
        if(validaP(P, tamP)) decode(K, P, tamK, tamP);
            else printf("Caractere invalido na entrada!");
    } else {
        printf("Chave invalida!");
    }
    return 0;
}