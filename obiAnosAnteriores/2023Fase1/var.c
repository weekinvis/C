#include <stdio.h>
#include <stdbool.h>

bool verificaVar(int x, int y) {
    char resposta;

    if(x > 8 || -8 > x || y > 8 || 0 > y) {
        return false;
    } else {
        return true;
    }

}

int main() {
    int x, y;
    bool resposta;

    scanf("%i %i", &x, &y);

    resposta = verificaVar(x, y);

    if(resposta) {
        printf("S");
    } else {
        printf("N");
    }

    return 0;
}
