#include <stdio.h>
#include <stdlib.h>
#define tamanho_dna 14

void zerar_dna(int vetor_dna[]) {
    for (int i = 0; i < tamanho_dna; i++) {
        vetor_dna[i] = 0;
    }
}

int main() {
    int tamanho;
    char dna[tamanho_dna];
    char rna[tamanho_dna];
    char *segmento;
    int vetor_dna[tamanho_dna];
    zerar_dna(vetor_dna);
    
    scanf("%s", dna);
    scanf("%s", rna);
    scanf("%d", &tamanho);
    tamanho++;

    segmento = (char*) malloc(tamanho * sizeof(char));

    for (int i = 0; i < tamanho; i++) { //recebo o segmento
        scanf("%c", &segmento[i]);
    }
    
    printf("ID: ");
    for (int i = 0; i < tamanho; i++) {
        char letra = segmento[i];
        for (int k = 0; k < tamanho_dna; k++) {
            if (dna[k] == letra) {
                printf("\t%d", vetor_dna[k]);
                vetor_dna[k] += 1;
            }
        }
    }
    
    printf("\nDNA:");
    for (int i = 0; i < tamanho; i++) {
        printf("\t%c", segmento[i]);
    }

    printf("\n");
    for (int i = 0; i < tamanho - 1; i++) {
        printf("\t|");
    }

    printf("\nRNA:");
    for (int i = 0; i < tamanho; i++) {
        char letra = segmento[i];
        for (int k = 0; k < tamanho_dna; k++) {
            if (dna[k] == letra) {
                printf("\t%c", rna[k]);
            }
        }
    }
    printf("\n");

    free(segmento);

    return 0;
}
