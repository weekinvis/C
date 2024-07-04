#include <stdio.h>

int main() {
    int D, E;

    scanf("%i", &E);
    scanf("%i", &D);

    if(E > D) {
        printf("%i", D + E);
    } else {
        printf("%i", (D - E) * 2);
    }
}