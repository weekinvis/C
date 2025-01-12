// Bibliotecas
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Constantes
#define SUCESSO                0
#define TAM_TAB                8
#define QNT_MINAS              (TAM_TAB * 3)
#define POSICAO_TABELA_ASCII   48

#define QNT_COORDENADAS 2
#define Y               1
#define X               0

// Estruturas

// Funcoes 
void inicializaTabuleiro(char tab[][TAM_TAB]) {

    for(int p = 0; p < TAM_TAB; p++) {
        for(int q = 0; q < TAM_TAB; q++) {
            tab[p][q] = '.';
        }
    }

}

void imprimeTabuleiro(char tab[][TAM_TAB]) {
    for(int p = 0; p < TAM_TAB; p++) {
        for(int q = 0; q < TAM_TAB; q++) {
            printf("%c ", tab[p][q]);
        }
        printf("\n");
    }
}

void trocaBubbleSort(int coordendasMinas[], int coordenadasMinas2[]) {
    int temporario[QNT_COORDENADAS];
    temporario[X] = coordendasMinas[X];
    temporario[Y] = coordendasMinas[Y];
    coordendasMinas[X] = coordenadasMinas2[X];
    coordendasMinas[Y] = coordenadasMinas2[Y];
    coordenadasMinas2[X] = temporario[X];
    coordenadasMinas2[Y] = temporario[Y];
}

void ordenaCoordenadasMinas(int coordenadasMinas[][QNT_COORDENADAS]) {
    for(int p = 0; p < QNT_MINAS - 1; p++) {
        for(int q = 0; q < QNT_MINAS - 1 - p; q++) {
            if(coordenadasMinas[q][X] < coordenadasMinas[q + 1][X]) {
                trocaBubbleSort(coordenadasMinas[q], coordenadasMinas[q + 1]);
            }
        }
    }
    for(int p = 0; p < QNT_MINAS - 1; p++) {
        for(int q = 0; q < QNT_MINAS - 1 - p; q++) {
            if(coordenadasMinas[q][Y] < coordenadasMinas[q + 1][Y] && coordenadasMinas[q][X] == coordenadasMinas[q + 1][X]) {
                trocaBubbleSort(coordenadasMinas[q], coordenadasMinas[q + 1]);
            }
        }
    }
}

void garanteNaoRepeticao(int coordenadasMinas[][QNT_COORDENADAS]) {
    bool repeticao;

    ordenaCoordenadasMinas(coordenadasMinas);
    do {
        repeticao = false;
        for(int p = 0; p < QNT_MINAS - 1; p++) {
            if(coordenadasMinas[p + 1][X] == coordenadasMinas[p][X] && coordenadasMinas[p + 1][Y] == coordenadasMinas[p][Y]) {
                coordenadasMinas[p][X] = rand() % TAM_TAB;
                coordenadasMinas[p][Y] = rand() % TAM_TAB;
                repeticao = true;
            }
            ordenaCoordenadasMinas(coordenadasMinas);
        }

    } while(repeticao);

}

void geraCoordenadasMinas(int coordenadasMinas[][QNT_COORDENADAS]) {

    for(int p = 0; p < QNT_MINAS; p++) {
        coordenadasMinas[p][X] = rand() % TAM_TAB;
        coordenadasMinas[p][Y] = rand() % TAM_TAB;
    }
    ordenaCoordenadasMinas(coordenadasMinas);
    garanteNaoRepeticao(coordenadasMinas);

}

int contaMinasProximas(int coordenadasMinas[][QNT_COORDENADAS], int jogadas[QNT_COORDENADAS]) {
    int qntMinasProximas = 0;

    for(int p = 0; p < QNT_MINAS; p++) {
        if(coordenadasMinas[p][X] == jogadas[X] + 1 || coordenadasMinas[p][X] == jogadas[X] || coordenadasMinas[p][X] == jogadas[X] - 1) {
            if(coordenadasMinas[p][Y] == jogadas[Y] + 1 || coordenadasMinas[p][Y] == jogadas[Y] - 1) {
                qntMinasProximas++;
            }
        }
        if(coordenadasMinas[p][Y] == jogadas[Y]) {
            if(coordenadasMinas[p][X] + 1 == jogadas[X] || coordenadasMinas[p][X] - 1 == jogadas[X]) {
                qntMinasProximas++;
            }
        }
    }
    return qntMinasProximas;
}

void imprimeCoordeadasMinas(int coordenadasMinas[][QNT_COORDENADAS]) {

    for(int p = 0; p < QNT_MINAS; p++) {
        printf("%d %d\n", coordenadasMinas[p][X], coordenadasMinas[p][Y]);
    }
}

bool verificaDerrota(char tab[][TAM_TAB], int coordenadasMinas[][QNT_COORDENADAS], int jogadas[]) {
    int minasProximas;
    for(int p = 0; p < QNT_MINAS; p++) {
        if(jogadas[X] == coordenadasMinas[p][X] && jogadas[Y] == coordenadasMinas[p][Y]) {
            return true;
        }
    }
    minasProximas = contaMinasProximas(coordenadasMinas, jogadas);
    tab[jogadas[X]][jogadas[Y]] = (char)(minasProximas + POSICAO_TABELA_ASCII);
    return false;
}

int main(int argc, char* argv[]) {
    char tabuleiro[TAM_TAB][TAM_TAB];
    int coordenadasMinas[QNT_MINAS][QNT_COORDENADAS];
    int jogadas[QNT_COORDENADAS];
    bool perdeu = false;

    srand(time(NULL));

    inicializaTabuleiro(tabuleiro);
    geraCoordenadasMinas(coordenadasMinas);
    imprimeCoordeadasMinas(coordenadasMinas);
    getchar();
    do{
        system("cls || clear");
        imprimeTabuleiro(tabuleiro);       
        scanf("%d %d%*c", &jogadas[X], &jogadas[Y]);
        perdeu = verificaDerrota(tabuleiro, coordenadasMinas, jogadas);
    }while(!perdeu);


    return SUCESSO;
}