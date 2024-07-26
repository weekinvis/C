#include <stdlib.h> // para usar alocacao dinamica
#include <stdio.h> // para usar scanf e printf

// ta incompleto, dps eu vou terminar

int main(int argc, char* argv[]) {
	int* seq, * seq2;
	int a, i, j, k;
	int count[2] = { 0, 0 };

	scanf_s("%d", &a);

	seq2 = (int*)malloc(sizeof(int) * a);
	seq = (int*)malloc(sizeof(int) * a);

	for (i = 0; a > i; i++) {
		scanf_s("%d", &seq[i]);
	}
	
	for (i = 0; a > i; i++) {
		for (j = i; a > j; j++) {
			seq2[j] = seq[j];
		}
	}

	free(seq);
	free(seq2);

	return 0;
}
