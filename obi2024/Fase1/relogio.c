#include <stdio.h>

int main() {
    int H, M, S, T;

    scanf("%i %i %i %i", &H, &M, &S, &T);

    S += T;

    while(S >= 60) {
        M += 1;
        S -= 60;
    }
    while(M >= 60) {
        H += 1;
        M -= 60;
    }
    while(H >= 24) {
        H -= 24;
    }
    printf("%i\n%i\n%i", H, M, S);
    return 0;
}
