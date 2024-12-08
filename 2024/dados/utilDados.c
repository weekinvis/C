#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "utilDados.h"

uint8_t* utilEncontraMaioresValores(uint8_t* resultados) {
    uint8_t maiorValor;

    uint8_t* indices = NULL;
    uint8_t qntIndices = 0;

    maiorValor = resultados[1];

    for(int p = 1; p < resultados[0]; p++) {
        if(resultados[p] > maiorValor) {
            maiorValor = resultados[p];
        }
    }

    for(int p = 1; p < resultados[0]; p++) {
        if(resultados[p] == maiorValor) {
            qntIndices++;
            indices = (uint8_t*)realloc(indices, sizeof(uint8_t) * qntIndices + 1);
            indices[qntIndices] = p;
        }
    }

    indices[0] = qntIndices + 1;

    return indices;
}

void utilMenuInicial() {
    system("clear || cls");
    printf("Bem vindo ao programa!\n");
    printf("Modo de usar: {quantidade de dados}d{num de faces do dado}\nEx: (3d20) < 3 dados de 20 faces\n");
    printf("Para sair, digite qualquer caractere e de enter!\n");
    printf("Nao passe, de nenhum modo, de 254. Seja por 254 lancamentos ou por dados maiores do que 254 faces.\n\n");
}

bool utilVerificaErro(uint8_t scan, int qnt, int nFacesDado) {
    fflush(stdin);
        
    if(scan != 2) {
        fprintf(stderr, "Digite conforme especificado! {qntDados}d{nFacesDado}!\n");
        return true;
    }
    if((0 >= qnt) || (0 >= nFacesDado)) {
        fprintf(stderr, "Digite um numero positivo para quantidade ou numero de faces!\n\n");
        return true;
    }
    if((qnt >= LIMITE_MEMORIA) || (nFacesDado >= LIMITE_MEMORIA)) {
        fprintf(stderr, "Limite de memoria alcancado!\n\n");
        return true;
    }

    return false;
        
}
