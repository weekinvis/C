#pragma once /* Primeira guarda */
#ifndef bdop$perfis_h__ /* Segunda guarda */
#define bdop$perfis_h__

/* Inclusoes */
#include <stdbool.h>

/* Constantes */
#define CARACTERE_NULO 1
#define MARGEM_DE_ERRO 1

#define MRG_DE_ERRO_E_CRCT_NULO (CARACTERE_NULO + MARGEM_DE_ERRO)

#define QNT_POSSIBILIDADES_ORDENACOES 3
#define TAM_MAX_EMAIL                 30 + MARGEM_DE_ERRO + CARACTERE_NULO
#define TAM_MAX_ID_PRODUTO            (TAM_MAX_EMAIL)
#define TAM_MAX_NOME                  (TAM_MAX_EMAIL)
#define TAM_MAX_ID                    (TAM_MAX_EMAIL)
#define TAM_MAX_NOME_PRODUTO          50 + CARACTERE_NULO 
#define TAM_MAX_COMENTARIO            100 + CARACTERE_NULO
#define TAM_MAX_DESCRICAO             500 + CARACTERE_NULO
#define TAM_MAX_IMAGEM                1000 + CARACTERE_NULO // tamanho maximo url
#define TAM_MAX_SENHA                 50 + CARACTERE_NULO
#define TAM_MAX_ID_AVALIACAO          (TAM_MAX_ID)

/* Tipos */

typedef struct avaliacao_s {
    char* ID_avaliacao;
    char* comentario;
    char* autor; // guarda o ID do autor da avaliacao
    int nota;
} avaliacao_t;

typedef struct produto_s {
    int quantidadeDesseProduto;
    avaliacao_t* avaliacoes;
    int QNT_AVALIACOES;
    int QNT_IMAGENS;
    char* ID_produto; // id especifico para cada produto
    char* descricao;
    char** imagem;
    char* nome;
} produto_t;

typedef struct dados_s {
    char* nome;
    produto_t* produtos; // pro listarProdutos
    int QNT_PRODUTOS_COMPRADOS;
    int QNT_FAVORITOS;
    int QNT_PRODUTOS;
    char** produtosComprados; // guarda o ID do produto comprado
    char** favoritos;
    char* email;
    char* senha;
    char* ID;
}dados_t;

/* Funcoes exportadas*/

// a palavra extern indica que a funcao vai ser definida em outro lugar

extern dados_t* Logar(char tempLog[], dados_t* perfil, bool* login, dados_t** perfilLogado);
extern dados_t* Login(dados_t** perfis, bool* login, int* atual, dados_t** perfilLogado);

extern void imprimirPerfis(dados_t* perfis, int atual, bool ordenacoes[QNT_POSSIBILIDADES_ORDENACOES], dados_t** perfilLogado);
extern void buscarPerfis(dados_t* perfis, int atual, bool ordenacoes[QNT_POSSIBILIDADES_ORDENACOES]);
extern void deletarPerfil(dados_t** perfis, dados_t** perfilLogado, bool* logado, int* atual);
extern void visitarPerfis(dados_t* perfis, int atual, dados_t* perfilLogado);

extern int cadastraEmail(char tempEmail[], dados_t* perfil, char tempID[], char tempNome[]);
extern int cadastraID(char tempID[], dados_t* perfil, char tempEmail[], char tempNome[]);
#endif