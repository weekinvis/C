#pragma once // primeria guarda
#ifndef bdop$materias_h__ // segunda guarda
#define bdop$materias_h__

/* Bibliotecas */

/* Constantes */

/* ----- */
#define NOM_ARQ "podbSisNotas.bin"
/* ----- */

#define TAM_MAX_NOME_MATERIA 24 + 1
#define QNT_TRIMESTRES 3
#define QNT_MATERIAS 13

/* Estruturas */
typedef struct materias_s {
	char* nomeMateria;
	float nota;

}materias_t;

/* Funcoes Exportadas*/

void leNotasTrimestreAtual(materias_t** materias, int* trimestreAtual);
void inicializaMaterias(materias_t** materias, int trimestreAtual);
void editarTrimestre(materias_t** materias, int trimestreAtual);
void alocaSegundaDimensaoMaterias(materias_t** materias);
void initMaterias(materias_t** materias);

materias_t** alocaPrimeiraDimensaoMaterias();

#endif // bdop$materias_h__
