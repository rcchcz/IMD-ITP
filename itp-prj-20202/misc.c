#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carta.h"

void readline(char *line) {
  fgets(line, MAX_LINE, stdin);
  int l = strlen(line) - 1;
  if(line[l] == '\n') {
    line[l] = '\0';
  }
}

void freeAll(vetCarta *mao, vetCarta *maoOpo, vetCarta *lixo, matCarta *minhaMesa, matCarta *mesaOpo)
{
  free(mao);
  free(maoOpo);
  free(lixo);
  free(minhaMesa);
  free(mesaOpo);
}