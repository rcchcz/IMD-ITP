#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char w[21];
    fgets(w, 21, stdin);

    int size = strlen(w);

    w[--size] = '\0';

    int i = 0;
    int palindromo = 1;
    while(w[i] != '\0')
    {
        if(w[size - i - 1] == w[i]) i++;
        else
        {
            palindromo = 0;
            break;
        }
    }

    if(palindromo) printf("%s é um palíndromo", w);
        else printf("%s não é um palíndromo", w);
    
    return 0;
}