
typedef struct funcionario Funcionario;

FILE* abrirArquivo(char *nomeArquivo);
Funcionario* lerArquivo(FILE *file, int *numFuncionarios);
void fecharArquivo(FILE *file);
void listaFuncionarios(Funcionario *funcionarios, int numFuncionarios);
Funcionario* countingSort(Funcionario array[], int size);
