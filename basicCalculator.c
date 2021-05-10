#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    char k;
    double n1, n2;
    
    do
    {
        scanf(" %c", &k);
        if(k != 'e'){
            scanf("%lf %lf", &n1, &n2);
            if(k == '+') printf("%.3f+%.3f=%.3f\n", n1, n2, n1 + n2);
            if(k == '-') printf("%.3f-%.3f=%.3f\n", n1, n2, n1 - n2);
            if(k == '*') printf("%.3f*%.3f=%.3f\n", n1, n2, n1 * n2);
            if(k == '/') printf("%.3f/%.3f=%.3f\n", n1, n2, n1 / n2);
            if(k == '^') printf("%.3f^%d=%.3f\n", n1, (int)n2, pow(n1, (int)n2));
        } else return -1;
    } while(k != 'e');

    return 0;
}