/**
* Implementacao do jogo da forca (trabalho do 1o ano de C)
* O codigo aqui escrito sera um codigo que tenta atender os requisitos de boa programacao.
* Propositalmente, o codigo tera apenas 1 arquivo (Certamente seriam pelo menos 3, mas para nao ser demasiadamente avancado).
* @date 2025-08-08
*/

/**
* Funcionamento: O Jogador joga e vai passando de fase, ate completar as 3 fases.
* Caso perca em uma das fases ou ganhe, ele pode escolher jogar de novo e aleatorizar novas palavras.
* Tema: COMIDA. 
*/

/* Bibliotecas */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

/* Diferenciacao para limpar o terminal... */

#ifdef _WIN32

void limpar_tela() {

	system("cls");

}

#else

void limpar_tela() {

	system("clear");

}

#endif

/* Constantes */
#define SUCESSO            0

#define BARRA_ZERO		   1
#define TAM_MAX_PALAVRA_N1 3
#define TAM_MAX_PALAVRA_N2 4
#define TAM_MAX_PALAVRA_N3 5
#define TAM_ALFABETO	   26
#define POSICAO_ASCII      97

#define QNT_NIVEIS		   3
#define QNT_MAX_PALAVRAS_N 5
#define QNT_INICIAL_VIDAS  5

static void imprime_info(const char * letras_descobertas, const char * letras_tentadas, const int tamanho_palavra, const int quantidade_vida) {

	printf("Voce ainda possui %i vidas.\n", quantidade_vida);

	printf("Letras tentadas: ");

	for (int p = 0; p < TAM_ALFABETO; p++) {
		if (letras_tentadas[p] != '?') {
			printf("%c ", letras_tentadas[p]);
		}
	}
	printf("\n");

	for (int p = 0; p < tamanho_palavra; p++) {
		printf("%c ", letras_descobertas[p]);
	}

	printf("\n\n");

	return;

}

static bool verifica_tentativa(const char * palavra, char * letras_descobertas, int tamanho_palavra, const char tentativa) {
	bool acertou = false;

	for (int p = 0; p < tamanho_palavra; p++) {
		if (palavra[p] == toupper(tentativa) || palavra[p] == tolower(tentativa)) {
			acertou = true;
			letras_descobertas[p] = tentativa;
		}
	}

	return acertou;

}

static bool verifica_reincidencia(char * alfabeto_tentativa, uint8_t tentativa) {
	tentativa -= POSICAO_ASCII;

	if (alfabeto_tentativa[tentativa] == '?') {
		alfabeto_tentativa[tentativa] = (char)(tentativa + POSICAO_ASCII);
		return false;
	}
	return true;
}

static inline bool descobriu_palavra(const char* letras_descobertas, const int tamanho_palavra) {

	for (int p = 0; p < tamanho_palavra; p++) {
		if (letras_descobertas[p] == '?') return false;
	}

	return true;
}

static bool nivel3() {
	static const char palavras_forca[QNT_MAX_PALAVRAS_N][TAM_MAX_PALAVRA_N3 + BARRA_ZERO] = { "Vinho", "Nozes", "Cacau", "Manga", "Pudim" };
	char letras_tentadas[TAM_ALFABETO];
	int quantidade_vidas = QNT_INICIAL_VIDAS;
	char letras_descobertas[TAM_MAX_PALAVRA_N3];
	int indice_sorteado;
	char tentativa;

	memset(letras_descobertas, '?', TAM_MAX_PALAVRA_N3);
	memset(letras_tentadas, '?', TAM_ALFABETO);

	indice_sorteado = rand() % QNT_MAX_PALAVRAS_N;

	while (true) {

		limpar_tela();

		imprime_info(letras_descobertas, letras_tentadas, TAM_MAX_PALAVRA_N3, quantidade_vidas);

		if (0 == quantidade_vidas) {
			return true; // Ele perdeu
		}
		if (descobriu_palavra(letras_descobertas, TAM_MAX_PALAVRA_N3)) {
			return false; // Ele venceu
		}

		printf("Tente uma letra\n: ");
		(void)scanf("%c%*c", &tentativa);

		if (verifica_reincidencia(letras_tentadas, tolower(tentativa))) continue;

		// Se ele errou...
		if (!verifica_tentativa(palavras_forca[indice_sorteado], letras_descobertas, TAM_MAX_PALAVRA_N3, tentativa)) quantidade_vidas--;

	}

}

static bool nivel2() {
	static const char palavras_forca[QNT_MAX_PALAVRAS_N][TAM_MAX_PALAVRA_N2 + BARRA_ZERO] = { "Cafe", "Bife", "Caju", "Pera", "Kiwi" };
	char letras_tentadas[TAM_ALFABETO];
	int quantidade_vidas = QNT_INICIAL_VIDAS;
	char letras_descobertas[TAM_MAX_PALAVRA_N2];
	int indice_sorteado;
	char tentativa;

	memset(letras_descobertas, '?', TAM_MAX_PALAVRA_N2);
	memset(letras_tentadas, '?', TAM_ALFABETO);

	indice_sorteado = rand() % QNT_MAX_PALAVRAS_N;

	while (true) {

		limpar_tela();

		imprime_info(letras_descobertas, letras_tentadas, TAM_MAX_PALAVRA_N2, quantidade_vidas);

		if (0 == quantidade_vidas) {
			return true; // Ele perdeu
		}
		if (descobriu_palavra(letras_descobertas, TAM_MAX_PALAVRA_N2)) {
			return false; // Ele venceu
		}

		printf("Tente uma letra\n: ");
		(void)scanf("%c%*c", &tentativa);

		if (verifica_reincidencia(letras_tentadas, tolower(tentativa))) continue;

		// Se ele errou...
		if (!verifica_tentativa(palavras_forca[indice_sorteado], letras_descobertas, TAM_MAX_PALAVRA_N2, tentativa)) quantidade_vidas--;

	}

}

static bool nivel1() {
	static const char palavras_forca[QNT_MAX_PALAVRAS_N][TAM_MAX_PALAVRA_N1 + BARRA_ZERO] = {"Uva", "Mel", "Pao", "Rum", "Sal"};
	char letras_tentadas[TAM_ALFABETO];
	int quantidade_vidas = QNT_INICIAL_VIDAS;
	char letras_descobertas[TAM_MAX_PALAVRA_N1];
	int indice_sorteado;
	char tentativa;

	memset(letras_descobertas, '?', TAM_MAX_PALAVRA_N1);
	memset(letras_tentadas, '?', TAM_ALFABETO);

	indice_sorteado = rand() % QNT_MAX_PALAVRAS_N;

	while (true) {

		limpar_tela();

		imprime_info(letras_descobertas, letras_tentadas, TAM_MAX_PALAVRA_N1, quantidade_vidas);

		if (0 == quantidade_vidas) {
			return true; // Ele perdeu
		}
		if (descobriu_palavra(letras_descobertas, TAM_MAX_PALAVRA_N1)) {
			return false; // Ele venceu
		}

		printf("Tente uma letra\n: ");
		(void)scanf("%c%*c", &tentativa);

		// Se o usuario tentar a mesma letra ja antes testada
		// Ignora...
		if (verifica_reincidencia(letras_tentadas, tolower(tentativa))) continue;

		// Se ele errou...
		if (!verifica_tentativa(palavras_forca[indice_sorteado], letras_descobertas, TAM_MAX_PALAVRA_N1, tentativa)) quantidade_vidas--;

	}

}

static bool comecar_jogo() {

	int nivel_atual = 1;
	bool perdeu = false;

	// Enquanto o usuario ainda nao perdeu ou nao chegou ao final...
	// Lembre-se que perdeu eh o oposto de venceu, entao bool venceu = !perdeu;

	while ((!perdeu) && (nivel_atual <= QNT_NIVEIS)) {

		switch (nivel_atual) {
		case 1:
			perdeu = nivel1();
			break;
		case 2:
			perdeu = nivel2();
			break;
		case 3:
			perdeu = nivel3();
			break;
		}
		nivel_atual++;
	}

	// A variavel se trata se o usuario perdeuou nao, mas o valor de retorno espera se o usuario venceu ou nao.
	// Se ele venceu, entao ele nao perdeu, se ele perdeu, entao nao venceu. (Sao contrarios)
	// Retorno o valor contrario de perdeu (venceu). Explicacao na linha imediatamente acima.
	return !perdeu; 

}

int main(int argc, char* argv[]) {
	bool continuar;
	bool venceu;
	char opcao;

	// Gero a seed para aleatorizar.
	srand(time(NULL));

	do {

		venceu = comecar_jogo();

		printf("%s\nDeseja continuar? (s ou S)\n: ", venceu ? "Parabens! Voce venceu!!!" : "Que pena, voce ainda nao conseguiu...");
		(void)scanf("%c%*c", &opcao);
		continuar = (opcao == 's') || (opcao == 'S');

	} while (continuar);

	return SUCESSO;

}

