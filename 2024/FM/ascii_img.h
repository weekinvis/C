#pragma once /* Primeira guarda */
#ifndef __asciiImg_h__ /* Segunda guarda */
#define __asciiImg_h__
// ----------------------------------------------------------------------------------------------------------------------------
// Início do código fornecido pelo professor
// Não adicione ou remova nada.

// Se estiver no Windows e não conseguir ver a imagem colorida, pode ser que seu terminal não suporte Ascii Escape Colors.
// Para habilitá-la, execute o comando abaixo no terminal com permissão de Administrador.
// Após executado, o terminado deve ser fechado e aberto novamente para ter o suporte às cores habilitado.
// Comando:
// reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f

// definicoes do cod pra imagem
#define MODO_IMAGEM           (IMAGEM_COLORIDA) // Definicao de imagem utilizada
#define IMAGEM_PRETO_BRANCO   (false) // Definicao de imagem preto/branco
#define IMAGEM_COLORIDA       (true)  // Definicao de imagem colorida
#define IMAGEM_NUMERO_COLUNAS (60)  // Numero de colunas da imagem
#define ERRO_CARREGAR_IMAGEM  (1)   // Falha ao carregar a imagem fornecida

// definicoes de bibliotecas
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>

/// Estrutura que representa uma imagem em Ascii
struct asciiImg_s {
    uint8_t* bytes;
    int nBytes;
};

/// Tipo "Imagem ASCII"
typedef struct asciiImg_s asciiImg_t;

// Tamanho do buffer para cada linha da imagem
#define BUFFER_TAMANHO  50000

// Tamanho máximo da linha de comando
#define LINHA_COMANDO   10000

// Limiar inferior que considera o download com sucesso
#define LIMIAR_INFERIOR_TAMANHO_IMAGEM  500

// Nome do executável da ferramenta de download e conversão da imagem
#ifdef __unix__ 
#define FERRAMENTA_IMAGEM "ascii-image-converter.bin"
#else
#define FERRAMENTA_IMAGEM "ascii-image-converter.exe"
#endif

// Nome do arquivo de saída temporário da imagem
#define ARQUIVO_IMAGEM_TMP  "ascii_art.txt"

/**
 *  \brief Função que carrega uma imagem informada na URL.
 *
 *  \param [in] colorido Define se a imagem será colorida.
 *  \param [in] largura Define a largura da imagem gerada.
 *  \return Endereço da estrutura com a imagem.
 *          Caso a imagem não tenha sido carregada corretamente, a função
 *          retornará NULL.
 */
extern asciiImg_t* insta_carregaImagem(char url[], bool colorido, int largura);

/**
 *  \brief Função que imprime uma Imagem ASCII.
 *
 *  \param [in] img Endereço da estrutura com os dados da imagem.
 */
extern void insta_imprimeImagem(asciiImg_t* img);

/**
 *  \brief Função que libera a memória alocada por uma imagem.
 *
 *  \param [in] img Endereço da estrutura com os dados da imagem a ser liberada.
 */
extern void insta_liberaImagem(asciiImg_t* img);

// Fim do código fornecido pelo professor
// ----------------------------------------------------------------------------------------------------------------------------
#endif