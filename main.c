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
    char *nomeArquivo = "massaDados.csv";
    FILE *arquivo = abrirArquivo(nomeArquivo);

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return 1;
    }

    int numFuncionarios = 14999;
    Funcionario *funcionarios = lerArquivo(arquivo, &numFuncionarios);

    if (funcionarios == NULL) {
        printf("Erro ao ler os dados do arquivo %s\n", nomeArquivo);
        fecharArquivo(arquivo);
        return 1;
    }

    Funcionario *funcionariosOrdenados = ordenacaoPorContagem(funcionarios, numFuncionarios);

    nomeArquivo = "dadosOrdenados.csv";
    salvarEmArquivo(funcionariosOrdenados, numFuncionarios, nomeArquivo);

    int opcao;

    do {
        exibirMenu();
        while (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Tente novamente: ");
            while (getchar() != '\n');
        }

        switch (opcao) {
            case 1:
                printf("Voce escolheu a opcao de arquivo ordenado.\n");
                alocarMassa(1, numFuncionarios, &tempoAVL, &tempoLLRB);
                printf("Tempo AVL: %f microsegundos\n", tempoAVL);
                printf("Tempo LLRB: %f microsegundos\n", tempoLLRB);
                #ifdef _WIN32
                    system("pause");
                #else
                    printf("Pressione Enter para continuar...\n");
                    while (getchar() != '\n');
                    getchar();
                #endif
                break;

            case 2:
                printf("Voce escolheu a opcao de arquivo desordenado.\n");
                alocarMassa(0, numFuncionarios, &tempoAVL, &tempoLLRB);
                printf("Tempo AVL: %f microsegundos\n", tempoAVL);
                printf("Tempo LLRB: %f microsegundos\n", tempoLLRB);
                #ifdef _WIN32
                    system("pause");
                #else
                    printf("Pressione Enter para continuar...\n");
                    while (getchar() != '\n');
                    getchar();
                #endif
                break;

            case 3:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção invalida.\n");
                break;
        }
    } while (opcao != 3);

    for(int i = 0; i < numFuncionarios; i++) {
        free(funcionarios[i].nome);
        free(funcionarios[i].empresa);
        free(funcionarios[i].departamento);
    }

    free(funcionarios);
    free(funcionariosOrdenados);
    fecharArquivo(arquivo);

    printf("\n\n");
    return 0;
}

void alocarMassa(int dadosOrdenados, int numElementos, double *tempoAVL, double *tempoLLRB) {
    int check;
    arvAVL *arvoreAVL = cria_arvAVL();
    arvoreLLRB *arvLLRB = cria_arvoreLLRB();
    char *nomeArquivo;

    if(dadosOrdenados == 1) {
        nomeArquivo = "dadosOrdenados.csv";
    } else {
        nomeArquivo = "massaDados.csv";
    }

    clock_t inicioAVL = clock();

    FILE *arquivo = abrirArquivo(nomeArquivo);

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        liberar_arvAVL(arvoreAVL);
        liberar_arvoreLLRB(arvLLRB);
        return;
    }

    Funcionario *funcionarios = lerArquivo(arquivo, &numElementos);

    if (funcionarios == NULL) {
        printf("Erro ao ler os dados do arquivo %s\n", nomeArquivo);
        fecharArquivo(arquivo);
        liberar_arvAVL(arvoreAVL);
        liberar_arvoreLLRB(arvLLRB);
        return;
    }

    for(int i = 0; i < numElementos; i++) {
        check = insere_arvAVL(arvoreAVL, &funcionarios[i]);
    }

    fecharArquivo(arquivo);

    clock_t fimAVL = clock();
    *tempoAVL = (double)(fimAVL - inicioAVL) / CLOCKS_PER_SEC * 1000000;

    clock_t inicioLLRB = clock();

    arquivo = abrirArquivo(nomeArquivo);

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        liberar_arvAVL(arvoreAVL);
        liberar_arvoreLLRB(arvLLRB);
        return;
    }

    for(int i = 0; i < numElementos; i++) {
        check = insere_arvoreLLRB(arvLLRB, &funcionarios[i]);
    }

    fecharArquivo(arquivo);

    clock_t fimLLRB = clock();
    *tempoLLRB = (double)(fimLLRB - inicioLLRB) / CLOCKS_PER_SEC * 1000000;

    liberar_arvAVL(arvoreAVL);
    liberar_arvoreLLRB(arvLLRB);
}
