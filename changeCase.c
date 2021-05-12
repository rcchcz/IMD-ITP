// This program reads characters from the keyboard and converts uppercase
// alphabetic characters to lowercase and vice versa, displaying them on
// the screen. The program ignores non-alphabetic characters and stops 
// when the @ character is entered.

#include <stdio.h>

char converte(char c[]) {
    if(c[0] >= 65 && c[0] <= 90) return c[0] + 32; // ascii conversion: from upper to lower
        else if(c[0] >= 97 && c[0] <= 122) return c[0] - 32; // ascii conversion: from lower to upper
}

int main(void) {
    char l[2];
    int controle = 1;
    do { // receives character
        scanf(" %c", &l[0]);
        if((l[0] >= 65 && l[0] <= 90) || (l[0] >= 97 && l[0] <= 122)) {
            if(controle) {
                printf("%c", converte(l));
                controle = 0;
            } else {
                printf(" %c", converte(l));    
            }
        }    
    } while(l[0] != '@');
    return 0;
}

