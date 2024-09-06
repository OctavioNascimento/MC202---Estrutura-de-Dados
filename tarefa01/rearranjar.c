#include <stdio.h>

void formatar_vetor(int n, int participantes[]) {
    /*  transforma o vetor criado na main em um 
    * vetor indice a partir de 1 até o input "n"*/
    
    for (int i = 0; i < n; i++) {
        participantes[i] = i+1;
    }
}

int encontrar_indice(int a, int n, int participantes[]) {
    /* encontra os indices relativos aos itens do vetor */
    int i;
    for (i = 0; i < n; i++) { 
        if (participantes[i] == a) {
            return i;
        }
    }
    return 0;
}

void ordenar(int c,int a, int b, int indice_a, int indice_b, int n, int participantes[]) {
    /* reorganiza o vetor para que os indices fiquem ordenados */
    
    int vetor[10000];
    
    if (c == 1) {
        //printf("%d %d %d %d\n", a, b, indice_a, indice_b);

        for (int i = 0; i < n; i++) {
            vetor[i] = participantes[i];
        }
        for (int i = indice_b; i >= indice_a; i--)  {
            participantes[indice_b - i + indice_a] = vetor[i];
        }
    }else if (c == 2) {
        int ia = participantes[indice_a];
        for (int i = indice_a; i < indice_b; i++)   {
            participantes[i] = participantes[i+1];
        }
        participantes[indice_b] = ia;
    }
}

void printar_vetor(int participantes[], int n) {
    /* printa o vetor completo */
    for (int i = 0; i < n; i++) {
        printf("%d ",participantes[i]);    
    }
    printf("\n");
}

int main() {
    int n, m; //n = numero de participantes e m = numero de movimentos
    int c, a, b;
    scanf("%d", &n);
    scanf("%d", &m);
    
    int participantes[10000];
    formatar_vetor(n, participantes);
    
    int indice_a, indice_b;

    for (int i = 0; i < m; i++) {

        scanf("%d %d %d", &c, &a, &b); 
        indice_a = encontrar_indice(a, n, participantes);
        indice_b = encontrar_indice(b, n, participantes);
        ordenar(c, a, b, indice_a, indice_b, n, participantes);
    }
    printar_vetor(participantes, n);
}