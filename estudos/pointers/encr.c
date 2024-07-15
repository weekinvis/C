/*
    arquivo que encripta strings em numeros usando ponteiros
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#define TAM_BYTE 8

int main() {
    int qLetras, i, j = 0, c = 0;
    char* letras;
    uint64_t fator = 1;
    uint64_t soma = 0;

    printf("Digite quantas letras vc precisa (caso o texto seja grande, chute alto.)\n:");
    scanf("%d%*c", &qLetras);

    letras = (char*)calloc(qLetras + 1, sizeof(char));

    printf("Digite a string: ");
    fgets(letras, qLetras + 1, stdin);    

    printf("\n\n---Texto encriptado---\n\n");
    for(i = 0; qLetras > i; i++) {
        if(j >= sizeof(uint64_t)) {
            if(soma == 0) {
                j = 0;
                soma = 0;
            } else {
                j = 0;
                printf("%lli ", soma);
                soma = 0;
                c++;
            }
        }
        fator = pow(2, (TAM_BYTE * j));
        j++;
        soma += letras[i] * fator;
    }
    free(letras);
    printf("%lli\n\n>qnt de numeros %i", soma, c + 1);
    return 0;
}
