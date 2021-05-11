#include <stdio.h>

float media(char tipo, float a, float b, float c);
float media_antiga(float a, float b, float c);
float media_nova(float a, float b, float c);

int main(void) {
    char tipo;
    float a,b,c;
    scanf(" %c", &tipo);
    scanf("%f", &a);
    scanf("%f", &b);
    scanf("%f", &c);
    media(tipo,a,b,c);

    float res = media(tipo,a,b,c);

    printf("%.2f", res);

    return 0;
}

float media(char tipo, float a, float b, float c) {
    float res;
    if(tipo == 'A') res = media_antiga(a,b,c);
    if(tipo == 'N') res = media_nova(a,b,c);
    return res;
}

float media_antiga(float a, float b, float c) {
    return ((4*a) + (5*b) + (6*c))/15;
}

float media_nova(float a, float b, float c) {
    return (a + b + c)/3;
}