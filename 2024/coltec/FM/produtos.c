#include "avaliacoes.h"
#include "ascii_img.h"
#include "favoritos.h"
#include "produtos.h"
#include "perfis.h"
#include "util.h"

bool listarProdutos(dados_t* perfis, int atual, dados_t* perfilLogado) {
    char id_produto[TAM_MAX_ID_PRODUTO];
    int detalhar;
    bool produtoExiste = false;
    bool jaComprou = false;

    asciiImg_t* img = NULL;

    for (int k = 0; k < atual; k++) {
        if (perfis[k].QNT_PRODUTOS > 0) {
            printf("\nNOME: %s QUANTIDADE DE PRODUTOS: %d", perfis[k].nome, perfis[k].QNT_PRODUTOS);
            printf("\nProdutos do perfil %s:\n", perfis[k].ID);
            for (int a = 0; a < perfis[k].QNT_PRODUTOS; a++) {
                printf("\nProduto %d:\n", a + 1);
                printf("Nome: %s\n", perfis[k].produtos[a].nome);
                printf("ID do Produto: %s\n", perfis[k].produtos[a].ID_produto);
                if (perfis[k].produtos[a].QNT_IMAGENS == 0) {
                    fprintf(stderr, "Esse produto nao tem imagens!\n");
                }
                else {
                    int b = 0;
                    printf("Imagem: (URL: %s)\n", perfis[k].produtos[a].imagem[b]);
                    remove("ascii_img.txt");
                    img = insta_carregaImagem(perfis[k].produtos[a].imagem[b], IMAGEM_COLORIDA, IMAGEM_NUMERO_COLUNAS);
                    if (img == NULL) {
                        fprintf(stderr, "Nao foi possivel abrir imagem!\n");
                    }
                    else {
                        insta_imprimeImagem(img);
                        insta_liberaImagem(img);
                    }
                }
            }
        }
    }

    do {
        printf("\nDigite 1 para detalhar algum produto ou 0 para sair: ");
        (void)scanf("%d%*c", &detalhar);

        switch (detalhar) {
        case true:
            detalharProduto(perfis, atual, perfilLogado);
            jaComprou = true;
            break;

        case false:
            return jaComprou;

        default:
            printf("Opcao invalida\n");
        }

    } while (detalhar != 0);

    return jaComprou;
}

void comprarProdutoDetalhado(dados_t* perfilLogado, produto_t* produtoAtual) {
    bool produtoJaComprado;
    int quantidadeCompra;

    if (perfilLogado == NULL) {
        fprintf(stderr, "Voce tem que estar logado para comprar produtos!\n");
        return;
    }

    if (produtoAtual->quantidadeDesseProduto <= 0) {
        fprintf(stdout, "Infelizmente nao ha mais desse produto!");
        return;
    }

    printf("Quantidade de produtos disponiveis: %d\n", produtoAtual->quantidadeDesseProduto);
    printf("Digite a quantidade que deseja comprar: ");
    (void)scanf("%d%*c", &quantidadeCompra);

    if (quantidadeCompra > 0 && quantidadeCompra <= produtoAtual->quantidadeDesseProduto) {

        produtoJaComprado = utilVerificaProdutoJaComprado(perfilLogado, produtoAtual->ID_produto);

        if (produtoJaComprado == false) {
            perfilLogado->QNT_PRODUTOS_COMPRADOS++;
            perfilLogado->produtosComprados = (char**)realloc(perfilLogado->produtosComprados, sizeof(char*) * perfilLogado->QNT_PRODUTOS_COMPRADOS);
            perfilLogado->produtosComprados[perfilLogado->QNT_PRODUTOS_COMPRADOS - 1] = (char*)malloc(sizeof(char) * strlen(produtoAtual->ID_produto) + 1);
            strcpy(perfilLogado->produtosComprados[perfilLogado->QNT_PRODUTOS_COMPRADOS - 1], produtoAtual->ID_produto);
        }

        produtoAtual->quantidadeDesseProduto -= quantidadeCompra;
        printf("Compra realizada com sucesso! Voce comprou %d unidade(s) do produto %s\n", quantidadeCompra, produtoAtual->nome);
    }

}

bool listarProdutosComprados(dados_t* perfilLogado) {
    if (perfilLogado == NULL) {
        fprintf(stderr, "Voce precisa estar logado para ver seus produtos comprados!\n");
        return false;
    }

    if (perfilLogado->QNT_PRODUTOS_COMPRADOS == 0) {
        fprintf(stderr, "Voce nao comprou nenhum produto ainda.\n");
        return false;
    }

    printf("Produtos comprados: \n");
    for (int a = 0; a < perfilLogado->QNT_PRODUTOS_COMPRADOS; a++) {
        printf("%d. %s\n", a + 1, perfilLogado->produtosComprados[a]); /* "%d. %s\n" serve para imprimir o numero do produto ex.: "1. produto" */
    }
    return true;
}

void cadastroProdutos(dados_t* perfis, int atual, dados_t* perfilLogado) {
    char tempNomeProd[TAM_MAX_NOME_PRODUTO];
    char tempDesc[TAM_MAX_DESCRICAO];
    char tempLink[TAM_MAX_IMAGEM];
    char id_perfil[TAM_MAX_ID];
    produto_t* produto = NULL;
    bool repeticao;

    strcpy(id_perfil, perfilLogado->ID);

    for (int a = 0; a < atual; a++) {
        if (strcmp(perfis[a].ID, id_perfil) == 0) {
            perfis[a].produtos = (produto_t*)realloc(perfis[a].produtos, sizeof(produto_t) * (perfis[a].QNT_PRODUTOS + 1));
            produto = &perfis[a].produtos[perfis[a].QNT_PRODUTOS];

            perfis[a].produtos[perfis[a].QNT_PRODUTOS].quantidadeDesseProduto = 0;
            perfis[a].produtos[perfis[a].QNT_PRODUTOS].QNT_AVALIACOES = 0;
            perfis[a].produtos[perfis[a].QNT_PRODUTOS].avaliacoes = NULL;
            perfis[a].produtos[perfis[a].QNT_PRODUTOS].QNT_IMAGENS = 0;
            perfis[a].produtos[perfis[a].QNT_PRODUTOS].imagem = NULL;

            printf("Digite o nome do produto: ");
            fgets(tempNomeProd, TAM_MAX_NOME_PRODUTO, stdin);
            utilRemoveQuebraLinhasFinal(tempNomeProd);
            produto->nome = (char*)malloc(sizeof(char) * (strlen(tempNomeProd) + 1));
            strcpy(produto->nome, tempNomeProd);

            produto->ID_produto = utilRetornaIDGeradoProduto(perfilLogado, produto);
            if (produto->ID_produto == NULL) {
                perfis[a].produtos = (produto_t*)realloc(perfis[a].produtos, sizeof(produto_t) * (perfis[a].QNT_PRODUTOS));
                fprintf(stderr, "Falha ao alocar o ID do produto!\n");
                return;
            }
            repeticao = utilVerificaIDProdutoRepetido(perfis, atual, produto->ID_produto);
            if (repeticao) {
                perfis[a].produtos = (produto_t*)realloc(perfis[a].produtos, sizeof(produto_t) * (perfis[a].QNT_PRODUTOS));
                fprintf(stderr, "ID para produto ja utilizado!\n");
                return;
            }

            printf("Digite a descricao do produto: ");
            fgets(tempDesc, TAM_MAX_DESCRICAO, stdin);
            utilRemoveQuebraLinhasFinal(tempDesc);
            produto->descricao = (char*)malloc(sizeof(char) * strlen(tempDesc) + 1);
            strcpy(produto->descricao, tempDesc);

            printf("O ID do seu produto gerado pelo programa: %s\n", produto->ID_produto);

            perfis[a].QNT_PRODUTOS++;

            printf("Digite a quantidade produtos gostaria de adicionar: ");
            (void)scanf("%d%*c", &produto->quantidadeDesseProduto);

            printf("Quantas imagens voce deseja adicionar: ");
            (void)scanf("%d%*c", &produto->QNT_IMAGENS);

            produto->imagem = (char**)malloc(produto->QNT_IMAGENS * sizeof(char*));
            if (produto->imagem == NULL) {
                fprintf(stderr, "Erro ao alocar espaco para o URL da imagem.\n");
                perfis[a].QNT_PRODUTOS--;
                return;
            }

            for (int b = 0; b < produto->QNT_IMAGENS; b++) {
                if (produto->imagem[b] == NULL) {
                    fprintf(stderr, "Erro espaco nao alocado!\n");
                    perfis[a].QNT_PRODUTOS--;
                    return;
                }
                printf("Digite a URL da imagem %d: ", b + 1);
                fgets(tempLink, TAM_MAX_IMAGEM, stdin);
                utilRemoveQuebraLinhasFinal(tempLink);
                produto->imagem[b] = (char*)malloc(sizeof(char) * (strlen(tempLink)) + 1);
                strcpy(produto->imagem[b], tempLink);
                utilRemoveQuebraLinhasFinal(produto->imagem[b]);
            }
            return;
        }
    }
    printf("Esse perfil nao existe\n");
}

void editarProduto(dados_t** perfilLogado) {
    FILE* arqProv = NULL;
    char dados[TAM_MAX_IMAGEM + 1]; // aloca o maior espaco que se pode alterarla
    asciiImg_t* img = NULL;
    int novaQntProdutos;
    int novaQntImagens;
    int indice;
    int opcao;

    if (*perfilLogado == NULL) {
        fprintf(stderr, "Voce precisa estar logado numa conta para modificar os produtos desta.\n");
        return;
    }
    if ((*perfilLogado)->QNT_PRODUTOS == 0) {
        fprintf(stderr, "Voce nao tem produtos cadastrados!\n");
        return;
    }

    printf("Ola, %s. Esses sao os produtos que voce pode modificar:\n", (*perfilLogado)->nome);
    printf("Produtos disponiveis:\n");
    for (int p = 0; p < (*perfilLogado)->QNT_PRODUTOS; p++) {
        printf("\nProduto %d:\n", p + 1);
        printf("Nome: %s\n", (*perfilLogado)->produtos[p].nome);
        ((*perfilLogado)->produtos[p].QNT_IMAGENS == 0) ? printf("Esse produto nao tem imagens!\n") : printf("2 - Imagens:\n");
        for (int q = 0; q < (*perfilLogado)->produtos[p].QNT_IMAGENS; q++) {
            img = insta_carregaImagem((*perfilLogado)->produtos[p].imagem[q], IMAGEM_COLORIDA, IMAGEM_NUMERO_COLUNAS);
            printf("Imagem %d (URL: %s):\n", q + 1, (*perfilLogado)->produtos[p].imagem[q]);
            insta_imprimeImagem(img);
            insta_liberaImagem(img);
        }
        printf("Descricao: %s\n", (*perfilLogado)->produtos[p].descricao);
        printf("Estoque: %d\n", (*perfilLogado)->produtos[p].quantidadeDesseProduto);
        printf("\n");
    }
    printf("Escolha o produto {digite 1 para o produto 1, 2 para o produto 2...} (Digite 0 para sair): ");
    (void)scanf("%d%*c", &indice);
    if (indice > (*perfilLogado)->QNT_PRODUTOS || 0 > indice) {
        fprintf(stderr, "Erro. Voce nao tem esse produto!\n");
        return;
    }
    if (indice == 0) {
        return;
    }
    indice--; // para encontrar o elemento correto do array

    printf("1 - Nome: %s (editar)\n2 - Imagens (editar)\n3 - Descricao: %s (editar)\n4 - Estoque: %d (editar)\n", (*perfilLogado)->produtos[indice].nome, (*perfilLogado)->produtos[indice].descricao, (*perfilLogado)->produtos[indice].quantidadeDesseProduto);
    printf("Insira o numero correspondente ao item que deseja editar: ");
    (void)scanf("%d%*c", &opcao);

    switch (opcao) {
    case 1:
        printf("Digite o novo nome do produto: ");
        fgets(dados, TAM_MAX_NOME_PRODUTO, stdin);

        if (strlen(dados) >= TAM_MAX_NOME_PRODUTO) {
            fprintf(stderr, "Tamanho de nome do produto muito grande!\n");
            fflush(stdin);
            return;
        }

        utilRemoveQuebraLinhasFinal(dados);
        strcpy((*perfilLogado)->produtos[indice].nome, dados);
        break;
    case 2:
        printf("Digite a nova quantidade de imagens: ");
        (void)scanf("%d%*c", &novaQntImagens);

        for (int p = 0; p < (*perfilLogado)->produtos[indice].QNT_IMAGENS; p++) {
            free((*perfilLogado)->produtos[indice].imagem[p]); // desaloca todas as imagens anteriores para evitar memory leak
        }
        free((*perfilLogado)->produtos[indice].imagem); // desaloca tudo relacionado a imagem para evitar memory leak

        (*perfilLogado)->produtos[indice].QNT_IMAGENS = novaQntImagens; // aloca as imagens
        (*perfilLogado)->produtos[indice].imagem = (char**)malloc(sizeof(char*) * novaQntImagens); // aloca a quantidade de imagens

        (novaQntImagens == 0) ? printf("") : printf("Digite os URLS das novas imagens.\n");
        for (int p = 0; p < novaQntImagens; p++) {
            printf("Digite o URL da imagem %i: ", p + 1); // roses are red, violets are blue and I want drummond :) 
            fgets(dados, TAM_MAX_IMAGEM, stdin);

            if (strlen(dados) >= TAM_MAX_IMAGEM) {
                fprintf(stderr, "URL muito grande\n");
                fflush(stdin);
                return;
            }

            utilRemoveQuebraLinhasFinal(dados);
            (*perfilLogado)->produtos[indice].imagem[p] = (char*)malloc(sizeof(char) * strlen(dados) + 1);
            strcpy((*perfilLogado)->produtos[indice].imagem[p], dados);
        }
        break;
    case 3:
        printf("Digite a nova descricao do produto: ");
        fgets(dados, TAM_MAX_DESCRICAO + 1, stdin);

        if (strlen(dados) >= TAM_MAX_DESCRICAO) {
            fprintf(stderr, "Tamanho de nome do produto muito grande!\n");
            fflush(stdin);
            return;
        }

        utilRemoveQuebraLinhasFinal(dados);
        strcpy((*perfilLogado)->produtos[indice].descricao, dados);
        break;
    case 4:
        printf("Quantidade atual de produtos: %i\n", (*perfilLogado)->produtos[indice].quantidadeDesseProduto);
        printf("Digite a nova quantidade de produtos: ");
        (void)scanf("%d%*c", &novaQntProdutos);
        (*perfilLogado)->produtos[indice].quantidadeDesseProduto = novaQntProdutos;
        break;
    default:
        fprintf(stderr, "Opcao invalida!\n");
    }

    return;
}

void apagarProduto(dados_t** perfilLogado) {
    int indice;
    asciiImg_t* img = NULL;

    if (*perfilLogado == NULL) {
        fprintf(stderr, "Voce precisa estar logado numa conta para modificar os produtos desta.\n");
        return;
    }
    if ((*perfilLogado)->QNT_PRODUTOS == 0) {
        fprintf(stderr, "Voce nao tem produtos cadastrados!\n");
        return;
    }

    printf("Ola, %s. Esses sao os produtos que voce pode apagar:\n", (*perfilLogado)->nome);
    printf("Lembre-se, essa eh uma acao irreversivel!\n");
    printf("Produtos disponiveis:\n");
    for (int p = 0; p < (*perfilLogado)->QNT_PRODUTOS; p++) {
        printf("\nProduto %i:\n", p + 1);
        printf("1 - Nome: %s\n", (*perfilLogado)->produtos[p].nome);
        ((*perfilLogado)->produtos[p].QNT_IMAGENS == 0) ? printf("Esse produto nao tem imagens!\n") : printf("2 - Imagens:\n");
        for (int q = 0; q < (*perfilLogado)->produtos[p].QNT_IMAGENS; q++) {
            img = insta_carregaImagem((*perfilLogado)->produtos[p].imagem[q], IMAGEM_COLORIDA, IMAGEM_NUMERO_COLUNAS);
            printf("Imagem %i (URL: %s):\n", q + 1, (*perfilLogado)->produtos[p].imagem[q]);
            insta_imprimeImagem(img);
            insta_liberaImagem(img);
        }
        printf("3 - Descricao: %s\n", (*perfilLogado)->produtos[p].descricao);
        printf("4 - Estoque: %i\n", (*perfilLogado)->produtos[p].quantidadeDesseProduto);
        printf("\n");
    }
    printf("Escolha o produto {digite 1 para o produto 1, 2 para o produto 2...} (Digite 0 para sair): ");
    (void)scanf("%d%*c", &indice);
    if (indice > (*perfilLogado)->QNT_PRODUTOS || 0 > indice) {
        fprintf(stderr, "Erro. Voce nao tem esse produto!\n");
        return;
    }
    if (indice == 0) {
        return;
    }
    indice--; // para encontrar o elemento correto do array

    // essa parte vai, efetivamente, excluir o produto
    (*perfilLogado)->QNT_PRODUTOS--;
    (*perfilLogado)->produtos[indice] = (*perfilLogado)->produtos[(*perfilLogado)->QNT_PRODUTOS]; // troca o produto que vai ser apagado pelo ultimo.
    (*perfilLogado)->produtos = (produto_t*)realloc((*perfilLogado)->produtos, sizeof(produto_t) * (*perfilLogado)->QNT_PRODUTOS); // realoca de modo a excluir o ultimo produto.
    return;
}

void detalharProduto(dados_t* perfis, int atual, dados_t* perfilLogado) {
    asciiImg_t* img;
    char id_produto[TAM_MAX_ID];
    bool produtoExiste = false;
    int opcao;

    printf("Digite o id do produto: ");
    fgets(id_produto, TAM_MAX_ID, stdin);
    utilRemoveQuebraLinhasFinal(id_produto);
    for (int k = 0; k < atual; k++) {
        for (int y = 0; y < perfis[k].QNT_PRODUTOS; y++) {
            if (strcmp(perfis[k].produtos[y].ID_produto, id_produto) == 0) {
                produtoExiste = true;
            }
        }
    }

    if (!produtoExiste) {
        fprintf(stderr, "Esse produto nao existe!\n");
        return;
    }

    bool produtoNaoAchado = true;
    int s = 0, t = 0;

    while (perfis[t].produtos == NULL) {
        t++;
        if (t == atual) {
            fprintf(stderr, "Nenhum perfil tem produtos!\n");
        }
    }

    for (t; t < (atual); t++) {
        for (s = 0; s < perfis[t].QNT_PRODUTOS; s++) {
            while ((perfis[t].produtos == NULL) && (produtoNaoAchado)) {
                t++;
                if (t == atual) {
                    fprintf(stderr, "Todos os produtos foram imprimidos!\n");
                }
            }
            if (s == perfis[t].QNT_PRODUTOS) {
                fprintf(stderr, "Produto nao encontrado\n");
            }
            if (strcmp(perfis[t].produtos[s].ID_produto, id_produto) == 0) {
                printf("\nProduto do perfil %s:\n", perfis[t].ID);
                printf("Nome: %s\n", perfis[t].produtos[s].nome);
                printf("Descricao: %s\n", perfis[t].produtos[s].descricao);
                printf("ID do Produto: %s\n", perfis[t].produtos[s].ID_produto);

                if (perfis[t].produtos[s].QNT_IMAGENS == 0) {
                    printf("Esse produto nao tem imagens!\n");
                }
                else {
                    printf("Imagens:\n");
                    for (int i = 0; i < perfis[t].produtos[s].QNT_IMAGENS; i++) {
                        printf("Imagem %d:\n", i + 1);
                        img = insta_carregaImagem(perfis[t].produtos[s].imagem[i], IMAGEM_COLORIDA, IMAGEM_NUMERO_COLUNAS);
                        if (img == NULL) {
                            fprintf(stderr, "Nao foi possivel abrir imagem!\n");
                        }
                        else {
                            insta_imprimeImagem(img);
                            insta_liberaImagem(img);
                        }

                    }
                }
                listarAvaliacoes(&perfis[t], atual, false);

                printf("\nMenu:\n1 - Comprar esse produto\n2 - Favoritar/Desfavoritar esse produto\n0 - Retornar\nOpcao: ");
                (void)scanf("%d%*c", &opcao);

                switch (opcao) {
                case 1:
                    comprarProdutoDetalhado(perfilLogado, &perfis[t].produtos[s]);
                    break;
                case 2:
                    favoritarProdutoDetalhado(perfilLogado, &perfis[t].produtos[s]);
                    break;
                case 0:
                    break;
                default:
                    fprintf(stderr, "Opcao invalida!\n");
                }

                return;

            }
        }
    }
}