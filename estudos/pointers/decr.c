/*
    Arquivo que destransforma os numeros em strings usando ponteiros
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

static int decr(int qntNum, uint64_t* numeros) {
    char* decript;

    numeros = (uint64_t*)calloc(qntNum , sizeof(uint64_t));

    if (numeros == NULL) {
        return 1;
    }

    printf("Digite os numeros:");

    for (int i = 0; qntNum > i; i++) {
        (void)scanf("%lli", &numeros[i]);
    }

    for (int i = 0; qntNum > i; i++) {
        decript = (char*)&numeros[i];

        for (int j = 0; sizeof(uint64_t) > j; j++) {
            printf("%c", *(decript + j));
        }

    }
    return 0;
    printf("\n");
}

int main(int argc, char* argv[]) {
    uint64_t* numeros = NULL;
    int fSucess;
    int qntNum;

    printf("Digite a quantidade de numeros:\n:");
    (void)scanf("%d%*c", &qntNum);

     fSucess = decr(qntNum, numeros);

     if (fSucess) {
         fprintf(stderr, "Nao foi possivel alocar!\n");
         return 1;
     }

    free(numeros);
    return 0;
}
