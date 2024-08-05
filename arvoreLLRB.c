#include <stdio.h>
#include <stdlib.h>
#include "projeto-arvores.h"

#define RED 1
#define BLACK 0

struct NO_arvoreLLRB *removeNO(struct NO_arvoreLLRB *H, int valor);
struct NO_arvoreLLRB *insereNO(struct NO_arvoreLLRB *H, Employee *dados, int *resp);

int cor(struct NO_arvoreLLRB *H){
    if(H == NULL){
        return BLACK;
    }else{
        return H->cor;
    }
}

void trocaCor(struct NO_arvoreLLRB *H){
    H->cor = !H->cor;
    if(H->esq != NULL){
        H->esq->cor = !H->esq->cor;
    }
    if(H->dir != NULL){
        H->dir->cor = !H->dir->cor;
    }
}

struct NO_arvoreLLRB *rotacionaEsquerda(struct NO_arvoreLLRB *A){
    struct NO_arvoreLLRB *B = A->dir;
    A->dir = B->esq;
    B->esq = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
};

struct NO_arvoreLLRB *rotacionaDireita(struct NO_arvoreLLRB *A){
    struct NO_arvoreLLRB *B = A->esq;
    A->esq = B->dir;
    B->dir = A;
    B->cor = A->cor;
    A->cor = RED;
    return B;
};

struct NO_arvoreLLRB *move2EsqRED(struct NO_arvoreLLRB *H){
    trocaCor(H);
    if(cor(H->dir->esq) == RED){
        H->dir = rotacionaDireita(H->dir);
        H = rotacionaEsquerda(H);
        trocaCor(H);
    }
    return H;
};

struct NO_arvoreLLRB *move2DirRED(struct NO_arvoreLLRB *H){
    trocaCor(H);
    if(cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
        trocaCor(H);
    }
    return H;
};

struct NO_arvoreLLRB *balancear(struct NO_arvoreLLRB *H){
    if(cor(H->dir) == RED){
        H = rotacionaEsquerda(H);
    }
    if(H->esq != NULL && cor(H->dir) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }
    return H;
};

arvoreLLRB *cria_arvoreLLRB(){
    arvoreLLRB *raiz = (arvoreLLRB*) malloc(sizeof(arvoreLLRB));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

void libera_NO_arvoreLLRB(struct NO_arvoreLLRB *no){
    if(no == NULL){
        return;
    }
    libera_NO_arvoreLLRB(no->esq);
    libera_NO_arvoreLLRB(no->dir);
    free(no);
    no = NULL;
}

void liberar_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return;
    }
    libera_NO_arvoreLLRB(*raiz);
    free(raiz);
}

int vazia_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return 1;
    }
    if(*raiz == NULL){
        return 1;
    }
    return 0;
}

int altura_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = altura_arvoreLLRB(&((*raiz)->esq));
    int alt_dir = altura_arvoreLLRB(&((*raiz)->dir));
    if(alt_esq > alt_dir){
        return(alt_esq + 1);
    }else{
        return(alt_dir + 1);
    }
}

int totalNO_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = altura_arvoreLLRB(&((*raiz)->esq));
    int alt_dir = altura_arvoreLLRB(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

void emOrdem_arvoreLLRB(arvoreLLRB *raiz){
    if(raiz == NULL || *raiz == NULL){
        return;
    }
    emOrdem_arvoreLLRB(&((*raiz)->esq));
    printf("%d\n", (*raiz)->dados.id);
    printf("%s\n", (*raiz)->dados.name);
    printf("%d\n", (*raiz)->dados.age);
    printf("%s\n", (*raiz)->dados.company);
    printf("%s\n", (*raiz)->dados.department);
    printf("%.2f\n\n", (*raiz)->dados.salary);
    emOrdem_arvoreLLRB(&((*raiz)->dir));
}

/*consulta_arvoreLLRB(arvoreLLRB *raiz, int valor){
    if(raiz == NULL){
        return 0;
    }
    struct NO_arvoreLLRB *atual = *raiz;
    while(atual != NULL){
        if(valor == atual->dados){
            return 1;
        }
        if(valor > atual->dados){
            atual = atual->dir;
        }else{
            atual = atual->esq;
        }
    }
    return 0;
}*/

int insere_arvoreLLRB(arvoreLLRB *raiz, Employee *dados){
    int resp;
    *raiz = insereNO(*raiz, dados, &resp);  // Corrigido aqui
    if((*raiz) != NULL){
        (*raiz)->cor = BLACK;
    }
    return resp;
}

struct NO_arvoreLLRB *insereNO(struct NO_arvoreLLRB *H, Employee *dados, int *resp){
    if(H == NULL){
        struct NO_arvoreLLRB *novo;
        novo = (struct NO_arvoreLLRB*) malloc(sizeof(struct NO_arvoreLLRB));
        if(novo == NULL){
            *resp = 0;
            return NULL;
        }
        novo->dados = *dados;
        novo->cor = RED;
        novo->dir = NULL;
        novo->esq = NULL;
        *resp = 1;
        return novo;
    }
    if(dados->id == H->dados.id){
        *resp = 0;
    } else {
        if(dados->id < H->dados.id){
            H->esq = insereNO(H->esq, dados, resp);
        } else {
            H->dir = insereNO(H->dir, dados, resp);
        }
    }
    if(cor(H->dir) == RED && cor(H->esq) == BLACK){
        H = rotacionaEsquerda(H);
    }
    if(cor(H->esq) == RED && cor(H->esq->esq) == RED){
        H = rotacionaDireita(H);
    }
    if(cor(H->esq) == RED && cor(H->dir) == RED){
        trocaCor(H);
    }
    return H;
}

void confirmaInsercaoArvoreLLRB(int x){
    if(x){
        printf("Elemento inserido com sucesso na arvore rubro negra. \n");
    }else{
        printf("Erro! Elemento nao inserido na arvore rubro negra. \n");
    }
}

/*int remove_arvoreLLRB(arvoreLLRB *raiz, int valor){
    if(consulta_arvoreLLRB(raiz, valor)){
        struct NO_arvoreLLRB *H = *raiz;
        *raiz = removeNO(H, valor);
        if(*raiz != NULL){
            (*raiz)->cor = BLACK;
        }
        return 1;
    }else{
        return 0;
    }
}*/


struct NO_arvoreLLRB *removeMenor(struct NO_arvoreLLRB *H){
    if(H->esq == NULL){
        free(H);
        return NULL;
    }
    if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK){
        H = move2EsqRED(H);
    }
    H->esq = removeMenor(H->esq);
    return balancear(H);
};

struct NO_arvoreLLRB *procuraMenor(struct NO_arvoreLLRB *atual){
    struct NO_arvoreLLRB *no1 = atual;
    struct NO_arvoreLLRB *no2 = atual->esq;
    while(no2 != NULL){
        no1 = no2;
        no2 = no2->esq;
    }
    return no1;
};

/*struct NO_arvoreLLRB *removeNO(struct NO_arvoreLLRB *H, int valor){
    if(valor < H->dados){
        if(cor(H->esq) == BLACK && cor(H->esq->esq) == BLACK){
            H = move2EsqRED(H);
        }
        H->esq = removeNO(H->esq, valor);
    }else{
        if(cor(H->esq) == RED){
            H = rotacionaDireita(H);
        }
        if(valor == H->dados && (H->dir == NULL)){
            free(H);
            return NULL;
        }
        if(cor(H->dir) == BLACK && cor(H->dir->esq) == BLACK){
            H = move2DirRED(H);
        }
        if(valor == H->dados){
            struct NO_arvoreLLRB *x = procuraMenor(H->dir);
            H->dados = x->dados;
            H->dir = removeMenor(H->dir);
        }else{
            H->dir = removeNO(H->dir, valor);
        }
    }
    return balancear(H);
};*/
