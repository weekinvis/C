#include "avaliacoes.h"
#include "ascii_img.h"
#include "produtos.h" /* < para a funcao visitar perfis */
#include "arquivos.h"
#include "perfis.h"
#include "util.h"
#include <string.h>
#include <stdio.h>

void imprimirPerfis(dados_t* perfis, int atual, bool ordenacoes[QNT_POSSIBILIDADES_ORDENACOES], dados_t** perfilLogado) {

    int tamanhoTxt1 = 4, tamanhoTxt2 = 5;

    if (ordenacoes[ORDENACAO_POR_ID] || ordenacoes[ORDENACAO_POR_EMAIL] || ordenacoes[ORDENACAO_POR_NOME]) {
        utilBubbleSort(perfis, atual, ordenacoes, perfilLogado);
    }
    printf("\nPerfil \t");
    printf("Nome");
    for (int j = 0; j < (TAM_MAX_NOME - tamanhoTxt1); j++) {
        printf(" ");
    }
    printf("Email");
    for (int j = 0; j < (TAM_MAX_NOME - tamanhoTxt2); j++) {
        printf(" ");
    }
    printf("ID\n");

    for (int i = 0; i < atual; i++) {
        printf("%4d\t", i + 1); // Numero do perfil
        printf("%-31s\t", perfis[i].nome); // Nome do perfil
        printf("%-31s\t", perfis[i].email); // E-mail do perfil
        printf("%-31s\n", perfis[i].ID); // ID do perfil
    }
}

bool verificarDominio(char tempEmail[]) {

    bool encontrouPontoNoDominio = false;
    bool encontrouArroba = false;
    int tamanho;
    int p = 0;

    tamanho = strlen(tempEmail); // descobre o tamanho do email

    // Percorre o e-mail até encontrar o '@' e garantir que há um domínio após ele
    while (p < tamanho) {
        if (tempEmail[p] == '@') {
            if (tempEmail[p + 1] != '\0') {
                return true;
            }
            else {
                return false;
            }
        }
        p++; // percorre todas as letras de tempEmail
    }

    return false;
}

int cadastraEmail(char tempEmail[], dados_t* perfil, char tempID[], char tempNome[]) {
    char TempSenha[TAM_MAX_SENHA];
    bool dominio;

    perfil->nome = (char*)malloc((strlen(tempNome) + 1) * sizeof(char));
    strcpy(perfil->nome, tempNome);

    perfil->email = (char*)malloc((strlen(tempEmail) + 1) * sizeof(char));
    strcpy(perfil->email, tempEmail);

    perfil->ID = (char*)malloc((strlen(tempID) + 1) * sizeof(char));
    strcpy(perfil->ID, tempID);

    printf("Digite sua senha: ");
    fgets(TempSenha, TAM_MAX_SENHA, stdin);
    utilRemoveQuebraLinhasFinal(TempSenha);

    perfil->senha = (char*)malloc(sizeof(char) * strlen(TempSenha) + 1);
    strcpy(perfil->senha, TempSenha);

    return SUCESSO;

}

int cadastraID(char tempID[], dados_t* perfil, char tempEmail[], char tempNome[]) {
    char tempSenha[TAM_MAX_SENHA];
    int qntArroba;

    perfil->nome = (char*)malloc((strlen(tempNome) + 1) * sizeof(char));
    strcpy(perfil->nome, tempNome);

    perfil->ID = (char*)malloc((strlen(tempID) + 1) * sizeof(char));
    strcpy(perfil->ID, tempID);

    perfil->email = (char*)malloc((strlen(tempEmail) + 1) * sizeof(char));
    strcpy(perfil->email, tempEmail);

    qntArroba = utilContaArroba(perfil->email);
    if (qntArroba != 1) {
        printf("Digite exclusivamente um arroba no email!\n");
        return ERRO_QNT_ARROBAS;
    }

    printf("Digite sua senha: ");
    fgets(tempSenha, TAM_MAX_SENHA, stdin);
    utilRemoveQuebraLinhasFinal(tempSenha);
    perfil->senha = (char*)malloc(((strlen(tempSenha)) + 1) * sizeof(char));
    strcpy(perfil->senha, tempSenha);

    return SUCESSO;
}

void visitarPerfis(dados_t* perfis, int atual, dados_t* perfilLogado) {
    asciiImg_t* img = NULL;
    int qntArroba, detalhar;
    char visita_perfil[TAM_MAX_ID];

    printf("Digite o ID ou e-mail do perfil que deseja visitar: ");
    fgets(visita_perfil, TAM_MAX_ID, stdin);
    utilRemoveQuebraLinhasFinal(visita_perfil);
    qntArroba = utilContaArroba(visita_perfil);

    if (qntArroba == 0) {
        /*pra procurar o id do perfil*/
        for (int a = 0; a < atual; a++) {
            if (strcmp(perfis[a].ID, visita_perfil) == 0) {
                printf("\nID do Perfil: %s\n", perfis[a].ID);
                printf("Nome do Perfil: %s\n", perfis[a].nome);
                printf("E-mail do Perfil: %s\n", perfis[a].email);
                (perfis[a].QNT_PRODUTOS == 0) ? printf("\nEsse perfil nao tem produtos!\n") : printf("\nProdutos disponiveis:\n");

                for (int b = 0; b < perfis[a].QNT_PRODUTOS; b++) {
                    printf("\nID do produto %d: %s\n", (b + 1), perfis[a].produtos[b].ID_produto);
                    printf("Nome do produto: %s\n", perfis[a].produtos[b].nome);

                    if (perfis[a].produtos[b].QNT_IMAGENS > 0) {
                        printf("Imagem:\n");
                        img = insta_carregaImagem(perfis[a].produtos[b].imagem[0], IMAGEM_COLORIDA, IMAGEM_NUMERO_COLUNAS);
                        if (img == NULL) {
                            fprintf(stderr, "Nao foi possivel abrir imagem!\n");
                        }
                        else {
                            insta_imprimeImagem(img);
                            insta_liberaImagem(img);
                        }
                    }
                    else {
                        printf("Esse produto nao possui imagens.\n");
                    }
                    printf("\n");
                }

                if (perfis[a].QNT_PRODUTOS != 0) {
                    do {
                        printf("\nDigite 1 para detalhar algum produto ou 0 para sair: ");
                        (void)scanf("%d%*c", &detalhar);

                        switch (detalhar) {
                        case true:
                            detalharProduto(perfis, atual, perfilLogado);
                            break;

                        case false:
                            return;

                        default:
                            printf("Opcao invalida\n");

                        }
                    } while (detalhar != 0);
                }
                return;
            }
        }
        fprintf(stderr, "Esse perfil nao existe!\n");
        return;
    }
    else if (qntArroba == 1) {
        /*pra procurar o email do perfil*/

        for (int a = 0; a < atual; a++) {
            if (strcmp(perfis[a].email, visita_perfil) == 0) {
                printf("\nID do Perfil: %s\n", perfis[a].ID);
                printf("Nome do Perfil: %s\n", perfis[a].nome);
                printf("E-mail do Perfil: %s\n", perfis[a].email);
                (perfis[a].QNT_PRODUTOS == 0) ? printf("\nEsse perfil nao tem produtos!\n") : printf("\nProdutos disponiveis:\n");

                for (int b = 0; b < perfis[a].QNT_PRODUTOS; b++) {
                    printf("\nID do Produto %d: %s\n", (b + 1), perfis[a].produtos[b].ID_produto);
                    printf("Nome do produto: %s\n", perfis[a].produtos[b].nome);

                    if (perfis[a].produtos[b].QNT_IMAGENS > 0) {
                        printf("Imagem: ");
                        img = insta_carregaImagem(perfis[a].produtos[b].imagem[0], IMAGEM_COLORIDA, IMAGEM_NUMERO_COLUNAS);
                        if (img == NULL) {
                            fprintf(stderr, "Nao foi possivel abrir imagem!\n");
                        }
                        else {
                            insta_imprimeImagem(img);
                            insta_liberaImagem(img);
                        }
                    }
                    else {
                        printf("Esse produto nao possui imagens.\n");
                    }
                    printf("\n");
                }
                return;
            }
        }
        fprintf(stderr, "Esse perfil nao existe!\n");
        return;

    }
    else {
        fprintf(stderr, "Digite algo com 1 ou 0 @'s!\n");
        return;
    }
    fprintf(stderr, "Perfil nao encontrado.\n");
    return;
}

void buscarPerfis(dados_t* perfis, int atual, bool ordenacoes[QNT_POSSIBILIDADES_ORDENACOES]) {
    char pesquisa_perfil[TAM_MAX_ID];
    int i = 1;

    printf("Digite partes do nome, ID ou email que gostaria de buscar: ");
    fgets(pesquisa_perfil, TAM_MAX_ID, stdin);
    utilRemoveQuebraLinhasFinal(pesquisa_perfil);

    for (int p = 0; p < atual; p++) {
        if ((strstr(perfis[p].nome, pesquisa_perfil) != NULL) || (strstr(perfis[p].ID, pesquisa_perfil) != NULL) || (strstr(perfis[p].email, pesquisa_perfil) != NULL)) {
            printf("\nPerfil com correspondencia %d:\n", i);
            printf("ID relativo: %s\n", perfis[p].ID);
            printf("Email relativo: %s\n", perfis[p].email);
            printf("Nome relativo: %s\n", perfis[p].nome);
            i++;
        }
    }
}

dados_t* Logar(char tempLog[], dados_t* perfil, bool* login, dados_t** perfilLogado) {
    char TempSenha[TAM_MAX_SENHA];

    printf("Digite sua senha: ");
    fgets(TempSenha, TAM_MAX_SENHA, stdin);
    utilRemoveQuebraLinhasFinal(TempSenha);
    if (strcmp(perfil->senha, TempSenha) == 0) {
        (*login) = true;
        *perfilLogado = perfil;
        return perfil;
    }
    else {
        printf("Senha incorreta!");
    }

    return NULL;
}

dados_t* Login(dados_t** perfis, bool* login, int* atual, dados_t** perfilLogado) {
    char tempEmail[TAM_MAX_EMAIL];
    char tempNome[TAM_MAX_NOME];
    char tempID[TAM_MAX_ID];
    char dados[TAM_MAX_EMAIL];
    int tempIndice;
    int qntArroba2;
    int qntArroba;

    if ((*login) == false) {
        printf("Digite seu e-mail ou ID (ate %d caracteres): ", (TAM_MAX_ID - MRG_DE_ERRO_E_CRCT_NULO));
        fgets(dados, TAM_MAX_EMAIL, stdin);

        if (strlen(dados) >= TAM_MAX_ID) {
            fflush(stdin);
            fprintf(stderr, "Email ou ID muito grande!\n");
            return *perfis;
        }

        utilRemoveQuebraLinhasFinal(dados);

        qntArroba = utilContaArroba(dados);
        *perfis = (dados_t*)realloc(*perfis, sizeof(dados_t) * ((*atual) + 1));
        inicializaStruct(&(*perfis)[(*atual)]);

        if (qntArroba == 1) {
            strcpy(tempEmail, dados);
            tempIndice = utilVerificaEmailExistente(*atual, *perfis, tempEmail);
            if (tempIndice != ERRO_EMAIL_NAO_ACHADO) {
                Logar(tempEmail, &(*perfis)[tempIndice], login, perfilLogado);
                return *perfis;
            }
            if (false == verificarDominio(tempEmail)) {
                printf("O e-mail precisa conter um dominio. \n");
                return *perfis;
            }
            // Se chegar aqui a conta nao existe e sera criada

            printf("Digite seu nome(ate %d caracteres): ", (TAM_MAX_NOME - MRG_DE_ERRO_E_CRCT_NULO));
            fgets(tempNome, TAM_MAX_NOME, stdin);

            if (strlen(dados) >= TAM_MAX_NOME) {
                fflush(stdin);
                fprintf(stderr, "Nome muito grande!\n");
                return *perfis;
            }

            utilRemoveQuebraLinhasFinal(tempNome);

            printf("Digite seu ID(ate %d caracteres): ", TAM_MAX_ID - MRG_DE_ERRO_E_CRCT_NULO);
            fgets(tempID, TAM_MAX_ID, stdin);
            if (strlen(tempID) >= TAM_MAX_ID) {
                fflush(stdin);
                fprintf(stderr, "ID muito grande!\n");
                return *perfis;
            }
            utilRemoveQuebraLinhasFinal(tempID);
            qntArroba2 = utilContaArroba(tempID);

            if (qntArroba2 != 0) {
                fprintf(stderr, "O ID nao pode conter arroba!\n");
                return *perfis;
            }

            if (utilVerificaIDeEmailExistente(*atual, *perfis, tempEmail, tempID) == ERRO_ID_EMAIL_JA_EXISTENTE) {
                fprintf(stderr, "Erro: Email ou ID ja cadastrado!\n");
                return *perfis;
            }
            cadastraEmail(tempEmail, &(*perfis)[*atual], tempID, tempNome);
            (*atual)++;
            return *perfis;
        }
        else if (qntArroba == 0) {
            strcpy(tempID, dados);
            tempIndice = utilVerificaIDExistente(*atual, *perfis, tempID);
            if (tempIndice != ERRO_ID_NAO_ACHADO) {
                Logar(tempID, &(*perfis)[tempIndice], login, perfilLogado);
                return *perfis;
            }
            // Se chegar aqui a conta nao existe e sera criada
            printf("Digite seu nome(ate %d caracteres): ", (TAM_MAX_NOME - 2));
            fgets(tempNome, TAM_MAX_NOME, stdin);

            if (strlen(tempNome) >= (TAM_MAX_NOME - MRG_DE_ERRO_E_CRCT_NULO)) {
                fprintf(stderr, "Erro nome muito grande!\n");
                fflush(stdin);
                return *perfis;
            }

            utilRemoveQuebraLinhasFinal(tempNome);

            printf("Digite seu Email: ");
            fgets(tempEmail, TAM_MAX_EMAIL, stdin);
            if (strlen(tempEmail) >= TAM_MAX_EMAIL) {
                fflush(stdin);
                fprintf(stderr, "Email muito grande!\n");
                return *perfis;
            }
            utilRemoveQuebraLinhasFinal(tempEmail);

            if (utilVerificaIDeEmailExistente(*atual, *perfis, tempEmail, tempID) == ERRO_ID_EMAIL_JA_EXISTENTE) {
                fprintf(stderr, "Erro: Email ou ID ja cadastrado!\n");
                return *perfis;
            }

            qntArroba = cadastraID(tempID, &(*perfis)[*atual], tempEmail, tempNome);
            if (qntArroba == ERRO_QNT_ARROBAS) {
                return *perfis;
            }
            (*atual)++;
            return *perfis;
        }
        else {
            fprintf(stderr, "Digite 1 arroba para email ou nenhum para ID!\n");
            return *perfis;
        }
    }
    else {
        (*login) = false;
        *perfilLogado = NULL;
        return *perfis;
    }
}

void deletarPerfil(dados_t** perfis, dados_t** perfilLogado, bool* logado, int* atual) {

    bool ordenacoes[QNT_POSSIBILIDADES_ORDENACOES] = { false, true, false };
    int indice;
    char tempSenha[TAM_MAX_SENHA];

    if (*perfilLogado == NULL) {
        fprintf(stderr, "Eh preciso estar logado na conta que sera excluida.\n\n");
        return;
    }

    printf("\nExcluir a conta eh uma acao irreversivel!\nDigite a sua senha para prosseguir: ");
    fgets(tempSenha, TAM_MAX_SENHA, stdin);

    if (strlen(tempSenha) >= TAM_MAX_SENHA) {
        fprintf(stderr, "Senha muito grande!\n");
        fflush(stdin);
        return;
    }

    utilRemoveQuebraLinhasFinal(tempSenha);

    if (!(strcmp(tempSenha, (*perfilLogado)->senha) == 0)) {
        fprintf(stderr, "Senha incorreta!\n");
        return;
    }

    printf("Digite novamente a senha: ");
    fgets(tempSenha, TAM_MAX_SENHA, stdin);
    utilRemoveQuebraLinhasFinal(tempSenha);

    if (!(strcmp(tempSenha, (*perfilLogado)->senha) == 0)) {
        fprintf(stderr, "Senha incorreta!\n");
        return;
    }

    printf("\nExcluindo conta...\n");

    indice = utilEncontraIndicePerfilLogado(*perfis, (*perfilLogado)->ID);

    utilTrocar(&(*perfis)[indice], &(*perfis)[(*atual) - 1]);

    *logado = false;
    *perfilLogado = NULL;
    (*atual)--;
    *perfis = (dados_t*)realloc(*perfis, sizeof(dados_t) * (*atual));

    utilBubbleSort(*perfis, *atual, ordenacoes, perfilLogado);

    printf("Conta excluida com sucesso!\n\n");

    return;
}