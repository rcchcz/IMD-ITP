// string inversion using pointer arithmetics

#include <stdio.h>

int meustrlen(char *str) {
    int n = 0;
    while(*(str++)!=0) n++;
    return n;
}

int main(void) {
    char entrada[100];
    fgets(entrada, 100, stdin);
    int tam = meustrlen(entrada);
    entrada[--tam] = 0;
    char *ptr1 = entrada;
    char *ptr2 = entrada + tam - 1;
    while(ptr1 < ptr2) {
        char temp = *ptr1;
        *ptr1 = *ptr2;
        *ptr2 = temp;
        ptr1++;
        ptr2--;
    }
    printf("%s\n", entrada);
    return 0;
}