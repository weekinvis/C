/* Bibliotecas */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/* Constantes */
#define TAM_MAX_NOME_MATERIA 24 + 1
#define QNT_TRIMESTRES 3
#define QNT_MATERIAS 13
#define SUCESSO 0

/* ----- */
#define NOM_ARQ "podbSisNotas.bin"

/* Estruturas */
typedef struct materias_s {
	char* nomeMateria;
	float nota;

}materias_t;

/* --------------- */

static void escreveArquivoBin(materias_t** materias, int trimAtual) {
	FILE* arquivo = NULL;

	arquivo = fopen(NOM_ARQ, "wb");

	fwrite(&trimAtual, sizeof(int), 1, arquivo);
	
	for (int p = 0; p < QNT_MATERIAS; p++) {
		for (int q = 0; q < trimAtual - 1; q++) {
			fwrite(materias[p][q].nomeMateria, sizeof(char), TAM_MAX_NOME_MATERIA, arquivo);
			fwrite(&materias[p][q].nota, sizeof(float), 1, arquivo);
	
		}
	}
	fclose(arquivo);
	return;
}

static void leArquivoBin(materias_t** materias, int* trimestreAtual, FILE* arquivo) {
	char temporario[TAM_MAX_NOME_MATERIA];

	fread(trimestreAtual, sizeof(int), 1, arquivo);

	for (int p = 0; p < QNT_MATERIAS; p++) {
		for (int q = 0; q < (*trimestreAtual) - 1; q++) {
			fread(temporario, sizeof(char), TAM_MAX_NOME_MATERIA, arquivo);
			fread(&materias[p][q].nota, sizeof(float), 1, arquivo);

			temporario[strlen(temporario)] = '\0';
			materias[p][q].nomeMateria = (char*)malloc(sizeof(char) * strlen(temporario) + 1);
			if (materias[p][q].nomeMateria == NULL) {
				exit(-1);
			}
			strcpy(materias[p][q].nomeMateria, temporario);
		}
	}
	return;
}

static void initMaterias(materias_t** materias) {
	for (int p = 0; p < QNT_MATERIAS; p++) {
		for (int q = 0; q < QNT_TRIMESTRES; q++) {
			materias[p][q].nomeMateria = NULL;
			materias[p][q].nota = 0;
		}
	}
}

static inline materias_t** alocaPrimeiraDimensaoMaterias() {
	return (materias_t**)malloc(sizeof(materias_t*) * QNT_MATERIAS);
}

static void alocaSegundaDimensaoMaterias(materias_t** materias) {

	if (materias == NULL) {
		exit(1);
	}

	for (int p = 0; p < QNT_MATERIAS; p++) {
		materias[p] = (materias_t*)malloc(sizeof(materias_t) * QNT_TRIMESTRES);
		if (materias[p] == NULL) {
			fprintf(stderr, "Falha no malloc!");
			exit(1);
		}
	}

	initMaterias(materias);
	return;
}

static void inicializaMaterias(materias_t** materias) {
	const char nomesMaterias[][TAM_MAX_NOME_MATERIA] = { 
		"Biologia", "Matematica", "Lingua Portuguesa",
		"Fisica Aplicada", "Historia", "Algoritmo e Est de Dados",
		"Banco de Dados", "Infr. e Virtualizacao", "Sis. Computacionais",
		"Prog. Orientada a Obj", "ED. Fisica", "Ingles", "Quimica"
	};

	for (int p = 0; p < QNT_MATERIAS; p++) {
		for (int q = 0; q < QNT_TRIMESTRES; q++) {
			materias[p][q].nomeMateria = (char*)malloc(sizeof(char) * (strlen(nomesMaterias[p]) + 1));
			materias[p][q].nota = 0;
			if (materias[p][q].nomeMateria == NULL) {
				exit(1);
			}
			strcpy(materias[p][q].nomeMateria, nomesMaterias[p]);
		}
	}
	return;
}

static void leNotasTrimestreAtual(materias_t** materias, int* trimestreAtual) {

	if (*trimestreAtual >= 4) {
		return;
	}
	
	for (int p = 0; p < QNT_MATERIAS; p++) {
		for (int q = ((*trimestreAtual) - 1); q < (*trimestreAtual); q++) {
			system("cls || clear");
			printf("Digite a nota de %s do %i trimestre: ", materias[p][q].nomeMateria, *trimestreAtual);
			(void)scanf("%f%*c", &materias[p][q].nota);
		}
	}
	(*trimestreAtual)++;
	return;
}

static void utilTrocar(materias_t** materias, int q) {
	materias_t* provisorio;
	provisorio = materias[q + 1];
	materias[q + 1] = materias[q];
	materias[q] = provisorio;

	return;
}

static void utilSomaValores(materias_t** materias, int trimestreAtual ,float total[], int q) {
	total[0] = 0;
	total[1] = 0;
	for (int r = 0; r < trimestreAtual - 1; r++) {
		total[0] += materias[q][r].nota;
		total[1] += materias[q + 1][r].nota;
	}

	return;
}

static void ordenaNotasTotais(materias_t** materias, int trimestreAtual) {
	float total[2];
	for (int p = 0; p < QNT_MATERIAS - 1; p++) {
		for (int q = 0; q < QNT_MATERIAS - 1 - p; q++) {
			utilSomaValores(materias, trimestreAtual, total, q);
			if (total[0] < total[1]) {
				utilTrocar(materias, q);
			}
		}
	}

	return;
}

static void imprimeNotasTrimestres(materias_t** materias, int trimestreAtual) {
	float total;
	system("cls || clear");
	ordenaNotasTotais(materias, trimestreAtual);
	for (int p = 0; p < QNT_MATERIAS; p++) {
		total = 0;
		for (int q = 0; q < trimestreAtual - 1; q++) {
			printf("%-26s: %-5.2f |", materias[p][q].nomeMateria, materias[p][q].nota);
			total += materias[p][q].nota;
		}
		printf(" Total: %.2f", total);
		printf("\n");
	}

	return;
}

/* --------------- */

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
		inicializaMaterias(materias);
	}
	else {
		leArquivoBin(materias, &trimestreAtual, arquivo);
		fclose(arquivo);
	}

	do {
		printf("\n1 - Inserir Notas\n");
		printf("2 - Imprimir Notas\n");
		printf("3 - Excluir Notas\n");
		printf("0 - Sair\n");
		printf("Opcao: ");
		(void)scanf("%d%*c", &opcao);

		switch (opcao) {
		case 1:
			leNotasTrimestreAtual(materias, &trimestreAtual);
			escreveArquivoBin(materias, trimestreAtual);
			break;
		case 2:
			imprimeNotasTrimestres(materias, trimestreAtual);
			break;
		case 3:
			removerArquivo = true;
			printf("Encerre o programa digitando 0 para concluir a exclusao dos dados.\n");
			break;
		case 0:
			break;
		default:
			fprintf(stderr, "Opcao invalida!\n");
		}

	} while (opcao != 0);

	if (removerArquivo) {
		remove(NOM_ARQ);
	}

	return SUCESSO;
}