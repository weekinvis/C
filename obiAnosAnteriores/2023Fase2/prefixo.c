#include <stdio.h>
#define MAX_PALAVRA 1000

int comparaStrings(char p1[], char p2[], int a, int b) {
    int i;
    int contador = 0;
    
    if(a > b) {
        for(i = 0; b > i; i++) {
            if(p1[i] == p2[i]) {
                contador++;
            } else {
                i = b;
            }
        }
    } else {
        for(i = 0; a > i; i++) {
            if(p1[i] == p2[i]) {
                contador++;
            } else {
                i = a;
            }
        }
    }
    return contador;
}

int main() {
    char p1[MAX_PALAVRA];
    char p2[MAX_PALAVRA];
    int a, b;
    int resultado;
    
    scanf("%i%*c", &a);
    fgets(p1, MAX_PALAVRA, stdin);
    scanf("%i%*c", &b);
    fgets(p2, MAX_PALAVRA, stdin);
    
    resultado = comparaStrings(p1, p2, a, b);
    
    printf("%i", resultado);
    
    return 0;
    
}
