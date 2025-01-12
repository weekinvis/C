#pragma once
#ifndef bdop$util_h__
#define bdop$util_h__

#include <stdbool.h>
#include <stdint.h>

#define LIMITE_MEMORIA 255

uint8_t* utilEncontraMaioresValores(uint8_t* resultados);

bool utilVerificaErro(uint8_t scan, int qnt, int nFacesDado);
void utilMenuInicial();

#endif // bdop$util_h__