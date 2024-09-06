#include <stdio.h>
#include "planejar.h"
#include <string.h>

Data ler_data() {
/* recebe os dados da data */ 
    Data data;
    scanf("%d/%d/%d", &(data.dia), &(data.mes), &(data.ano));
    return data;
}
void alterar(Voo voos[], int qtd_voos, int numero_voo, float novo_valor) {
    for (int j = 0; j < qtd_voos; j++) {
        if (voos[j].num_voo == numero_voo) {
            voos[j].valor = novo_valor;
        }
    }
}

void cancelar(Voo voos[], int qtd_voos, int numero_voo) {
    for (int j = 0; j <= qtd_voos; j++) {
        if (voos[j].num_voo == numero_voo) {
            voos[j].num_voo = 0;
        }
    }
}

int compara_data(Data data1, Data data2) {
    
    if (data1.ano > data2.ano) {
        return 1;
    
    } else if (data2.ano > data1.ano) {
        return 2;
    
    } else if (data1.mes > data2.mes) {
        return 1;
    
    } else if (data2.mes > data1.mes) {
        return 2;
    
    } else if (data1.dia > data2.dia) {
        return 1;

    } else {
        return 2;
    }  
}

int diferenca_data(Data data1, Data data2) {
    int dias1 = 1;
    dias1 += ((data1.ano * 365) - 365);
    //printf("%d %d\n", dias1, data1.ano);
    for (int i = 1; i < data1.mes; i++) {
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
            dias1 += 31;
        } else if (i == 4 || i == 6 || i == 9 || i == 11) {
            dias1 += 30;
        } else {
            dias1 += 28;
        }
    }
    dias1 += data1.dia;
    //printf("%d\n", dias1);

    int dias2 = 1;
    dias2 += ((data2.ano * 365) - 365);
    //printf("%d\n", dias2);
    for (int i = 1; i < data2.mes; i++) {
        if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
            dias2 += 31;
        } else if (i == 4 || i == 6 || i == 9 || i == 11) {
            dias2 += 30;
        } else {
            dias2 += 28;
        }
    }
    dias2 += data2.dia;
    //printf("%d\n", dias2);
    int dias = dias2 - dias1;
    //printf("%d - %d = %d\n", dias1, dias2, dias);
    return dias;
}

void planejar(Voo voos[], int qtd_voos, Data data_inicio, Data data_fim, char codigo_origem[]) {
    //identifica o codigo do voo ida e volta
    Planejamento validos[1];
    validos[0].valor = 9999999;
    for (int k = 0; k < qtd_voos; k++) { //percorre todos os voos
        int compara_ida = compara_data(data_inicio, voos[k].data);
        if((strcmp(voos[k].cod_aero_origem, codigo_origem) == 0) && compara_ida==2) { //verifica se a origem do voo de ida está certa
            for (int m = 0; m < qtd_voos; m++) { //percorre o todos os voos
                int compara_volta = compara_data(voos[m].data, data_fim);
                if ((strcmp(voos[k].cod_aero_destino, voos[m].cod_aero_origem) == 0)) { //verifica se o voo da volta sai do mesmo lugar do destino
                    if ((strcmp(voos[m].cod_aero_destino, codigo_origem) == 0) && compara_volta==2) {  //verifica se o voo da volta volta pra origem
                        float soma_valor = voos[k].valor + voos[m].valor;
                        int data_diferenca = diferenca_data(voos[k].data, voos[m].data);
                        if (soma_valor < validos[0].valor && voos[k].num_voo != 0 && voos[m].num_voo != 0 && data_diferenca >= 3) {
                            validos[0].valor = soma_valor;
                            validos[0].num_ida = voos[k].num_voo;
                            validos[0].num_volta = voos[m].num_voo;
                            validos[0].data_ida = voos[k].data;
                            validos[0].data_volta = voos[m].data;

                        }
                    }
                } 
            }
        }
    }
    printf("%d\n%d\n", validos[0].num_ida, validos[0].num_volta);
}