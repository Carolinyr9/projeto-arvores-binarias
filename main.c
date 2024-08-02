#include <stdio.h>
#include <stdlib.h>
#include "projeto-arvores.h"

int main() {
    char *fileName = "testeDados.csv";
    FILE *file = openFile(fileName);

    int numEmployees = 13;
    Employee *employees = readFile(file, &numEmployees);

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

