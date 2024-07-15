/*
    arquivo que encripta strings em numeros usando ponteiros
*/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

int main() {
    int qLetras, i, j = 0;
    char* letras;
    uint64_t fator = 1;
    uint64_t soma = 0;

    printf("Digite quantas letras vc precisa\n:");
    scanf("%d%*c", &qLetras);

    letras = (char*)calloc(qLetras + 1, sizeof(char));

    printf("Digite a string: ");
    fgets(letras, qLetras + 1, stdin);    

    for(i = 0; qLetras > i; i++) {
        if(j >= sizeof(uint64_t)) {
            j = 0;
            printf("%lli\n", soma);
            soma = 0;
        }
        fator = pow(2, (8 * j));
        j++;
        soma += letras[i] * fator;
    }
    free(letras);
    printf("%lli\n", soma);
    return 0;
}
