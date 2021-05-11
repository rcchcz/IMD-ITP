#include <stdio.h>

int main(void) {
    int index[20];
    char bg[10][10];

    for(int i = 0; i < 20; i += 2) { // coordinates
        scanf("%d %d", &index[i], &index[i+1]);
    }

    for(int i = 0; i < 10; i++) { // bg filled with water ('~')
        for(int j = 0; j < 10; j++) {
            bg[i][j] = '~';
        }
    }

    bg[index[0]][index[1]] = '*'; // canoe

    if(index[2] == index[4]) { // boat
        bg[index[2]][index[3]] = '<';
        bg[index[4]][index[5]] = '>';
    } else {
        bg[index[2]][index[3]] = '^';
        bg[index[4]][index[5]] = 'v';
    }

    if(index[6] == index[8] && index[8] == index[10]) { // frigate
        bg[index[6]][index[7]] = '<';
        bg[index[8]][index[9]] = '=';
        bg[index[10]][index[11]] = '>';
    } else {
        bg[index[6]][index[7]] = '^';
        bg[index[8]][index[9]] = '|';
        bg[index[10]][index[11]] = 'v';
    }

    if(index[12] == index[14] && index[14] == index[16] && index[16] == index[18]) { // destroyer
        bg[index[12]][index[13]] = '<';
        bg[index[14]][index[15]] = '=';
        bg[index[16]][index[17]] = '=';
        bg[index[18]][index[19]] = '>';
    } else {
        bg[index[12]][index[13]] = '^';
        bg[index[14]][index[15]] = '|';
        bg[index[16]][index[17]] = '|';
        bg[index[18]][index[19]] = 'v';
    }

    for(int i = 0; i < 10; i++) { // prints bg
        for(int j = 0; j < 10; j++) {
            printf("%c", bg[i][j]);
        }
        printf("\n");
    }

    return 0;
}