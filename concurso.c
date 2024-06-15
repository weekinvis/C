#include <stdio.h>

int main() {

    int n, k;
    int nota[500], maiornota;
    int i, in;

    // le os participantes e a quantidade de aprovados
    scanf("%i %i", &n, &k);

    // le todas as notas
    for(i = 0; n > i; i++) {    
        scanf("%i", &nota[i]);
    }
    maiornota = nota[0];

    // encontra a maior nota
    // evita que, caso a quantidade de aprovados seja 1, nao imprima a maior nota
    for(i = 0; n > i; i++) {
        if(nota[i] > maiornota) {
            maiornota = nota[i];
            in = i;
        }
    }
    
    // ate a quantidade de aprovados for igual a 1
    for(k; k > 1; k--) {
        // destroi a maior nota e encontra a enesima maior nota
        nota[in] = -1;
        maiornota = -1;
        for(i = 0; n > i; i++) {
            if(nota[i] > maiornota) {
                maiornota = nota[i];
                in = i;
            }
        }
    } 
     
    // a enesima maior nota eh igual a nota de corte
    // imprime a nota de corte
    printf("%i", maiornota);
}