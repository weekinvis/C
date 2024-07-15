/*
    arquivo que decripta as mensagens criptografadas pelo arquivo encr.c usando ponteiros
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

int main() {
    uint64_t* numeros;
    char* decript;
    int qntNum;
    int i, j = 0;

    printf("Digite a quantidade de numeros:\n:");
    scanf("%d", &qntNum);

    numeros = (uint64_t*)calloc(qntNum, sizeof(uint64_t));

    for(i = 0; qntNum > i; i++) {
        printf("Digite o numero %i: ", i + 1);
        scanf("%*c%lli", &numeros[i]);
    }

    for(i = 0; qntNum > i; i++) {
        decript = (char*)&numeros[i];
        
        for(j = 0; sizeof(uint64_t) > j; j++) {
            printf("%c", *(decript + j));
        }
        
    }
    free(numeros);
    return 0;
}
