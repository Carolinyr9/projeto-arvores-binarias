typedef struct NO *arvAVL;

arvAVL *cria_arvAVL();
void rotacaoLL(arvAVL *A);
void rotacaoRR(arvAVL *A);
void rotacaoLR(arvAVL *A);
void rotacaoRL(arvAVL *A);
void liberar_arvAVL(arvAVL *raiz);
int vazia_arvAVL(arvAVL *raiz);
int altura_arvAVL(arvAVL *raiz);
int totalNO_arvAVL(arvAVL * raiz);
void preOrdem_arvAVL(arvAVL *raiz);
void emOrdem_arvAVL(arvAVL *raiz);
void posOrdem_arvAVL(arvAVL *raiz);
void confirmaInsercao(int x);
int insere_arvAVL(arvAVL *raiz, Employee dados);
int remove_arvAVL(arvAVL *raiz, int valor);
int consulta_arvAVL(arvAVL *raiz, int valor);
