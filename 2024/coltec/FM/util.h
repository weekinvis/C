#pragma once /* Primeira guarda */
#ifndef bdop$util_h__ /* Segunda guarda */
#define bdop$util_h__

/* Inclusoes */
#include "perfis.h"

/* Constantes */
#define ORDENACAO_POR_ID              2
#define ORDENACAO_POR_NOME            1
#define ORDENACAO_POR_EMAIL           0

#define ERRO_ID_PRODUTO_JA_EXSITENTE -1
#define ERRO_ID_EMAIL_JA_EXISTENTE   -1
#define ERRO_EMAIL_JA_EXISTENTE       1
#define ERRO_EMAIL_NAO_ACHADO        -1
#define ERRO_ID_NAO_ACHADO           -1
#define ERRO_TAMANHO_EMAIL           -1
#define ERRO_QNT_ARROBAS             -1
#define ERRO_NAO_LOGADO              -2
#define SUCESSO                       0
/* Tipos */

/* Funcoes exportadas*/

// a palavra extern indica que a funcao vai ser definida em outro lugar

extern void utilBubbleSort(dados_t* dados, int atual, bool ordenacoes[QNT_POSSIBILIDADES_ORDENACOES], dados_t** perfilLogado);
extern void utilTracker(dados_t* dados, int indice, dados_t** perfilLogado);
extern void utilMudaValoresOrdenacao(bool* valoresOrdenacao, int cod);
extern void Menu(int numMenu, bool ordenacoes[], bool logado);
extern void utilTrocar(dados_t* dados1, dados_t* dados2);
extern void utilRemoveQuebraLinhasFinal(char dados[]);

extern char* utilRetornaIDGeradoAvaliacao(dados_t* perfilLogado, produto_t* produto);
extern char* utilRetornaIDGeradoProduto(dados_t* perfilLogado, produto_t* produto);

extern int utilVerificaIDeEmailExistente(int qntCadastros, dados_t* todosDados, char* novoEmail, char* novoID);
extern int utilVerificaEmailExistente(int qntCadastros, dados_t* todosDados, char* novoEmail);
extern int utilVerificaIDExistente(int qntCadastros, dados_t* todosDados, char* novoID);
extern int utilEncontraIndicePerfilLogado(dados_t* perfis, char IDPerfilEncontrar[]);
extern int utilContaArroba(char dados[]);

extern bool utilVerificaIDProdutoRepetido(dados_t* perfis, int atual, char buffer[]);
extern bool utilVerificaProdutoJaFavoritado(dados_t* perfilAtual, char* ID_Produto);
extern bool utilVerificaProdutoJaComprado(dados_t* perfilAtual, char* ID_Produto);
extern bool utilVerificaExistemProdutos(dados_t* perfis, int atual);

#endif