#pragma once /* Primeira guarda */
#ifndef bdop$arquivos_h__ /* Segunda guarda */
#define bdop$arquivos_h__

/* Inclusoes */
#include <stdio.h>
#include "perfis.h"

/* Constantes */
#define STRUCTS "structs.bin"

// a palavra extern indica que a funcao vai ser definida em outro lugar

extern void escreverDados(FILE* arq, dados_t* perfis, int atual);
extern void lerDados(FILE* arq, dados_t** perfis, int* atual);
extern void inicializaStruct(dados_t* perfis);

#endif