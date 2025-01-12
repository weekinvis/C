#include "favoritos.h"
#include <stdio.h>
#include "util.h"
#include <stdlib.h>
#include <string.h>

void desfavoritarProduto(dados_t* perfis, dados_t* perfilLogado, int atual) {
    char id_produto[TAM_MAX_ID_PRODUTO];
    char id_perfil[TAM_MAX_ID];

    if (perfilLogado == NULL) {
        fprintf(stderr, "Voce precisa estar logado para desfavoritar produtos!\n");
        return;
    }
    else {
        strcpy(id_perfil, perfilLogado->ID);
    }

    printf("Digite o ID do produto a ser removido dos favoritos: ");
    fgets(id_produto, TAM_MAX_ID_PRODUTO, stdin);

    if (strlen(id_produto) >= TAM_MAX_ID_PRODUTO) {
        fprintf(stderr, "ID produto grande de mais!\n");
        fflush(stdin);
        return;
    }

    utilRemoveQuebraLinhasFinal(id_produto);

    for (int i = 0; i < atual; i++) {
        if (strcmp(perfis[i].ID, id_perfil) == 0) {
            for (int j = 0; j < perfis[i].QNT_FAVORITOS; j++) {
                if (strcmp(perfis[i].favoritos[j], id_produto) == 0) {
                    for (int k = j; k < perfis[i].QNT_FAVORITOS - 1; k++) {
                        perfis[i].favoritos[k] = perfis[i].favoritos[k + 1];
                    }
                    perfis[i].favoritos = (char**)realloc(perfis[i].favoritos, sizeof(char*) * (perfis[i].QNT_FAVORITOS - 1));
                    perfis[i].QNT_FAVORITOS--;

                    printf("Produto %s removido dos favoritos do perfil %s.\n", id_produto, id_perfil);
                    return;
                }
            }
            printf("Produto nao encontrado nos favoritos.\n");
            return;
        }
    }
    printf("Perfil nao encontrado.\n");
}

void listarFavoritos(dados_t* perfilLogado) {

    if (perfilLogado == NULL) {
        fprintf(stderr, "Voce precisa estar logado para listar os favoritos!\n");
        return;
    }

    if (perfilLogado->QNT_FAVORITOS == 0) {
        printf("Nenhum produto favoritado.\n");
        return;
    }

    printf("Favoritos do perfil %s:\n", perfilLogado->ID);
    for (int a = 0; a < perfilLogado->QNT_FAVORITOS; a++) {
        printf("Produto Favorito %d: ID: %s\n", a + 1, perfilLogado->favoritos[a]);
    }
    return;
}

void favoritarProdutoDetalhado(dados_t* perfilLogado, produto_t* produtoAtual) {
    bool produtoNaoEncontrado = true;
    bool produtoJaFavoritado;
    int indice = -1;

    if (perfilLogado == NULL) {
        fprintf(stderr, "Voce precisa estar logado para favoritar um produto!\n");
        return;
    }

    produtoJaFavoritado = utilVerificaProdutoJaFavoritado(perfilLogado, produtoAtual->ID_produto);

    if (produtoJaFavoritado == false) {

        perfilLogado->QNT_FAVORITOS++;
        perfilLogado->favoritos = (char**)realloc(perfilLogado->favoritos, sizeof(char*) * perfilLogado->QNT_FAVORITOS);
        perfilLogado->favoritos[perfilLogado->QNT_FAVORITOS - 1] = (char*)malloc(sizeof(char) * strlen(produtoAtual->ID_produto) + 1);
        strcpy(perfilLogado->favoritos[perfilLogado->QNT_FAVORITOS - 1], produtoAtual->ID_produto);
        printf("O produto %s adicionado aos favoritos do perfil %s.\n", produtoAtual->ID_produto, perfilLogado->nome);

    }
    else {

        while (produtoNaoEncontrado) {
            indice++;
            if (strcmp(perfilLogado->favoritos[indice], produtoAtual->ID_produto) == 0) {
                produtoNaoEncontrado = false;
            }
            if (indice == perfilLogado->QNT_FAVORITOS + 1) {
                break;
            }
        }

        perfilLogado->QNT_FAVORITOS--;
        perfilLogado->favoritos[indice] = perfilLogado->favoritos[perfilLogado->QNT_FAVORITOS];
        perfilLogado->favoritos = (char**)realloc(perfilLogado->favoritos, sizeof(char*) * perfilLogado->QNT_FAVORITOS);

        printf("Produto %s removido dos favoritos do perfil %s\n", produtoAtual->ID_produto, perfilLogado->nome);

    }

}