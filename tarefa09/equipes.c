#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

typedef struct no* p_no;

struct no {
    int altura, final;
    p_no anterior;
    p_no proximo;
};

void destruir_lista(p_no inicio) {
    if (inicio->final) {
        free(inicio);
    }
    else{
        free(inicio);
        destruir_lista(inicio->proximo);
    }
}

void remover(p_no atual);

void printar_crescente(p_no atual){
    p_no menor = atual;
    while(atual){
        if (atual->altura < menor->altura){
            menor = atual;
        }
        if(atual->final){
            if(menor->altura == 99999){
                break;
            }
            printf("%d ", menor->altura);
            menor->altura = 99999;
        }
        if(atual->proximo){
            atual = atual->proximo;
        }
    }
    printf("\n");
}

p_no alocar(int altura) {
    p_no novo = malloc(sizeof(struct no));
    novo->anterior = NULL;
    novo->proximo = NULL;
    novo->altura = altura;
    return novo;
}

void jogar_dado(p_no inicio, int m, p_no time1, p_no time2) {
    p_no atual, novo, inicio1, inicio2;
    int dado;

    for (int j = 0; j < m; j++) {
        atual = inicio;
        scanf("%d", &dado);
        for (int i = 0; i < dado - 1; i++) {
            if (j%2 != 0) {
                atual = atual->proximo;
            } else {
                atual = atual->anterior;
            }
        }

        if (j == 1) {
            time1 = alocar(atual->altura);
            inicio1 = time1;
        } else if (j == 0) {
            time2 = alocar(atual->altura);
            inicio2 = time2;
        } else {
            novo = alocar(atual->altura);
            if (j%2 != 0) {
                time1->proximo = novo;
                novo->anterior = time1;
                time1 = novo;
            } else {
                time2->proximo = novo;
                novo->anterior = time2;
                time2 = novo;
            }
        }

        if (atual == inicio) {
            if (atual->proximo != atual) {
                inicio = atual->proximo;
            } else {
                free(atual);
                break;
            }
        }
        remover(atual);
    }
    time1->proximo = inicio1;
    time1->final = true;
    inicio1->anterior = time1;

    time2->proximo = inicio2;
    time2->final = true;
    inicio2->anterior = time2;

    printar_crescente(inicio2);
    destruir_lista(inicio2);

    printar_crescente(inicio1);
    destruir_lista(inicio1);

}

p_no criar_vetor() { //cria uma lista vazia
    return NULL;
}

void remover(p_no atual) {
    p_no anterior, proximo;

    anterior = atual->anterior;
    proximo = atual->proximo;

    anterior->proximo = atual->proximo;
    proximo->anterior = atual->anterior;

    free(atual);
    atual = NULL;
}

int main(void) {
    p_no anterior, novo;
    p_no time1 = NULL; 
    p_no time2 = NULL;
    int altura, m;

    scanf("%d", &m);


    for (int i = 0; i < m; i++) {
        scanf("%d", &altura);
        novo = alocar(altura);
        if (i == 0) {
            anterior = novo;
        } else {
            novo->anterior = anterior;
            anterior->proximo = novo;
        }
        anterior = novo;
    }

    while (anterior->anterior) {
        anterior = anterior->anterior;
    }

    anterior->anterior = novo;
    novo->proximo = anterior;
    novo->final = true;

    jogar_dado(novo->proximo, m, time1, time2);
    
    return 0;
}