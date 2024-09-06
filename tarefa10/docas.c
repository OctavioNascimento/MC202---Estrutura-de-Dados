#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define true 1
#define false 0
#define carrega 1
#define descarrega 0

typedef struct navio {
    int num_cont, objetivo;
    char mercadoria[21];
    char nome_navio[21];
    struct navio* anterior;
    struct navio* proximo;
}Navio;

typedef struct container {
    int num_cont;
    char mercadoria[21];
    struct container* anterior;
}Cont;

typedef struct doca {
    int num_navios, num_cont, cap_doca, num_doca;
    Cont* topo;
    struct doca* proximo;
}Doca;

void alocar_navio(char nome_navio[21], char objetivo[11], char mercadoria[21], int num_cont, Navio **novo) {
    *novo = malloc(sizeof(Navio));
    (*novo)->anterior = NULL;
    (*novo)->proximo = NULL;
    strcpy((*novo)->nome_navio, nome_navio);
    if (strcmp(objetivo,"carrega") == 0) {
        (*novo)->objetivo = carrega;
    } else {
        (*novo)->objetivo = descarrega;
    }
    strcpy((*novo)->mercadoria, mercadoria);
    (*novo)->num_cont = num_cont;
}

void alocar_cont(char mercadoria[21], Doca **doca) {
    Cont* novo = malloc(sizeof(Cont));
    novo->anterior = (*doca)->topo;
    novo->num_cont = 0;
    strcpy(novo->mercadoria, mercadoria);
    (*doca)->topo = novo;
}

void alocar_doca(int cap_doca, int num_doca, Doca **novo) {
    *novo = malloc(sizeof(Navio));
    (*novo)->topo = NULL;
    (*novo)->proximo = NULL;
    (*novo)->num_cont = 0;
    (*novo)->cap_doca = cap_doca;
    (*novo)->num_doca = num_doca;
}

void retira_container(Doca **doca) {
    Cont *vazio = (*doca)->topo;
    (*doca)->topo = (*doca)->topo->anterior;
    free(vazio);
}

void carregar_navio(Navio** navio, Doca** doca, int *verifica) {
    while((*doca)) {
        if ((*doca)->topo && strcmp((*doca)->topo->mercadoria, (*navio)->mercadoria) == 0) {
            int quantidade = 0;
            while((*doca)->topo->num_cont > 0 && (*navio)->num_cont > 0) {
                quantidade++;
                (*navio)->num_cont--;
                (*doca)->num_cont--;
                (*doca)->topo->num_cont--;
            }
            printf("%s carrega %s doca: %d conteineres: %d\n", (*navio)->nome_navio, (*navio)->mercadoria, (*doca)->num_doca, quantidade);
            if((*doca)->topo->num_cont == 0) {
                retira_container(doca);
            }
            *verifica = true;
            break;
        } else {
            (*doca) = (*doca)->proximo;
        }
    }
}

void retira_navio(Navio **navio) {
    Navio *proximo, *anterior;
    proximo = (*navio)->proximo;
    anterior = (*navio)->anterior;
    if (anterior)
        anterior->proximo = proximo;
    if (proximo)
        proximo->anterior = anterior;
    navio = NULL;
}

void descarregar_navio(Navio** navio, Doca** doca, int *verifica) {
    while ((*doca)) {
        if ((*doca)->num_cont < (*doca)->cap_doca) {
            if ((*doca)->topo == NULL || strcmp((*navio)->mercadoria, (*doca)->topo->mercadoria)) {
                alocar_cont((*navio)->mercadoria, doca);
            }
            int quantidade = 0;
            while ((*navio)->num_cont > 0 && (*doca)->num_cont < (*doca)->cap_doca) {
                quantidade++;
                (*navio)->num_cont--;
                (*doca)->num_cont++;
                (*doca)->topo->num_cont++;
            }
            *verifica = true;
            printf("%s descarrega %s doca: %d conteineres: %d\n", (*navio)->nome_navio, (*navio)->mercadoria, (*doca)->num_doca, quantidade);
            break;
        } 
        //else {}
            (*doca) = (*doca)->proximo;
        
    }
}

int main() {
    int num_docas, cap_doca, num_navios, num_cont;
    Navio *nav_inicio, *nav_novo, *nav_final, *qual_navio;
    Doca *doc_inicio, *doc_novo, *doc_final, *p_doc_ini;
    char nome_navio[21];
    char objetivo[11];
    char mercadoria[21];

    scanf("%d\n %d\n %d\n", &num_docas, &cap_doca, &num_navios); 
    
        for (int i = 0; i < num_navios; i++) { //fila navios
            scanf("%s %s %s %d", nome_navio, objetivo, mercadoria, &num_cont);
            alocar_navio(nome_navio, objetivo, mercadoria, num_cont, &nav_novo);
        
            if (i == 0) {
                nav_inicio = nav_novo;
                nav_final = nav_novo;

            } else {
                nav_final->proximo = nav_novo;
                nav_novo->anterior = nav_final;
                nav_final = nav_novo;
            }
        }
        nav_final->proximo = nav_inicio;
        nav_inicio->anterior = nav_final;
            
        for (int i = 0; i < num_docas; i++) {  //fila docas
            alocar_doca(cap_doca, i, &doc_novo);
        
            if (i == 0) {
                doc_inicio = doc_novo;
                doc_final = doc_novo;

            } else {
                doc_final->proximo = doc_novo;
                doc_final = doc_novo;
            }
        }

        qual_navio = nav_inicio;
        int verifica;
        int *p_verifica = &verifica;

        while(1) {
            p_doc_ini = doc_inicio;
            if (qual_navio->objetivo == carrega) {
                carregar_navio(&qual_navio, &p_doc_ini, p_verifica);
            } else {
                descarregar_navio(&qual_navio, &p_doc_ini, p_verifica);
            }
            if(qual_navio->num_cont == 0){
                if(&qual_navio == &nav_final) {
                    nav_final = qual_navio->anterior;
                }
                if(qual_navio == qual_navio->proximo) {
                    qual_navio->proximo = NULL;
                }
                else {
                retira_navio(&qual_navio);
                }
            }
            if (&qual_navio == &nav_final && verifica == false) {
                break;
            } 
            else if(qual_navio->proximo == NULL) {
                break;
            }
            else {
                qual_navio = qual_navio->proximo;
            }   
        }

    return 0;
}