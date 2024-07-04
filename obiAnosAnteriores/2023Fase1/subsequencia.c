#include <stdio.h>
#define TAMANHO_MAX 100000

int leDados(int sa[], int sb[], int a, int b) {
    int i;

    for(i = 0; a > i; i++) {
        scanf("%i", &sa[i]);
    }
    for(i = 0; b > i; i++) {
        scanf("%i", &sb[i]);
    }
}

char comparaDados(int sa[], int sb[], int a, int b) {
    int i, j = 0;
    char resultado;

    for(i = 0; a > i; i++) {
        if(sb[j] == sa[i]) {
            j++;
        }
    }
    if(b > j) {
        resultado = 'N';
        return resultado;
    } else {
        resultado = 'S';
        return resultado;
    }
}

int main() {
    int a, b;
    int sa[TAMANHO_MAX], sb[TAMANHO_MAX];
    char resultado;

    scanf("%d %d", &a, &b);

    leDados(sa, sb, a, b);
    resultado = comparaDados(sa, sb, a, b);

    printf("%c", resultado);

    return 0;
}