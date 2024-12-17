/*
    Arquivo que destransforma numeros em strings usando ponteiros
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define SUCESSO 0

static bool decr(int qntNum, uint64_t* numeros) {
    char* dec;

    numeros = (uint64_t*)calloc(qntNum , sizeof(uint64_t));

    if (numeros == NULL) {
        return true;
    }

    printf("Digite os numeros:");

    for (int i = 0; qntNum > i; i++) {
        (void)scanf("%lli", &numeros[i]);
    }

    for (int i = 0; qntNum > i; i++) {
        dec = (char*)&numeros[i];

        for (int j = 0; sizeof(uint64_t) > j; j++) {
            printf("%c", *(dec + j));
        }

    }
    return false;
}

int main(int argc, char* argv[]) {
    uint64_t* numeros = NULL;
    bool erro;
    int qntNum;

    printf("Digite a quantidade de numeros:\n:");
    (void)scanf("%d%*c", &qntNum);

     erro = decr(qntNum, numeros);

     if (erro) {
         fprintf(stderr, "Nao foi possivel alocar!\n");
         return erro;
     }

    free(numeros);
    return SUCESSO;
}
