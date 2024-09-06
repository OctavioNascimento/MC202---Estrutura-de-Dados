#include <stdio.h>
#include "minecraft.h"
#include <stdlib.h>

int **calcularAltitudes(int m, int n, int seed) {
    int **altitude;
    altitude = (int**)(malloc(m * sizeof(int*)));

    for (int i = 0; i < m; i++) {
        altitude[i] = (int*)(malloc(n * sizeof(int)));
        for (int j = 0; j < n; j++) {
            altitude[i][j] = (seed * (202 + i + j) + 12345 + i + j) % 256;
        }
        
    }
   return altitude; 
}

Bloco ***criarMundo(int m, int n, int **altitudes, int seed) {
    Bloco ***mundo;
    mundo = (malloc(m * sizeof(Bloco**)));

    for (int i = 0; i < m; i++) {
        mundo[i] = (malloc(n * sizeof(Bloco*)));
        for (int j = 0; j < n; j++) {
            mundo[i][j] = (malloc(256 * sizeof(Bloco)));
            for (int k = 0; k < 256; k++) {
                if (k <= altitudes[i][j]) {
                    mundo[i][j][k].bloco = (seed * (202 + i + k + j) + i + k + j) % 33;
                } else {
                    mundo[i][j][k].bloco = 21;
                }
            }
        }
        
    }
   return mundo; 
}

double explorarMundo(
    Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco,
    int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 256; k++) {
                if (mundo[i][j][k].bloco < 21) {
                    *qtdBlocos = *qtdBlocos + 1;
                }
                if (mundo[i][j][k].bloco == 0) {
                    *qtdDiamante = *qtdDiamante + 1;

                } else if (mundo[i][j][k].bloco > 0 && mundo[i][j][k].bloco < 3) {
                    *qtdOuro = *qtdOuro + 1;
                
                } else if (mundo[i][j][k].bloco > 2 && mundo[i][j][k].bloco < 6) {
                    *qtdFerro = *qtdFerro + 1;
                }
            }
        }
    }
    return (tempoPorBloco * (*qtdBlocos));
}

int main() {
    int dimensao, largura, seed;
    float mineracao;
    Bloco ***mundo;
    int **altitude;

    int qtdDiamante = 0, qtdOuro = 0, qtdFerro = 0, qtdBlocos = 0;
    //int *qtdDiamante = &Diamante, *qtdOuro = &Ouro, *qtdFerro = &Ferro, *qtdBlocos = &Blocos;

    scanf("%d %d", &dimensao, &largura);
    scanf("%d", &seed);
    scanf("%f", &mineracao);
    
    altitude = calcularAltitudes(dimensao, largura, seed);
    mundo = criarMundo(dimensao, largura, altitude, seed);
    float tempo_total = explorarMundo(mundo, dimensao, largura, altitude, mineracao, &qtdDiamante, &qtdOuro, &qtdFerro, &qtdBlocos);

    printf("Total de Blocos: %d\n", qtdBlocos);
    printf("Tempo total: %0.2fs\n", tempo_total);
    printf("Diamantes: %d\n", qtdDiamante);
    printf("Ouros: %d\n", qtdOuro);
    printf("Ferros: %d\n", qtdFerro);
    
    for (int i = 0; i < dimensao; i++) {
        for (int j = 0; j < largura; j++) {
            free(mundo[i][j]);
        }
        free(altitude[i]);
        free(mundo[i]);
    }

    free(altitude);
    free(mundo);

    return 0;
}
