#include <stdio.h>
#include <stdlib.h>
#include "projeto-arvores.h"

void alocarMassa(int dadosOrdenados, int numElementos, double *tempoAVL, double *tempoLLRB);

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

    for(int i = 0; i < numEmployees; i++) {
        free(employees[i].name);
        free(employees[i].company);
        free(employees[i].department);
    }

    free(employees);
    free(sortedEmployees);
    closeFile(file);

    //
    // ALEX: MENU
    //
    double tempoAVL;
    double tempoLLRB;
    // Ordenados
    alocarMassa(1, numEmployees, &tempoAVL, &tempoLLRB);
    // Desordenados
    alocarMassa(0, numEmployees, &tempoAVL, &tempoLLRB);


    printf("\n\n");
    system("pause");
    return 0;
}

void alocarMassa(int dadosOrdenados, int numElementos, double *tempoAVL, double *tempoLLRB)
{
    int check;
    arvAVL *arvoreAVL = cria_arvAVL();
    arvoreLLRB *arvLLRB = cria_arvoreLLRB();
    char *fileName;

    if(dadosOrdenados == 1)
    {
        fileName = "dadosOrdenados.csv";
    }
    else
    {
        fileName = "testeDados.csv";
    }

    //CAROL: Começar a contabilizar o tempo para AVL

    FILE *file = openFile(fileName);

    Employee *employees = readFile(file, &numElementos);

    for(int i = 0; i < numElementos; i++) {
        check = insere_arvAVL(arvoreAVL, &employees[i]);
        confirmaInsercaoArvoreAVL(check);
    }

    emOrdem_arvAVL(arvoreAVL);

    closeFile(file);

    // CAROL Parar de contabilizar o tempo AVL

    // CAROL Começar contabilizar o tempo LLRB

    file = openFile(fileName);

    for(int i = 0; i < numElementos; i++) {
        check = insere_arvoreLLRB(arvLLRB, &employees[i]);
        confirmaInsercaoArvoreLLRB(check);
    }

    emOrdem_arvoreLLRB(arvLLRB);

    closeFile(file);

    // CAROL Parar de contabilizar o tempo LLRB

    liberar_arvAVL(arvoreAVL);
    liberar_arvoreLLRB(arvLLRB);
}

