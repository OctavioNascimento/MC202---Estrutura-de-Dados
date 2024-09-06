#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct palavra {
    char word[51];
    int aparicoes;
    int is_stop_word;
    struct palavra* prox;
}Palavra;

typedef struct nuvem {
    Palavra* atual;
}Nuvem;

typedef struct fila {
    struct fila* anterior, *proximo;
    Palavra* palavra;
}Fila;

int hash(char *chave) {
    int i, n = 0;
    for (i = 0; i < strlen(chave); i++)
        n = (256 * n + chave[i]) % 1783;
    return n;
}

int filtra(char *letra, char *filtrada) {
    int contagem = 0;
    for (int i = 0; '\0' != letra[i]; i++) {
        if (letra[i] >= 65 && letra[i] <= 90) {
            filtrada[contagem] = letra[i] + 32;
            contagem++;
        } else if (letra[i] >= 97 && letra[i] <= 122) {
            filtrada[contagem] = letra[i];
            contagem++;
        }
    }
    filtrada[contagem] = '\0';
    return 0;
}

void cria_fila(Fila** inicio, Palavra* palavra) {
    // cria lista duplamente ligada
    if ((*inicio) == NULL){
        (*inicio) = malloc(sizeof(Fila));
        (*inicio)->palavra = palavra;
        (*inicio)->proximo = NULL;
        (*inicio)->anterior = NULL;
    }else{
        while ((*inicio)->proximo) {
            (*inicio) = (*inicio)->proximo;
        }
        (*inicio)->proximo = malloc(sizeof(Fila));
        (*inicio)->proximo->anterior = (*inicio);
        (*inicio) = (*inicio)->proximo;
        (*inicio)->palavra = palavra;
        (*inicio)->proximo = NULL;        
    }
    
}

void insere_palavra(Palavra* atual, char filtrada[]){
    atual->aparicoes = 1;
    strcpy(atual->word, filtrada);
    atual->is_stop_word = 0;
    atual->prox = NULL;
}

void printa_em_sequencia(Fila** inicio){
    Fila *maior = (*inicio);
    while (maior != NULL){
        Fila *menor = maior->anterior;
        while (menor != NULL){
            int lugar_errado = 0;
            if (menor->palavra->aparicoes == maior->palavra->aparicoes && strcmp(menor->palavra->word, maior->palavra->word) < 0){
                lugar_errado = 1;
            }
            else if (maior->palavra->aparicoes < menor->palavra->aparicoes){
                lugar_errado = 1;
            }
            if (lugar_errado == 1){
                Palavra *aux = menor->palavra;
                menor->palavra = maior->palavra;
                maior->palavra = aux;
                aux = NULL;
            }
            menor = menor->anterior;
        }
        maior = maior->anterior;
    }
}

int main(){
    int palavras;
    int stop_words;
    char word[51];
    int indice_hash;
    char letra[51];
    int restantes = 50;
    Fila* inicio = NULL;

    scanf("%d\n%d", &palavras, &stop_words);
    
    Nuvem* tabela = malloc(sizeof(Nuvem)*palavras);
    
    /*salva as stop words no hash*/
    for (int i = 0; i < stop_words; i++) {
        scanf(" %s", word);
        indice_hash = hash(word);
        Palavra* atual;
        
        if (tabela[indice_hash].atual == NULL){
            tabela[indice_hash].atual = malloc(sizeof(Palavra));
            atual = tabela[indice_hash].atual;
        } else {
            atual = tabela[indice_hash].atual;
            while(atual->prox) {
                atual = atual->prox;
            }
            atual->prox = malloc(sizeof(Palavra));
            atual = atual->prox;
        }
        atual->prox = NULL;
        atual->aparicoes = 1;
        atual->is_stop_word = 1;
        strcpy(atual->word, word);
    }
    while (scanf("%s ",letra) != EOF) {
        char filtrada[51];
        filtra(letra, filtrada);
        
        indice_hash = hash(filtrada);
        //Palavra* atual = tabela[indice_hash].atual;
        Palavra* atual;
        
        // acha uma posicao vazia na lista ligada
        if (tabela[indice_hash].atual == NULL){
            tabela[indice_hash].atual = malloc(sizeof(Palavra));
            atual = tabela[indice_hash].atual;
            insere_palavra(atual, filtrada);
            cria_fila(&inicio, atual);
        }
        else{
            atual = tabela[indice_hash].atual;
            while(atual->prox){
                // verifica se achou a palavra no mafagafo de palavras
                if (strcmp(atual->word, filtrada) == 0)
                    break;
                atual = atual->prox;
            }
            // verifica se chegou no final e o ultimo elemento e diferente
            if (atual->prox == NULL && strcmp(atual->word, filtrada) != 0){
                atual->prox = malloc(sizeof(Palavra));
                atual = atual->prox;
                insere_palavra(atual, filtrada);
                cria_fila(&inicio, atual);
            }
            else{
                atual->aparicoes += 1;
            }
        }

    }
    printa_em_sequencia(&inicio);
    while (inicio) {
        if (strlen(inicio->palavra->word) >= 2 && restantes > 0 && inicio->palavra->is_stop_word == 0){
            printf("%s %d\n", inicio->palavra->word, inicio->palavra->aparicoes);
            restantes -= 1;
        }
        inicio = inicio->anterior;
    }
    

    return 0;
}