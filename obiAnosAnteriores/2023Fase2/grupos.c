#include <stdio.h>
#include <stdlib.h>

// O codigo esta extremamente ineficiente, entretanto, a logica parece estar correta.

int compara(int** grupos, int** juntos, int** separados, int qE, int qJ, int qS) {

	int i, j, k = 0;
	int quebras = 0;

	// quebra dos alunos que queriam estar juntos
	for (k = 0; qJ > k; k++) {
		for (i = 0; qE / 3 > i; i++) {
			for (j = 0; 3 > j; j++) {
				if (juntos[k][0] == grupos[i][j]) {
					if ((juntos[k][1] == grupos[i][0]) || (juntos[k][1] == grupos[i][1]) || (juntos[k][1] == grupos[i][2])) {
					}
					else {
						quebras++;
					}
				}
			}
		}
	}

	// quebra dos alunos que queriam estar separados

	for (k = 0; qS > k; k++) {
		for (i = 0; qE / 3 > i; i++) {
			for (j = 0; 3 > j; j++) {
				if (separados[k][0] == grupos[i][j]) {
					if ((separados[k][1] == grupos[i][0]) || (separados[k][1] == grupos[i][1]) || (separados[k][1] == grupos[i][2])) {
						quebras++;
					}
					else {
					}
				}
			}
		}
	}

	printf("%i", quebras);
	return 0;
}

int main(int argc, char** argv) {
	int a, b, c;
	int** grupos;
	int** juntos, **separados;
	int i;

	scanf_s("%d %d %d", &a, &b, &c);

	grupos = (int**)malloc(sizeof(int*) * a / 3);

	for (i = 0; a / 3 > i; i++) {
		grupos[i] = (int*)malloc(sizeof(int) * 3);
	}

	juntos = (int**)malloc(sizeof(int*) * b);

	for (i = 0; b > i; i++) {
		juntos[i] = (int*)malloc(sizeof(int) * 2);
	}

	separados = (int**)malloc(sizeof(int*) * b);

	for (i = 0; c > i; i++) {
		separados[i] = (int*)malloc(sizeof(int) * 2);
	}

	for (i = 0; b > i; i++) {
		(void)scanf_s("%d %d", &juntos[i][0], &juntos[i][1]);
	}
	for (i = 0; c > i; i++) {
		(void)scanf_s("%d %d", &separados[i][0], &separados[i][1]);
	}
	for (i = 0; a / 3 > i; i++) {
		(void)scanf_s("%d %d %d", &grupos[i][0], &grupos[i][1], &grupos[i][2]);
	}
	
	(void)compara(grupos, juntos, separados, a, b, c);
	return 0;
}
