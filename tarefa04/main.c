#include <stdio.h>
#include <string.h>
#include "planejar.h"

int main() {
    char comando[10];
    Voo voos[100];
    int i = 0;
    while (1) {
        scanf("%s", comando);
        if (strcmp(comando, "registrar") == 0) {
            
            scanf("%d", &voos[i].num_voo);
            scanf("%s %s", voos[i].cod_aero_origem, voos[i].cod_aero_destino);
            Data data = ler_data();
            voos[i].data.dia = data.dia;
            voos[i].data.mes = data.mes;
            voos[i].data.ano = data.ano;
            scanf("%f", &voos[i].valor);
            //printf("%d\n",voos[i].num_voo);
            i++;
        }else if (strcmp(comando, "alterar") == 0) {
            int num_voo; //numero do voo que deseja mudar o valor
            float novo_valor;
            scanf("%d %f", &num_voo, &novo_valor);
            alterar(voos, i, num_voo, novo_valor);

        }else if (strcmp(comando, "cancelar") == 0) {
            int num_voo;
            scanf("%d", &num_voo);
            cancelar(voos, i, num_voo);

        }else if (strcmp(comando, "planejar") == 0) {
            char cod_origem[4];
            scanf("%s", cod_origem);
            Data data_ida = ler_data();
            Data data_volta = ler_data();
            //printf("%d %d\n", data_ida.ano, data_volta.ano);
            planejar(voos, i, data_ida, data_volta, cod_origem);
            break;
        }
    }
    return 0;
}