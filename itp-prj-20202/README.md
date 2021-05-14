# Projeto da disciplina de ITP - 2020.2

- [Grupo](#grupo)
- [Compilação](#compilação)
- [Status do Projeto](#status-do-projeto)

# Grupo

* **Arthur Soares Ramalho** - T05 - 20200038767
* **Rita de Cássia Chagas da Cruz** - T05 -20200041181

# Compilação

É necessário compilar os arquivos em C (`carta.c`, `misc.c`, `vetCarta.c`, `bot.c`), gerando um executável (`bot`), e, em seguida, executar o programa juiz (`buraco.js`) passando o executável gerado como parâmetro. O programa `buraco` é um script desenvolvido em Javascript e, portanto, deve ser chamado usando o nodeJs.

As linhas a seguir farão esses passos.

```sh
$ gcc carta.c misc.c vetCarta.c bot.c -o bot
$ node buraco.js bot
```

No exemplo acima, como apenas um executável foi passado como parâmetro (`bot`), o juiz irá lançar um processo especial que irá substituir o bot adversário. Esse processo irá interagir com o usuário, será uma partida *human player vs bot*.

Para competir com outro bot (ou mesmo fazer com que o bot compita contra ele mesmo), é necessário passar o nome dos dois executáveis. Nesse caso, não haverá interação com o usuário, será uma partida *bot vs bot*.

```sh
$ node buraco.js bot1 bot2
```

## Definir um estado inicial do jogo

Para definir esse estado inicial, basta lançar o programa com o parâmetro `-i` seguido do nome de um arquivo. Este arquivo deverá conter os dados do estado no seguinte formato: para 2 jogadores, haverá inicialmente linhas com as sequências de cartas dos jogadores (envolvidas por `[ ]`), depois a carta do lixo e, por fim, um número indicando o índice do jogador que irá começar.

O arquivo `estadoInicial.txt` exemplifica o formato do arquivo. O teste do estado inicial definido no arquivo é feito com a linha de comando:
```sh
node buraco -i estadoInicial.txt bot
```

# Status do Projeto

Concluído.

## Features

- Checkpoint 1
  - Implementação básica do bot
  - Utilização de arranjos e registros
  - Definição de estrutura de dados para as cartas e para a mão do jogador
  - Modularização base
  - Alocação dinâmica
  - Implementação de uma estratégia base
- Checkpoint 2
  - Implementação das modificações identificadas no Checkpoint 1
  - Modularização otimizada
  - Utilização de ponteiros e alocação dinâmica otimizada
  - Implementação de uma estratégia aprimorada, que leva em consideração, além das cartas do jogador: 
    - todas as cartas do lixo
    - as cartas do adversário
    - a situação atual da partida e a pontuação
  - Anexação de cartas a jogos existentes
  - Busca por jogos na mão 