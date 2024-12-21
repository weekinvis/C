/* Bibliotecas */
#include "materias.h"
#include <stdbool.h>
#include <stdio.h>
#include "util.h"

/* Constantes */
#define SUCESSO 0

int main(int argc, char* argv[]) {
	materias_t** materias = NULL;
	bool removerArquivo = false;
	int trimestreAtual = 1;
	FILE* arquivo = NULL;
	int opcao;

	arquivo = fopen(NOM_ARQ, "rb");

	materias = alocaPrimeiraDimensaoMaterias();
	alocaSegundaDimensaoMaterias(materias);

	if (arquivo == NULL) {
		inicializaMaterias(materias, trimestreAtual);
	}
	else {
		utilLeArquivoBin(materias, &trimestreAtual, arquivo);
		inicializaMaterias(materias, trimestreAtual);
		fclose(arquivo);
	}

	do {
		printf("\n1 - Inserir Notas\n");
		printf("2 - Imprimir Notas\n");
		printf("3 - Excluir Notas\n");
		printf("4 - Editar\n");
		printf("0 - Sair\n");
		printf("Opcao: ");
		(void)scanf("%d%*c", &opcao);

		switch (opcao) {
		case 1:
			leNotasTrimestreAtual(materias, &trimestreAtual);
			if (!removerArquivo) {
				utilEscreveArquivoBin(materias, trimestreAtual);
			}
			break;
		case 2:
			imprimeNotasTrimestres(materias, trimestreAtual);
			break;
		case 3:
			remove(NOM_ARQ);
			removerArquivo = true;
			break;
		case 4:
			imprimeNotasTrimestres(materias, trimestreAtual);
			editarTrimestre(materias, trimestreAtual);
			break;
		case 0:
			break;
		default:
			fprintf(stderr, "Opcao invalida!\n");
		}

	} while (opcao != 0);



	return SUCESSO;
}
