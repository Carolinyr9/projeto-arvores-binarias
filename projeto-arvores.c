#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct funcionario {
    int id;
    char *nome;
    int idade;
    char *departamento;
    float salario;
} Funcionario;

FILE* abrirArquivo(char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("\n\tErro ao abrir o arquivo!\n");
        system("pause");
        exit(1);
    }
    return file;
}

Funcionario* lerArquivo(FILE *file, int *numFuncionarios) {
    size_t capacidade = 13;
    *numFuncionarios = 0;
    Funcionario *funcionarios = malloc(capacidade * sizeof(Funcionario));
    if (!funcionarios) {
        perror("Erro ao alocar memória");
        exit(1);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        if (*numFuncionarios >= capacidade) {
            capacidade *= 2;
            funcionarios = realloc(funcionarios, capacidade * sizeof(Funcionario));
            if (!funcionarios) {
                perror("Erro ao realocar memória");
                exit(1);
            }
        }

        Funcionario funcionario;
        funcionario.id = atoi(strtok(buffer, ","));
        funcionario.nome = strdup(strtok(NULL, ","));
        funcionario.idade = atoi(strtok(NULL, ","));
        funcionario.departamento = strdup(strtok(NULL, ","));
        funcionario.salario = atof(strtok(NULL, "\n"));

        funcionarios[*numFuncionarios] = funcionario;
        (*numFuncionarios)++;
    }

    return funcionarios;
}

//FUNÇÃO DE TESTE PARA VER SE OS FUNCIONÁRIOS ESTÃO SENDO PEGOS CORRETAMENTE
void listaFuncionarios(Funcionario *funcionarios, int numFuncionarios) {
    for (int i = 0; i < numFuncionarios; i++) { // Correção: i < numFuncionarios
        printf("ID: %d, Nome: %s, Idade: %d, Departamento: %s, Salário: %.2f\n",
               funcionarios[i].id, funcionarios[i].nome, funcionarios[i].idade,
               funcionarios[i].departamento, funcionarios[i].salario);
    }
}

void fecharArquivo(FILE *file) {
    fclose(file);
}

// Função do couting sort
Funcionario* countingSort(Funcionario array[], int size) {
    if (size <= 0) return NULL;

    int maxVal = array[0].id;
    for (int i = 1; i < size; i++) {
        if (array[i].id > maxVal) {
            maxVal = array[i].id;
        }
    }

    int *count = (int *)calloc(maxVal + 1, sizeof(int));
    Funcionario *output = (Funcionario *)malloc(size * sizeof(Funcionario));

    for (int i = 0; i < size; i++) {
        count[array[i].id]++;
    }

    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[array[i].id] - 1] = array[i];
        count[array[i].id]--;
    }

    free(count);
    return output;
}

void gravarNoArquivo(Funcionario array[], int size){
    FILE *file;
    file = fopen("dadosOrdenados.csv", "w");
    if(file == NULL){
        printf("Erro ao abrir funcs.bin!\n");
        system("pause");
        exit(1);
    }

    char *linha;
    for(int i = 0; i < size; i++){ // A FAZER AINDA
        linha = strcat((char)array.id, ',');
        strcat(array.nome, ',');
        strcat((char)array.idade, ',');
        strcat(array.departamento, ',');
        strcat((char)array.salario, ',');

    }

    texto = fwrite(funcs, sizeof(FUNC), 5, file);
}
