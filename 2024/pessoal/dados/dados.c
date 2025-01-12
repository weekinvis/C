#include "dados.h"
#include "utilDados.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define VALOR_MINIMO 1

uint8_t leDados(int* qnt, int* nFacesDado) {
    uint8_t scan;

    printf("Digite os dados: ");
    scan = scanf("%d%*c%d%*c", qnt, nFacesDado);

    return scan;

}

uint8_t geraNumeroDado(int nFacesDado) {
    return (rand() % nFacesDado) + VALOR_MINIMO;
}

uint8_t* girarDados(int qnt, int nFacesDado) {
    uint8_t* resultados = NULL;

    resultados = (uint8_t*)malloc(sizeof(uint8_t) * qnt + 1);
    resultados[0] = qnt + 1;

    for(int p = 1; p < qnt + 1; p++) {
        resultados[p] = geraNumeroDado(nFacesDado);
    }

    return resultados;

}

void imprimeResultadosDados(uint8_t* resultados) {
    uint8_t* indicesMaioresValores = NULL;
    uint16_t soma = 0;
    int q = 1;

    indicesMaioresValores = utilEncontraMaioresValores(resultados);

    system("cls || clear");

    printf("[");

    for(int p = 1; p < resultados[0]; p++) {

        soma += resultados[p];
        
        if(p == indicesMaioresValores[q] && q < indicesMaioresValores[0]) {
            printf("\033[94m");
        }

        p + 1 == resultados[0] ? printf("%hhu\033[0m] < Soma = %hu", resultados[p], soma) : printf("%hhu, ", resultados[p]);

        if(p == indicesMaioresValores[q] && q < indicesMaioresValores[0]) {
            printf("\033[0m");
            q++;
        }

    }
    printf("\n");

    free(indicesMaioresValores);

    return;
}

void liberaResultadosDados(uint8_t* resultados) {
    free(resultados); 
}