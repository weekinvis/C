#include <stdio.h>
#include <stdlib.h>

int main() {
    int candidatos, corte;
    int* notas;
    int maiornota;
    int i, in = 0;

    scanf("%d %d", &candidatos, &corte);

    notas = (int*)malloc(candidatos * sizeof(int));

    for(i = 0; candidatos > i; i++) {
        scanf("%d", &notas[i]);
    }

    maiornota = notas[0];

    for(i = 0; candidatos > i; i++) {
        if(notas[i] > maiornota) {
            maiornota = notas[i];
            in = i;
        }
    }

    for(corte; corte > 1; corte--) {
        notas[in] = -1;
        maiornota = -1;
        for(i = 0; candidatos > i; i++) {
            if(notas[i] > maiornota) {
                maiornota = notas[i];
                in = i;
            } else {}
        }
    }
    
    printf("%i", maiornota);
    free(notas);
    return 0;
}
