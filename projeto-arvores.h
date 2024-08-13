typedef struct {
    int id;
    char *nome;
    int idade;
    char *empresa;
    char *departamento;
    double salario;
} Funcionario;

FILE* abrirArquivo(char *nomeArquivo);
Funcionario* lerArquivo(FILE *arquivo, int *numFuncionarios);
void listarFuncionarios(Funcionario *funcionarios, int numFuncionarios);
void fecharArquivo(FILE *arquivo);
Funcionario* ordenacaoPorContagem(Funcionario array[], int tamanho);
void salvarEmArquivo(Funcionario array[], int tamanho, char *nomeArquivo);
char* converterFuncionariosParaString(Funcionario array[], int tamanho);

/* FUNÇÕES ARVORE AVL */
struct NO_arvoreAVL{
    Funcionario dados;
    int alt;
    struct NO_arvoreAVL *esq;
    struct NO_arvoreAVL *dir;
};

typedef struct NO_arvoreAVL *arvAVL;
arvAVL *cria_arvAVL();

void rotacaoLL(arvAVL *A);
void rotacaoRR(arvAVL *A);
void rotacaoLR(arvAVL *A);
void rotacaoRL(arvAVL *A);
void liberar_arvAVL(arvAVL *raiz);
int vazia_arvAVL(arvAVL *raiz);
int altura_arvAVL(arvAVL *raiz);
int totalNO_arvAVL(arvAVL * raiz);
int insere_arvAVL(arvAVL *raiz, Funcionario *dados);

/* FUNÇÕES ARVORE RUBRO NEGRA */
struct NO_arvoreLLRB{
    Funcionario dados;
    struct NO_arvoreLLRB *esq;
    struct NO_arvoreLLRB *dir;
    int cor;
};

typedef struct NO_arvoreLLRB* arvoreLLRB;

arvoreLLRB* cria_arvoreLLRB();
void liberar_arvoreLLRB(arvoreLLRB *raiz);
int vazia_arvoreLLRB(arvoreLLRB *raiz);
int altura_arvoreLLRB(arvoreLLRB *raiz);
int totalNO_arvoreLLRB(arvoreLLRB *raiz);
int insere_arvoreLLRB(arvoreLLRB *raiz, Funcionario *dados);
