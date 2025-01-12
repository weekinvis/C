#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "perfis.h"
#include "util.h"

void utilRemoveQuebraLinhasFinal(char dados[]) {
    int tamanho;
    tamanho = strlen(dados);
    if (dados[tamanho - 1] == '\n' && tamanho > 0) {
        dados[tamanho - 1] = '\0';
    }
}

int utilContaArroba(char dados[]) {
    int qntArrobas = 0;
    int tamanho = strlen(dados);
    for (int i = 0; i < tamanho; i++) {
        if (dados[i] == '@') {
            qntArrobas++;
        }
    }
    if (qntArrobas > 1) {
        fprintf(stderr, "Favor digitar um ou nenhum arroba.\n");
        return ERRO_QNT_ARROBAS;
    }
    return qntArrobas;
}

void utilTrocar(dados_t* dados1, dados_t* dados2) {
    dados_t temporario;
    temporario = *dados1;
    *dados1 = *dados2;
    *dados2 = temporario;
}

void utilTracker(dados_t* dados, int indice, dados_t** perfilLogado) { /* fica seguindo a conta do logado*/
    if ((*perfilLogado) == NULL) {
        fprintf(stderr, "Perfil logado NULL!\n");
        return;
    }
    if (strcmp(dados[indice].ID, (*perfilLogado)->ID) == 0) {
        (*perfilLogado) = &dados[indice + 1];
    }
    else {
        *perfilLogado = &dados[indice];
    }
    return;
}
void utilBubbleSort(dados_t* dados, int atual, bool ordenacoes[QNT_POSSIBILIDADES_ORDENACOES], dados_t** perfilLogado) {
    if (ordenacoes[ORDENACAO_POR_ID]) {
        for (int p = 0; p < atual - 1; p++) {
            for (int q = 0; q < atual - p - 1; q++) {
                if (strcmp(dados[q].ID, dados[q + 1].ID) > 0) {
                    // se o perfil estiver logado
                    if (*perfilLogado != NULL) {
                        if ((strcmp(dados[q].ID, (*perfilLogado)->ID) == 0) || (strcmp(dados[q + 1].ID, (*perfilLogado)->ID) == 0)) {
                            // nao ira perder o perfil logado, essa funcao seguira o perfil logado muahahahaha >:)
                            utilTracker(dados, q, perfilLogado);
                        }
                    }
                    utilTrocar(&dados[q], &dados[q + 1]);
                }
            }
        }
    }
    else if (ordenacoes[ORDENACAO_POR_NOME]) {
        for (int p = 0; p < atual - 1; p++) {
            for (int q = 0; q < atual - p - 1; q++) {
                if (strcmp(dados[q].nome, dados[q + 1].nome) > 0) {
                    if (*perfilLogado != NULL) {
                        if ((strcmp(dados[q].nome, (*perfilLogado)->nome) == 0) || (strcmp(dados[q + 1].nome, (*perfilLogado)->nome) == 0)) {
                            utilTracker(dados, q, perfilLogado);
                        }
                    }
                    utilTrocar(&dados[q], &dados[q + 1]);
                }
            }
        }
    }
    else {
        for (int p = 0; p < atual - 1; p++) {
            for (int q = 0; q < atual - p - 1; q++) {
                if (strcmp(dados[q].email, dados[q + 1].email) > 0) {
                    if (*perfilLogado != NULL) {
                        if ((strcmp(dados[q].email, (*perfilLogado)->email) == 0) || (strcmp(dados[q + 1].email, (*perfilLogado)->email) == 0)) {
                            utilTracker(dados, q, perfilLogado);
                        }
                    }
                    utilTrocar(&dados[q], &dados[q + 1]);
                }
            }
        }
    }
}

void utilMudaValoresOrdenacao(bool* valoresOrdenacao, int cod) {
    switch (cod) {
    case 1:
        (valoresOrdenacao)[ORDENACAO_POR_EMAIL] = true;
        (valoresOrdenacao)[ORDENACAO_POR_NOME] = false;
        (valoresOrdenacao)[ORDENACAO_POR_ID] = false;
        break;
    case 2:
        (valoresOrdenacao)[ORDENACAO_POR_EMAIL] = false;
        (valoresOrdenacao)[ORDENACAO_POR_NOME] = true;
        (valoresOrdenacao)[ORDENACAO_POR_ID] = false;
        break;
    case 3:
        (valoresOrdenacao)[ORDENACAO_POR_EMAIL] = false;
        (valoresOrdenacao)[ORDENACAO_POR_NOME] = false;
        (valoresOrdenacao)[ORDENACAO_POR_ID] = true;
    }
}

void Menu(int numMenu, bool ordenacoes[], bool logado) {

    switch (numMenu) {
    case 0:
        printf("\n1 - Perfis\n"\
            "2 - Produtos\n"\
            "3 - Avaliacoes\n"\
            "4 - Favoritos\n"\
            "5 - Configuracoes\n"\
            "0 - Salvar e Sair\n"
            "\nOpcao: ");
        break;

    case 1:
        printf("\n1 - %s\n", (logado) ? "Deslogar" : "Logar");
        printf("2 - Listar perfis\n"\
            "3 - Buscar perfis\n"\
            "4 - Visitar perfis\n"\
            "0 - Voltar\n"
            "\nOpcao: ");
        break;

    case 2:
        printf("\n1 - Cadastrar produto\n"\
            "2 - Listar produtos\n"\
            "3 - Editar produto\n"\
            "4 - Apagar produto\n"\
            "0 - Voltar\n"\
            "\nOpcao: ");
        break;

    case 3:
        printf("\n1 - Avaliar produto\n"\
            "2 - Listar avaliacoes\n"\
            "3 - Apagar avaliacoes\n"\
            "0 - Voltar\n"
            "\nOpcao: ");
        break;

    case 4:
        printf("\n1 - Favoritar produto\n"\
            "2 - Desfavoritar produto\n"\
            "3 - Listar favoritos\n"\
            "0 - Voltar\n"
            "\nOpcao: ");
        break;

    case 5:
        printf("1 - Listagem por email: %s\n", ordenacoes[ORDENACAO_POR_EMAIL] ? "Ativado" : "Desativado");
        printf("2 - Listagem por nome:  %s\n", ordenacoes[ORDENACAO_POR_NOME] ? "Ativado" : "Desativado");
        printf("3 - Listagem por ID:    %s\n", ordenacoes[ORDENACAO_POR_ID] ? "Ativado" : "Desativado");
        printf("4 - Deletar Conta\n");
        printf("0 - Voltar\n");
        printf("\nOpcao: ");
    }
}

int utilVerificaIDeEmailExistente(int qntCadastros, dados_t* todosDados, char* novoEmail, char* novoID) {
    for (int i = 0; i < qntCadastros; i++) {
        if (strcmp(todosDados[i].email, novoEmail) == 0) {
            return ERRO_ID_EMAIL_JA_EXISTENTE;
        }
        if (strcmp(todosDados[i].ID, novoID) == 0) {
            return ERRO_ID_EMAIL_JA_EXISTENTE;
        }
    }
    return SUCESSO;
}

int utilVerificaIDExistente(int qntCadastros, dados_t* todosDados, char* novoID) {
    for (int i = 0; i < qntCadastros; i++) {
        if (strcmp(todosDados[i].ID, novoID) == 0) {
            return i;
        }
    }
    return ERRO_ID_NAO_ACHADO;
}

int utilVerificaEmailExistente(int qntCadastros, dados_t* todosDados, char* novoEmail) {
    for (int i = 0; i < qntCadastros; i++) {
        if (strcmp(todosDados[i].email, novoEmail) == 0) {
            return i;
        }
    }
    return ERRO_EMAIL_NAO_ACHADO;
}

bool utilVerificaExistemProdutos(dados_t* perfis, int atual) {

    for (int i = 0; i < atual; i++) {
        if (perfis[i].QNT_PRODUTOS != 0) {
            return true;
        }
    }
    return false;
}

bool utilVerificaIDProdutoRepetido(dados_t* perfis, int atual, char idNovoProduto[]) {

    for (int i = 0; i < atual; i++) {
        for (int j = 0; j < perfis[i].QNT_PRODUTOS; j++) {
            if (strcmp(perfis[i].produtos[j].ID_produto, idNovoProduto) == 0) {
                return true;
            }
        }
    }
    return false;
}

int utilEncontraIndicePerfilLogado(dados_t* perfis, char IDPerfilEncontrar[]) {
    bool perfilNaoAchado = true;
    int p = 0;

    while (perfilNaoAchado) {
        if (strcmp(IDPerfilEncontrar, perfis[p].ID) == 0) {
            perfilNaoAchado = false;
            break;
        }
        p++;
    }

    return p;
}

char* utilRetornaIDGeradoProduto(dados_t* perfilLogado, produto_t* produto) {
    char tempidgerado[TAM_MAX_ID_PRODUTO];
    char* idgerado = NULL;
    int p = 0, q = 0;

    while (p < strlen(perfilLogado->ID)) {
        if (perfilLogado->ID[p] != ' ') {
            tempidgerado[q] = (perfilLogado->ID[q]); /*transforma os caracteres de uma string em minusculos*/
            q++;
        }
        p++;
    }
    p = 0;

    while (p < strlen(produto->nome)) {
        if ((produto->nome[p] != ' ') && (q < TAM_MAX_ID_PRODUTO - 1)) { /*remove espaços*/
            tempidgerado[q] = toupper(produto->nome[p]); /*transforma os caracteres de uma string em maiusculos*/
            q++;
        }
        p++;
    }
    tempidgerado[q] = '\0';


    idgerado = (char*)malloc(sizeof(char) * (q + 1));
    strcpy(idgerado, tempidgerado);

    return idgerado;

}

char* utilRetornaIDGeradoAvaliacao(dados_t* perfilLogado, produto_t* produto) {
    char tempidgerado[TAM_MAX_ID_PRODUTO];
    char* idgerado = NULL;
    int p = 0, q = 0;

    while (p < strlen(perfilLogado->ID)) {
        if (perfilLogado->ID[p] != ' ') {
            tempidgerado[q] = tolower(perfilLogado->ID[q]); /*transforma os caracteres de uma string em minusculos*/
            q++;
        }
        p++;
    }
    p = 0;

    while (p < strlen(produto->nome)) {
        if ((produto->nome[p] != ' ') && (q < TAM_MAX_ID_PRODUTO - 1)) { /*remove espaços*/
            tempidgerado[q] = toupper(produto->nome[p]); /*transforma os caracteres de uma string em maiusculos*/
            q++;
        }
        p++;
    }
    tempidgerado[q] = '\0';

    idgerado = (char*)malloc(sizeof(char) * (q + 1));
    strcpy(idgerado, tempidgerado);

    return idgerado;
}

bool utilVerificaProdutoJaComprado(dados_t* perfilAtual, char* ID_Produto) {
    for (int p = 0; p < perfilAtual->QNT_PRODUTOS_COMPRADOS; p++) {
        if (strcmp(perfilAtual->produtosComprados[p], ID_Produto) == 0) {
            return true;
        }
    }
    return false;
}

bool utilVerificaProdutoJaFavoritado(dados_t* perfilAtual, char* ID_Produto) {
    for (int p = 0; p < perfilAtual->QNT_FAVORITOS; p++) {
        if (strcmp(perfilAtual->favoritos[p], ID_Produto) == 0) {
            return true;
        }
    }
    return false;
}