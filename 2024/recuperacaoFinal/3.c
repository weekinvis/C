#include <stdbool.h>
#include <stdio.h>

#define SUCESSO 0;

bool verificaPrimo(int numAtual) {
    int denominador = 1;
    int divisores = 0;
    
    if(numAtual == 1) {
        return false;
    } else {
        for(denominador; denominador <= numAtual; denominador++) {
            if(numAtual % denominador == 0) {
                divisores++;
            }
        }
        if(divisores == 2) {
            return true;
        }
    
    }
    return false;   

}

int main(int argc, char* argv[]) {
    bool ehPrimo;
    int N;
    int soma = 0;

    printf("Digite ate que numero que gostaria de ir percorrendo os numeros primos e somando-os: ");
    (void)scanf("%d%*c", &N);

    for(int p = 1; p <= N; p++) {
        if(verificaPrimo(p)) {
            soma += p;
        }
    }
    printf("%i eh a soma dos primos de 1 ate %i.\n", soma, N);

    return SUCESSO;

}