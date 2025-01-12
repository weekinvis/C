#include "ascii_img.h"

asciiImg_t* insta_carregaImagem(char url[], bool colorido, int largura) {

    FILE* arquivo;
    char buffer[BUFFER_TAMANHO];
    int nBytes, nBytesTotal = 0;
    char linhaComando[LINHA_COMANDO];

    asciiImg_t* img;

    // Aloca espaço para uma imagem
    img = malloc(sizeof(asciiImg_t));
    if (img == NULL) return NULL;

    // Inicializa a estrutura
    img->bytes = NULL;
    img->nBytes = 0;

    // Monta a linha de comando
    (void)sprintf(linhaComando, "%s %s %s -W %d -c > %s", FERRAMENTA_IMAGEM, url, (colorido ? "-C" : ""), largura, ARQUIVO_IMAGEM_TMP);

    // Chama o programa para fazer o download da imagem
    (void)system(linhaComando);

    // Tenta abrir o arquivo recem criado
    arquivo = fopen(ARQUIVO_IMAGEM_TMP, "r");
    if (arquivo != NULL) {

        while (!feof(arquivo)) {

            // Limpa a linha
            (void)memset(buffer, 0, sizeof(buffer));

            // Tenta ler uma linha
            if (fgets(buffer, BUFFER_TAMANHO, arquivo) == NULL) continue;

            // Descobre o número de bytes da linha
            for (nBytes = 0; buffer[nBytes] != 0; nBytes++);

            // Aloca o espaço
            img->bytes = realloc(img->bytes, sizeof(unsigned char) * (nBytesTotal + nBytes));

            // Copia para o espaço alocado
            (void)memcpy(&(img->bytes[nBytesTotal]), buffer, nBytes);
            nBytesTotal += nBytes;
        }

        // Finaliza a imagem colocando o \0 final e o tamanho
        img->bytes = realloc(img->bytes, sizeof(unsigned char) * (nBytesTotal + 1));
        img->bytes[nBytesTotal++] = '\0';
        img->nBytes = nBytesTotal;

        // Fecha o arquivo
        fclose(arquivo);
    }

    // Verifica se a imagem é válida
    if (img->nBytes < LIMIAR_INFERIOR_TAMANHO_IMAGEM) {
        // Libera todo o espaço alocado
        free(img->bytes);
        free(img);

        return NULL;
    }

    // Retorna a imagem carregada
    return img;
}

void insta_imprimeImagem(asciiImg_t* img) {
    printf("%s", img->bytes);
}

void insta_liberaImagem(asciiImg_t* img) {
    free(img->bytes);
    free(img);
}