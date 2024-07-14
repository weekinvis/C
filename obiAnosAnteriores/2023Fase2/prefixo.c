#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define barraZero 1

int main(int argc, char** argv) {
    char* p1;
    char* p2;
    int tamanho[2];
    int i, count = 0;
    bool pre = true;

    scanf("%d%*c", &tamanho[0]);
    p1 = (char*)malloc(sizeof(char) * tamanho[0] + barraZero);
    fgets(p1, tamanho[0] + barraZero, stdin);

    scanf("%d%*c", &tamanho[1]);
    p2 = (char*)malloc(sizeof(char) * tamanho[1] + barraZero); 
    fgets(p2, tamanho[1] + barraZero, stdin);

    if(tamanho[0] > tamanho[1]) {
        for(i = 0; tamanho[1] > i; i++) {
            if(p1[i] == p2[i] && pre == true) {
                count++;
            } else {
                pre = false;
            }
        }
    } else {
        for(i = 0; tamanho[0] > i; i++) {
            if(p1[i] == p2[i] && pre == true) {
                count++;
            } else {
                pre = false;
            }
        }
    }

    free(p1);
    free(p2);

    printf("%i", count);
    return 0;
}
