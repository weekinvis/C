#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    int* sA;
    int* sB;
    int sizeA, sizeB;
    int i, j = 0;

    scanf("%d %d", &sizeA, &sizeB);
    sA = (int*)malloc(sizeof(int) * sizeA);
    sB = (int*)malloc(sizeof(int) * sizeB);

    for(i = 0; sizeA > i; i++) {
        scanf("%d", &sA[i]);
    }
    for(i = 0; sizeB > i; i++) {
        scanf("%d", &sB[i]);
    }

    for(i = 0; sizeA > i; i++) {
        if(sA[i] == sB[j]) {
            j++;
        } else {}
    }

    if(j == sizeB) {
        printf("S");
    } else {
        printf("N");
    }

    free(sA);
    free(sB);
    return 0;
}
