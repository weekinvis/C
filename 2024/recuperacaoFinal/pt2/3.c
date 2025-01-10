#include "3.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

void buscarReceita(receita_t* receitas, int qntReceitas) {
	char tempNome[TAM_MAX_NOME_RECEITA];
	system("clear || cls");
	printf("Digite o nome da receita que quer buscar: ");
	fgets(tempNome, TAM_MAX_NOME_RECEITA, stdin);
	removeQuebraLinhaFinal(tempNome);

	for (int p = 0; p < qntReceitas; p++) {
		if (strstr(receitas[p].nomeReceita, tempNome) != NULL) {
			printf("Nome: %s\n", receitas[p].nomeReceita);
			printf("Ingredientes:\n");
			for (int q = 0; q < receitas[p].QNT_INGREDIENTES; q++) {
				printf("%4d%-5s: %s\n", receitas[p].ingredientes[q].quantidade, receitas[p].ingredientes[q].unidade, receitas[p].ingredientes[q].nomeIngrediente);
			}
			printf("Modo de preparo: %s\n", receitas[p].modoPreparo);
		
		}
	}
}