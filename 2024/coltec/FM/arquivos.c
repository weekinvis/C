#include "perfis.h"
#include "arquivos.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void inicializaStruct(dados_t* perfis) {
    perfis->produtosComprados = NULL;
    perfis->favoritos = NULL;
    perfis->produtos = NULL;
    perfis->QNT_PRODUTOS_COMPRADOS = 0;
    perfis->QNT_FAVORITOS = 0;
    perfis->QNT_PRODUTOS = 0;
}

void inicializaProdutos(produto_t* produtoAtual) {
    produtoAtual->QNT_AVALIACOES = 0;
    produtoAtual->avaliacoes = NULL;
    produtoAtual->QNT_IMAGENS = 0;
    produtoAtual->imagem = NULL;
}

void escreverDados(FILE* arq, dados_t* perfis, int atual) {
    fwrite(&atual, sizeof(int), 1, arq);
    for (int p = 0; p < atual; p++) {
        fwrite(perfis[p].nome, sizeof(char), TAM_MAX_NOME, arq);
        fwrite(perfis[p].email, sizeof(char), TAM_MAX_EMAIL, arq);
        fwrite(perfis[p].senha, sizeof(char), TAM_MAX_SENHA, arq);
        fwrite(perfis[p].ID, sizeof(char), TAM_MAX_ID, arq);
        fwrite(&perfis[p].QNT_PRODUTOS, sizeof(int), 1, arq);
        fwrite(&perfis[p].QNT_FAVORITOS, sizeof(int), 1, arq);
        fwrite(&perfis[p].QNT_PRODUTOS_COMPRADOS, sizeof(int), 1, arq);

        for (int q = 0; q < perfis[p].QNT_PRODUTOS; q++) {
            fwrite(perfis[p].produtos[q].nome, sizeof(char), TAM_MAX_NOME_PRODUTO, arq);
            fwrite(perfis[p].produtos[q].descricao, sizeof(char), TAM_MAX_DESCRICAO, arq);
            fwrite(perfis[p].produtos[q].ID_produto, sizeof(char), TAM_MAX_ID_PRODUTO, arq);
            fwrite(&perfis[p].produtos[q].QNT_AVALIACOES, sizeof(int), 1, arq);
            fwrite(&perfis[p].produtos[q].quantidadeDesseProduto, sizeof(int), 1, arq);

            for (int r = 0; r < perfis[p].produtos[q].QNT_AVALIACOES; r++) {
                fwrite(perfis[p].produtos[q].avaliacoes[r].comentario, sizeof(char), TAM_MAX_COMENTARIO, arq);
                fwrite(&perfis[p].produtos[q].avaliacoes[r].nota, sizeof(int), 1, arq);
                fwrite(perfis[p].produtos[q].avaliacoes[r].autor, sizeof(char), TAM_MAX_ID, arq);
                fwrite(perfis[p].produtos[q].avaliacoes[r].ID_avaliacao, sizeof(char), TAM_MAX_ID, arq);
            }
        }
        for (int q = 0; q < perfis[p].QNT_FAVORITOS; q++) {
            fwrite(perfis[p].favoritos[q], sizeof(char), TAM_MAX_ID_PRODUTO, arq);
        }

        for (int q = 0; q < perfis[p].QNT_PRODUTOS; q++) {
            fwrite(&perfis[p].produtos[q].QNT_IMAGENS, sizeof(int), 1, arq);
        }
        for (int q = 0; q < perfis[p].QNT_PRODUTOS; q++) {
            for (int r = 0; r < perfis[p].produtos[q].QNT_IMAGENS; r++) {
                fwrite(perfis[p].produtos[q].imagem[r], sizeof(char), TAM_MAX_IMAGEM, arq);
            }
        }
        for (int q = 0; q < perfis[p].QNT_PRODUTOS_COMPRADOS; q++) {
            fwrite(perfis[p].produtosComprados[q], sizeof(char), TAM_MAX_ID_PRODUTO, arq);
        }
    }
}

void lerDados(FILE* arq, dados_t** perfis, int* atual) {
    char dados[TAM_MAX_IMAGEM + 2];
    fread(atual, sizeof(int), 1, arq);
    *perfis = (dados_t*)malloc(sizeof(dados_t) * (*atual));

    int a = 0;

    for (int p = 0; p < (*atual); p++) {
        inicializaStruct(&(*perfis)[p]);
    }

    for (int p = 0; p < *atual; p++) {
        fread(dados, sizeof(char), TAM_MAX_NOME, arq);
        (*perfis)[p].nome = (char*)malloc(strlen(dados) + 1 * sizeof(char));
        strcpy(((*perfis)[p].nome), dados);
        fread(dados, sizeof(char), TAM_MAX_EMAIL, arq);
        (*perfis)[p].email = (char*)malloc(strlen(dados) + 1 * sizeof(char));
        strcpy(((*perfis)[p].email), dados);
        fread(dados, sizeof(char), TAM_MAX_SENHA, arq);
        (*perfis)[p].senha = (char*)malloc(strlen(dados) + 1 * sizeof(char));
        strcpy(((*perfis)[p].senha), dados);
        fread(dados, sizeof(char), TAM_MAX_ID, arq);
        (*perfis)[p].ID = (char*)malloc(strlen(dados) + 1 * sizeof(char));
        strcpy(((*perfis)[p].ID), dados);

        fread(&(*perfis)[p].QNT_PRODUTOS, sizeof(int), 1, arq);
        fread(&(*perfis)[p].QNT_FAVORITOS, sizeof(int), 1, arq);
        fread(&(*perfis)[p].QNT_PRODUTOS_COMPRADOS, sizeof(int), 1, arq);

        ((*perfis)[p].QNT_PRODUTOS == 0) ? ((*perfis)[p].produtos = NULL) : ((*perfis)[p].produtos = (produto_t*)malloc(sizeof(produto_t) * (*perfis)[p].QNT_PRODUTOS));
        ((*perfis)[p].QNT_FAVORITOS == 0) ? ((*perfis)[p].favoritos = NULL) : ((*perfis)[p].favoritos = (char**)malloc(sizeof(char*) * (*perfis)[p].QNT_FAVORITOS));
        ((*perfis)[p].QNT_PRODUTOS_COMPRADOS == 0) ? ((*perfis)[p].produtosComprados = NULL) : ((*perfis)[p].produtosComprados = (char**)malloc(sizeof(char*) * (*perfis)[p].QNT_PRODUTOS_COMPRADOS));

        for (a = 0; a < (*perfis)[p].QNT_FAVORITOS; a++) {
            (*perfis)[p].favoritos[a] = NULL;
        }

        for (int q = 0; q < (*perfis)[p].QNT_PRODUTOS; q++) {
            fread(dados, sizeof(char), TAM_MAX_NOME_PRODUTO, arq);
            (*perfis)[p].produtos[q].nome = (char*)malloc(sizeof(char) * (strlen(dados) + 1));
            strcpy((*perfis)[p].produtos[q].nome, dados);

            fread(dados, sizeof(char), TAM_MAX_DESCRICAO, arq);
            (*perfis)[p].produtos[q].descricao = (char*)malloc(sizeof(char) * (strlen(dados) + 1));
            strcpy((*perfis)[p].produtos[q].descricao, dados);

            fread(dados, sizeof(char), TAM_MAX_ID_PRODUTO, arq);
            (*perfis)[p].produtos[q].ID_produto = (char*)malloc(sizeof(char) * (strlen(dados) + 1));
            strcpy((*perfis)[p].produtos[q].ID_produto, dados);

            inicializaProdutos(&(*perfis)[p].produtos[q]);
            fread(&(*perfis)[p].produtos[q].QNT_AVALIACOES, sizeof(int), 1, arq);
            if ((*perfis)[p].produtos[q].QNT_AVALIACOES != 0) {
                (*perfis)[p].produtos[q].avaliacoes = (avaliacao_t*)malloc(sizeof(avaliacao_t) * (*perfis)[p].produtos[q].QNT_AVALIACOES);
            }
            else {
                (*perfis)[p].produtos[q].avaliacoes = NULL;
            }
            fread(&(*perfis)[p].produtos[q].quantidadeDesseProduto, sizeof(int), 1, arq);

            for (int r = 0; r < (*perfis)[p].produtos[q].QNT_AVALIACOES; r++) {
                fread(dados, sizeof(char), TAM_MAX_COMENTARIO, arq);
                (*perfis)[p].produtos[q].avaliacoes[r].comentario = (char*)malloc(sizeof(char) * (strlen(dados) + 1));
                strcpy((*perfis)[p].produtos[q].avaliacoes[r].comentario, dados);

                fread(&(*perfis)[p].produtos[q].avaliacoes[r].nota, sizeof(int), 1, arq);

                fread(dados, sizeof(char), TAM_MAX_ID, arq);
                (*perfis)[p].produtos[q].avaliacoes[r].autor = (char*)malloc(sizeof(char) * strlen(dados) + 1);
                strcpy((*perfis)[p].produtos[q].avaliacoes[r].autor, dados);

                fread(dados, sizeof(char), TAM_MAX_ID, arq);
                (*perfis)[p].produtos[q].avaliacoes[r].ID_avaliacao = (char*)malloc(sizeof(char) * strlen(dados) + 1);
                strcpy((*perfis)[p].produtos[q].avaliacoes[r].ID_avaliacao, dados);

            }
        }
        for (int q = 0; q < (*perfis)[p].QNT_FAVORITOS; q++) {
            fread(dados, sizeof(char), TAM_MAX_ID_PRODUTO, arq);
            (*perfis)[p].favoritos[q] = (char*)malloc(sizeof(char) * (strlen(dados) + 1));
            strcpy((*perfis)[p].favoritos[q], dados);
        }

        for (int q = 0; q < (*perfis)[p].QNT_PRODUTOS; q++) {
            fread(&(*perfis)[p].produtos[q].QNT_IMAGENS, sizeof(int), 1, arq);
        }
        for (int q = 0; q < (*perfis)[p].QNT_PRODUTOS; q++) {
            if ((*perfis)[p].produtos[q].QNT_IMAGENS > 0) {
                (*perfis)[p].produtos[q].imagem = (char**)malloc(sizeof(char*) * (*perfis)[p].produtos[q].QNT_IMAGENS);
                for (int r = 0; r < (*perfis)[p].produtos[q].QNT_IMAGENS; r++) {
                    (*perfis)[p].produtos[q].imagem[r] = (char*)malloc(sizeof(char) * TAM_MAX_IMAGEM);
                }
            }
            else {
                (*perfis)[p].produtos[q].imagem = NULL;
            }
            for (int r = 0; r < (*perfis)[p].produtos[q].QNT_IMAGENS; r++) {
                fread((*perfis)[p].produtos[q].imagem[r], sizeof(char), TAM_MAX_IMAGEM, arq);
            }
        }
        for (int q = 0; q < (*perfis)[p].QNT_PRODUTOS_COMPRADOS; q++) {
            fread(dados, sizeof(char), TAM_MAX_ID_PRODUTO, arq);
            (*perfis)[p].produtosComprados[q] = (char*)malloc(sizeof(char) * strlen(dados) + 1);
            strcpy((*perfis)[p].produtosComprados[q], dados);

        }
    }
}