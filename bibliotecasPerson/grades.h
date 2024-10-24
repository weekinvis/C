#define NUM_CONCEITOS 13
#define TAM_CONCEITOS 3

// definicoes de nomes
#define NOME_ARQUIVO "grades.txt"

// definicoes de tamanhos / quantidades
#define DISCIPLINA_MAIOR_NOME 15 + 1
#define QNT_TRIMESTRES 3
#define QNT_MATERIAS 13

typedef struct grades_s {
	char* nomeDisciplina;
	double notaTrimestre;
	char conceito[3];

}grades_t;

void pHconceito(char conceito[TAM_CONCEITOS], double per) {
	const char conceitos[NUM_CONCEITOS][TAM_CONCEITOS] = {
		"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-",
		"D+", "D", "D-", "F"
	};
	if (per >= 0.9) {
		if (per >= 0.97) {
			strcpy(conceito, conceitos[0]);
		}
		else if (per >= 0.93) {
			strcpy(conceito, conceitos[1]);
		}
		else {
			strcpy(conceito, conceitos[2]);
		}
	}
	else if (per >= 0.8) {
		if (per >= 0.87) {
			strcpy(conceito, conceitos[3]);
		}
		else if (per >= 0.83) {
			strcpy(conceito, conceitos[4]);
		}
		else {
			strcpy(conceito, conceitos[5]);
		}
	}
	else if (per >= 0.7) {
		if (per >= 0.77) {
			strcpy(conceito, conceitos[6]);
		}
		else if (per >= 0.73) {
			strcpy(conceito, conceitos[7]);
		}
		else {
			strcpy(conceito, conceitos[8]);
		}
		
	}
	else if (per >= 0.6) {
		if (per >= 0.67) {
			strcpy(conceito, conceitos[9]);
		}
		else if (per >= 0.63) {
			strcpy(conceito, conceitos[10]);
		}
		else {
			strcpy(conceito, conceitos[11]);
		}
	}
	else {
		strcpy(conceito, conceitos[12]);
	}
}

void preencheConceito(grades_t** dadosNotas) {
	double percentagem;
	for (int i = 0; i < QNT_TRIMESTRES; i++) {
		if (dadosNotas[i] == NULL) {

		}
		else {
			for (int j = 0; j < QNT_MATERIAS; j++) {
				percentagem = dadosNotas[i][j].notaTrimestre;
				if (i == 0) {
					percentagem /= 30;
				}
				else {
					percentagem /= 35;
				}
				pHconceito(dadosNotas[i][j].conceito, percentagem);
			}
		}
	}
}

/* ------------------- Funcoes ----------------- */

int fnumQuebras(FILE* arquivoAtual) {
	char charAtual;
	int numQuebras = 0;
	bool eof;

	while (!feof(arquivoAtual)) {
		(void)fscanf(arquivoAtual, "%c", &charAtual);
		eof = feof(arquivoAtual);
		if (!eof && (charAtual == '\n')) {
			numQuebras++;
		}
	}

	fseek(arquivoAtual, 0, SEEK_SET);

	return numQuebras + 1;
}

void preencheNomes(grades_t** dadosNotas, int trimestreAtual) {
	const char nomeDisciplinas[QNT_MATERIAS][DISCIPLINA_MAIOR_NOME] = {
		"BIOLOGIA", "QUIMICA", "MATEMATICA", "SOCIOLOGIA", "PORTUGUES",
		"EDUCACAO FISICA", "ARTES", "INGLES", "IP", "ESD", "FISICA",
		"MADEIRA", "ESPANHOL"
	};
	for (int i = 0; i < QNT_MATERIAS; i++) {
		dadosNotas[trimestreAtual - 1][i].nomeDisciplina = (char*)malloc(sizeof(char) * strlen(nomeDisciplinas[i]) + 1);
		if ((dadosNotas)[trimestreAtual - 1][i].nomeDisciplina == NULL) {
			return;
		}
		strcpy(dadosNotas[trimestreAtual - 1][i].nomeDisciplina, nomeDisciplinas[i]);
	}
	return;
}

void recuperaDados(FILE* arq, grades_t** dadosNotas) {
	int trimestreAtual;
	int nTrimestres;
	int numQuebras;

	numQuebras = fnumQuebras(arq);

	nTrimestres = numQuebras / (QNT_MATERIAS + 1);

	for (int i = 0; nTrimestres > i; i++) {
		(void)fscanf(arq, "%i", &trimestreAtual);
		dadosNotas[trimestreAtual - 1] = (grades_t*)malloc(sizeof(grades_t) * QNT_MATERIAS);
		if (dadosNotas[trimestreAtual - 1] == NULL) {
			fprintf(stderr, "Nao foi possivel alocar!\n");
			return;
		}
		for (int j = 0; j < QNT_MATERIAS; j++) {
			(void)fscanf(arq, "%lf", &dadosNotas[trimestreAtual - 1][j].notaTrimestre);
		}
		preencheNomes(dadosNotas, trimestreAtual);
		preencheConceito(dadosNotas);
	}


	return;
}

void verificaArquivo(grades_t** dadosNotas) {
	FILE* arq = NULL;

	arq = fopen(NOME_ARQUIVO, "r");

	if (arq == NULL) {
		arq = fopen(NOME_ARQUIVO, "w");
		fclose(arq);
		return;
	}

	recuperaDados(arq, dadosNotas);

	fclose(arq);
	return;

}

void preencheArquivo(grades_t** dadosNotas, FILE* arquivoNotas) {

	for (int i = 0; i < QNT_TRIMESTRES; i++) {
		if (dadosNotas[i] == NULL) {

		}
		else {
			fprintf(arquivoNotas, "%i\n", i + 1);
			for (int j = 0; j < QNT_MATERIAS; j++) {
				fprintf(arquivoNotas, "%lf\n", dadosNotas[i][j].notaTrimestre);
			}
		}
	}
	fclose(arquivoNotas);
	return;

}

void preencheDados(grades_t** dadosNotas, FILE* arquivoNotas) {
	int trimAtual;

	printf("Digite o Trimestre: ");
	(void)scanf("%d%*c", &trimAtual);

	if (dadosNotas[trimAtual - 1] == NULL) {
		dadosNotas[trimAtual - 1] = (grades_t*)malloc(sizeof(grades_t) * QNT_MATERIAS);
		preencheNomes(dadosNotas, trimAtual);
		for (int i = 0; i < QNT_MATERIAS; i++) {
			printf("Digite a nota de %s do %i trimestre: ", dadosNotas[trimAtual - 1][i].nomeDisciplina, trimAtual);
			(void)scanf("%lf%*c", &dadosNotas[trimAtual - 1][i].notaTrimestre);
		}
	}
	else {
		for (int i = 0; i < QNT_MATERIAS; i++) {
			printf("Digite a nota de %s do %i trimestre: ", dadosNotas[trimAtual - 1][i].nomeDisciplina, trimAtual);
			(void)scanf("%lf%*c", &dadosNotas[trimAtual - 1][i].notaTrimestre);
		}
	}
	arquivoNotas = fopen(NOME_ARQUIVO, "w");
	preencheArquivo(dadosNotas, arquivoNotas);
	preencheConceito(dadosNotas);

}

void imprimeDados(grades_t** dadosNotas) {
	for (int i = 0; i < QNT_TRIMESTRES; i++) {
		if (dadosNotas[i] == NULL) {
			printf("\nSem dados do %i trimestre.\n", i + 1);
		}
		else {
			printf("\nTrimestre %i:\n", i + 1);
			for (int j = 0; j < QNT_MATERIAS; j++) {
				printf("%-15s : %-2s  (%.1f)\n", dadosNotas[i][j].nomeDisciplina, dadosNotas[i][j].conceito, dadosNotas[i][j].notaTrimestre);
			}
		}
	}
}

void imprimirIntervalos() {
	printf(
		"\nA + : 97%% - 100%% (Excelente superior)\n"  
		"A   : 93%% - 96%% (Excelente)\n"
		"A - : 90%% - 92%% (Excelente inferior)\n\n"
		"B + : 87%% - 89%% (Bom superior)\n"
		"B   : 83%% - 86%% (Bom)\n"
		"B - : 80%% - 82%% (Bom inferior)\n\n"
		"C + : 77%% - 79%% (Medio superior)\n"
		"C   : 73%% - 76%% (Medio)\n"
		"C - : 70%% - 72%% (Medio inferior)\n\n"
		"D + : 67%% - 69%% (Abaixo da media superior)\n"
		"D   : 63%% - 66%% (Abaixo da media)\n"
		"D - : 60%% - 62%% (Abaixo da media inferior)\n\n"
		"F   : 0%% - 59%% (Reprovado)\n");
}
