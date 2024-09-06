#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

typedef struct produto {
    char loja[50];
    int codigo;
    double valor;
}Produto;

typedef struct arvore {
    struct arvore* esq;
    struct arvore* dir;
    Produto* produto;
}Arvore;

typedef struct fila {
    char loja[50];
    int codigo;
    double valor;
    struct fila* prox;
}Fila;

void insere_fila(Fila* fila, double valor, int codigo, char loja[]) {
    while (fila->prox) {
        fila = fila->prox;
    }
    fila->prox = malloc(sizeof(Fila));
    fila->prox->prox = NULL;
    fila->prox->codigo = codigo;
    fila->prox->valor = valor;
    strcpy(fila->prox->loja, loja);
}

void aloca_arvore(Arvore **novo) {
    *novo = malloc(sizeof(Arvore));
    (*novo)->dir = NULL;
    (*novo)->esq = NULL;
    (*novo)->produto = malloc(sizeof(Produto));
}

void insere_valor(Arvore** atual, char loja[], int codigo, double valor) {
    if ((*atual)) {
        if ((*atual)->produto->valor > valor) {
            insere_valor(&(*atual)->esq, loja, codigo, valor);
        } else {
            insere_valor(&(*atual)->dir, loja, codigo, valor);
        }
    } else {
        aloca_arvore(atual);
        (*atual)->produto->codigo = codigo;
        strcpy((*atual)->produto->loja, loja);
        (*atual)->produto->valor = valor;
    }
}

void procura_produto(Arvore* atual, double valor, int codigo, Fila** fila) {
    if (atual) {
        procura_produto(atual->esq, valor, codigo, fila);
        procura_produto(atual->dir, valor, codigo, fila);
        if (atual->produto->valor <= valor*1.1 && atual->produto->codigo == codigo) {
            if ((*fila)) {
                insere_fila((*fila), atual->produto->valor, codigo,atual->produto->loja);
            } else {
                (*fila) = malloc(sizeof(Fila));
                (*fila)->valor = atual->produto->valor;
                (*fila)->codigo = atual->produto->codigo;
                strcpy((*fila)->loja, atual->produto->loja);
                (*fila)->prox = NULL;
            }
        }
    }
}

void quicksort(Fila *fila){
    Fila *menor;
    Fila *maior = fila;
    
    while (maior) {
        menor = maior->prox;
        while (menor) {
            if (strcmp(maior->loja, menor->loja) > 0) {
                double aux_val = maior->valor;
                char aux_stg[50];
                strcpy(aux_stg, maior->loja);
                
                maior->valor = menor->valor;
                strcpy(maior->loja, menor->loja);

                menor->valor = aux_val;
                strcpy(menor->loja, aux_stg);
            }
            menor = menor->prox;
        }
        maior = maior->prox;
    }
}

void desaloca(Arvore* atual) {
    if (atual != NULL) {
        desaloca(atual->esq);
        desaloca(atual->dir);
        free(atual->produto);
        free(atual);
    }
}

int main() {
    int n, m;
    char loja[50];
    int codigo, p_codigo;
    double valor, p_valor;
    Arvore* topo = NULL;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s %d %lf", loja, &codigo, &valor);
        insere_valor(&topo, loja, codigo, valor);
    }
    
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d %lf", &p_codigo, &p_valor);
        Fila* fila = NULL;
        procura_produto(topo, p_valor, p_codigo, &fila);
        
        printf("OFERTAS para %d:\n", p_codigo);
        
        if (fila) {
            quicksort(fila);
            while (fila) {
                printf("%s %d %0.2lf\n", fila->loja, fila->codigo, fila->valor);
                Fila* deletar = fila;
                fila = fila->prox;
                free(deletar);
            }
        } else {
            printf("nenhuma boa oferta foi encontrada\n");
        }
        printf("\n");
    }
    desaloca(topo);

    return 0;
}