#include <stdio.h>
#include <stdlib.h>
#include "projeto-arvores.h"

int main() {
    char *fileName = "testeDados.csv";
    FILE *file = openFile(fileName);
    arvAVL *arvoreAVL = cria_arvAVL();
    arvoreLLRB *arvLLRB = cria_arvoreLLRB();

    int check;

    int numEmployees = 13;
    Employee *employees = readFile(file, &numEmployees);

    for(int i = 0; i < numEmployees; i++) {
        check = insere_arvAVL(arvoreAVL, &employees[i]);
        confirmaInsercaoArvoreAVL(check);
    }

    emOrdem_arvAVL(arvoreAVL);

    for(int i = 0; i < numEmployees; i++) {
        check = insere_arvoreLLRB(arvLLRB, &employees[i]);
        confirmaInsercaoArvoreLLRB(check);
    }

    emOrdem_arvoreLLRB(arvLLRB);

    // Testando
    // printf("Desordenado\n");
    // listEmployees(employees, numEmployees);

    Employee *sortedEmployees = countingSort(employees, numEmployees);

    // Testando
    // printf("\n\nOrdenado\n");
    // listEmployees(sortedEmployees, numEmployees);

    fileName = "dadosOrdenados.csv";
    saveToFile(sortedEmployees, numEmployees, fileName);

    for (int i = 0; i < numEmployees; i++) {
        free(employees[i].name);
        free(employees[i].company);
        free(employees[i].department);
    }

    free(employees);
    free(sortedEmployees);
    closeFile(file);
    liberar_arvAVL(arvoreAVL);
    liberar_arvoreLLRB(arvLLRB);

    printf("\n\n");
    system("pause");
    return 0;
}

