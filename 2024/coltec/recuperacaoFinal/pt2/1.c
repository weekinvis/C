#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void cadastrarReceita(receita_t** receitas, int* qntReceitas) {
    char tempNome[TAM_MAX_NOME_RECEITA];
    char tempUnidade[TAM_MAX_UNIDADE_MEDIDA];
    char tempNomeIng[TAM_MAX_NOME_INGREDIENTE];
    char tempModoPreparo[TAM_MAX_MODO_PREPARO];
    (*receitas) = (receita_t*)realloc((*receitas), sizeof(receita_t) * ((*qntReceitas) + 1));
    inicializaStructReceita(&(*receitas)[*qntReceitas]);
    receita_t* receitaAtual = &(*receitas)[(*qntReceitas)];

    printf("Digite o nome da receita: ");
    fgets(tempNome, TAM_MAX_NOME_RECEITA, stdin);
    removeQuebraLinhaFinal(tempNome);
    receitaAtual->nomeReceita = (char*)malloc(sizeof(char) * strlen(tempNome) + CHAR_FINALIZADOR_STRING);
    strcpy(receitaAtual->nomeReceita, tempNome);

    printf("Digite a quantidade de ingredientes: ");
    (void)scanf("%d%*c", &(*receitas)[*qntReceitas].QNT_INGREDIENTES);
    int qntIngredientes = (*receitas)[*qntReceitas].QNT_INGREDIENTES;

    receitaAtual->ingredientes = (ingrediente_t*)malloc(sizeof(ingrediente_t) * qntIngredientes);

    for (int p = 0; p < qntIngredientes; p++) {
        inicializaStructIngrediente(&(receitaAtual->ingredientes[p]));
        printf("Digite a quantidade do ingrediente %i: ", p + 1);
        (void)scanf("%d%*c", &(receitaAtual->ingredientes[p].quantidade));

        printf("Digite a unidade (g, mg, kg, l, etc) do ingrediente %i: ", p + 1);
        fgets(tempUnidade, TAM_MAX_UNIDADE_MEDIDA, stdin);
        removeQuebraLinhaFinal(tempUnidade);
        receitaAtual->ingredientes[p].unidade = (char*)malloc(sizeof(char) * strlen(tempUnidade) + CHAR_FINALIZADOR_STRING);
        strcpy(receitaAtual->ingredientes[p].unidade, tempUnidade);

        printf("Digite o nome do ingrediente %i: ", p + 1);
        fgets(tempNomeIng, TAM_MAX_NOME_INGREDIENTE, stdin);
        removeQuebraLinhaFinal(tempNomeIng);
        receitaAtual->ingredientes[p].nomeIngrediente = (char*)malloc(sizeof(char) * strlen(tempNomeIng) + CHAR_FINALIZADOR_STRING);
        strcpy(receitaAtual->ingredientes[p].nomeIngrediente, tempNomeIng);

    }

    printf("Digite o modo de preparo: ");
    fgets(tempModoPreparo, TAM_MAX_MODO_PREPARO, stdin);
    removeQuebraLinhaFinal(tempModoPreparo);
    receitaAtual->modoPreparo = (char*)malloc(sizeof(char) * strlen(tempModoPreparo) + CHAR_FINALIZADOR_STRING);
    strcpy(receitaAtual->modoPreparo, tempModoPreparo);

    (*qntReceitas)++;
}
