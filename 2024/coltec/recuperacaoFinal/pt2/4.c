#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "4.h"

void leArquivo(receita_t** receitas, int *qntReceitas, FILE* arq) {
	char tempDados[TAM_MAX_MODO_PREPARO];
	fread(qntReceitas, sizeof(int), 1, arq);

	(*receitas) = (receita_t*)malloc(sizeof(receita_t) * (*qntReceitas));

	for (int p = 0; p < (*qntReceitas); p++) {

		fread(tempDados, sizeof(char), TAM_MAX_NOME_RECEITA, arq);
		(*receitas)[p].nomeReceita = (char*)malloc(sizeof(char) * strlen(tempDados) + CHAR_FINALIZADOR_STRING);
		strcpy(((*receitas)[p].nomeReceita), tempDados);

		fread(tempDados, sizeof(char), TAM_MAX_MODO_PREPARO, arq);
		(*receitas)[p].modoPreparo = (char*)malloc(sizeof(char) * strlen(tempDados) + CHAR_FINALIZADOR_STRING);
		strcpy((*receitas)[p].modoPreparo, tempDados);

		fread(&(*receitas)[p].QNT_INGREDIENTES, sizeof(int), 1, arq);

		(*receitas)[p].ingredientes = (ingrediente_t*)malloc(sizeof(ingrediente_t) * (*receitas)[p].QNT_INGREDIENTES);

		for (int q = 0; q < (*receitas)[p].QNT_INGREDIENTES; q++) {
			fread(tempDados, sizeof(char), TAM_MAX_NOME_INGREDIENTE, arq);
			(*receitas)[p].ingredientes[q].nomeIngrediente = (char*)malloc(sizeof(char) * strlen(tempDados));
			strcpy((*receitas)[p].ingredientes[q].nomeIngrediente, tempDados);

			fread(tempDados, sizeof(char), TAM_MAX_UNIDADE_MEDIDA, arq);
			(*receitas)[p].ingredientes[q].unidade = (char*)malloc(sizeof(char) * strlen(tempDados));
			strcpy((*receitas)[p].ingredientes[q].unidade, tempDados);

			fread(&(*receitas)[p].ingredientes[q].quantidade, sizeof(int), 1, arq);
		}

	}
	fclose(arq);
}

void escreveArquivo(receita_t* receitas, int qntReceitas, FILE* arq) {
	fwrite(&qntReceitas, sizeof(int), 1, arq);

	for (int p = 0; p < qntReceitas; p++) {
		fwrite(receitas[p].nomeReceita, sizeof(char), TAM_MAX_NOME_RECEITA, arq);
		fwrite(receitas[p].modoPreparo, sizeof(char), TAM_MAX_MODO_PREPARO, arq);
		fwrite(&receitas[p].QNT_INGREDIENTES, sizeof(int), 1, arq);

		for (int q = 0; q < receitas[p].QNT_INGREDIENTES; q++) {
			fwrite(receitas[p].ingredientes[q].nomeIngrediente, sizeof(char), TAM_MAX_NOME_INGREDIENTE, arq);
			fwrite(receitas[p].ingredientes[q].unidade, sizeof(char), TAM_MAX_UNIDADE_MEDIDA, arq);
			fwrite(&receitas[p].ingredientes[q].quantidade, sizeof(int), 1, arq);
		}
	}
	fclose(arq);
}