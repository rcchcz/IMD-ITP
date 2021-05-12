// This program is a case-sensitive counter. It reads a string w and prints
// 2 integers: the number of uppercase and lowercase letters, respectively.

#include <stdio.h>

int main(void) {
    char w[31];
    fgets(w, 31, stdin);

    int mai, min;
    mai = min = 0;

    int i = 0;
    while(w[i] != '\0') {
        if(w[i] >= 65 && w[i] <= 90) mai++;
            else if(w[i] >= 97 && w[i] <= 122) min++;
        i++;
    }

    printf("%i %i", mai, min);
    return 0;
}