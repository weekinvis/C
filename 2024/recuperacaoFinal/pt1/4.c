#include <stdio.h>

#define SUCESSO 0
#define PI 3.1415

double calculaVolume() {
    double valorLado;
    printf("Digite o lado do cubo: ");
    scanf("%lf", &valorLado);

    if(0 > valorLado) {
        printf("Digite um valor valido!\n");
        return 0.0;
    }

    return (valorLado * valorLado * valorLado);
}

double calculaArea() {
    double base, altura;
    printf("Digite o valor da base: ");
    scanf("%lf", &base);
    printf("Digite o valor da altura: ");
    scanf("%lf", &altura);


    if(0 > altura || 0 > base) {
        printf("Digite um valor valido!\n");
        return 0.0;
    }

    return base * altura;
}

double calculaPerim() {
    double raio;
    printf("Digite o raio da sua circunferencia: ");
    scanf("%lf", &raio);
    
    
    if(0 > raio) {
        printf("Digite um valor valido!\n");
        return 0.0;
    }

    return (raio * PI * 2);

}

int main(int argc, char** argv) {
    int opcao;
    double resultado;

    do {
        printf("1 - Calcular volume de um cubo\n2 - Calcular a area de um retangulo\n3 - Calcular o perimetro de um circulo\n4 - Sair\nOpcao: ");
        (void)scanf("%d%*c", &opcao);

        switch (opcao) {
        case 1:
            resultado = calculaVolume();
            if(resultado == 0.0) {
                break;
            }
            printf("%.2lf unidades cubicas\n", resultado);
            break;
        case 2:
            resultado = calculaArea();
            if(resultado == 0.0) {
                break;
            }
            printf("A area do seu retangulo eh de %.2lf unidades quadradas\n", resultado);
            break;
        case 3:
            resultado = calculaPerim();
            if(resultado == 0.0) {
                break;
            }
            printf("A circunferencia da sua esfera possui %.2lf unidades\n", resultado);
            break;
        case 4:
            break;
        default:
            break;
        
        }

    } while(opcao != 4);

    return SUCESSO;

}