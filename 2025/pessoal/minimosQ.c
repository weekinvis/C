/*
* @file    minimosQ.c
* @brief   Programa para calcular uma reta
*          usando o metodo dos minimos quadrados.
* @authors Frederico S. Goncalves & Bernardo D. O. Penna
* @date    2025-02-12
*/

// Inclusoes de Bibliotecas
#include <stdlib.h>
#include <stdio.h>

// Definicoes de constantes
#define QNT_DIM   (2)
#define SUCESSO   (0)
#define X         (0)
#define Y         (1)

// ===================================================================== FUNÇÕES ===================================================================

/**
 * Função que aloca a matriz para guardar as coordenadas X e Y.
 * @param qntCoordenadas Quantidade de pontos em cada dimensao.
 * @return Retorna o endereço da matriz coordenadasPontos alocada.
 */

double** alocaDimPontos(int qntCoordenadas) {
    double** coordenadasPontos = NULL;

    coordenadasPontos = (double**)malloc(sizeof(double) * qntCoordenadas);

    for (int p = 0; p < qntCoordenadas; p++) {
        coordenadasPontos[p] = (double*)malloc(sizeof(double) * QNT_DIM);
    }

    return coordenadasPontos;
}

/**
 * Função que le os valores dados pelo usuario para as coordenadas.
 * @param coordenadasPontos Matriz que guarda um ponto X e seu determinado ponto Y.
 * @param qntCoordenadas Quantidade de pontos em cada dimensao.
 */

void leValores(double** coordenadasPontos, int qntCoordenadas) {

    for (int f = 0; f < qntCoordenadas; f++) {
        printf("Digite o valor X da coordenada %i: ", f + 1);
        (void)scanf("%lf%*c", &coordenadasPontos[f][X]);
    }

    printf("\n");

    for (int f = 0; f < qntCoordenadas; f++) {
        printf("Digite o valor Y da coordenada %i: ", f + 1);
        (void)scanf("%lf%*c", &coordenadasPontos[f][Y]);

    }
}

/**
 * Função que calcula a media dos valores da dimensão X.
 * @param coordenadasPontos Matriz que guarda um ponto X e seu determinado ponto Y.
 * @param qntCoordenadas Quantidade de pontos em cada dimensao.
 * @return Retorna a divisao do valor da somatoria pela quantidade de elementos (media aritmetica).
 */

double calculaMediaX(double** coordenadasPontos, int qntCoordenadas) {
    double total = 0.0;

    for (int f = 0; f < qntCoordenadas; f++)
    {
        total += coordenadasPontos[f][X];
    }

    return total / qntCoordenadas;
}

/**
 * Função que calcula a media dos valores da dimensão Y.
 * @param coordenadasPontos Matriz que guarda um ponto X e seu determinado ponto Y.
 * @param qntCoordenadas Quantidade de pontos em cada dimensao.
 * @return Retorna a divisao do valor da somatoria pela quantidade de elementos (media aritmetica).
 */

double calculaMediaY(double** coordenadasPontos, int qntCoordenadas) {
    double total = 0.0;

    for (int p = 0; p < qntCoordenadas; p++) {
        total += coordenadasPontos[p][Y];
    }
    return total / qntCoordenadas;
}

/**
 * Função que calcula a somatoria da expressao (Xi - X')(Yi - Y').
 * @param coordenadasPontos Matriz que guarda um ponto X e seu determinado ponto Y.
 * @param qntCoordenadas Quantidade de pontos em cada dimensao.
 * @param mediaX A media dos valores da dimensão X.
 * @param mediaY A media dos valores da dimensão Y.
 * @return Retorna o resultado da somatoria.
 */

double calculaSxy(double** coordenadasPontos, int qntCoordenadas, double mediaX, double mediaY) {
    double total = 0.0;

    for (int f = 0; f < qntCoordenadas; f++)
    {
        total += (coordenadasPontos[f][X] - mediaX) * (coordenadasPontos[f][Y] - mediaY);
    }

    return total;
}


/**
 * Função que calcula a somatoria da expressao (Xi - X')^2.
 * @param coordenadasPontos Matriz que guarda um ponto X e seu determinado ponto Y.
 * @param qntCoordenadas Quantidade de pontos em cada dimensao.
 * @param mediaX A media dos valores da dimensão X.
 * @return Retorna o resultado da somatoria.
 */

double calculaSxx(double** coordenadasPontos, int qntCoordenadas, double mediaX) {
    double Sxx = 0.0;

    for (int p = 0; p < qntCoordenadas; p++) {
        Sxx += (coordenadasPontos[p][X] - mediaX) * (coordenadasPontos[p][X] - mediaX);
    }

    return Sxx;
}

/**
 * Função que calcula o coeficiente angular (a) da funcao afim desejada a partir de Sxy e Sxx.
 * @param Sxy Valor da somatoria da expressao (Xi - X')(Yi - Y').
 * @param Sxx Valor da somatoria da expressao (Xi - X')^2.
 * @return Retorna a divisao de Sxy por Sxx (o valor de a).
 */

static inline double calculaA(double Sxy, double Sxx) {
    return Sxy / Sxx;
}

/**
 * Função que calcula o coeficiente linear (b) da funcao afim desejada a partir de mediaX, mediaY e a.
 * @param a Coeficiente angular da funcao afim.
 * @param mediaX A media dos valores da dimensão X.
 * @param mediaY A media dos valores da dimensão Y.
 * @return Retorna o valor de b.
 */

static inline double calculaB(double a, double mediaX, double mediaY) {
    return mediaY - (mediaX * a);
}

/**
 * Função que imprime todos os pontos da funcao afim a partir das coordenadas X originais.
 * @param coordenadasPontos Matriz que guarda um ponto X e seu determinado ponto Y.
 * @param qntCoordenadas Quantidade de pontos em cada dimensao.
 * @param a Coeficiente angular da funcao afim.
 * @param b Coeficiente linear da funcao afim.
 */

void imprimeCoordPontos(double** coordenadasPontos, int qntCoordenadas, double a, double b) {
    double yPonto;

    printf("Pontos:\n");

    for (int f = 0; f < qntCoordenadas; f++)
    {
        yPonto = a * coordenadasPontos[f][X] + b;
        printf("Ponto %d: %.3lf;\n", f + 1, yPonto);
    }
}

/**
 * Função que libera a matriz coordenadasPontos alocada.
 * @param coordenadasPontos Matriz que guarda um ponto X e seu determinado ponto Y.
 * @param qntCoordenadas Quantidade de pontos em cada dimensao.
 */

void desalocaMemoria(double** coordenadasPontos, int qntCoordenadas) {

    for (int p = 0; p < qntCoordenadas; p++) {
        free(coordenadasPontos[p]);

    }
    free(coordenadasPontos);
}

// ==================================================================== INT MAIN ===================================================================

/**
 * Função onde o programa é inicializado.
 * @param argc Número de argumentos passados para o programa pela linha
 * de comando.
 * @param argv Valores dos argumentos.
 * @return SUCESSO caso o programa termine conforme esperado, ou caso
 * contrário, o código do erro ocorrido.
 */

int main(int argc, char* argv[]) {
    double** coordenadasPontos = NULL;      // linhas = N de pontos/ Colunas = qnt coordenadass

    int opcao;                              // Opcao escolhida pelo usuario para navegar no menu.
    int qntCoordenadas;                     // Quantidade de coordenadas X.

    double mediaX, mediaY;                  // Medias dos valores de X e Y.
    double Sxx, Sxy;                        // Somatorias para o calculo.
    double a, b;                            // Coeficientes angular e linear.

    do {
        printf("\n\n1 - Calcular reta;\n0 - Sair.\nOpcao: ");
        (void)scanf("%d%*c", &opcao);

        switch (opcao) {
        case 1:

            printf("\nQuant. coordenadas grafico: ");
            (void)scanf("%d%*c", &qntCoordenadas);
            printf("\n");

            coordenadasPontos = alocaDimPontos(qntCoordenadas);

            leValores(coordenadasPontos, qntCoordenadas);

            mediaX = calculaMediaX(coordenadasPontos, qntCoordenadas);
            mediaY = calculaMediaY(coordenadasPontos, qntCoordenadas);
            Sxx = calculaSxx(coordenadasPontos, qntCoordenadas, mediaX);
            Sxy = calculaSxy(coordenadasPontos, qntCoordenadas, mediaX, mediaY);
            a = calculaA(Sxy, Sxx);
            b = calculaB(a, mediaX, mediaY);

            printf("\nMedia x (x'): %.2lf\n", mediaX);
            printf("Media y (y'): %.2lf\n", mediaY);
            printf("Sxy: %.2lf\n", Sxy);
            printf("Sxx: %.2lf\n", Sxx);
            printf("Coeficiente angular (a): %.3lf\n", a);
            printf("Coeficiente linear(b): %.3lf\n", b);
            printf("Funcao afim: f(x) = %.3lfx + %.3lf\n\n", a, b);

            imprimeCoordPontos(coordenadasPontos, qntCoordenadas, a, b);

            desalocaMemoria(coordenadasPontos, qntCoordenadas);

            break;

        case 0:
            printf("\n");
            break;

        default:
            fprintf(stderr, "Opcao invalida!\n");
            break;
        }

    } while (opcao != 0);

    return SUCESSO;
}
