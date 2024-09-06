typedef struct data {
    int dia, mes, ano;
} Data;

typedef struct voo {
    int num_voo;
    char cod_aero_origem[4];
    char cod_aero_destino[4];
    Data data;
    float valor;
} Voo;

typedef struct planejamento {
    int num_ida;
    int num_volta;
    float valor;
    Data data_ida;
    Data data_volta;
} Planejamento;

Data ler_data(); //ok

int compara_data(Data data1, Data data2); //ok

int diferenca_data(Data data1, Data data2); //ok

void cancelar(Voo voos[], int qtd_voos, int numero_voo); //ok

void alterar(Voo voos[], int qtd_voos, int numero_voo, float novo_valor); //ok

void planejar(Voo voos[], int qtd_voos, Data data_inicio, Data data_fim, char codigo_origem[]); //ok