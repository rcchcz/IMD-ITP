#include <stdio.h>

typedef struct {
    int numerador;
    int denominador;
} fracao;

fracao add(fracao a, fracao b) {
    fracao result;
    result.denominador = a.denominador*b.denominador;
    result.numerador = (a.numerador*result.denominador)/a.denominador+(b.numerador*result.denominador)/b.denominador;
    return result;
}

fracao mult(fracao a, fracao b) {
    fracao result;
    result.numerador = a.numerador*b.numerador;
    result.denominador = a.denominador*b.denominador;
    return result;
}

fracao inv(fracao a) {
    fracao result;
    result.numerador = a.denominador;
    result.denominador = a.numerador;
    return result;
}

fracao div(fracao a, fracao b) {
    fracao result;
    result = mult(a,inv(b));
    return result;
}

void corrigeSinal(fracao *a) {
    if(a->denominador < 0) {
        a->numerador *= -1;
        a->denominador *= -1;
    }
}

void imprimeFracao(fracao a) {
    printf("%d/%d\n", a.numerador, a.denominador);
}

int main(void) {
    fracao a, b, result;
    char operacao;

    scanf("%d/%d %d/%d %c", &a.numerador, &a.denominador, &b.numerador, &b.denominador, &operacao);

    switch(operacao) {
        case 'a':
            result = add(a,b);
            break;
        case 'm':
            result = mult(a,b);
            break;
        case 'd':
            result = div(a,b);
            break;
    }

    corrigeSinal(&result);

    imprimeFracao(result);

    return 0;
}