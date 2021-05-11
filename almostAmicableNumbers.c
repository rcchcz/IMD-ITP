// In number theory, Pythagoras called a pair of integers amicable (“friendly”)
// if each was the sum of the proper divisors of the other. This program considers
// a difference in module of up to 2, something like "almost amicable numbers".

#include <stdio.h>
#include <stdlib.h>

int soma_div(int a);
int colegas(int a, int b);

int main(void) {
    int a,b;
    scanf("%d %d", &a, &b);
    
    if(colegas(a,b)) printf("S");
        else printf("N");

    return 0;
}

int soma_div(int a) {
    int cont = 0;
    for(int div = 1; div < a; div++) {
        if(a%div == 0) cont+=div;
    }
    return cont;
}


int colegas(int a, int b) {
    if(abs(soma_div(a) - b) <= 2 && abs(soma_div(b) - a) <= 2) return 1;
    return 0;
}