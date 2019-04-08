#include "avl.h"
#include <stdio.h>
#include <stdlib.h>




no * inserir (no* raiz, tipo_dado elemento, int *cresceu){
    if(raiz == NULL) {
        no *novo = (no *) malloc(sizeof(struct no));
        novo->valor = elemento;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->fb = 0;
        *cresceu = 1;
        return novo;
    } else {
           if(elemento > raiz->valor) {
                raiz->dir = inserir(raiz->dir, elemento, cresceu);
                if(*cresceu) {
                       switch(raiz->fb) {
                            case -1:
                                 raiz->fb = 0;
                                 *cresceu = 0;
                                 break;
                            case 0:
                                raiz->fb = 1;
                                 *cresceu = 1;
                                 break;
                            case 1:
                                raiz->fb = 2;
                                *cresceu = 0;
                                return rotacionar(raiz);
                                break;
                       }
                }
           } else {
                raiz->esq = inserir(raiz->esq, elemento, cresceu);
                if(*cresceu) {
                       switch(raiz->fb) {
                            case -1:
                                 raiz->fb = -2;
                                 *cresceu = 0;
                                 return rotacionar(raiz);
                                 break;
                            case 0:
                                raiz->fb = -1;
                                 *cresceu = 1;
                                 break;
                            case 1:
                                raiz->fb = 0;
                                *cresceu = 0;
                                break;
                       }
                }
           }
           return raiz;
    }
}

int maior(no* raiz){
    if(raiz->dir == NULL){
        return raiz->valor;
    } else {
        maior(raiz->dir);
    }
}

int menor(no* raiz){
    if(raiz->esq == NULL){
        return raiz->valor;
    } else {
        menor(raiz->esq);
    }
}

int altura(no* raiz){
    int alturaEsquerda, alturaDireita;
    if(raiz == NULL){
        return 0;
    } else {
        alturaEsquerda = altura(raiz->esq);
        alturaDireita = altura(raiz->dir);
        if (alturaEsquerda < alturaDireita){
            return alturaDireita + 1;
        }
        else{
            return alturaEsquerda + 1;
        }
    }
}

no* remover(no* raiz, tipo_dado elemento){
    if(raiz == NULL){
        return NULL;
    }
    if(raiz->valor == elemento){
            if(raiz->dir == NULL && raiz->esq == NULL){
                raiz = NULL;
            } else if(raiz->dir != NULL && raiz->esq == NULL){
                raiz = raiz->dir;
            } else if(raiz->esq != NULL && raiz->dir == NULL){
                raiz = raiz->esq;
            } else if(raiz->esq != NULL && raiz->dir != NULL){
                raiz->valor = maior(raiz->esq);
                raiz->esq = remover(raiz->esq, raiz->valor);
                raiz->fb += 1;
                rotacionar(raiz);
            }
            return raiz;
    }
    if(elemento > raiz->valor) {
			raiz->dir = remover(raiz->dir, elemento);
			raiz->fb -= 1;
			rotacionar(raiz);
	} else {
			raiz->esq = remover(raiz->esq, elemento);
			raiz->fb += 1;
			rotacionar(raiz);
	}
	return raiz;
}

no* rotacionar(no* pivo) {
        if(pivo->fb == -2 && pivo->esq->fb == -1)
            return rotacao_simples_direita(pivo);
        if(pivo->fb == 2 && pivo->dir->fb == 1)
            return rotacao_simples_esquerda(pivo);
        if(pivo->fb == 2 && pivo->dir->fb == -1)
            return rotacao_dupla_esquerda(pivo);
        if(pivo->fb == -2 && pivo->esq->fb == 1)
            return rotacao_dupla_direita(pivo);
        else
            return pivo;
}

no* rotacao_simples_direita(no* pivo) {
       no* u = pivo->esq;
       u->fb = 0;
       pivo->fb = 0;
       pivo->esq = u->dir;
       u->dir = pivo;
       return u;
}

no * rotacao_simples_esquerda(no* pivo){
       no* u = pivo->dir;
       u->fb = 0;
       pivo->fb = 0;
       pivo->dir = u->esq;
       u->esq = pivo;
       return u;
}

no * rotacao_dupla_esquerda(no* pivo){
    no* u = pivo->dir;
    u->fb = 0;
    pivo->fb = 0;
    pivo->dir = u->esq;
    u->esq = u->esq->dir;
    pivo->dir->dir = u;
    return rotacao_simples_esquerda(pivo);
}

no * rotacao_dupla_direita(no* pivo){
    no* u = pivo->esq;
    u->fb = 0;
    pivo->fb = 0;
    pivo->esq = u->dir;
    u->dir = u->dir->esq;
    pivo->esq->esq = u;
    return rotacao_simples_direita(pivo);
}

no* elementoPai(no* raiz, tipo_dado elemento){
    if(raiz == NULL){
        return NULL;
    }
    else{
        if(raiz->valor > elemento){
            no* aux1 = raiz->esq;
            if(aux1->valor == elemento){
                return raiz;
            } else if(aux1->valor > elemento){
                return -1;
            }
            elementoPai(raiz->esq, elemento);
        } else if(raiz->valor < elemento){
            no* aux2 = raiz->dir;
            if(aux2->valor == elemento){
                return raiz;
            } else if(aux2->valor < elemento){
                return -1;
            }
            elementoPai(raiz->dir, elemento);
        }
    }
}


void preorder(no* raiz){
    if(raiz == NULL) ;
    else {
        printf("[%d, %d]", raiz->valor, raiz->fb);
        preorder(raiz->esq);
        preorder(raiz->dir);
    }
}
