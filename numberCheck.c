/** This program receives 5 integers numbers and prints
 * how many of them are even, odd, positive and negative, 
 * in this order.
 */
 
#include <stdio.h>

int main(void) 
{
    int n;
    int par, impar, positivo, negativo;
    par = impar = positivo = negativo = 0;

    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &n);
        if(n > 0) positivo++;
        if(n < 0) negativo++;
        if(n%2) impar++;
        else par++;
    }

    printf("%d valores pares\n%d valores impares\n%d valores positivos\n%d valores negativos\n", par, impar, positivo, negativo);

    return 0;
}