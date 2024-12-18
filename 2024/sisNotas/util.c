#include "materias.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "util.h"

void utilEscreveArquivoBin(materias_t** materias, int trimAtual) {
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

void utilLeArquivoBin(materias_t** materias, int* trimestreAtual, FILE* arquivo) {
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

void utilTrocar(materias_t** materias, int q) {
	materias_t* provisorio;
	provisorio = materias[q + 1];
	materias[q + 1] = materias[q];
	materias[q] = provisorio;

	return;
}

void utilSomaValores(materias_t** materias, int trimestreAtual, float total[], int q) {
	total[0] = 0;
	total[1] = 0;
	for (int r = 0; r < trimestreAtual - 1; r++) {
		total[0] += materias[q][r].nota;
		total[1] += materias[q + 1][r].nota;
	}

	return;
}

void ordenaNotasTotais(materias_t** materias, int trimestreAtual) {
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

void imprimeNotasTrimestres(materias_t** materias, int trimestreAtual) {
	float total;
	system("cls || clear");
	ordenaNotasTotais(materias, trimestreAtual);
	for (int p = 0; p < QNT_MATERIAS; p++) {
		total = 0;
		for (int q = 0; q < trimestreAtual - 1; q++) {
			printf("%-25s: %-5.2f |", materias[p][q].nomeMateria, materias[p][q].nota);
			total += materias[p][q].nota;
		}
		printf(" Total: %.2f", total);
		printf("\n");
	}

	return;
}