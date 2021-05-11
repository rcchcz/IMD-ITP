#include <stdio.h>

int recebe(void);
int med(int p1, int p2, int p3);
int score(void);

int main(void) {
    int pa = score();
    int pb = score();

    if(pa > pb) printf("A");
        else if(pa < pb) printf("B");
            else printf("empate");

    return 0;
}

int med(int p1, int p2, int p3) {
    if((p2 <= p1 && p1 <= p3) || (p2 >= p1 && p1 >= p3)) return p1;
    if((p1 <= p2 && p2 <= p3) || (p1 >= p2 && p2 >= p3)) return p2;
    if((p1 <= p3 && p3 <= p2) || (p1 >= p3 && p3 >= p2)) return p3;
}

int recebe(void) {
    int p1,p2,p3;
    for(int i = 0; i < 3; i++) {
        scanf("%d %d %d", &p1, &p2, &p3);
        return med(p1,p2,p3);
    }
}

int score(void) {
    return med(recebe(), recebe(), recebe());
}