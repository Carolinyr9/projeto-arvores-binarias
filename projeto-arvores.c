#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projeto-arvores.h"

FILE* abrirArquivo(char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        system("pause");
        exit(1);
    }
    return arquivo;
}

Funcionario* lerArquivo(FILE *arquivo, int *numFuncionarios) {
    size_t capacidade = 14999;
    *numFuncionarios = 0;
    Funcionario *funcionarios = malloc(capacidade * sizeof(Funcionario));
    if (!funcionarios) {
        perror("Erro de alocação de memória\n");
        exit(1);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        if (*numFuncionarios >= capacidade) {
            capacidade *= 2;
            funcionarios = realloc(funcionarios, capacidade * sizeof(Funcionario));
            if (!funcionarios) {
                perror("Erro de alocação de memória\n");
                exit(1);
            }
        }

        Funcionario funcionario;
        funcionario.id = atoi(strtok(buffer, ";"));
        funcionario.nome = strdup(strtok(NULL, ";"));
        funcionario.idade = atoi(strtok(NULL, ";"));
        funcionario.empresa = strdup(strtok(NULL, ";"));
        funcionario.departamento = strdup(strtok(NULL, ";"));
        funcionario.salario = atof(strtok(NULL, "\n"));

        funcionarios[*numFuncionarios] = funcionario;
        (*numFuncionarios)++;
    }

    return funcionarios;
}

void listarFuncionarios(Funcionario *funcionarios, int numFuncionarios) {
    for (int i = 0; i < numFuncionarios; i++) {
        printf("ID: %d, Nome: %s, Idade: %d, Empresa: %s, Departamento: %s, Salário: %.2f\n",
               funcionarios[i].id, funcionarios[i].nome, funcionarios[i].idade,
               funcionarios[i].empresa, funcionarios[i].departamento, funcionarios[i].salario);
    }
}

void fecharArquivo(FILE *arquivo) {
    fclose(arquivo);
}

Funcionario* ordenacaoPorContagem(Funcionario array[], int tamanho) {
    if (tamanho <= 0) return NULL;

    int valorMaximo = array[0].id;
    for (int i = 1; i < tamanho; i++) {
        if (array[i].id > valorMaximo) {
            valorMaximo = array[i].id;
        }
    }

    int *contagem = (int *)calloc(valorMaximo + 1, sizeof(int));
    Funcionario *saida = (Funcionario *)malloc(tamanho * sizeof(Funcionario));

    for (int i = 0; i < tamanho; i++) {
        contagem[array[i].id]++;
    }

    for (int i = 1; i <= valorMaximo; i++) {
        contagem[i] += contagem[i - 1];
    }

    for (int i = tamanho - 1; i >= 0; i--) {
        saida[contagem[array[i].id] - 1] = array[i];
        contagem[array[i].id]--;
    }

    free(contagem);
    return saida;
}

void salvarEmArquivo(Funcionario array[], int tamanho, char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para gravação!\n");
        system("pause");
        exit(1);
    }

    char *dados = converterFuncionariosParaString(array, tamanho);
    fputs(dados, arquivo);

    fclose(arquivo);
    free(dados);
}

char* converterFuncionariosParaString(Funcionario array[], int tamanho) {
    char* linha = malloc(1024 * tamanho);
    if (linha == NULL) {
        perror("Falha na alocação de memória");
        exit(EXIT_FAILURE);
    }
    linha[0] = '\0';

    char temp[300];
    for (int i = 0; i < tamanho; i++) {
        sprintf(temp, "%d", array[i].id);
        strcat(linha, temp);
        strcat(linha, ",");

        strcat(linha, array[i].nome);
        strcat(linha, ",");

        sprintf(temp, "%d", array[i].idade);
        strcat(linha, temp);
        strcat(linha, ",");

        strcat(linha, array[i].empresa);
        strcat(linha, ",");

        strcat(linha, array[i].departamento);
        strcat(linha, ",");

        sprintf(temp, "%.2f", array[i].salario);
        strcat(linha, temp);
        strcat(linha, "\n");
    }

    return linha;
}
