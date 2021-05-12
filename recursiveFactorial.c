#include <stdio.h>
#include <math.h>

/*
int recursiveFactorial(int n) { // long version
    if(n == 0) return 1;
    return n*recursiveFactorial(n-1);
}
*/

int recursiveFactorial(int n) { // short version
    if(n) return n*recursiveFactorial(n-1);
    return 1;
}

int main(void) {
    int n;
    scanf("%i", &n);

    if(n >= 0) printf("%i", recursiveFactorial(n));
        else printf("Error: enter a non-negative integer.");

    return 0;
}