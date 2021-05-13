#include <stdio.h>

/*
funcionamento de bin(int z):
por causa do teorema do quociente-resto, z%2 eh igual a 0 ou 1
seja z = 10
(i) primeiro, ocorre as chamadas sucessivas:
bin(10) -> bin(5) -> bin(2) -> bin(1)
(ii) em bin(1), z==1 eh verdade, comeca a desempilhagem e os prints:
bin(1) printa 1 | bin(2) printa 2%2, que eh 0 | bin(5) printa 5%2, que eh 1 | bin(10) printa 10%2, que eh 0
(iii) ou seja, a saida do programa eh 1010
*/

void bin(int z) {
    if(z == 0) printf("0");
        else if(z == 1) printf("1");
        else {   
            bin(z/2);
            printf("%d", z%2);
        }
}

int main(void) {
    int z;
    scanf("%d", &z);
    bin(z);
    return 0;
}