#include <stdlib.h>
#include <stdio.h>

int leEstoque(int** estoque, int tamanho, int tipo) {
    int i, j;

    for(i = 0; tipo > i; i++) {
        for(j = 0; tamanho > j; j++) {
            scanf("%d%*c", &estoque[i][j]);
        }
    }

}

int verificaVenda(int** estoque) {
    int qntVendas;
    int tamanho, tipo;
    int i, count = 0;
    
    scanf("%d", &qntVendas);

    for(i = 0; qntVendas > i; i++) {
        scanf("%d %d", &tipo, &tamanho);
        tamanho--;
        tipo--;
        if(estoque[tipo][tamanho] > 0) {
            count++;
            estoque[tipo][tamanho]--;
        } else {
            continue;
        }
        
    }

    return count;
}

int main(int argc, char** argv) {
    int tamanho, tipo, vendas;
    int** estoque;
    int i, j;

    scanf("%d %d", &tipo, &tamanho);

    // aloca espaco

    estoque = (int**)malloc(sizeof(int*) * tipo);

    for(i = 0; tipo > i; i++) {
        estoque[i] = (int*)malloc(sizeof(int) * tamanho);
    }

    // le o estoque

    leEstoque(estoque, tamanho, tipo);
    vendas = verificaVenda(estoque);

    printf("%i", vendas);

    return 0;
}
