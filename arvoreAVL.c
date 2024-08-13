#include <stdio.h>
#include <stdlib.h>
#include "projeto-arvores.h"

arvAVL *cria_arvAVL(){
    arvAVL *raiz = (arvAVL*) malloc(sizeof(arvAVL));
    if(raiz != NULL){
        *raiz = NULL;
    }
    return raiz;
}

int alt_no(struct NO_arvoreAVL *no){
    if(no == NULL){
        return -1;
    }else{
        return no->alt;
    }
}

int maior(int x, int y){
    if(x > y){
        return(x);
    }else{
        return(y);
    }
}

int fatorBalanceamento_NO(struct NO_arvoreAVL *no){
    return abs(alt_no(no->esq) - alt_no(no->dir));
}

void rotacaoLL(arvAVL *A){
    struct NO_arvoreAVL *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->alt = maior(alt_no((*A)->esq), alt_no((*A)->dir)) + 1;
    B->alt = maior(alt_no(B->esq), (*A)->alt) + 1;
    *A = B;
}

void rotacaoRR(arvAVL *A){
    struct NO_arvoreAVL *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = *A;
    (*A)->alt = maior(alt_no((*A)->esq), alt_no((*A)->dir)) + 1;
    B->alt = maior(alt_no(B->dir), (*A)->alt) + 1;
    *A = B;
}

void rotacaoLR(arvAVL *A){
    rotacaoRR(&(*A)->esq);
    rotacaoLL(A);
}

void rotacaoRL(arvAVL *A){
    rotacaoLL(&(*A)->dir);
    rotacaoRR(A);
}

void libera_NO(struct NO_arvoreAVL *no){
    if(no == NULL){
        return;
    }
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void liberar_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return;
    }
    libera_NO(*raiz);
    free(raiz);
}

int altura_arvAVL(arvAVL *raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = altura_arvAVL(&((*raiz)->esq));
    int alt_dir = altura_arvAVL(&((*raiz)->dir));
    if(alt_esq > alt_dir){
        return(alt_esq + 1);
    }else{
        return(alt_dir + 1);
    }
}

int totalNO_arvAVL(arvAVL * raiz){
    if(raiz == NULL){
        return 0;
    }
    if(*raiz == NULL){
        return 0;
    }
    int alt_esq = altura_arvAVL(&((*raiz)->esq));
    int alt_dir = altura_arvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int insere_arvAVL(arvAVL *raiz, Employee *employee){
    int res;
    if (*raiz == NULL) {
        struct NO_arvoreAVL *novo;
        novo = (struct NO_arvoreAVL*) malloc(sizeof(struct NO_arvoreAVL));
        if (novo == NULL) {
            return 0;
        }
        novo->dados = *employee;
        novo->alt = 0;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }
    struct NO_arvoreAVL *atual = *raiz;
    if (employee->id < atual->dados.id) {
        if ((res = insere_arvAVL(&(atual->esq), employee)) == 1) {
            if (fatorBalanceamento_NO(atual) >= 2) {
                if (employee->id < (*raiz)->esq->dados.id) {
                    rotacaoLL(raiz);
                } else {
                    rotacaoLR(raiz);
                }
            }
        }
    } else if (employee->id > atual->dados.id) {
        if ((res = insere_arvAVL(&(atual->dir), employee)) == 1) {
            if (fatorBalanceamento_NO(atual) >= 2) {
                if ((*raiz)->dir->dados.id < employee->id) {
                    rotacaoRR(raiz);
                } else {
                    rotacaoRL(raiz);
                }
            }
        }
    } else {
        printf("Elemento %d ja existe. Insercao duplicada! \n", employee->id);
        return 0;
    }
    atual->alt = maior(alt_no(atual->esq), alt_no(atual->dir)) + 1;
    return res;
}
