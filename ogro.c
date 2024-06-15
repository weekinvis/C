#include <stdio.h>

int main() {
    int D, E, res;

    scanf("%i", &E);
    scanf("%i", &D);

    if(E > D) {
        res = D + E;
        printf("%i", res);
    } else {
        res = D - E;
        res *= 2;
        printf("%i", res);
    }
}