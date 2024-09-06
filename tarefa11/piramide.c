#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

typedef struct arvore {
    char nome[21];
    double valor;
    int altura;
    struct arvore* dir;
    struct arvore* esq;
    struct arvore* pai;
} Arvore;

typedef struct fila {
    Arvore* atual;
    struct fila* proximo;
} Fila;

void alocar_piramide(char nome[21], double valor, int altura, Arvore **novo, Arvore *pai) {
    *novo = malloc(sizeof(Arvore));
    strcpy((*novo)->nome, nome);
    (*novo)->valor = valor;
    (*novo)->altura = altura;
    (*novo)->dir = NULL;
    (*novo)->esq = NULL;
    (*novo)->pai = pai;
}

void procura_pai(Arvore *atual, char nome_pai[51], Arvore **pai) {
    if (atual) {
        if (strcmp(atual->nome, nome_pai) == 0) {
            (*pai) = atual;
        } else {
            procura_pai(atual->esq, nome_pai, pai);
            procura_pai(atual->dir, nome_pai, pai);
        }
    }
}

void adiciona_filho(char nome[21], double valor, Arvore **pai) {
    (*pai)->valor -= valor * 0.1;
    if ((*pai)->esq == NULL) {
        alocar_piramide(nome, valor, (*pai)->altura+1, &(*pai)->esq, (*pai));
        (*pai)->esq->valor += valor * 0.1;
    } else {
        alocar_piramide(nome, valor, (*pai)->altura+1, &(*pai)->dir, (*pai));
        (*pai)->dir->valor += valor * 0.1;
    }
}

void bonifica_pai(Arvore **atual) {
    double porcentagem = 6;
    if ((*atual)->esq && (*atual)->dir) {
        (*atual)->valor += (*atual)->esq->valor * (porcentagem/100);
        (*atual)->esq->valor -= (*atual)->esq->valor * (porcentagem/100);
        (*atual)->valor += (*atual)->dir->valor * (porcentagem/100);
        (*atual)->dir->valor -= (*atual)->dir->valor * (porcentagem/100);
        while ((*atual) && (*atual)->pai && porcentagem) {
            porcentagem--;
            (*atual)->pai->valor += (*atual)->valor * (porcentagem/100);
            (*atual)->valor -= (*atual)->valor * (porcentagem/100);
            (*atual) = (*atual)->pai;
        }
    }
}

Fila *criar_fila(Arvore *arvore_atual, Fila *proximo){
    Fila *novo = malloc(sizeof(Fila));
    novo->atual = arvore_atual;
    novo->proximo = proximo;
    return novo;
}

void printa_libera_fila(Fila *f, int altura_atual){
    while (f){
        if (f->atual->altura != altura_atual){
            altura_atual++;
            printf("\n");
            printf("Nivel %d: ", altura_atual);
        }
        printf("[%s %0.2lf] ", f->atual->nome, f->atual->valor);
        Fila *antiga = f;
        f = f->proximo;
        free(antiga);
    }
    free(f);
}

void enfileirar(Fila *f, Arvore *raiz)
{
    if(raiz != NULL)
    {
        enfileirar(f, raiz->esq);
        Fila *auxiliar;
        auxiliar = f;
        while (auxiliar && auxiliar->proximo && auxiliar->proximo->atual->altura <= raiz->altura)
        {
            auxiliar = auxiliar->proximo;
        }
        if(1 < raiz->altura)
        {
            Fila *novo = criar_fila(raiz, auxiliar->proximo);
            auxiliar->proximo = novo;
        }
        enfileirar(f, raiz->dir);
    }
}

void libera_arvore(Arvore *topo){
    if (topo){
        libera_arvore(topo->esq);
        libera_arvore(topo->dir);
        free(topo);
    }
}

int main() {
    char nome_pai[21];
    char nome[21];
    char objetivo[8];
    double valor;
    Arvore *topo, *pai;

    scanf("%s %s %lf", objetivo, nome_pai, &valor); //primeira linha da entrada
    
    printf("Nivel 1: [%s %0.2lf]\n", nome_pai, valor);

    alocar_piramide(nome_pai, valor, 1, &topo, NULL); //aloca o topo
    
    while (scanf("%s %s %s %lf", nome_pai, objetivo, nome, &valor) != EOF) { //restante das linhas da entrada
        Fila *f = criar_fila(topo, NULL);
        procura_pai(topo, nome_pai, &pai);
        adiciona_filho(nome, valor, &pai);
        bonifica_pai(&pai);
        enfileirar(f, topo);
        printa_libera_fila(f, 0);
        printf("\n");
    }

    libera_arvore(topo);

    return 0;
}