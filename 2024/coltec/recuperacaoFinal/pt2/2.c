#include "util.h"
#include "2.h"
#include <stdlib.h>
#include <stdio.h>

void imprimirReceitas(receita_t* receitas, int qntReceitas) {
	system("clear || cls");
	for (int p = 0; p < qntReceitas; p++) {
		printf("Nome: %s\n", receitas[p].nomeReceita);
		printf("Ingredientes:\n");
		for (int q = 0; q < receitas[p].QNT_INGREDIENTES; q++) {
			printf("%4d%-5s: %s\n", receitas[p].ingredientes[q].quantidade, receitas[p].ingredientes[q].unidade, receitas[p].ingredientes[q].nomeIngrediente);
		}
		printf("Modo de preparo: %s\n\n", receitas[p].modoPreparo);
	}

}