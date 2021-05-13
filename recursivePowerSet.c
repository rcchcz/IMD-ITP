#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printSet(int set[], int subset[], int n) {
    for(int i = 0; i < n; i++) {
        if(subset[i] == 1) printf("%d ", set[i]);
    }
    printf("\n");
    return;
}

void powerSet(int set[], int subset[], int n, int nSubset) {
    for(int i = 0; i < n; i++) {
        if(--nSubset >= 0 && subset[i] == 0) {
            subset[i] = 1;
            printSet(set, subset, n);
            powerSet(set, subset, n, nSubset);
            subset[i] = 0;
        }
    }
    return;
}

int main(void) {
    int n, nSubset;
    int *set;
    int *subset;
    scanf("%d", &n);
    set = calloc(n,sizeof(int));
    subset = calloc(n,sizeof(int));
    nSubset = pow(2,n);
    for(int i = 0; i < n; i++) scanf("%d", &set[i]);
    powerSet(set, subset, n, nSubset);
    return 0;
}