#pragma once
#ifndef bdop$util_h__
#define bdop$util_h__

#define TAM_MAX_MODO_PREPARO     10000
#define TAM_MAX_NOME_INGREDIENTE 500
#define TAM_MAX_NOME_RECEITA     500
#define TAM_MAX_UNIDADE_MEDIDA   100
#define CHAR_FINALIZADOR_STRING  1
#define SUCESSO                  0

typedef struct ingrediente_s {
    char* nomeIngrediente;
    int quantidade;
    char* unidade;

}ingrediente_t;

typedef struct receita_s {
    ingrediente_t* ingredientes;
    int QNT_INGREDIENTES;
    char* nomeReceita;
    char* modoPreparo;

}receita_t;

void removeQuebraLinhaFinal(char dados[]);
void inicializaStructReceita(receita_t* receitas);
void inicializaStructIngrediente(ingrediente_t* ingredienteAtual);

#endif