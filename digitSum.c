/**
 * This program receives 1 integer number and prints
 * the sum of its digits.
 */ 

#include <stdio.h>

int main(void)
{
    int n;
    int sum = 0;

    scanf("%d", &n);

    while(n >= 1)
    {
        sum += (n%10);
        n = (n/10) - ((n%10)/10);
    } 

    printf("%d", sum);

    return 0;
}