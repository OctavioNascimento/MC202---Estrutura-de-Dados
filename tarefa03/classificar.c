#include <stdio.h>
#include <string.h>
//strlen retorna o numero de chars da string - "int variavel = strlen(string)"
//strcpy realiza a cópia do conteúdo de uma variável a outra - "strcpy(string_destino, string_origem);"
//strcmp compara duas strings - 0: a == b, <0: a < b, >0: a > b - "int variavel = strcmp(string1, string2);"

void printar_vetor(int n, char lista_nomes[150][31]);

void formatar_vetor(int n, char lista_estudantes[150][31]) {
    char nome_estudante[31];
    for (int i = 0; i < n; i++) {
        scanf("%s", nome_estudante);
        strcpy(lista_estudantes[i], nome_estudante);
    }
}

void separar(int n, char lista_estudantes[150][31], char comando[10], char nome_filtrado[150][31]) {
    /* identifica e separa apenas o primeiro nome do estudante*/
    if (strcmp(comando, "homonimos") == 0) {
        for (int i = 0; i < n; i++) {
            int tam = strlen(lista_estudantes[i]);
            for (int j = 0; j < tam; j++) {
                if (lista_estudantes[i][j] == '_'){
                    nome_filtrado[i][j] = '\0';
                    break;
                }
                else{
                    nome_filtrado[i][j] = lista_estudantes[i][j];
                }
            }
        }
    }
}

void filtrar(int n, char nome_filtrado[150][31], char lista_estudantes[150][31], char lista_nomes[150][31]) {
    /* identifica e separa os alunos homonimos*/
    char comparada[31]; //string que recebera o nome a ser comparado
    int compare2;
    for (int i = 0; i < n; i++) {
        strcpy(comparada, nome_filtrado[i]); //copia o termo i do array para ser comparado
        for (int j = 0; j < n; j++) {
            int compare = strcmp(nome_filtrado[j], comparada); //compara o termo com os outros do array
            if (compare == 0 && i!=j) {
                for (int k = 0; k < n; k++) {
                    compare2 = strcmp(lista_estudantes[i], lista_nomes[i]); //verifica se o termo está repetido
                }
                if (compare2 != 0) {
                    strcpy(lista_nomes[i], lista_estudantes[i]); //adiciona o nome na lista
                }
            }
        }
    }
}

void ordenar(int n, char lista_nomes[150][31]) { //quick sort
    char comparada[31];
    for (int i = 0; i < 150; i++){
        for (int j = i+1; j < n; j++) {
            int compare = strcmp(lista_nomes[i], lista_nomes[j]);
            if(compare > 0){
                strcpy(comparada, lista_nomes[i]);
                strcpy(lista_nomes[i], lista_nomes[j]);
                strcpy(lista_nomes[j], comparada);
            }
        }
    }
}

void printar_vetor(int n, char lista_nomes[150][31]) {
    for (int i = 0; i < n; i++) {
        if (strlen(lista_nomes[i]) > 7){
            printf("%s\n", lista_nomes[i]);
        }
    }
}

int main() {
    int n; //numero de estudantes
    char comando[10]; //comando desejado (homonimos ou parentes)
    char lista_estudantes[150][31]; //contém o nome dos "n" estudantes
    char nome_filtrado[150][31]; //contém apenas o primeiro nome
    char lista_nomes[150][31]; //lista final com os nomes homonimos
    scanf("%d", &n);
    scanf("%s", comando);
    formatar_vetor(n, lista_estudantes);
    separar(n, lista_estudantes, comando, nome_filtrado);
    filtrar(n, nome_filtrado, lista_estudantes, lista_nomes);
    ordenar(n, lista_nomes);
    printar_vetor(n, lista_nomes);
    return 0;
}