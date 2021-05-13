#include <stdio.h>

/*
(i) a = bq + r, 0 <= r < a
(ii) conforme o algoritmo de euclides, mdc(a,b) = mdc(b,r)
(iii) mdc(z,0) = z
*/

int mdc(int a, int b) {
    if(b == 0) return a;
    return mdc(b, a%b); 
}

int main(void) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    printf("MDC de %d, %d e %d: %d", a, b, c, mdc(mdc(a,b), c));
    return 0;
}