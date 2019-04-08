#ifndef AVL_H
#define AVL_H

typedef  int  tipo_dado;

typedef struct no {
    int fb;
    tipo_dado valor;
    struct no *esq, *dir;
} no;

no * inserir (no* raiz, tipo_dado elemento, int *cresceu);

no* rotacionar(no* pivo);
no* rotacao_simples_direita(no* pivo);
no* rotacao_simples_esquerda(no* pivo);
no* rotacao_dupla_esquerda(no* pivo);
no* rotacao_dupla_direita(no* pivo);

void preorder(no* raiz);
void inorder(no* raiz);
void posorder(no* raiz);

int maior(no* raiz);
int menor(no* raiz);
int altura(no* raiz);
no* elementoPai(no* raiz, tipo_dado elemento);

no* remover(no* raiz, tipo_dado elemento);

#endif
