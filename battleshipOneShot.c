// This program checks the result of a shot on a grid. The first line of the
// data entry has 2 integers corresponding to the height l and width c of the
// grid. Then, it receives l lines, each containing c values, defining the 
// content of the grid positions, whose values ​​are 0 if it is water or 1 if it
// is part of a ship. Finally, there is a last entry containing 2 integer values
// corresponding to the line lt and the column ct of the shot. Row and column
// values ​​start from 1. The program prints the result of the shot: 1 if the shot
// hit the water, 2 if it hit a part of a ship, but it has not yet sunk completely
// or 3 if it hit a part of a ship, sinking it completely.

#include <stdio.h>

int main(void) {
    int l, c, lt, ct;

    scanf("%d %d", &l, &c);

    #define L l
    #define C c

    int bg[L][C];

    for(int i = 0; i < L; i++) {
        for(int j = 0; j < C; j++) {
            scanf("%d", &bg[i][j]);
        }
    }

    scanf("%d %d", &lt, &ct);

    lt--;
    ct--;
    if(bg[lt][ct] == 0) printf("1");
    if(bg[lt][ct] == 1) {
        if(bg[lt][ct-1] == 1 || bg[lt][ct+1] == 1 || bg[lt-1][ct] == 1 || bg[lt+1][ct] == 1) printf("2");
            else printf("3");
    }

    return 0;
}