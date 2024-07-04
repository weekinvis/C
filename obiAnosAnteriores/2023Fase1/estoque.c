#include <stdio.h>
#define MAX_ESTOQUE 500

int leEstoque(int estoque[][MAX_ESTOQUE], int tamanho, int tipo) {

    int i, j;

    for(j = 0; tamanho > j; j++) {
        for(i = 0; tipo > i; i++) {
            scanf("%i", &estoque[i][j]);
        }
    }

}

int verificaVenda(int estoque[][MAX_ESTOQUE], int q) {
    int tamanho, tipo;
    int contador = 0;

    for(q; q > 0; q--) {
        scanf("%i %i", &tamanho, &tipo);
        tamanho--;
        tipo--;
        if(estoque[tipo][tamanho] > 0) {
            contador++;
            estoque[tipo][tamanho]--;
        } else {}
    }

    return contador;
}

int main() {
    
    int estoque[MAX_ESTOQUE][MAX_ESTOQUE];
    int tamanho, tipo;
    int qntCompras;
    int contador;
    
    scanf("%i %i", &tamanho, &tipo);

    leEstoque(estoque, tamanho, tipo);

    scanf("%i", &qntCompras);

    contador = verificaVenda(estoque, qntCompras);

    printf("%i", contador);
    
    return 0;
}