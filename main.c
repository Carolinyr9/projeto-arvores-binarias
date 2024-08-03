#include <stdio.h>
#include <stdlib.h>
#include "projeto-arvores.h"

int main() {
    char *fileName = "testeDados.csv";
    FILE *file = openFile(fileName);
    arvAVL *arvoreAVL = cria_arvAVL();
    int check;

    int numEmployees = 13;
    Employee *employees = readFile(file, &numEmployees);

    for(int i = 0; i < sizeof(employees);i++){
        check = insere_arvAVL(arvoreAVL, employees);
        confirmaInsercao(check);
    }

    // Testando
    // printf("Desordenado\n");
    // listEmployees(employees, numEmployees);

    Employee *sortedEmployees = countingSort(employees, numEmployees);

    // Testando
    // printf("\n\nOrdenado\n");
    // listEmployees(sortedEmployees, numEmployees);

    fileName = "dadosOrdenados.csv";
    saveToFile(sortedEmployees, numEmployees, fileName);

    free(employees);
    free(sortedEmployees);
    closeFile(file);

    return 0;
}

