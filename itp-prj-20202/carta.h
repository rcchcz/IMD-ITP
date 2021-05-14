#define MAX_LINE 200 /** Tamanho máximo de uma linha da entrada-padrão */
#define MAX_TAM_CARTA_STR 6 //tamanho máximo de uma carta str ("A♥")
#define MAX_CARTAS_DECK 104 //quantidade máxima de cartas que existem no deck
#define MAX_JOGOS_MESA 34 //quantidade máxima de jogos em uma das mesas
#define MAX_CARTAS_JOGO 14 //quantidade máxima de cartas em um jogo na mesa

//estratégia
#define MIN_LIXO_P_PUXAR 1 //quantidade de cartas no lixo mínima para puxar o lixo
#define QNT_MAO_OPO_P_BAIXAR 6 //baixar cartas/jogos assim que o oponente tem essa quantidade ou menor de cartas na mão
#define PEGAR_LIXO_COM_C2 0 //0: não pegar lixo baixando jogo com coringa; 1: pega o lixo baixando com coringa

typedef enum{
    cdesc = -1, cvoid, ca, c2, c3, c4, c5, c6, c7, c8, c9, c10, cj, cq, ck
} Valor; //cdesc: carta desconhecida; cvoid: espaço vazio (sem carta)

typedef enum{
    ndesc = -1, nvoid, copas, ouro, paus, espada
} Naipe; //ndesc: carta desconhecida; nvoid: espaço vazio (sem carta)

typedef struct{
    Valor valor;
    Naipe naipe;
} carta;

typedef struct VetCarta{
    carta cartas[MAX_CARTAS_DECK];
    int qntCartas;
} vetCarta;

typedef struct MatCarta{
    vetCarta jogos[MAX_JOGOS_MESA];
    int qntJogos;
} matCarta;

/* carta.c */

//converte str ("A♥") em carta (VALOR, NAIPE)
void strPCarta(char cartaStr[MAX_TAM_CARTA_STR], carta *card);

//converte carta (VALOR, NAIPE) em str ("A♥")
void cartaPStr(char cartaStr[MAX_TAM_CARTA_STR], carta card);

//troca o valor de 2 cartas
void trocaCarta(carta *card1, carta *card2);

/* vetCarta.c */

//limpa vetores de cartas
void limpaVetorCarta(vetCarta *vetC);

//lê comandos que enviam as cartas entre [] e armazena essas cartas num vetor de cartas
vetCarta lerVetCartaStr(char line[]);

//converte o str da sua mão na sua mão em cartas
void maoInicial(vetCarta *mao, char line[], int *qntCartasDeck);

//colocar 11 cartas desconhecidas na mão do oponente
void maoInicialOpo(vetCarta *maoOpo, int *qntCartasDeck);

//recebe a carta do juiz e a adiciona no lixo
void lixoInicial(vetCarta *lixo, char line[], int *qntCartasDeck);

//armazena a carta descartada pelo oponente no topo do lixo
void opponentDiscard(vetCarta *maoOpo, vetCarta *lixo, char line[]);

//adiciona uma carta desconhecida do deck na mão do oponente
void oponentePuxaDeck(vetCarta *maoOpo, int *qntCartasDeck);

//adiciona as cartas do lixo para a mão do oponente e coloca o jogo na mesa dele
void oponentePuxaLixo(vetCarta *maoOpo, vetCarta *lixo, matCarta *mesaOpo, char line[]);

//tira as cartas da mão do oponente e as coloca num jogo novo da mesa dele
void oponenteFazJogo(vetCarta *maoOpo, matCarta *mesaOpo, char line[]);

//tira as cartas da mão do oponente e as adiciona num jogo já existente da mesa dele
void opoAddCartaEmJogo(vetCarta *maoOpo, matCarta *mesaOpo, char line[]);

//ordena as cartas da mão em ordem decrescente, priorizando o naipe
void bubbleSort(vetCarta *mao);

//verifica se pode pegar carta do lixo (fazendo jogo também). se não, compra do deck
void puxarDeckOuLixo(char *line, matCarta *minhaMesa, vetCarta *mao, vetCarta *lixo, int *qntCartasDeck);

//verifica a melhor carta da mão a ser descartada e a descarta
void descartar(vetCarta *mao, matCarta *minhaMesa, vetCarta *lixo);

//verifica se tem cartas que podem ser adicionados a jogos na mesa e as coloca lá
void adicionarCartasEmJogos(matCarta *minhaMesa, vetCarta *mao, char comandos[][MAX_LINE], int *qntComandos);

//tenta baixar apenas um jogo. se conseguir baixar, retorna 1, se não, retorna 0
int baixarUmJogo(vetCarta *mao, matCarta *minhaMesa, char comandos[][MAX_LINE], int *qntComandos);

//calcula e retorna os pontos de um jogador
int calcularPontuacao(vetCarta *mao, matCarta *mesa);

//verifica se pode bater gahnando. se puder bater, baixa toda a mão na mesa e ganha. se tiver pouca carta no deck, baixa tudo o que pode
void verSeBate(vetCarta *mao, vetCarta *maoOpo, matCarta *minhaMesa, matCarta *mesaOpo, int qntCartasDeck);

//encontra uma carta na mão retorna sua posição
int acharPosCartaOpo(vetCarta *mao, carta card);

/* misc.c */

/**
 * Lê uma linha da entrada padrão e remove o '\n' se necessário.
 * @param line string a ser alterada com o conteúdo da entrada-padrão.
 */
void readline(char *line);

//libera os ponteiros alocados dinamicamente
void freeAll(vetCarta *mao, vetCarta *maoOpo, vetCarta *lixo, matCarta *minhaMesa, matCarta *mesaOpo);