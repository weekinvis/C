#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "util.h"
#include "1.h"
#include "2.h"
#include "3.h"
#include "4.h"


int main(int argc, char* argv[]) {
    receita_t* receitas = NULL;
    FILE* arquivo = NULL;
    int qntReceitas = 0;
    int opcao;

    arquivo = fopen(NOME_ARQUIVO, "rb");

    if (arquivo != NULL) {
        leArquivo(&receitas, &qntReceitas, arquivo);
    }

    do {
        printf("1 - Cadastrar Receita\n"\
               "2 - Imprimir Receitas\n"\
               "3 - Buscar Receita\n"\
               "4 - Sair\n"\
               "Opcao: ");

        (void)scanf("%d%*c", &opcao);

        switch (opcao) {
        case 1:
            cadastrarReceita(&receitas, &qntReceitas);
            break;
        case 2:
            imprimirReceitas(receitas, qntReceitas);
            break;
        case 3:
            buscarReceita(receitas, qntReceitas);
            break;
        case 4:
            break;
        default:
            fprintf(stderr, "Opcao invalida!\n");
            break;
        }


    } while (opcao != 4);

    arquivo = fopen(NOME_ARQUIVO, "wb");

    escreveArquivo(receitas, qntReceitas, arquivo);

    return SUCESSO;
}