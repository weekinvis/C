#pragma once
#ifndef bdop$avaliacoes_h__
#define bdop$avaliacoes_h__

/* Inclusoes */
#include "perfis.h"
#include <stdbool.h>

/* Constantes */

/* Tipos */

/* Bibliotecas extraidas */

// a palavra extern indica que a funcao vai ser definida em outro lugar

extern void apagarAvaliacao(dados_t* perfis, dados_t* perfilLogado, int atual);
extern void avaliarProduto(dados_t* perfis, dados_t* perfilLogado, int atual);
extern void listarAvaliacoes(dados_t* perfis, int atual, bool chamadaNoMain);

#endif