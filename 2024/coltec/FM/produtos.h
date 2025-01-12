#pragma once
#ifndef bdop$produtos_h__
#define bdop$produtos_h__

/* Inclusoes */
#include "perfis.h"
#include <stdbool.h>

/* Constantes */

/* Tipos */

/* Bibliotecas exportadas */

// a palavra extern indica que a funcao vai ser definida em outro lugar

extern bool listarProdutos(dados_t* perfis, int atual, dados_t* perfilLogado);
extern bool listarProdutosComprados(dados_t* perfilLogado);

extern void cadastroProdutos(dados_t* perfis, int atual, dados_t* perfilLogado);
extern void detalharProduto(dados_t* perfis, int atual, dados_t* perfilLogado);
extern void editarProduto(dados_t** perfilLogado);
extern void apagarProduto(dados_t** perfilLogado);

#endif