#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "dados.h"
#include "utilDados.h"

#define SUCESSO 0

int main(int argc, char* argv[]) {
    uint8_t* resultados = NULL;
    bool executar = true, erro;
    int qnt, nFacesDado;
    uint8_t scan;

    utilMenuInicial();

    do {

        scan = leDados(&qnt, &nFacesDado);
        erro = utilVerificaErro(scan, qnt, nFacesDado);

        if(erro) {
            continue; // volta para a funcao leDados
        }
        
        resultados = girarDados(qnt, nFacesDado);
        imprimeResultadosDados(resultados);
        liberaResultadosDados(resultados);    

    } while(executar);

    return SUCESSO;
}