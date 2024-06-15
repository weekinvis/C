#include <stdio.h>
#define SUCESS 0

int main(int agrc , char ** agrv) {
    
    int number, step;
    printf("Insert the number:");
    scanf("%i", &number);

    while(number > 1) {
        
        if(number % 2 == 0) {
            number /= 2;
            step += 1;
            printf("The result of step n%i is %i\n", step, number);
    }   else {
            number *= 3, number += 1;
            step += 1;
            printf("The result of step n%i is %i\n", step, number);
        } 
    }
    printf("Sucess\n");
    return SUCESS;
}
