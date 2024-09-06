#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0

typedef struct no* p_no;

struct no {
    int documento;
    char profissao[26];
    char vacina[13];
    p_no anterior;
};

p_no criar_vetor() { //cria uma lista vazia
    return NULL;
}

p_no adicionar_elemento(int documento, char profissao[], char vacina[]) {
    p_no novo = malloc(sizeof(struct no));
    novo->documento = documento;
    strcpy(novo->profissao, profissao);
    strcpy(novo->vacina, vacina);
    //?novo->anterior = lista;
    return novo;
}

//void organiza_fila(p_no lista, int documento, char profissao[], char vacina[]) {}

void print_lista(p_no lista) { //printa recursivamente
    if (lista != NULL) {
        print_lista(lista->anterior);
        if (lista->documento) {
        printf("%d %s %s\n", lista->documento, lista->profissao, lista->vacina);
        }
    }
}

void destruir_lista(p_no lista) {
    if (lista != NULL) {
        destruir_lista(lista->anterior);
        free(lista);
    }
}

int main() {
    int documento;
    char profissao[26], vacina[13];
    int verifica = false;
    p_no lista, novo, inicio, inicio_antigo = NULL;
    inicio = adicionar_elemento(0,"0","0");
    inicio->anterior = NULL;
    lista = inicio;

    while (scanf("%d %s %s", &documento, profissao, vacina) != EOF) {
        novo = adicionar_elemento(documento, profissao, vacina);
        if (strcmp(novo->profissao, "funcionario")==0){
            if (verifica && inicio_antigo) {
                p_no auxiliar = inicio_antigo;
                while (auxiliar->anterior->documento){
                    auxiliar = auxiliar->anterior;
                }
                auxiliar->anterior = lista;
                lista = inicio_antigo;
            }
            verifica = false;
        }   
        
        if (strcmp(novo->profissao, "coach") == 0 || strcmp(novo->profissao, "ex-bbb") == 0 || strcmp(novo->profissao, "filho-politico") == 0 ||
        strcmp(novo->profissao, "herdeiro") == 0 || strcmp(novo->profissao, "youtuber-financas") == 0) {
            if (verifica && inicio_antigo) {
                p_no auxiliar = inicio_antigo;
                while (auxiliar->anterior->documento){
                    auxiliar = auxiliar->anterior;
                }
                auxiliar->anterior = lista;
                lista = inicio_antigo;
            }
            if(lista->documento){
                inicio_antigo = lista;
            }
            novo->anterior = inicio;
            lista = novo;
            verifica = true;
        
        }
        
        else {
            //adiciona pro final da fila e entrega a lanterna
            novo->anterior = lista;
            lista = novo;
        }
    }
    
    if (verifica) {    
        p_no auxiliar = inicio_antigo;
        while (auxiliar->anterior->documento){
            auxiliar = auxiliar->anterior;
        }
        auxiliar->anterior = lista;
        lista = inicio_antigo;
    }

    print_lista(lista);

    destruir_lista(lista);

    return 0;
}