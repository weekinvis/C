#include "materias.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void initMaterias(materias_t** materias) {
	for (int p = 0; p < QNT_MATERIAS; p++) {
		for (int q = 0; q < QNT_TRIMESTRES; q++) {
			materias[p][q].nomeMateria = NULL;
			materias[p][q].nota = 0;
		}
	}
}

materias_t** alocaPrimeiraDimensaoMaterias() {
	return (materias_t**)malloc(sizeof(materias_t*) * QNT_MATERIAS);
}

void alocaSegundaDimensaoMaterias(materias_t** materias) {

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

void inicializaMaterias(materias_t** materias, int trimestreAtual) {
	const char nomesMaterias[][TAM_MAX_NOME_MATERIA] = {
		"Biologia", "Matematica", "Lingua Portuguesa",
		"Fisica", "Madeira", "IP",
		"ESD", "Artes", "Sociologia",
		"Espanhol", "ED. Fisica", "Ingles", "Quimica"
	};

	for (int p = 0; p < QNT_MATERIAS; p++) {
		for (int q = trimestreAtual - 1; q < QNT_TRIMESTRES; q++) {
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

void leNotasTrimestreAtual(materias_t** materias, int* trimestreAtual) {

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

void editarTrimestre(materias_t** materias, int trimestreAtual) {
	int trimestreEditar;
	int materiaEditar;
	printf("Digite qual o trimestre deseja editar: ");
	(void)scanf("%d%*c", &trimestreEditar);

	if(trimestreEditar > (trimestreAtual - 1)) {
		return;
	}

	if(0 >= trimestreEditar || trimestreEditar >= 4) {
		return;
	}

	for(int p = 0; p < QNT_MATERIAS; p++) {
		printf("%-2i - %-25s: %4.1f\n", p + 1, materias[p][trimestreEditar - 1].nomeMateria, materias[p][trimestreEditar - 1].nota);
	}
	printf("Digite o numero relativo a materia que deseja editar: ");
	(void)scanf("%d%*c", &materiaEditar);

	if(0 >= materiaEditar || materiaEditar >= 14) {
		return;
	}
	materiaEditar--;

	printf("Digite a nova nota de %s: ", materias[materiaEditar][trimestreEditar - 1]);
	(void)scanf("%f%*c", &materias[materiaEditar][trimestreEditar - 1].nota);

	system("clear || cls");

	return;

}
