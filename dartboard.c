#include <stdio.h>
#include <math.h>

float dist(float x1, float y1, float x0, float y0);
int pont_principal(float x);
int pont_bonus(float x);

int main(void) {
    float x1, y1, x0, y0;
    int bonus = 1;
    int score = 0;
    for(int i = 0; i < 10; i++){
        if(bonus) {
            scanf("%f %f", &x1, &y1);
            score+=pont_principal(dist(x1, y1, 0, 0));
            bonus = 0;
        } else {
            x0 = x1;
            y0 = y1;
            scanf("%f %f", &x1, &y1);
            score+=pont_principal(dist(x1, y1, 0, 0));
            score+=pont_bonus(dist(x1,y1,x0,y0));
        }
    }
    printf("%d", score);
    return 0;
}

float dist(float x1, float y1, float x0, float y0) {
    return sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2));
}

int pont_principal(float x) {
    if(x >= 0 && x <= 1) return 10;
    if(x > 1 && x <= 2) return 6;
    if(x > 2 && x <= 3) return 4;
    return 0;
}

int pont_bonus(float x) {
    if(x >= 0 && x <= 1) return 5;
    if(x > 1 && x <= 2) return 3;
    if(x > 2 && x <= 3) return 2;
    return 0;
}