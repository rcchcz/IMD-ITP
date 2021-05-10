// This program prints the digit of a given position p of an
// integer x, considering that 0 is the first digit to the right.
// This is part of an introductory study of functions.

#include <stdio.h>

int dig(int pf, int xf);

int main(void) {
    int x, p;
    scanf("%d %d", &x, &p);
    dig(x,p);
    return 0;
}

int dig(int xf, int pf){
    int res;
    for(int i = 0; i <= pf; i++) {
        res = (xf%10);
        xf = (xf/10) - ((xf%10)/10);
    }
    return printf("O digito na posicao solicitada e %d", res);
}
