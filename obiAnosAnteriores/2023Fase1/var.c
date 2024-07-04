#include <stdio.h>

char verificaVar(int x, int y) {
    char resposta;

    if(x > 8 || -8 > x || y > 8 || 0 > y) {
        resposta = 'N';
        return resposta;
    } else {
        resposta = 'S';
        return resposta;
    }

}

int main() {
    int x, y;
    char resposta;

    scanf("%i %i", &x, &y);

    resposta = verificaVar(x, y);

    printf("%c", resposta);

    return 0;
}