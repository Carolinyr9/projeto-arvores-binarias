#include <stdio.h>
#include <stdlib.h>
#include "projeto-arvores.h"

int main() {
    char nomeArquivo[] = "testeDados.csv";
    FILE *file = abrirArquivo(nomeArquivo);

    int numFuncionarios;
    Funcionario *funcionarios = lerArquivo(file, &numFuncionarios);

    printf("Sem ordenar\n");
    listaFuncionarios(funcionarios, 13);

    Funcionario *sortedFuncionarios = countingSort(funcionarios, numFuncionarios);

    printf("\n\nOrdenado\n");
    listaFuncionarios(sortedFuncionarios, 13);

    free(funcionarios);
    fecharArquivo(file);

    return 0;
}
