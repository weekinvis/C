#pragma once
#ifndef bdop$4_h__
#define bdop$4_h__
#include "util.h"
#include <stdio.h>

#define NOME_ARQUIVO "receitas.bin"

void escreveArquivo(receita_t* receitas, int qntReceitas, FILE* arq);
void leArquivo(receita_t** receitas, int* qntReceitas, FILE* arq);

#endif