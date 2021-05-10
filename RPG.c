#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main()
{
    int n, v, a;
    char c;
    char *res;

    scanf("%d %d", &n, &v);

    while(n > 0)
    {
        scanf("%s %d", &c, &a);
        if(a > 14)
        {
            if(v > 0)
            {
                if(c=='A') v -= 10, res = "Alyson";
                if(c=='I') v -= 10, res = "Isaac";
                if(c=='R') v -= 6, res = "Rafaela";
                if(c=='W') v -= 8, res = "Wellington";
                if(c=='S') v -= 4, res = "Salgado";
                if(c=='C') v -= 1, res = "Careca";
            }
        }
        n--;
    }

    if(v > 0) printf("Casa caiu!")
        else printf("%s derrotou o dragão!", res);

    return 0;
}