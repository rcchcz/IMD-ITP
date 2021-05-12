#include <stdio.h>
#include <string.h>

int main(void) {
    char s[61];
    fgets(s, 61, stdin);
    int tams = strlen(s);

    s[--tams] = 0;

    for(int i = 0; i < tams; i++) {
        if(s[i] >= 65 && s[i] <= 90) s[i] += 32;
        if((i == 0 && (s[i] >= 97 && s[i] <= 122)) || ((s[i-1] == 32) && (s[i] >= 97 && s[i] <= 122))) printf("%c", s[i] -= 32);
            else printf("%c", s[i]); 
    }
    return 0;
}