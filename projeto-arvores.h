
typedef struct {
    int id;
    char *name;
    int age;
    char *company;
    char *department;
    double salary;
} Employee;

FILE* openFile(char *fileName); // PROBLEMAS AQUI AINDA

Employee* readFile(FILE *file, int *numEmployees);

void listEmployees(Employee *employees, int numEmployees);

void closeFile(FILE *file);

Employee* countingSort(Employee array[], int size);

void saveToFile(Employee array[], int size, char *fileName);

char* convertEmployeesToString(Employee array[], int size);

/* FUNÇÕES ARVORE AVL */

struct NO_arvoreAVL{
    Employee dados;
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

void emOrdem_arvAVL(arvAVL *raiz);

void confirmaInsercaoArvoreAVL(int x);

int insere_arvAVL(arvAVL *raiz, Employee *dados);

/* FUNÇÕES ARVORE RUBRO NEGRA */

struct NO_arvoreLLRB{
    Employee dados;
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

void emOrdem_arvoreLLRB(arvoreLLRB *raiz);

int insere_arvoreLLRB(arvoreLLRB *raiz, Employee *dados);

void confirmaInsercaoArvoreLLRB(int x);
