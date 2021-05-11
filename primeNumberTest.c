// This program reads n lines each containing an integer x
// and prints whether x is a prime or not.
// This is part of an introductory study of functions.

#include <stdio.h>

void primo(int x);

int main(void) {
    int n, x;

    scanf("%d", &n);

    for(int cont_testes = 0; cont_testes < n; cont_testes++) {
        scanf("%d", &x);
        primo(x);
    }

    return 0;
}

void primo(int x) {
    int cont_div = 0;
    int div = 1;

    while(div <= x) {
        if(x%div == 0) {
        cont_div++;
        div++;
        } else div++;
    }

    if(cont_div == 2) printf("%d eh primo\n", x);
        else printf("%d nao eh primo\n", x);

    return;
}