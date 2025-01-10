#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SUCESSO 0

int main(int argc, char* argv[]) {
    char caracterePreenchimento;
    char* provisorio;
    int alturaTriangulo;

    do {
        
        printf("Digite a altura do triangulo: ");
        (void)scanf("%d%*c", &alturaTriangulo);

        if(alturaTriangulo < 0) {
            fprintf(stderr, "Altura invalida! Tente um numero positivo e inteiro!\n");
        }

    } while(alturaTriangulo < 0);

    printf("Digite o caractere de preenchimento: ");
    (void)scanf("%c", &caracterePreenchimento);

    for(int p = 0; p < alturaTriangulo; p++) {
        printf("%c", caracterePreenchimento);
        for(int q = 1; q < alturaTriangulo ; q++) {
            if(p == 0 || p == alturaTriangulo - 1) {
                if(p == 0) {
                    printf("%c", caracterePreenchimento);
                }
            }
            else if(p + q == alturaTriangulo) {
                printf("%c", caracterePreenchimento);
            } else {
                printf(" ");
            }

        }
        printf("\n");
    }

    return SUCESSO;
}