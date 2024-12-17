/*
    Arquivo que transforma strings em inteiros usando ponteiros
*/

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define TAM_BYTE 8
#define SUCESSO 0
#define QNT_MAX_LETRAS 6000

static uint64_t* encr(char string[], int* r) {
    uint64_t fator = 1;
    uint64_t soma = 0;
    uint64_t* arr = NULL;
    int q = 0;

     for(int p = 0; strlen(string) + 1 > p; p++) {
        if(q >= sizeof(uint64_t)) {
            if(soma == 0) {
                break;
            } else {
                (*r)++;
                arr = (uint64_t*)realloc(arr, sizeof(uint64_t) * (*r));
                arr[(*r) - 1] = soma;
                soma = 0;
                q = 0;
            }
        }
        fator = pow(2, (TAM_BYTE * q));
        q++;
        soma += string[p] * fator;
    }

    if(soma) {
        (*r)++;
        arr = (uint64_t*)realloc(arr, sizeof(uint64_t) * (*r));
        arr[(*r) - 1] = soma;
    }

    return arr;
}

int main(int argc, char* argv[]) {
    char string[QNT_MAX_LETRAS];
    uint64_t* arr_encr = NULL;
    int r = 0;

    printf("Digite a string: ");
    fgets(string, QNT_MAX_LETRAS + 1, stdin);    

    arr_encr = encr(string, &r);

    for(int p = 0; p < r; p++) {
        printf("%llu ", arr_encr[p]);
    }

    printf("\n\nQnt numeros: %d", r);

    free(arr_encr);

    return SUCESSO;
}
