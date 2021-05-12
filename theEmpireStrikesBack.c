#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int validaK(int k[]) {
    for(int i = 0; i < 4; i++) {
        if(k[i] == -1) return 0;
        return 1;
    }
}

void key(char c[], char kp[], int k[]) {
    const char S[] =
    {'0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z','.',',','?',' '};
    int sizeC = strlen(c);
    int jC[sizeC];
    int sizeKP = strlen(kp);
    int jKP[sizeKP];

    for(int i = 0; i < sizeC; i++) { // positions of C[] in S[]
        for(int j = 0; j < 40; j++) {
            if(c[i] == S[j]) jC[i] = j;
        }
    }

    for(int i = 0; i < 27; i++) {  // positions of KP[] in S[]
        for(int j = 0; j < 40; j++) {
            if(kp[i] == S[j]) jKP[i] = j;
        }
    }

    int cont = 0;
    int test = 0;
    int indexKP = 0;
    int delta;
    for(int i = 0; i < sizeC; i++) {
        if(jKP[indexKP] > jC[i]) { 
            delta = 40 + jC[i] - jKP[indexKP];
        } else {
            delta = jC[i] - jKP[indexKP];
        }
        if(cont == 4) cont = 0;
        if(k[cont] == delta || k[cont] == -1) {
            k[cont] = delta;
            test++;
            indexKP++;
        } else {
            i -= 4;
            test = indexKP = 0;
            k[0] = k[1] = k[2] = k[3]= -1;
        }
        if(test == 27) break;
        cont++;
    }
    if(test != 27) k[0] = k[1] = k[2] = k[3] = -1;
}

char decode(int k[], char c[], int sizeK, int sizeC) {
    const char S[] =
    {'0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z','.',',','?',' '};
    int index = 0;
    for(int i = 0; i < sizeC; i++) {
        for(int j = 0; j < 40; j++) {
            if(index == sizeK && c[i] != '\0') index = 0;
            if(S[j]==c[i]) {
                if(j - k[index] < 0) {
                    printf("%c", S[39 - (k[index] - j - 1)]);
                    index++;
                } else {
                    printf("%c", S[j - k[index]]);
                    index++;
                }
            }
        }   
    }
}

int main(void) {
    int K[4] = {-1,-1,-1,-1};
    char C[203];
    char KP[] = "QUE A FORCA ESTEJA COM VOCE"; // strlen = 27

    fgets(C, 203, stdin);

    int tamC = strlen(C);

    C[--tamC] = 0;

    key(C, KP, K);
    if(validaK(K)) {
        for(int i = 0; i < 4; i++) {
            printf("%i", K[i]);
        }
        printf("\n");
        decode(K, C, 4, tamC);
    } else {
        printf("Mensagem nao e da Resistencia!"); 
    }

    return 0;
}