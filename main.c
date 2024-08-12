#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "projeto-arvores.h"

void exibirMenu() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    printf("Menu:\n");
    printf("Escolha o tipo de arranjo do arquivo .csv para inserir nas arvores:\n");
    printf("1. Arquivo ordenado\n");
    printf("2. Arquivo desordenado\n");
    printf("3. Sair\n");
}

void alocarMassa(int dadosOrdenados, int numElementos, double *tempoAVL, double *tempoLLRB);

int main() {
    double tempoAVL = 0.0;
    double tempoLLRB = 0.0;
    char *fileName = "testeDados.csv";
    FILE *file = openFile(fileName);

    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", fileName);
        return 1;
    }

    int numEmployees = 13;
    Employee *employees = readFile(file, &numEmployees);

    if (employees == NULL) {
        printf("Erro ao ler os dados do arquivo %s\n", fileName);
        closeFile(file);
        return 1;
    }

    Employee *sortedEmployees = countingSort(employees, numEmployees);

    fileName = "dadosOrdenados.csv";
    saveToFile(sortedEmployees, numEmployees, fileName);

    int opcao;

    do {
        exibirMenu();
        while (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Tente novamente: ");
            while (getchar() != '\n'); // Limpar o buffer
        }

        switch (opcao) {
            case 1:
                printf("Voce escolheu a opcao de arquivo ordenado.\n");
                alocarMassa(1, numEmployees, &tempoAVL, &tempoLLRB);
                printf("Tempo AVL: %f segundos\n", tempoAVL);
                printf("Tempo LLRB: %f segundos\n", tempoLLRB);
                #ifdef _WIN32
                    system("pause");
                #else
                    printf("Pressione Enter para continuar...\n");
                    while (getchar() != '\n'); // Limpar o buffer
                    getchar();  // Aguardar o Enter do usuário
                #endif
                break;

            case 2:
                printf("Voce escolheu a opcao de arquivo desordenado.\n");
                alocarMassa(0, numEmployees, &tempoAVL, &tempoLLRB);
                printf("Tempo AVL: %f segundos\n", tempoAVL);
                printf("Tempo LLRB: %f segundos\n", tempoLLRB);
                #ifdef _WIN32
                    system("pause");
                #else
                    printf("Pressione Enter para continuar...\n");
                    while (getchar() != '\n'); // Limpar o buffer
                    getchar();  // Aguardar o Enter do usuário
                #endif
                break;

            case 3:
                printf("Saindo...\n");
                #ifdef _WIN32
                    system("pause");
                #else
                    printf("Pressione Enter para sair...\n");
                    while (getchar() != '\n'); // Limpar o buffer
                    getchar();  // Aguardar o Enter do usuário
                #endif
                break;

            default:
                printf("Opção inválida.\n");
                break;
        }
    } while (opcao != 3);

    for(int i = 0; i < numEmployees; i++) {
        free(employees[i].name);
        free(employees[i].company);
        free(employees[i].department);
    }

    free(employees);
    free(sortedEmployees);
    closeFile(file);

    printf("\n\n");
    return 0;
}

void alocarMassa(int dadosOrdenados, int numElementos, double *tempoAVL, double *tempoLLRB) {
    int check;
    arvAVL *arvoreAVL = cria_arvAVL();
    arvoreLLRB *arvLLRB = cria_arvoreLLRB();
    char *fileName;

    if(dadosOrdenados == 1) {
        fileName = "dadosOrdenados.csv";
    } else {
        fileName = "testeDados.csv";
    }

    clock_t startAVL = clock();

    FILE *file = openFile(fileName);

    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", fileName);
        liberar_arvAVL(arvoreAVL);
        liberar_arvoreLLRB(arvLLRB);
        return;
    }

    Employee *employees = readFile(file, &numElementos);

    if (employees == NULL) {
        printf("Erro ao ler os dados do arquivo %s\n", fileName);
        closeFile(file);
        liberar_arvAVL(arvoreAVL);
        liberar_arvoreLLRB(arvLLRB);
        return;
    }

    for(int i = 0; i < numElementos; i++) {
        check = insere_arvAVL(arvoreAVL, &employees[i]);
    }

    closeFile(file);

    clock_t endAVL = clock();
    *tempoAVL = (double)(endAVL - startAVL) / CLOCKS_PER_SEC;

    clock_t startLLRB = clock();

    file = openFile(fileName);

    if (file == NULL) {
        printf("Erro ao abrir o arquivo %s\n", fileName);
        liberar_arvAVL(arvoreAVL);
        liberar_arvoreLLRB(arvLLRB);
        return;
    }

    for(int i = 0; i < numElementos; i++) {
        check = insere_arvoreLLRB(arvLLRB, &employees[i]);
    }

    closeFile(file);

    clock_t endLLRB = clock();
    *tempoLLRB = (double)(endLLRB - startLLRB) / CLOCKS_PER_SEC;

    liberar_arvAVL(arvoreAVL);
    liberar_arvoreLLRB(arvLLRB);
}
