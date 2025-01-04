#pragma once // primeira guarda
#ifndef bdop$favoritos_h__ // segunda guarda
#define bdop$favoritos_h__

/* Inclusoes */
#include "perfis.h"

// a palavra extern indica que a funcao vai ser definida em outro lugar

extern void favoritarProdutoDetalhado(dados_t* perfilLogado, produto_t* produtoAtual);
extern void desfavoritarProduto(dados_t* perfis, dados_t* perfilLogado, int atual);
extern void listarFavoritos(dados_t* perfilLogado);

#endif