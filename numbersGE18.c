/**
 * This program receives 6 integers numbers and prints
 * how many of them are greater than or equal to 18.
 */ 

#include <stdio.h>

int main(void)
{
    int maiores = 0;
    int idade;

    for(int i = 0; i < 6; i++)
    {
        scanf("%d", &idade);
        if(idade>=18) maiores++;
    }

    printf("%d", maiores);

    return 0;
}