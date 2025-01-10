#include <stdlib.h>
#include <stdio.h>

#define SUCESSO 0

float determinaMediaNegativa(int* conjuntoNumero, int atual) {
    int soma = 0;
    int qntNumNegativo = 0;

    for(int p = 0; p < atual - 1; p++) {
        if(conjuntoNumero[p] < 0) {
            soma += conjuntoNumero[p];
            qntNumNegativo++;
        } 
    }
    if(qntNumNegativo == 0) {
        return 0.0;
    }

    return (soma * 1.0) / qntNumNegativo;
}

float determinaMediaPositiva(int* conjuntoNumero, int atual) {
    int soma = 0;
    int qntNumPositivo = 0;

    for(int p = 0; p < atual - 1; p++) {
        if(conjuntoNumero[p] > 0) {
            soma += conjuntoNumero[p];
            qntNumPositivo++;
        } 
    }

    if(qntNumPositivo == 0) {
        return 0.0;
    }

    return (soma * 1.0) / qntNumPositivo;
}

float determinaMedia(int* conjunto, int atual) {
    int soma = 0;
    for(int p = 0; p < atual - 1; p++) {
        soma += conjunto[p];
    }

    return (soma * 1.0) / (atual - 1);

}

int main(int argc, char* argv[]) {
    int* conjuntoNumeros = NULL;
    int atual = 0;
    float mediaNegativo;
    float mediaPostivo;
    float mediaGeral;

    do {
        conjuntoNumeros = (int*)realloc(conjuntoNumeros, sizeof(int) * atual + 1);
        printf("Digite o numero %i do conjunto: ", atual + 1);
        (void)scanf("%d%*c", &conjuntoNumeros[atual]);
        atual++;

    } while(conjuntoNumeros[atual - 1] != 0);
    
    mediaNegativo = determinaMediaNegativa(conjuntoNumeros, atual);    
    mediaPostivo = determinaMediaPositiva(conjuntoNumeros, atual);
    mediaGeral = determinaMedia(conjuntoNumeros, atual);

    printf("Media negativa: %f\nMedia positiva: %f\nMedia Geral: %f\n", mediaNegativo, mediaPostivo, mediaGeral);

    return SUCESSO;
}