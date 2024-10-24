// inclusoes de bibliotecas
#include <stdio.h>
#include <stdlib.h.>
#include <stdbool.h>
#include <string.h>

// bibliotecas personalizadas
#include "grades.h"

int main(int argc, char** argv) {
	grades_t** dadosNotas = NULL;
	FILE* arquivoNotas = NULL;
	int opcao;

	dadosNotas = (grades_t**)malloc(sizeof(grades_t*) * QNT_TRIMESTRES);

	for (int i = 0; i < QNT_TRIMESTRES; i++) {
		dadosNotas[i] = NULL;
	}

	if (dadosNotas == NULL) {
		return ERRO_PTR_NULL;
	}

	verificaArquivo(dadosNotas);

	do {
		printf("Menu:\n"
			"1 - Inserir Dados\n"\
			"2 - Imprimir Dados\n"\
			"3 - Imprimir Intervalos\n"\
			"0 - Sair\n"\
			"Opcao: ");
		(void)scanf("%d%*c", &opcao);

		switch (opcao) {
		case 1:
			preencheDados(dadosNotas, arquivoNotas);
			break;

		case 2:
			imprimeDados(dadosNotas);
			break;

		case 3:
			imprimirIntervalos();
			break;

		case 0:
			break;

		default:
			printf("Opcao invalida!\n");
		}

	} while (opcao != 0);


	return SUCESSO;
}