#include <string.h>
#include <stdio.h> // NULL ((void*)0)
#include "util.h"

void removeQuebraLinhaFinal(char dados[]) {
    int tamanho = strlen(dados);

    if (tamanho > 0 && dados[tamanho - 1] == '\n') {
        dados[tamanho - 1] = '\0';
    }

}

void inicializaStructReceita(receita_t* receitas) {
    receitas->QNT_INGREDIENTES = 0;
    receitas->ingredientes = NULL;
    receitas->modoPreparo = NULL;
    receitas->nomeReceita = NULL;
}

void inicializaStructIngrediente(ingrediente_t* ingredienteAtual) {
    ingredienteAtual->nomeIngrediente = NULL;
    ingredienteAtual->quantidade = 0;
    ingredienteAtual->unidade = NULL;

}