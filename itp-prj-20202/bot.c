/********************************************************************
  Bot-exemplo
  
  Após receber as informações iniciais do jogo, a cada rodada, esse
  bot irá apenas puxar uma carta e, em seguida, descartá-la.
  Cabe a você agora aprimorar sua estratégia!!!
 ********************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carta.h"

/** Tamanho máximo do identificador do bot */
#define ID_SIZE 10

int main() {
  char line[MAX_LINE];   // dados temporários
  char myId[ID_SIZE];    // identificador do bot em questão

  vetCarta *mao = (vetCarta*) malloc(sizeof(vetCarta)); //cartas na mão do bot
  limpaVetorCarta(mao); //limpa o mao, deixando todos os valores em 0

  vetCarta *maoOpo = (vetCarta*) malloc(sizeof(vetCarta)); //cartas na mão do oponente
  limpaVetorCarta(maoOpo); //limpa o mao, deixando todos os valores em 0
  maoOpo->qntCartas = 11; //quantidade de cartas que o oponente começa

  vetCarta *lixo = (vetCarta*) malloc(sizeof(vetCarta)); //cartas no lixo (fundo é [0])
  limpaVetorCarta(lixo); //limpa o mao, deixando todos os valores em 0

  matCarta *minhaMesa = (matCarta*) malloc(sizeof(matCarta)); //jogos na mesa desse bot
  for(int i = 0; i < MAX_JOGOS_MESA; i++) limpaVetorCarta(&minhaMesa->jogos[i]); //limpa a mesa

  matCarta *mesaOpo = (matCarta*) malloc(sizeof(matCarta)); //jogos na mesa do oponente
  for(int i = 0; i < MAX_JOGOS_MESA; i++) limpaVetorCarta(&mesaOpo->jogos[i]); //limpa a mesa

  //quantidade de cartas no deck
  int qntCartasDeck = MAX_CARTAS_DECK;

  setbuf(stdin, NULL);   // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL);  // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

                         // DADOS DO INÍCIO DA PARTIDA
  readline(line);        // lê os identificadores dos jogadores
  readline(line);        // lê o identificador do bot (seu id)
  strncpy(myId, line, ID_SIZE); // guarda para uso futuro

  readline(line);        // lê as cartas que o bot tem na mão
  maoInicial(mao, line, &qntCartasDeck); //adiciona a mão inicial
  maoInicialOpo(maoOpo, &qntCartasDeck); //adiciona a mão inicial do oponente

  readline(line);        // lê a carta inicial da pilha de descarte.
  lixoInicial(lixo, line, &qntCartasDeck); //adiciona a primeira carta do lixo

  while(1) {              // DADOS DURANTE A PARTIDA
    do {                  // lê e descarta os dados até chegar sua vez
      readline(line);     // sai do laço quando for enviado seu id
      fprintf(stderr, "JUIZ: %s\n", line);  // exemplo de saída para debugar

      //"DISCARD c" se o oponente descartar, armazena a carta descartada no lixo
      if(line[0] == 'D') opponentDiscard(maoOpo, lixo, line);
      //"GET_DISCARD [ c1 c2 ... ]" se o oponente puxar as cartas do lixo
      else if(line[4] == 'D') oponentePuxaLixo(maoOpo, lixo, mesaOpo, line);
      //"GET_STOCK" se o oponente puxa uma carta
      else if(line[4] == 'S') oponentePuxaDeck(maoOpo, &qntCartasDeck);
      //"MELD_NEW [ c1 c2 c3 ... ]" se o oponente faz um jogo novo
      else if(line[5] == 'N') oponenteFazJogo(maoOpo, mesaOpo, line);
      //"MELD_JOIN ind [ c1 ... ]" se o oponente adicionar carta(s) em jogos já existentes
      else if(line[5] == 'J') opoAddCartaEmJogo(maoOpo, mesaOpo, line);
    } while (strcmp(line, myId)); // sai do laço quando for a sua vez!

    //verifica se deve puxar do lixo ou do deck e o faz
    fprintf(stderr, "puxarDeckOuLixo();\n");//apagar
    puxarDeckOuLixo(line, minhaMesa, mao, lixo, &qntCartasDeck);

    //verifica se pode bater ganhando nesse turno. se puder, bate. se tiver pouca carta no deck, baixa tudo o que pode
    fprintf(stderr, "verSeBate();\n");//apagar
    verSeBate(mao, maoOpo, minhaMesa, mesaOpo, qntCartasDeck);

    //verifica a melhor carta a ser descartada e a descarta
    fprintf(stderr, "descartar();\n");//apagar
    descartar(mao, minhaMesa, lixo);

    for (int i = 0; i < mao->qntCartas; i++)//apagar
      fprintf(stderr, "carta: %d / %d\n", mao->cartas[i].valor, mao->cartas[i].naipe);
    for (int i = 0; i < maoOpo->qntCartas; i++)//apagar
      fprintf(stderr, "cartaOpo: %d / %d\n", maoOpo->cartas[i].valor, maoOpo->cartas[i].naipe);
    fprintf(stderr, "qntCartasMao: %d\n", mao->qntCartas);
    fprintf(stderr, "qntCartasLixo: %d\n", lixo->qntCartas);
    fprintf(stderr, "qntJogosMesa: %d\n", minhaMesa->qntJogos);
    fprintf(stderr, "qntCartasDeck: %d\n", qntCartasDeck);
  }

  freeAll(mao, maoOpo, lixo, minhaMesa, mesaOpo);

  return 0;
}