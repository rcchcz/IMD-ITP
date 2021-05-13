#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int adicionarLinhas(int n, char *linhas[], char str[]) {
    static int contNL;
    if(contNL == n) return 0;
    if(linhas[contNL] == NULL) {
        linhas[contNL] = malloc(strlen(str)*sizeof(char)+1);
        strcpy(linhas[contNL],str);
    } else {
        linhas[contNL] = realloc(linhas[contNL], (strlen(linhas[contNL])+strlen(str))*sizeof(char)+1);
        strcat(linhas[contNL],str);
    }
    if(str[strlen(str)-1]=='\n') contNL++; 
    return 1;
}

void imprimirLinhas(int n, char *linhas[]) {
    for(int i = 0; i < n; i++) printf("%s", linhas[i]);
}

void liberarLinhas(int n, char *linhas[]) {
    for(int i = 0; i < n; i++) free(linhas[i]);
}

int main() {
    char str[10];
    int N;   
    scanf("%d\n", &N);
    char *linhas[N];

    for(int i = 0; i < N; i++) linhas[i] = NULL;   

    do {
        fgets(str,10,stdin);
    } while(adicionarLinhas(N,linhas,str));

    printf("Texto liberado pelo Ministro\n");
    imprimirLinhas(N, linhas);

    liberarLinhas(N, linhas);
    return 0;
}