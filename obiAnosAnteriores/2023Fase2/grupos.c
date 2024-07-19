#include <stdio.h>
#include <stdint.h>
#define MAX 333333
#define MAX2 10000

// ainda vou escrever em alocacao dinamica. O codigo esta extremamente ineficiente, entretanto, a logica parece estar correta.

int compara(int grupos[][3], int juntos[][2], int separados[][2], int qE, int qJ, int qS) {

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
	int grupos[MAX][3];
	int juntos[MAX2][2], separados[MAX2][2];
	int i;

	do {

	scanf("%d %d %d", &a, &b, &c);

	for (i = 0; b > i; i++) {
		(void)scanf("%d %d", &juntos[i][0], &juntos[i][1]);
	}
	for (i = 0; c > i; i++) {
		(void)scanf("%d %d", &separados[i][0], &separados[i][1]);
	}
	for (i = 0; a / 3 > i; i++) {
		(void)scanf("%d %d %d", &grupos[i][0], &grupos[i][1], &grupos[i][2]);
	}
	(void)compara(grupos, juntos, separados, a, b, c);

	printf("\n\n\n");

	} while (a != -1);
	return 0;
}
