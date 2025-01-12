#pragma once
#ifndef bdop$dados_h__
#define bdop$dados_h__

#include <stdint.h>
#include <stdio.h>

void imprimeResultadosDados(uint8_t* resultados);
void liberaResultadosDados(uint8_t* resultados);

uint8_t* girarDados(int qnt, int nFacesDado);
uint8_t leDados(int* qnt, int* nFacesDado);
uint8_t geraNumeroDado(int nFacesDado);


#endif // bdop$dados_h__