#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>

// definicoes de bibliotecas

#include "perfis.h"
#include "ascii_img.h"
#include "produtos.h"
#include "avaliacoes.h"
#include "arquivos.h"
#include "util.h"
#include "favoritos.h"

int main(int argc, char** argv) {
    bool ordenacoes[QNT_POSSIBILIDADES_ORDENACOES] = { false, true, false };
    dados_t* perfilLogado = NULL;
    dados_t* perfis = NULL;
    FILE* arqDados = NULL;
    bool produtosComprados;
    bool logado = false;
    int atual = 0;
    int opcao2;
    int opcao;

    arqDados = fopen(STRUCTS, "rb");
    if (arqDados != NULL) {
        lerDados(arqDados, &perfis, &atual);
        fclose(arqDados);
    }
    if (perfis == NULL) {
        perfis = (dados_t*)malloc(sizeof(dados_t));
    }

    do {
        system("cls || clear"); /*pra limpar o terminal*/
        (logado) ? printf("Bem Vindo, %s!\n", perfilLogado->nome) : (void)0 /* pass */;
        Menu(0, NULL, logado);
        (void)scanf("%d%*c", &opcao);
        switch (opcao) {
        case 1:
            do {
                Menu(1, NULL, logado);
                (void)scanf("%d%*c", &opcao2);
                switch (opcao2) {
                case 1:
                    perfis = Login(&perfis, &logado, &atual, &perfilLogado);
                    break;
                case 2:
                    if (atual == 0) {
                        fprintf(stderr, "Nenhum perfil foi cadastrado!\n");
                    }
                    else if (perfis == NULL) {
                        fprintf(stderr, "Falha no malloc! Perfis nao alocados\n");
                    }
                    else {
                        system("cls || clear");
                        imprimirPerfis(perfis, atual, ordenacoes, &perfilLogado);
                    }

                    break;
                case 3:
                    if (atual == 0) {
                        fprintf(stderr, "Nenhum perfil foi cadastrado!\n");
                    }
                    else {
                        printf("Perfis disponiveis:\n");
                        imprimirPerfis(perfis, atual, ordenacoes, &perfilLogado);
                        printf("\n\n");
                        buscarPerfis(perfis, atual, ordenacoes);
                    }
                    break;
                case 4:
                    if (atual == 0) {
                        fprintf(stderr, "Nenhum perfil foi cadastrado!\n");
                    }
                    else {
                        printf("Perfis disponiveis:\n");
                        imprimirPerfis(perfis, atual, ordenacoes, &perfilLogado);
                        printf("\n\n");
                        visitarPerfis(perfis, atual, perfilLogado);
                    }
                    break;
                case 0:
                    break;
                default:
                    fprintf(stderr, "Opcao invalida!\n");
                }
            } while (opcao2 != 0);
            break;
        case 2:
            do {
                Menu(2, NULL, logado);
                (void)scanf("%d%*c", &opcao2);
                switch (opcao2) {
                case 1:
                    if (perfilLogado == NULL) {
                        fprintf(stderr, "Voce precisa estar logado antes de cadastrar um produto!\n");
                        break;
                    }
                    cadastroProdutos(perfis, atual, perfilLogado);
                    break;

                case 2:
                    if ((utilVerificaExistemProdutos(perfis, atual))) {
                        system("cls || clear");
                        listarProdutos(perfis, atual, perfilLogado);
                    }
                    else {
                        fprintf(stderr, "Nao ha produtos cadastrados!\n");
                    }
                    break;
                case 3:
                    editarProduto(&perfilLogado);
                    break;
                case 4:
                    apagarProduto(&perfilLogado);
                case 0:
                    break;
                default:
                    fprintf(stderr, "Opcao invalida!\n");
                }
            } while (opcao2 != 0);
            break;
        case 3:
            do {
                Menu(3, NULL, logado);
                (void)scanf("%d%*c", &opcao2);
                switch (opcao2) {
                case 1:
                    produtosComprados = listarProdutosComprados(perfilLogado);
                    produtosComprados ? avaliarProduto(perfis, perfilLogado, atual) : (void)0;
                    break;
                case 2:
                    listarAvaliacoes(perfis, atual, true);
                    break;
                case 3:
                    apagarAvaliacao(perfis, perfilLogado, atual);
                    break;
                case 0:
                    break;
                default:
                    fprintf(stderr, "Opcao invalida!\n");
                }
            } while (opcao2 != 0);
            break;
        case 4:
            do {
                Menu(4, NULL, logado);
                (void)scanf("%d%*c", &opcao2);
                switch (opcao2) {
                case 1:
                    if (perfilLogado == NULL) {
                        fprintf(stderr, "Eh preciso estar logado para favoritar produtos!\n");
                        break;
                    }
                    listarProdutos(perfis, atual, perfilLogado);
                    break;
                case 2:
                    desfavoritarProduto(perfis, perfilLogado, atual);
                    break;
                case 3:
                    if (atual == 0) {
                        fprintf(stderr, "Nenhum perfil foi cadastrado!\n");
                    }
                    else {
                        listarFavoritos(perfilLogado);
                    }
                    break;
                case 0:
                    break;
                default:
                    fprintf(stderr, "Opcao invalida!\n");
                }
            } while (opcao2 != 0);
            break;
        case 5:
            do {
                system("cls || clear");
                Menu(5, ordenacoes, logado);
                (void)scanf("%d%*c", &opcao2);
                switch (opcao2) {
                case 1:
                    utilMudaValoresOrdenacao(ordenacoes, opcao2);
                    break;
                case 2:
                    utilMudaValoresOrdenacao(ordenacoes, opcao2);
                    break;
                case 3:
                    utilMudaValoresOrdenacao(ordenacoes, opcao2);
                    break;
                case 4:
                    deletarPerfil(&perfis, &perfilLogado, &logado, &atual);
                    break;
                case 0:
                    break;
                default:
                    fprintf(stderr, "Opcao invalida!\n");
                }
            } while (opcao2 != 0);
            break;
        case 0:
            break;
        default:
            printf("Acao indisponivel.\n");
        }

    } while (opcao != 0);

    if (atual == 0) {
        return SUCESSO;
    }

    arqDados = fopen(STRUCTS, "wb");
    if (arqDados) {
        escreverDados(arqDados, perfis, atual);
        fclose(arqDados);
    }

    // libera memoria
    for (int i = 0; i < atual; i++) {
        for (int j = 0; j < perfis[i].QNT_PRODUTOS; j++) {
            free(perfis[i].produtos[j].ID_produto);
            for (int k = 0; k < perfis[i].produtos[j].QNT_IMAGENS; k++) {
                free(perfis[i].produtos[j].imagem[k]);
            }
            free(perfis[i].produtos[j].imagem);
        }
        free(perfis[i].produtos);
        free(perfis[i].senha);
        free(perfis[i].email);
        free(perfis[i].ID);
    }
    free(perfis);

    return SUCESSO;
}