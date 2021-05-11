#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int n, dist, maior;
    maior = 0;
    scanf("%d", &n); //receives the number of buildings
    #define N n
    int p[N]; //creates the array that stores the buildings

    for(int i = 0; i < N; i++) { //fills the array
        scanf("%d", &p[i]);
    }

    for(int i = 0; i < N; i++) { //compares the distance
        for(int j = 0; j < N; j++) {
            dist = p[i] + abs(j-i) + p[j];
            if(dist >= maior) maior = dist;
        }
    }

    printf("%d", maior); //prints the longest distance

    return 0;
}