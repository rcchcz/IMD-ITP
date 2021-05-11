#include <stdio.h>

int rondas(int hora, int minuto, int segundo);
int formata(int tts);

int main(void) {
    int hora, minuto, segundo;
    scanf("%d %d %d", &hora, &minuto, &segundo);
    rondas(hora, minuto, segundo);
    return 0;
}

int rondas(int hora, int minuto, int segundo) {
    int tts = 0;
    tts = (hora*3600) + (minuto*60) + segundo;
    formata(tts + 3600);
    formata(tts + 7830);
    formata(tts + 16850);
    formata(tts + 43505);
    return 0;
}

int formata(int tts) {
    int h, m;
    h = m = 0;
    h = (tts - (tts%3600))/3600;
    tts-=h*3600;
    m = (tts - (tts%60))/60;
    tts-=m*60;

    if(h >= 24) h-=24;

    printf("%02d:%02d:%02d\n", h,m,tts);
    return 0;
}