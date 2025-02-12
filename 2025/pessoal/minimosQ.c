/*
* @file    minimosQ.c
* @brief   Programa para calcular uma reta
*          usando o metodo dos minimos quadrados.
* @authors Frederico S. Goncalves & Bernardo D. O. Penna
* @date    2025-02-12
*/

// Definicoes de Bibliotecas
#include <stdlib.h>
#include <stdio.h>

// Definicoes de constantes
#define QNT_DIM   2
#define SUCESSO   0
#define X         0
#define Y         1

double calculaMediaX(double** coordenadasPontos, int qntCoordenadas) {
    double total = 0.0;

    for (int f = 0; f < qntCoordenadas; f++)
    {
        total += coordenadasPontos[f][X];
    }

    return total / qntCoordenadas;
}

double calculaMediaY(double** coordenadasPontos, int qntCoordenadas) {
    double total = 0.0;

    for (int p = 0; p < qntCoordenadas; p++) {
        total += coordenadasPontos[p][Y];
    }
    return total / qntCoordenadas;
}

double calculaSxy(double** coordenadasPontos, int qntCoordenadas, double mediaX, double mediaY) {
    double total = 0.0;

    for (int f = 0; f < qntCoordenadas; f++)
    {
        total += (coordenadasPontos[f][X] - mediaX) * (coordenadasPontos[f][Y] - mediaY);
    }

    return total;
}

double calculaSxx(double** coordenadasPontos, int qntCoordenadas, double mediaX) {
    double Sxx = 0.0;

    for (int p = 0; p < qntCoordenadas; p++) {
        Sxx += (coordenadasPontos[p][X] - mediaX) * (coordenadasPontos[p][X] - mediaX);
    }

    return Sxx;
}

static inline double calculaA(double Sxy, double Sxx) {
    return Sxy / Sxx;
}

static inline double calculaB(double a, double mediaX, double mediaY) {
    return mediaY - (mediaX * a);
}

double** alocaDimPontos(int qntCoordenadas) {
    double** coordenadasPontos = NULL;

    coordenadasPontos = (double**)malloc(sizeof(double*) * qntCoordenadas);

    for (int p = 0; p < qntCoordenadas; p++) {
        coordenadasPontos[p] = (double*)malloc(sizeof(double) * QNT_DIM);
    }

    return coordenadasPontos;

}

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

void desalocaMemoria(double** coordenadasPontos, int qntCoordenadas) {

    for (int p = 0; p < qntCoordenadas; p++) {
        free(coordenadasPontos[p]);

    }
    free(coordenadasPontos);

}

int main(int argc, char* argv[]) {
    double** coordenadasPontos = NULL; // linhas = N de ponts/ Colunas = qnt coordenadass
    double mediaX, mediaY;
    double Sxx, Sxy;
    double a, b;
    int qntCoordenadas;
    int opcao;

    do {
        printf("1 - Calcular reta;\n0 - Sair.\nOpcao: ");
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
            printf("Coeficiente linear(b): %.3lf\n\n", b);

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
