#include "avaliacoes.h"
#include "perfis.h"
#include "util.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void listarAvaliacoes(dados_t* perfis, int atual, bool chamadaNoMain) {
    char id_produto[TAM_MAX_EMAIL];

    if (atual == 0) {
        fprintf(stderr, "Nao ha perfis criados!\n");
        return;
    }

    if (chamadaNoMain) {
        printf("Digite o ID do produto: ");
        fgets(id_produto, TAM_MAX_EMAIL, stdin);
        utilRemoveQuebraLinhasFinal(id_produto);
        for (int a = 0; a < atual; a++) {
            for (int b = 0; b < perfis[a].QNT_PRODUTOS; b++) {
                if (strcmp(perfis[a].produtos[b].ID_produto, id_produto) == 0) { // encontra o id do produto
                    printf("\nAvaliacoes do produto %s:\n", id_produto);
                    for (int c = 0; c < perfis[a].produtos[b].QNT_AVALIACOES; c++) {
                        printf("\n%s Comentou: \nNota: %d\nComentario: %s\nID da Avaliacao: %s\n", perfis[a].produtos[b].avaliacoes[c].autor, perfis[a].produtos[b].avaliacoes[c].nota, perfis[a].produtos[b].avaliacoes[c].comentario, perfis[a].produtos[b].avaliacoes[c].ID_avaliacao);
                    }
                    return;
                }
            }
        }
        printf("Esse produto nao existe\n");
        return;
    }
    else {
        for (int p = 0; p < perfis->QNT_PRODUTOS; p++) {
            for (int q = 0; q < perfis->produtos[p].QNT_AVALIACOES; q++) {
                printf("\n%s Comentou:\nNota: %d\nAvaliacao: %s\nID da Avaliacao: %s\n", perfis->produtos[p].avaliacoes[q].autor, perfis->produtos[p].avaliacoes[q].nota, perfis->produtos[p].avaliacoes[q].comentario, perfis->produtos[p].avaliacoes[q].ID_avaliacao);
            }
        }
    }
}

void editarAvaliacao(avaliacao_t* avaliacao, dados_t* perfilLogado) {
    char dados[TAM_MAX_COMENTARIO];

    printf("Digite a nova nota: ");
    (void)scanf("%d%*c", &avaliacao->nota);

    printf("Digite o novo comentario: ");
    free(avaliacao->comentario);  // liberra o que tava antes
    fgets(dados, TAM_MAX_COMENTARIO, stdin);
    utilRemoveQuebraLinhasFinal(dados);
    avaliacao->comentario = (char*)malloc(sizeof(char) * strlen(dados) + 1);
    strcpy(avaliacao->comentario, dados);
    return;

}

void extraiIDUsuario(char idAvaliacao[], char radical[]) {
    int p = 0;

    while (islower(idAvaliacao[p]) || isdigit(idAvaliacao[p])) {
        radical[p] = idAvaliacao[p];
        p++;
    }
    radical[p] = '\0';

}

void apagarAvaliacao(dados_t* perfis, dados_t* perfilLogado, int atual) {
    char id_avaliacao[TAM_MAX_ID_AVALIACAO];
    char id_produto[TAM_MAX_ID_PRODUTO];
    char id_Radical[TAM_MAX_ID];
    int indice_perfil = -1, indice_produto = -1, indice_avaliacao = -1;

    if (perfilLogado == NULL) {
        fprintf(stderr, "Voce precisa estar logado para apagar uma avaliacao!\n");
        return;
    }

    printf("Digite o ID do produto cuja avaliacao deseja apagar: ");
    fgets(id_produto, TAM_MAX_ID_PRODUTO, stdin);
    utilRemoveQuebraLinhasFinal(id_produto);

    for (int a = 0; a < atual; a++) {
        for (int b = 0; b < perfis[a].QNT_PRODUTOS; b++) {
            if (strcmp(perfis[a].produtos[b].ID_produto, id_produto) == 0) {
                indice_perfil = a;
                indice_produto = b;
                break;
            }
        }
        if (indice_perfil != -1) break;
    }

    if (indice_perfil == -1 || indice_produto == -1) {
        fprintf(stderr, "Produto nao encontrado.\n");
        return;
    }

    printf("Digite o ID da avaliacao que deseja apagar: ");
    fgets(id_avaliacao, TAM_MAX_ID_AVALIACAO, stdin);
    utilRemoveQuebraLinhasFinal(id_avaliacao);

    extraiIDUsuario(id_avaliacao, id_Radical);

    if (strcmp(perfilLogado->ID, id_Radical) != 0) {
        fprintf(stderr, "Essa avaliacao nao foi feita por voce!\n");
        return;
    }

    for (int c = 0; c < perfis[indice_perfil].produtos[indice_produto].QNT_AVALIACOES; c++) {
        if (strcmp(perfis[indice_perfil].produtos[indice_produto].avaliacoes[c].ID_avaliacao, id_avaliacao) == 0) {
            indice_avaliacao = c;
            break;
        }
    }

    if (indice_avaliacao == -1) {
        fprintf(stderr, "Avaliacao nao encontrada.\n");
        return;
    }

    // Apaga a avaliação
    avaliacao_t* avaliacoes = perfis[indice_perfil].produtos[indice_produto].avaliacoes;
    free(avaliacoes[indice_avaliacao].comentario);
    free(avaliacoes[indice_avaliacao].autor);
    free(avaliacoes[indice_avaliacao].ID_avaliacao);

    perfis[indice_perfil].produtos[indice_produto].QNT_AVALIACOES--;
    if (indice_avaliacao != perfis[indice_perfil].produtos[indice_produto].QNT_AVALIACOES) {
        avaliacoes[indice_avaliacao] = avaliacoes[perfis[indice_perfil].produtos[indice_produto].QNT_AVALIACOES];
    }

    perfis[indice_perfil].produtos[indice_produto].avaliacoes = (avaliacao_t*)realloc(avaliacoes, sizeof(avaliacao_t) * perfis[indice_perfil].produtos[indice_produto].QNT_AVALIACOES);
}

void avaliarProduto(dados_t* perfis, dados_t* perfilLogado, int atual) {
    avaliacao_t* avaliacao = NULL;
    char id_produto[TAM_MAX_ID_PRODUTO];
    char id_perfil[TAM_MAX_ID];
    char tempComentario[TAM_MAX_COMENTARIO];
    bool comprouProduto = false;

    if (perfilLogado != NULL) {

        printf("Digite o ID do produto: ");
        fgets(id_produto, TAM_MAX_ID_PRODUTO, stdin);
        utilRemoveQuebraLinhasFinal(id_produto);

        for (int p = 0; p < perfilLogado->QNT_PRODUTOS_COMPRADOS; p++) {
            if (strcmp(perfilLogado->produtosComprados[p], id_produto) == 0) {
                comprouProduto = true;
            }
        }

        for (int a = 0; a < atual; a++) {
            for (int b = 0; b < perfis[a].QNT_PRODUTOS; b++) {
                if (strcmp(perfis[a].produtos[b].ID_produto, id_produto) == 0) { // identifica qual produto
                    perfis[a].produtos[b].avaliacoes = (avaliacao_t*)realloc(perfis[a].produtos[b].avaliacoes, sizeof(avaliacao_t) * (perfis[a].produtos[b].QNT_AVALIACOES + 1));
                    avaliacao = &perfis[a].produtos[b].avaliacoes[perfis[a].produtos[b].QNT_AVALIACOES];
                    if (avaliacao == NULL) {
                        fprintf(stderr, "Falha no realloc!\n");
                        return;
                    }

                    if (!comprouProduto) {
                        fprintf(stderr, "Voce precisa comprar o produto que voce ira avaliar!\n");
                        return;
                    }

                    for (int c = 0; c < perfis[a].produtos[b].QNT_AVALIACOES; c++) {
                        if (strcmp(perfis[a].produtos[b].avaliacoes[c].autor, perfilLogado->ID) == 0) {
                            editarAvaliacao(&perfis[a].produtos[b].avaliacoes[c], perfilLogado);
                            return;
                        }
                    }

                    perfis[a].produtos[b].QNT_AVALIACOES++;

                    printf("Digite a nota (1 ate 5): ");
                    (void)scanf("%d%*c", &avaliacao->nota);
                    if (avaliacao->nota > 5 || 0 > avaliacao->nota) {
                        fprintf(stderr, "Digite uma nota entre 0 e 5!\n");
                        perfis[a].produtos[b].QNT_AVALIACOES--;
                        return;
                    }

                    printf("Digite seu comentario: ");
                    fgets(tempComentario, TAM_MAX_COMENTARIO, stdin);
                    utilRemoveQuebraLinhasFinal(tempComentario);
                    avaliacao->comentario = (char*)malloc(sizeof(char) * (strlen(tempComentario) + 1));
                    strcpy(avaliacao->comentario, tempComentario);

                    avaliacao->autor = (char*)malloc(sizeof(char) * strlen(perfilLogado->ID) + 1);
                    strcpy(avaliacao->autor, perfilLogado->ID);

                    avaliacao->ID_avaliacao = utilRetornaIDGeradoAvaliacao(perfilLogado, &perfis[a].produtos[b]);
                    printf("ID DA AVALIACAO: %s\n", avaliacao->ID_avaliacao);

                    return;
                }
            }
        }
        printf("Produto nao encontrado.\n");
        return;
    }
    else {
        printf("Voce precisa estar logado para avaliar um produto!\n");
        return;
    }
}
