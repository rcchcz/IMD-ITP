#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "carta.h"

void limpaVetorCarta(vetCarta *vetC)
{
    for (int i = 0; i < MAX_CARTAS_DECK; i++)
    {
        vetC->cartas[i].valor = cvoid;
        vetC->cartas[i].naipe = nvoid;
    }

    vetC->qntCartas = 0;
}

vetCarta lerVetCartaStr(char line[])
{
    char *cartasStr; //"... [ c1 c2 ... ]"
    vetCarta tmpCartas; //vetor de cartas temporário
    tmpCartas.qntCartas = 0;

    cartasStr = strtok(line, " "); //separar a string entre os espaços

    while (strcmp(cartasStr, "[")) //pular até chegar no "["
        cartasStr = strtok(NULL, " ");
    cartasStr = strtok(NULL, " "); //pular o "["

    while (strcmp(cartasStr, "]")) //adicionar cartas no vetor até chegar no "]"
    {
        strPCarta(cartasStr, &tmpCartas.cartas[tmpCartas.qntCartas]); //converte e coloca no vetor de cartas
        tmpCartas.qntCartas++;

        cartasStr = strtok(NULL, " ");
    }

    return tmpCartas;
}

void maoInicial(vetCarta *mao, char line[], int *qntCartasDeck)
{
    vetCarta tmpCartas; //vetor de cartas temporário
    tmpCartas = lerVetCartaStr(line); //converter o texto de vetor de carta em um vetor de carta

    for (int i = 0; i < tmpCartas.qntCartas; i++) //colocar as cartas do vetor temporário na mão
        trocaCarta(&mao->cartas[i], &tmpCartas.cartas[i]);

    bubbleSort(mao); //ordena as cartas da mão

    mao->qntCartas = 11;
    (*qntCartasDeck) -= 11;
}

void maoInicialOpo(vetCarta *maoOpo, int *qntCartasDeck)
{
    for (int i = 0; i < 11; i++) //11 cartas na mão inicial
    {
        maoOpo->cartas[i].valor = cdesc;
        maoOpo->cartas[i].naipe = ndesc;
    }

    bubbleSort(maoOpo); //ordena as cartas da mão

    maoOpo->qntCartas = 11;
    (*qntCartasDeck) -= 11;
}

void lixoInicial(vetCarta *lixo, char line[], int *qntCartasDeck)
{
    strPCarta(line, &lixo->cartas[0]); //converte e coloca a carta no lixo
    lixo->qntCartas = 1; //adiciona 1 na quantidade de cartas no lixo
    (*qntCartasDeck)--;
}

void opponentDiscard(vetCarta *maoOpo, vetCarta *lixo, char line[])
{
    char *cardStr;

    cardStr = strtok(line, " "); //dividir line em um vetor (separando por " ")

    cardStr = strtok(NULL, " "); //pular o "DISCARD"

    strPCarta(cardStr, &lixo->cartas[lixo->qntCartas]); //converte e coloca no lixo

    //verificando se a carta descartada não é desconhecida
    int posC = acharPosCartaOpo(maoOpo, lixo->cartas[lixo->qntCartas]); //encontrando a posição da carta na mão
    maoOpo->cartas[posC].valor = cvoid; //retirando a carta da mão do oponente
    maoOpo->cartas[posC].naipe = nvoid;

    bubbleSort(maoOpo); //ordena as cartas da mão

    lixo->qntCartas++; //aumenta a quantidade de cartas no lixo
    maoOpo->qntCartas--; //diminuir a quantidade de cartas na mão do oponente
}

void oponentePuxaDeck(vetCarta *maoOpo, int *qntCartasDeck)
{
    //adicionando carta desconhecida na mão do oponente
    maoOpo->cartas[maoOpo->qntCartas].valor = cdesc;
    maoOpo->cartas[maoOpo->qntCartas].naipe = ndesc;

    bubbleSort(maoOpo); //ordena as cartas da mão

    maoOpo->qntCartas++; //adicionar carta na mão do oponente
    qntCartasDeck--; //remover carta do deck
}

void oponentePuxaLixo(vetCarta *maoOpo, vetCarta *lixo, matCarta *mesaOpo, char line[])
{
    vetCarta tmpCartas; //vetor de cartas temporário
    tmpCartas = lerVetCartaStr(line); //converter o texto de vetor de carta em um vetor de carta

    trocaCarta(&mesaOpo->jogos[mesaOpo->qntJogos].cartas[0], &lixo->cartas[lixo->qntCartas-1]); //adicionar topo do lixo no jogo
    mesaOpo->jogos[mesaOpo->qntJogos].qntCartas++;
    lixo->qntCartas--;

    for (int i = 0; i < tmpCartas.qntCartas; i++) //adicionar as cartas da mão no jogo
    {
        //verificando se a carta descartada não é desconhecida
        int posC = acharPosCartaOpo(maoOpo, tmpCartas.cartas[i]); //encontrando a posição da carta na mão
        maoOpo->cartas[posC].valor = cvoid; //retirando a carta da mão do oponente
        maoOpo->cartas[posC].naipe = nvoid;

        //adicionando as cartas na mesa
        trocaCarta(&mesaOpo->jogos[mesaOpo->qntJogos].cartas[mesaOpo->jogos[mesaOpo->qntJogos].qntCartas], &tmpCartas.cartas[i]);
        mesaOpo->jogos[mesaOpo->qntJogos].qntCartas++;
    }

    for (int i = 0; i < lixo->qntCartas; i++) //adicionar o resto do lixo na mão do oponente
        trocaCarta(&maoOpo->cartas[maoOpo->qntCartas+i], &lixo->cartas[i]);

    bubbleSort(maoOpo); //ordena as cartas da mão

    mesaOpo->qntJogos++; //aumenta a quantidade de jogos da mesa do oponente
    maoOpo->qntCartas += lixo->qntCartas -tmpCartas.qntCartas; //alterar a quantidade de cartas na mão do oponente

    limpaVetorCarta(lixo); //limpa o lixo
}

void oponenteFazJogo(vetCarta *maoOpo, matCarta *mesaOpo, char line[])
{
    vetCarta tmpCartas; //vetor de cartas temporário
    tmpCartas = lerVetCartaStr(line); //converter o texto de vetor de carta em um vetor de carta

    for (int i = 0; i < tmpCartas.qntCartas; i++) //adicionar as cartas da mão no jogo
    {
        //verificando se a carta descartada não é desconhecida
        int posC = acharPosCartaOpo(maoOpo, tmpCartas.cartas[i]); //encontrando a posição da carta na mão
        maoOpo->cartas[posC].valor = cvoid; //retirando a carta da mão do oponente
        maoOpo->cartas[posC].naipe = nvoid;

        //adicionando as cartas na mesa
        trocaCarta(&mesaOpo->jogos[mesaOpo->qntJogos].cartas[mesaOpo->jogos[mesaOpo->qntJogos].qntCartas], &tmpCartas.cartas[i]);
        mesaOpo->jogos[mesaOpo->qntJogos].qntCartas++;
    }

    bubbleSort(maoOpo); //ordena as cartas da mão

    mesaOpo->qntJogos++; //aumenta a quantidade de jogos da mesa do oponente
    maoOpo->qntCartas -= tmpCartas.qntCartas; //alterar a quantidade de cartas na mão do oponente
}

void opoAddCartaEmJogo(vetCarta *maoOpo, matCarta *mesaOpo, char line[])
{
    char *cartasStr; //"... ind [ c1 c2 ... ]"
    vetCarta tmpCartas; //vetor de cartas temporário
    tmpCartas.qntCartas = 0;
    int ind; //índice do jogo que será adicionado cartas

    cartasStr = strtok(line, " "); //separar a string entre os espaços

    cartasStr = strtok(NULL, " "); //pular o comando para chegar no índice
    ind = atoi(cartasStr); //converte o índice para inteiro

    while (strcmp(cartasStr, "[")) //pular até chegar no "["
        cartasStr = strtok(NULL, " ");
    cartasStr = strtok(NULL, " "); //pular o "["

    while (strcmp(cartasStr, "]")) //adicionar cartas no vetor até chegar no "]"
    {
        strPCarta(cartasStr, &tmpCartas.cartas[tmpCartas.qntCartas]); //converte e coloca no vetor de cartas
        tmpCartas.qntCartas++;

        cartasStr = strtok(NULL, " ");
    }

    for (int i = 0; i < tmpCartas.qntCartas; i++) //adicionar as cartas da mão no jogo
    {
        //verificando se a carta descartada não é desconhecida
        int posC = acharPosCartaOpo(maoOpo, tmpCartas.cartas[i]); //encontrando a posição da carta na mão
        maoOpo->cartas[posC].valor = cvoid; //retirando a carta da mão do oponente
        maoOpo->cartas[posC].naipe = nvoid;

        //adicionando as cartas na mesa
        trocaCarta(&mesaOpo->jogos[ind].cartas[mesaOpo->jogos[ind].qntCartas], &tmpCartas.cartas[i]);
        mesaOpo->jogos[ind].qntCartas++;
    }

    bubbleSort(maoOpo); //ordena as cartas da mão

    maoOpo->qntCartas -= tmpCartas.qntCartas; //alterar a quantidade de cartas na mão do oponente
}

void bubbleSort(vetCarta *mao)
{
    for (int i = 0; i < MAX_CARTAS_DECK-1; i++)
        for (int j = i+1; j < MAX_CARTAS_DECK; j++)
            //ordena em ordem crescente priorizando o naipe. as cartas vazias vão para direita
            if((mao->cartas[i].naipe > mao->cartas[j].naipe ||
            (mao->cartas[i].naipe == mao->cartas[j].naipe && mao->cartas[i].valor > mao->cartas[j].valor) ||
            mao->cartas[i].valor == cvoid) && mao->cartas[j].valor != cvoid)
                trocaCarta(&mao->cartas[i], &mao->cartas[j]);
}

void puxarDeckOuLixo(char *line, matCarta *minhaMesa, vetCarta *mao, vetCarta *lixo, int *qntCartasDeck)
{
    char card1[MAX_TAM_CARTA_STR];
    char card2[MAX_TAM_CARTA_STR];

    int fazJogo = 0; //se fizer jogo com cartas na mesa, fazJogo > 0

    if(lixo->qntCartas >= MIN_LIXO_P_PUXAR) //não puxar lixo caso ele tenha poucas cartas
    {
        for(int i = 0; i<mao->qntCartas-1; i++) //buscando jogo sem coringa (c2)
            //checagem se o naipe do topo do lixo ta presente na mao do bot e se as cartas da mão não são c2
            if(lixo->cartas[lixo->qntCartas-1].naipe == mao->cartas[i].naipe && lixo->cartas[lixo->qntCartas-1].naipe == mao->cartas[i+1].naipe && mao->cartas[i].valor != c2 && mao->cartas[i+1].valor != c2)
            {
                //1 2 3(lixo) || Q K A(lixo)
                if(mao->cartas[i].valor + 1 == mao->cartas[i+1].valor && (mao->cartas[i+1].valor + 1 == lixo->cartas[lixo->qntCartas-1].valor || mao->cartas[i+1].valor == ck && lixo->cartas[lixo->qntCartas-1].valor == ca))             
                    fazJogo = 1;
                //1 2(lixo) 3 || Q K(lixo) A
                else if(mao->cartas[i].valor + 1 == lixo->cartas[lixo->qntCartas-1].valor && (lixo->cartas[lixo->qntCartas-1].valor + 1 == mao->cartas[i+1].valor || lixo->cartas[lixo->qntCartas-1].valor == ck && mao->cartas[i+1].valor == ca))               
                    fazJogo = 2;
                //1(lixo) 2 3 || Q(lixo) K A
                else if(lixo->cartas[lixo->qntCartas-1].valor + 1 == mao->cartas[i].valor && (mao->cartas[i].valor + 1 == mao->cartas[i+1].valor || mao->cartas[i].valor == ck && mao->cartas[i+1].valor == ca))            
                    fazJogo = 3;

                if(fazJogo)
                {
                    cartaPStr(card1, mao->cartas[i]);
                    cartaPStr(card2, mao->cartas[i+1]);
                    fprintf(stderr,"GET_DISCARD [ %s %s ]\n", card1, card2); //apagar
                    printf("GET_DISCARD [ %s %s ]\n", card1, card2); //envia o comando ao juiz
                    readline(line); //ler a carta que pegou do lixo (mesmo não usando)

                    //coloca a carta do lixo e as da mão em um jogo novo
                    switch (fazJogo)
                    {
                    case 1://1 2 3(lixo) || Q K A(lixo)
                        trocaCarta(&(mao->cartas[i]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[0]));
                        trocaCarta(&(mao->cartas[i+1]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[1]));
                        trocaCarta(&(lixo->cartas[lixo->qntCartas-1]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[2]));
                        break;
                    case 2://1 2(lixo) 3 || Q K(lixo) A
                        trocaCarta(&(mao->cartas[i]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[0]));
                        trocaCarta(&(lixo->cartas[lixo->qntCartas-1]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[1]));
                        trocaCarta(&(mao->cartas[i+1]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[2]));
                        break;
                    case 3://1(lixo) 2 3 || Q(lixo) K A
                        trocaCarta(&(lixo->cartas[lixo->qntCartas-1]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[0]));
                        trocaCarta(&(mao->cartas[i]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[1]));
                        trocaCarta(&(mao->cartas[i+1]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[2]));
                        break;
                    }
                    
                    break;
                }
            }

        if(!fazJogo && PEGAR_LIXO_COM_C2) //se não achar um jogo sem coringa (c2): busca jogo com coringa (c2)
            for (int i = 0; i < mao->qntCartas; i++)
                if(mao->cartas[i].valor == c2) //mao[i] é a carta com valor 2 (c2)
                {
                    for (int j = 0; j < mao->qntCartas; j++)
                    {
                        //checagem se o naipe do topo do lixo ta presente na mao do bot e se não é um c2
                        if(lixo->cartas[lixo->qntCartas-1].naipe == mao->cartas[j].naipe && mao->cartas[j].valor != c2)
                        {
                            //1 2(c2) 3(lixo) || Q K(c2) A(lixo)
                            if(mao->cartas[j].valor + 2 == lixo->cartas[lixo->qntCartas-1].valor || mao->cartas[i].valor == cq && lixo->cartas[lixo->qntCartas-1].valor == ca)
                                fazJogo = 1;
                            //1(c2) 2 3(lixo) || Q(c2) K A(lixo)
                            else if(mao->cartas[j].valor + 1 == lixo->cartas[lixo->qntCartas-1].valor || mao->cartas[i].valor == ck && lixo->cartas[lixo->qntCartas-1].valor == ca)
                                fazJogo = 2;
                            //1(lixo) 2(c2) 3 || Q(lixo) K(c2) A
                            else if(lixo->cartas[lixo->qntCartas-1].valor + 2 == mao->cartas[j].valor || lixo->cartas[lixo->qntCartas-1].valor == cq && mao->cartas[i].valor == ca)
                                fazJogo = 3;

                            if(fazJogo)
                            {
                                cartaPStr(card1, mao->cartas[j]);
                                cartaPStr(card2, mao->cartas[i]); //c2
                                fprintf(stderr,"GET_DISCARD [ %s %s ] (esse pode mudar a ordem)\n", card1, card2); //apagar
                                if(fazJogo == 1) printf("GET_DISCARD [ %s %s ]\n", card1, card2); //envia o comando ao juiz [ cx c2 ]
                                else printf("GET_DISCARD [ %s %s ]\n", card2, card1); //envia o comando ao juiz [ c2 cx ]
                                readline(line); //ler a carta que pegou do lixo (mesmo não usando)

                                //coloca a carta do lixo e as da mão em um jogo novo
                                switch (fazJogo)
                                {
                                case 1://1 2(c2) 3(lixo) || Q K(c2) A(lixo)
                                    trocaCarta(&(mao->cartas[j]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[0]));
                                    trocaCarta(&(mao->cartas[i]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[1]));
                                    trocaCarta(&(lixo->cartas[lixo->qntCartas-1]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[2]));
                                    break;
                                case 2://1(c2) 2 3(lixo) || Q(c2) K A(lixo)
                                    trocaCarta(&(mao->cartas[i]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[0]));
                                    trocaCarta(&(mao->cartas[j]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[1]));
                                    trocaCarta(&(lixo->cartas[lixo->qntCartas-1]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[2]));
                                    break;
                                case 3://1(lixo) 2(c2) 3 || Q(lixo) K(c2) A
                                    trocaCarta(&(lixo->cartas[lixo->qntCartas-1]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[0]));
                                    trocaCarta(&(mao->cartas[i]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[1]));
                                    trocaCarta(&(mao->cartas[j]), &(minhaMesa->jogos[minhaMesa->qntJogos].cartas[2]));
                                    break;
                                }

                                break;
                            }
                        }
                    }
                    
                    break;
                }
    }

    if(fazJogo)
    {
        //ajustar quantidades depois das alterações nos vetores
        minhaMesa->jogos[minhaMesa->qntJogos].qntCartas += 3; //ajustando quantidade de cartas nesse jogo que foi baixado
        minhaMesa->qntJogos++;
        lixo->qntCartas--;
        mao->qntCartas -= 2;

        bubbleSort(mao); //ordena as cartas da mão

        //coloca as cartas do lixo na mão (ajusta qntCartasLixo e qntCartasMao)
        for (int j = 0; j < lixo->qntCartas; j++)
            trocaCarta(&(lixo->cartas[j]), &(mao->cartas[mao->qntCartas + j]));
        mao->qntCartas += lixo->qntCartas;
        lixo->qntCartas = 0;

        bubbleSort(mao); //ordena as cartas da mão
    }
    else
    {
        printf("GET_STOCK\n");         // envia a ação para puxar uma carta
        readline(line);                // recebe a carta que puxou

        strPCarta(line, &mao->cartas[mao->qntCartas]); //converte e coloca a carta na mão
        mao->qntCartas++; //adiciona 1 na quantidade de cartas na mão
        (*qntCartasDeck)--; //tirar carta do deck

        bubbleSort(mao); //ordena a mão
    }
}

void descartar(vetCarta *mao, matCarta *minhaMesa, vetCarta *lixo)
{
    char cartaDescarte[MAX_TAM_CARTA_STR]; //qual carta será descartada (para colocar no comando)
    int descartou = 0; //se já tiver descartado, descartou == 1
    carta cDescarte; //carta que será descartada

    //fazendo um teste de jogo temporário
    char comandos[MAX_CARTAS_DECK/*maxQntComandos*/][MAX_LINE]; //variável que armazena os comandos que serão utilizados no teste
    int qntComandos = 0; //quantidade de comandos que foram utilizados no teste
    vetCarta maoTemp = *mao;
    matCarta mesaTemp = *minhaMesa;

    carta remendo = maoTemp.cartas[0];//remendar o problema misterioso :O

    int baixouJogo = 1; //se tiver baixado um jogo, o loop continua
    while (baixouJogo) //para quando não conseguir baixar mais jogos nem cartas
    {
        baixouJogo = 0;

        //baixar todas as cartas possíveis (adicionar em jogos)
        adicionarCartasEmJogos(minhaMesa, mao, comandos, &qntComandos);

        //tentar baixar UM jogo
        baixouJogo = baixarUmJogo(mao, minhaMesa, comandos, &qntComandos);
    }

    for (int maoComp = 0; maoComp < 2; maoComp++)
    {
        int naipeDescarte = 0; //qual o naipe da carta que será descartada
        descartou = 0; //se já tiver descartado, descartou == 1
        int qntCartaNaipe[4] = {0};
        /*
            qntCartaNaipe[0]: quantidade cartas de naipe copas
            qntCartaNaipe[1]: quantidade cartas de naipe ouros
            qntCartaNaipe[2]: quantidade cartas de naipe paus
            qntCartaNaipe[3]: quantidade cartas de naipe espadass
        */

        //ver se tem carta repetida
        for (int i = 0; i < mao->qntCartas-1 && !descartou; i++)
            for (int j = i+1; j < mao->qntCartas; j++)
                if(mao->cartas[i].valor == mao->cartas[j].valor && mao->cartas[i].naipe == mao->cartas[j].naipe &&
                mao->cartas[i].valor != c2) //se a carta for repetida e não for coringa (c2)
                {
                    cDescarte = mao->cartas[i];

                    descartou = 1;
                    break;
                }

        for (int i = 0; i < mao->qntCartas; i++) //contagem de cartas de cada naipe
        {
            if(mao->cartas[i].naipe == copas) qntCartaNaipe[0]++;
            else if(mao->cartas[i].naipe == ouro) qntCartaNaipe[1]++;
            else if(mao->cartas[i].naipe == paus) qntCartaNaipe[2]++;
            else if(mao->cartas[i].naipe == espada) qntCartaNaipe[3]++;
        }

        while(!descartou && naipeDescarte < 4 && mao->qntCartas) //só sai do laço assim que descarta uma carta ou se todas as cartas da mão forem coringas (c2)
        {
            for(; naipeDescarte<4; naipeDescarte++) //faz com que naipeDescarte = ao primeiro naipe que possui pelo menos 1 carta
                if(qntCartaNaipe[naipeDescarte]) //verifica se o naipe possui pelo menos 1 carta
                    break;

            for(int i = naipeDescarte + 1; i < 4; i++) //faz com que naipeDescarte = ao naipe com menos cartas (que pussoa pelo menos 1 carta)
                if(qntCartaNaipe[i] < qntCartaNaipe[naipeDescarte] && qntCartaNaipe[i])
                    naipeDescarte = i;

            if(naipeDescarte < 4)
                for (int i = 0; i < mao->qntCartas; i++) //se tiver uma carta nesse naipe que não for coringa (c2): descarta ela
                    if(mao->cartas[i].naipe == naipeDescarte+1 && mao->cartas[i].valor != c2)
                    {
                        cDescarte = mao->cartas[i];

                        descartou = 1;
                        break;
                    }
            
            qntCartaNaipe[naipeDescarte] = 0; //fazer com que esse não seja um naipe válido para descartar
        }

        if(!descartou) //se não achou carta no teste de jogo: tenta fazer com a mão normal
        {
            maoTemp.cartas[0] = remendo;
            *mao = maoTemp;
            *minhaMesa = mesaTemp;
        }
        else maoComp = 5; //sair do loop
    }

    //voltar mão e mesa originais
    maoTemp.cartas[0] = remendo;
    *mao = maoTemp;
    *minhaMesa = mesaTemp;

    if(!descartou) //se todas as cartas da mão forem coringas (c2): descarta a última carta da mão
        cDescarte =  mao->cartas[mao->qntCartas-1];

    for (int cMao = 0; cMao < mao->qntCartas; cMao++)
        if(mao->cartas[cMao].valor == cDescarte.valor && mao->cartas[cMao].naipe == cDescarte.naipe)
        {
            cartaPStr(cartaDescarte, mao->cartas[cMao]); //convertendo para string e enviando comando de descarte para o juiz
            fprintf(stderr,"DISCARD %s\n", cartaDescarte); //apagar
            printf("DISCARD %s\n", cartaDescarte); //comando para o juiz descartar a carta

            trocaCarta(&(mao->cartas[cMao]), &(lixo->cartas[lixo->qntCartas])); //ajustando lixo e mão
            mao->qntCartas--;
            lixo->qntCartas++;
            
            break;
        }

    bubbleSort(mao); //ordena as cartas da mão
}

void adicionarCartasEmJogos(matCarta *minhaMesa, vetCarta *mao, char comandos[][MAX_LINE], int *qntComandos)
{
    char cartaStr[MAX_TAM_CARTA_STR]; //a string da carta adicionada ao jogo
    int fezJogo = 1; //se fez um jogo, fezJogo = 1;
    int posC2 = -5;

    while(fezJogo) //para de procurar assim que não consegue mais colocar cartas em jogos na mesa
    {
        fezJogo = 0;

        for(int jogo=0; jogo < minhaMesa->qntJogos && !fezJogo; jogo++) //para cada jogo da mesa
        {
            posC2 = -5; //resetar a posição do coringa (-5 == coringa não encontrado ainda)
            for (int posC = 0; posC < minhaMesa->jogos[jogo].qntCartas; posC++) //achar a posição do coringa (c2)
                if( //minhaMesa->jogos[jogo].cartas[posC] é a carta que estamos verificando se é coringa (c2)
                    minhaMesa->jogos[jogo].cartas[posC].valor == c2 &&
                    (
                        //lado <
                        posC > 0 && //se tiver carta na esquerda da carta testada
                        (
                            //se o naipe não for igual
                            minhaMesa->jogos[jogo].cartas[posC-1].naipe != minhaMesa->jogos[jogo].cartas[posC].naipe
                            ||
                            //se o valor não for sequência
                            minhaMesa->jogos[jogo].cartas[posC-1].valor +1 != minhaMesa->jogos[jogo].cartas[posC].valor
                        )

                        || //separa os lados

                        //lado >
                        posC < minhaMesa->jogos[jogo].qntCartas -1 && //se tiver carta na esquerda da carta testada
                        (
                            //se o naipe não for igual
                            minhaMesa->jogos[jogo].cartas[posC].naipe != minhaMesa->jogos[jogo].cartas[posC+1].naipe
                            ||
                            //se o valor não for sequência
                            minhaMesa->jogos[jogo].cartas[posC].valor +1 != minhaMesa->jogos[jogo].cartas[posC+1].valor
                        )
                    )
                )
                {
                    posC2 = posC;
                    break;
                }

            for(int cMao=0; cMao < mao->qntCartas; cMao++) //para cada carta da mão
            {
                //carta no começo do jogo
                if(
                    //se o naipe é igual entre mão e a carta no começo do jogo
                    mao->cartas[cMao].naipe == minhaMesa->jogos[jogo].cartas[0].naipe &&
                    //se o valor da mão é sequência da carta no começo do jogo
                    mao->cartas[cMao].valor + 1 == minhaMesa->jogos[jogo].cartas[0].valor &&

                    0 != posC2 //se a carta no começo do jogo NÃO é um coringa

                    || //divide entre o a carta do começo ser coringa (v) ou não ser coringa (^)

                    0 == posC2 && //se a carta no começo do jogo É um coringa

                    //se o naipe é igual entre mão e a carta depois do coringa
                    mao->cartas[cMao].naipe == minhaMesa->jogos[jogo].cartas[1].naipe &&
                    //se o valor da mão é sequência +1 da carta depois do coringa
                    mao->cartas[cMao].valor + 2 == minhaMesa->jogos[jogo].cartas[1].valor
                )
                {
                    //move as cartas do jogo para a direita, dando espaço para a carta da mão entrar
                    for (int i = minhaMesa->jogos[jogo].qntCartas-1; i >= 0; i--)
                        trocaCarta(&(minhaMesa->jogos[jogo].cartas[i]), &(minhaMesa->jogos[jogo].cartas[i+1]));

                    trocaCarta(&(mao->cartas[cMao]), &(minhaMesa->jogos[jogo].cartas[0])); //coloca a carta da mão no jogo

                    cartaPStr(cartaStr, minhaMesa->jogos[jogo].cartas[0]); //converter a carta adicionada em uma string de carta

                    fezJogo = 1;
                }
                //carta no final do jogo
                else if(
                    (
                        //se o valor da mão é sequência da carta no final do jogo
                        minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-1].valor + 1 == mao->cartas[cMao].valor &&
                        //se NÃO é uma combinação Q K A (evitar K♥ A♥ 2♥)
                        minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-1].valor != ca

                        || //divide entre fazer (v) ou não fazer (^) combinação Q K A

                        //se É uma combinação Q K A
                        minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-1].valor == ck &&
                        mao->cartas[cMao].valor == ca
                    ) &&
                    //se o naipe é igual entre mão e a carta no final do jogo
                    minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-1].naipe == mao->cartas[cMao].naipe &&

                    //se a carta no final do jogo NÃO é um coringa
                    minhaMesa->jogos[jogo].qntCartas-1 != posC2

                    || //divide entre o a carta do começo ser coringa (v) ou não ser coringa (^)

                    //se a carta no final do jogo É um coringa
                    minhaMesa->jogos[jogo].qntCartas-1 == posC2 &&

                    //se o naipe é igual entre mão e a carta depois do coringa
                    minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-2].naipe == mao->cartas[cMao].naipe &&
                    (
                        //se o valor da mão é sequência da carta depois do coringa
                        minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-2].valor + 2 == mao->cartas[cMao].valor &&
                        //se NÃO é uma combinação Q K A
                        minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-2].valor != cq

                        || //divide entre fazer (v) ou não fazer (^) combinação Q K A

                        //se É uma combinação Q K A
                        minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-2].valor == cq &&
                        mao->cartas[cMao].valor == ca
                    )
                )
                {
                    trocaCarta(&(mao->cartas[cMao]), &(minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas])); //coloca a carta da mão no jogo

                    cartaPStr(cartaStr, minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas]); //converter a carta adicionada em uma string de carta

                    fezJogo = 1;
                }

                if(!fezJogo) //caso não tenha achado jogo naquelas posições, tenta fazer jogo com a carta da mão entre o coringa e o jogo
                {
                    if(//começo do jogo
                        mao->cartas[cMao].naipe == minhaMesa->jogos[jogo].cartas[1].naipe && //se o naipe é igual a carta depois do c2
                        mao->cartas[cMao].valor + 1 == minhaMesa->jogos[jogo].cartas[1].valor && //se é sequência da carta depois do c2
                        0 == posC2 && //se a carta do começo é coringa

                        !(minhaMesa->jogos[jogo].cartas[1].valor == c2) //se a carta depois do coringa é c2 (para evitar 2♣ A♥ 2♥)
                    )
                    {
                        //move as cartas do jogo para a direita, dando espaço para a carta da mão entrar
                        for (int i = minhaMesa->jogos[jogo].qntCartas-1; i >= 1; i--)
                            trocaCarta(&(minhaMesa->jogos[jogo].cartas[i]), &(minhaMesa->jogos[jogo].cartas[i+1]));

                        trocaCarta(&(mao->cartas[cMao]), &(minhaMesa->jogos[jogo].cartas[1])); //coloca a carta da mão no jogo

                        cartaPStr(cartaStr, minhaMesa->jogos[jogo].cartas[1]); //converter a carta adicionada em uma string de carta

                        fezJogo = 1;
                    }
                    else if(//final do jogo
                        //se o naipe é igual a carta depois do coringa
                        minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-2].naipe == mao->cartas[cMao].naipe &&
                        //se é sequência da carta depois do coringa
                        minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-2].valor + 1 == mao->cartas[cMao].valor &&
                        //se a carta do final é coringa
                        minhaMesa->jogos[jogo].qntCartas-1 == posC2 &&

                        //se a carta depois do coringa é ck (para evitar K♥ A♥ 2♣)
                        !(minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-2].valor == ck)
                    )
                    {
                        trocaCarta(&(minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-1]), &(minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas])); //avança o c2 para a direita

                        trocaCarta(&(mao->cartas[cMao]), &(minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-1])); //coloca a carta da mão no jogo

                        cartaPStr(cartaStr, minhaMesa->jogos[jogo].cartas[minhaMesa->jogos[jogo].qntCartas-1]); //converter a carta adicionada em uma string de carta

                        fezJogo = 1;
                    }
                }

                if(fezJogo)
                {
                    sprintf(comandos[*qntComandos], "MELD_JOIN %d [ %s ]\n", jogo, cartaStr); //usando o comando para o juiz colocar a carta no jogo
                    (*qntComandos)++;

                    //ajustando as quantidades
                    mao->qntCartas--;
                    minhaMesa->jogos[jogo].qntCartas++;

                    bubbleSort(mao); //ordena as cartas da mão

                    break;
                }
            }
        }
    }
}

int baixarUmJogo(vetCarta *mao, matCarta *minhaMesa, char comandos[][MAX_LINE], int *qntComandos)
{
    //strings das cartas que iram pro jogo
    char cartaStr1[MAX_TAM_CARTA_STR];
    char cartaStr2[MAX_TAM_CARTA_STR];
    char cartaStr3[MAX_TAM_CARTA_STR];

    int fezJogo = 0; //quando fez um jogo: fezJogo = 1

    //tentando achar um jogo SEM coringa
    for (int cMao = 0; cMao < mao->qntCartas-2; cMao++) //for mao
            if(//se achar um jogo (sem coringa), baixa o jogo
                (//se naipes forem iguais
                    mao->cartas[cMao].naipe == mao->cartas[cMao+1].naipe &&
                    mao->cartas[cMao+1].naipe == mao->cartas[cMao+2].naipe
                )
                &&
                (//se valores forem sequência
                    mao->cartas[cMao].valor +1 == mao->cartas[cMao+1].valor &&
                    (mao->cartas[cMao+1].valor +1 == mao->cartas[cMao+2].valor ||
                    mao->cartas[cMao+1].valor == ck && mao->cartas[cMao+2].valor == ca)
                )
                &&
                (//se não for c2
                    mao->cartas[cMao].valor != c2 &&
                    mao->cartas[cMao+1].valor != c2 &&
                    mao->cartas[cMao+2].valor != c2
                )
            )
            {
                //convertendo as cartas para string
                cartaPStr(cartaStr1, mao->cartas[cMao]);
                cartaPStr(cartaStr2, mao->cartas[cMao+1]);
                cartaPStr(cartaStr3, mao->cartas[cMao+2]);

                for (int i = 0; i < 3; i++) //colocar as cartas da mão no jogo
                    trocaCarta(&mao->cartas[cMao+i], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[i]);

                fezJogo = 1; //baixou um jogo

                break;
            }

    //tentando achar um jogo COM coringa de MESMO naipe
    for (int posC2 = 0; posC2 < mao->qntCartas && !fezJogo; posC2++) //procurando coringa na mão
        if(mao->cartas[posC2].valor == c2) //se achar um coringa
            for (int cMao = 0; cMao < mao->qntCartas-1; cMao++) //procurando um jogo de 2 cartas na mão
            {
                if(//2♥ 5♥ 6♥
                    (//se naipes forem iguais
                        mao->cartas[posC2].naipe == mao->cartas[cMao].naipe &&
                        mao->cartas[cMao].naipe == mao->cartas[cMao+1].naipe
                    )
                    &&
                    (//se valores forem sequência
                        mao->cartas[cMao].valor +1 == mao->cartas[cMao+1].valor ||
                        mao->cartas[cMao].valor == ck && mao->cartas[cMao+1].valor == ca
                    )
                    &&
                    (//se não tiver mais c2
                        mao->cartas[cMao].valor != c2 &&
                        mao->cartas[cMao+1].valor != c2
                    )
                )
                {
                    //convertendo as cartas para string
                    cartaPStr(cartaStr1, mao->cartas[posC2]);
                    cartaPStr(cartaStr2, mao->cartas[cMao]);
                    cartaPStr(cartaStr3, mao->cartas[cMao+1]);

                    //colocar as cartas da mão no jogo
                    trocaCarta(&mao->cartas[posC2], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[0]);
                    trocaCarta(&mao->cartas[cMao], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[1]);
                    trocaCarta(&mao->cartas[cMao+1], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[2]);

                    fezJogo = 1; //baixou um jogo

                    break;
                }
                else if(//5♥ 2♥ 7♥
                    (//se naipes forem iguais
                        mao->cartas[posC2].naipe == mao->cartas[cMao].naipe &&
                        mao->cartas[cMao].naipe == mao->cartas[cMao+1].naipe
                    )
                    &&
                    (//se valores forem sequência +2
                        mao->cartas[cMao].valor +2 == mao->cartas[cMao+1].valor ||
                        mao->cartas[cMao].valor == cq && mao->cartas[cMao+1].valor == ca
                    )
                    &&
                    (//se não tiver mais c2
                        mao->cartas[cMao].valor != c2 &&
                        mao->cartas[cMao+1].valor != c2
                    )
                )
                {
                    //convertendo as cartas para string
                    cartaPStr(cartaStr1, mao->cartas[cMao]);
                    cartaPStr(cartaStr2, mao->cartas[posC2]);
                    cartaPStr(cartaStr3, mao->cartas[cMao+1]);

                    //colocar as cartas da mão no jogo
                    trocaCarta(&mao->cartas[cMao], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[0]);
                    trocaCarta(&mao->cartas[posC2], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[1]);
                    trocaCarta(&mao->cartas[cMao+1], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[2]);

                    fezJogo = 1; //baixou um jogo

                    break;
                }
            }

    //tentando achar um jogo COM QUALQUER coringa
    for (int posC2 = 0; posC2 < mao->qntCartas && !fezJogo; posC2++) //procurando coringa na mão
        if(mao->cartas[posC2].valor == c2) //se achar um coringa
            for (int cMao = 0; cMao < mao->qntCartas-1; cMao++) //procurando um jogo de 2 cartas na mão
            {
                if(//2♣ 5♥ 6♥
                    //se naipes forem iguais
                    mao->cartas[cMao].naipe == mao->cartas[cMao+1].naipe
                    &&
                    (//se valores forem sequência
                        mao->cartas[cMao].valor +1 == mao->cartas[cMao+1].valor ||
                        mao->cartas[cMao].valor == ck && mao->cartas[cMao+1].valor == ca
                    )
                    &&
                    (//se as outras cartas não forem o coringa
                        cMao != posC2 &&
                        cMao+1 != posC2
                    )
                )
                {
                    //convertendo as cartas para string
                    cartaPStr(cartaStr1, mao->cartas[posC2]);
                    cartaPStr(cartaStr2, mao->cartas[cMao]);
                    cartaPStr(cartaStr3, mao->cartas[cMao+1]);

                    //colocar as cartas da mão no jogo
                    trocaCarta(&mao->cartas[posC2], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[0]);
                    trocaCarta(&mao->cartas[cMao], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[1]);
                    trocaCarta(&mao->cartas[cMao+1], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[2]);

                    fezJogo = 1; //baixou um jogo

                    break;
                }
                else if(//5♥ 2♣ 7♥
                    //se naipes forem iguais
                    mao->cartas[cMao].naipe == mao->cartas[cMao+1].naipe
                    &&
                    (//se valores forem sequência +2
                        mao->cartas[cMao].valor +2 == mao->cartas[cMao+1].valor ||
                        mao->cartas[cMao].valor == cq && mao->cartas[cMao+1].valor == ca
                    )
                    &&
                    (//se as outras cartas não forem o coringa
                        cMao != posC2 &&
                        cMao+1 != posC2
                    )
                )
                {
                    //convertendo as cartas para string
                    cartaPStr(cartaStr1, mao->cartas[cMao]);
                    cartaPStr(cartaStr2, mao->cartas[posC2]);
                    cartaPStr(cartaStr3, mao->cartas[cMao+1]);

                    //colocar as cartas da mão no jogo
                    trocaCarta(&mao->cartas[cMao], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[0]);
                    trocaCarta(&mao->cartas[posC2], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[1]);
                    trocaCarta(&mao->cartas[cMao+1], &minhaMesa->jogos[minhaMesa->qntJogos].cartas[2]);

                    fezJogo = 1; //baixou um jogo

                    break;
                }
            }

    if(fezJogo) //se fez um jogo
    {
        //ajustando quantidades
        mao->qntCartas -= 3;
        minhaMesa->jogos[minhaMesa->qntJogos].qntCartas += 3;
        minhaMesa->qntJogos++;

        bubbleSort(mao); //ordena as cartas da mão

        sprintf(comandos[*qntComandos], "MELD_NEW [ %s %s %s ]\n", cartaStr1, cartaStr2, cartaStr3); //salva o comando no vetor
        (*qntComandos)++;
    }
            
    return fezJogo; //se não baixou um jogo: 0. se baixou um jogo: 1
}

int calcularPontuacao(vetCarta *mao, matCarta *mesa)
{
    int pontuacao = 0; //pontuação do jogador a ser verificado

    //remover pontos com basenas cartas da mão
    for (int posC = 0; posC < mao->qntCartas; posC++) //for mao
    {
        //desconhecida e do 3 ao 7: -5 pontos
        if(mao->cartas[posC].valor == cdesc ||
        mao->cartas[posC].valor >= c3 && mao->cartas[posC].valor <= c7)
            pontuacao -= 5;
        //2 e do 8 ao K: -10 pontos
        else if(mao->cartas[posC].valor == c2 ||
        mao->cartas[posC].valor >= c8 && mao->cartas[posC].valor <= c10)
            pontuacao -= 10;
        //Ás: -15 pontos
        else if(mao->cartas[posC].valor == ca)
            pontuacao -= 15;
    }

    //adicionar pontos com base na mesa
    for (int jogo = 0; jogo < mesa->qntJogos; jogo++) //for mesa
    {
        int temC2 = 0; //se tiver coringa no jogo
        if(mesa->jogos[jogo].qntCartas >= 7) //se é uma canastra, verifica se tem coringa
        {
            for (int posC = 0; posC < mesa->jogos[jogo].qntCartas-1; posC++) //for jogo
                if(mesa->jogos[jogo].cartas[posC].naipe != mesa->jogos[jogo].cartas[posC+1].naipe)
                {
                    temC2 = 1; //tem coringa
                    pontuacao += 100; //+100 por ser canastra suja
                    break;
                }
            
            if(!temC2) //se não tiver coringa
                pontuacao += 200; //+200 por ser canastra limpa
        }

        for (int posC = 0; posC < mesa->jogos[jogo].qntCartas-1; posC++) //for jogo
        {
            //do 3 ao 7: 5 pontos
            if(mesa->jogos[jogo].cartas[posC].valor >= c3 && mesa->jogos[jogo].cartas[posC].valor <= c7)
                pontuacao += 5;
            //2 e do 8 ao K: 10 pontos
            else if(mesa->jogos[jogo].cartas[posC].valor == c2 ||
            mesa->jogos[jogo].cartas[posC].valor >= c8 && mesa->jogos[jogo].cartas[posC].valor <= c10)
                pontuacao += 10;
            //Ás: 15 pontos
            else if(mesa->jogos[jogo].cartas[posC].valor == ca)
                pontuacao += 15;
        }
    }

    return pontuacao;
}

void verSeBate(vetCarta *mao, vetCarta *maoOpo, matCarta *minhaMesa, matCarta *mesaOpo, int qntCartasDeck)
{
    char comandos[MAX_CARTAS_DECK/*maxQntComandos*/][MAX_LINE]; //variável que armazena os comandos que serão utilizados no teste
    int qntComandos = 0; //quantidade de comandos que foram utilizados no teste

    vetCarta maoTmp = *mao; //guarda a mão para retornar seu valor caso o teste falhe
    matCarta mesaTmp = *minhaMesa; //guarda a mesa para retornar seu valor caso o teste falhe


    int baixouJogo = 1; //se tiver baixado um jogo, o loop continua
    while (baixouJogo) //para quando não conseguir baixar mais jogos nem cartas
    {
        baixouJogo = 0;

        //baixar todas as cartas possíveis (adicionar em jogos)
        adicionarCartasEmJogos(minhaMesa, mao, comandos, &qntComandos);

        //tentar baixar UM jogo
        baixouJogo = baixarUmJogo(mao, minhaMesa, comandos, &qntComandos);
    }

    //se a pontuação for maior que a do oponente (se puder bater)
    if(mao->qntCartas <= 1 && calcularPontuacao(mao, minhaMesa) +100 > calcularPontuacao(maoOpo, mesaOpo) ||
    qntCartasDeck <= 1 ||
    maoOpo->qntCartas <= QNT_MAO_OPO_P_BAIXAR)
    {
        if(mao->qntCartas <= 1 && calcularPontuacao(mao, minhaMesa) +100 > calcularPontuacao(maoOpo, mesaOpo))
            fprintf(stderr, "BATI!!\n");//apagar

        fprintf(stderr, "Comandos do verSeBate();\n");//apagar
        for (int i = 0; i < qntComandos; i++)
            printf("%s", comandos[i]);
    }
    else //se ainda tiver cartas na mão (se não puder bater)
    {
        *mao = maoTmp; //volta a mão antes do teste
        *minhaMesa = mesaTmp; //volta a mesa antes do teste
    }
}

int acharPosCartaOpo(vetCarta *mao, carta card)
{
    //procurando a carta card na mão do oponente
    for (int posC = 0; posC < mao->qntCartas; posC++) //for mao
        if(mao->cartas[posC].valor == card.valor && mao->cartas[posC].naipe == card.naipe) //se for igual
            return posC; //retorna a posição da carta

    //se não encontrar a carta card, procura uma carta desconhecida
    for (int posC = 0; posC < mao->qntCartas; posC++) //for mao
        if(mao->cartas[posC].valor == cdesc && mao->cartas[posC].naipe == ndesc) //se for igual
            return posC; //retorna a posição da carta desconhecida

    fprintf(stderr, "ERRO: acharPosCartaOpo(); Sem cartas na mão do oponente\n");//apagar
    return -1; //se o oponente não pussuir cartas na mão
}