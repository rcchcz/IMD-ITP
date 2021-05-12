#include <stdio.h>

/**
 * Cria um histograma H com C categorias a partir de uma sequência de valores lidos da entrada-padrão.
 * A entrada a ser lida contém um valor inteiro N seguido de uma sequência de N valores reais.
 * 
 * Os valores lidos estarão entre na faixa de 0 a 10 (incluindo estes) e serão contabilizados no histograma
 * de acordo com o intervalo a qual pertence, levando em conta que haverá C categorias entre 0 e 10.
 * 
 * Por exemplo, se C for 5, teremos os intervalos [0; 2[, [2; 4[, [4; 6[, [6; 8[ e [8; 10]. Portanto, se o
 * valor 3.0 for lido, a 2ª categoria terá um elemento a mais no histograma. Se C for 3, os intervalos
 * seriam [0; 3.333...[, [3.333...; 6.666...[ e [6.666...;10]. Portanto, a 1ª categoria será atualizada.
 * 
 * @param c Número de categorias do histograma
 * @param h Array do histograma cujos valores serão atualizados a partir de dados lidos da entrada-padrão.
 */
void createHistogram(int c, int h[c]) {
    int quantidade_notas;
    float nota;

    for (int i = 0; i < c; i++) {
        h[i] = 0;
    }

    int variacoes[c];

    for(int i = 0; i < c; i++) {
        if(i) variacoes[i] = variacoes[i-1] + (10/c);
            else variacoes[i] = 0;
    }

    scanf("%i", &quantidade_notas);
    for(int i = 0; i < quantidade_notas; i++) {
        scanf("%f", &nota);
        for(int j = 0; j < c; j++) {
            if(nota >= variacoes[c-1]) {
                h[c-1]++;
                break;
            } else if(nota >= variacoes[j] && nota < variacoes[j+1]) {
                h[j]++;        
            }
        }
    }
}

/**
 * Junta os valores de dois histogramas em um terceiro histograma.
 * 
 * @param c  Número de categorias do histograma.
 * @param h1 Array com os dados do 1º histograma.
 * @param h2 Array com os dados do 2º histograma.
 * @param joint Array do histograma cujos valores serão atualizados a partir dos dois primeiros.
 */
void joinHistograms(int c, int h1[c], int h2[c], int joint[c]) {
    for(int i = 0; i < c; i++) { // preenche intervalos
        joint[i] = h1[i] + h2[i];
    }   
}

/**
 * Imprime um histograma em modo textual. A altura do histograma (quantidade de linhas a
 * serem impressas) corresponde ao maior valor de seu array.
 * 
 * @param c Número de categorias do histograma.
 * @param h Array com os dados do histograma a imprimir.
 */
void printHistogram(int c, int h[c]) {
    int maior = h[0];
    for(int i = 0; i < c; i++) { // busca maior numero de ocorrencias
        if(h[i] > maior) maior = h[i];
    }

    for(int i = 0; i < maior; i++) { // imprime histograma
        for(int j = 0; j < c; j++) {
            printf("_");
            if(h[j] >= maior-i) printf("##");
                else printf("__");
            printf("_");
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int numCateg;
    scanf("%i", &numCateg);

    int histA[numCateg];
    int histB[numCateg];
    int histAll[numCateg];

    createHistogram(numCateg, histA);
    createHistogram(numCateg, histB);
    joinHistograms(numCateg, histA, histB, histAll);

    printHistogram(numCateg, histA);
    printHistogram(numCateg, histB);
    printHistogram(numCateg, histAll);

    return 0;
}