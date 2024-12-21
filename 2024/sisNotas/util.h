#pragma once
#ifndef bdop$util_h__
#define bdop$util_h__

#include "materias.h"

void utilSomaValores(materias_t** materias, int trimestreAtual, float total[], int q);
void utilLeArquivoBin(materias_t** materias, int* trimestreAtual, FILE* arquivo);
void imprimeNotasTrimestres(materias_t** materias, int trimestreAtual);
void ordenaNotasTotais(materias_t** materias, int trimestreAtual);
void utilEscreveArquivoBin(materias_t** materias, int trimAtual);
void utilTrocar(materias_t** materias, int q);

#endif // bdop$util_h__
