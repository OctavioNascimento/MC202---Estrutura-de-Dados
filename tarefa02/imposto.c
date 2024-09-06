#include <stdio.h>
#define max 1000

double imporcentagem (double m);
double imposto_anual (double m);

void formatar_vetor (int n, double rendimentos[][15]) {
    /* recebe os inputs e os atribui ao vetor*/
    double m;
    for (int i = 0; i < n; i++) {
        double soma_renda = 0, soma_imposto = 0;
        for (int j = 0; j < 12; j++) {
            scanf("%lf", &m);
            double somaliquota;
            soma_renda += m;
            somaliquota = imporcentagem(m);
            soma_imposto += somaliquota;
            rendimentos[i][j] = somaliquota;
        }   
        rendimentos[i][13] = soma_renda;
        rendimentos[i][12] = soma_imposto;
    }   
    for (int i = 0; i < n; i++) {
        double a;
        double ptrend = rendimentos[i][13];
        scanf("%lf", &a); //a de abater
        rendimentos[i][13] = imposto_anual(ptrend - a);
        rendimentos[i][14] = rendimentos[i][13] - rendimentos[i][12];
    }
}

double imporcentagem (double m) {
    /* calcula o valor do imposto retido na fonte */
    double aliquota = 0;
    if (m <= 1499.15) {
        aliquota = 0;
    
    }else {
        if (m < 2246.75) {
            aliquota = (m - 1499.15) * 0.075;  
        
        }else{
            aliquota += (2246.75 - 1499.15) * 0.075;
            if (m < 2995.70) {
                aliquota += (m - 2246.75) * 0.15;
                }else{
                    aliquota += (2995.70 - 2246.75) * 0.15;
                    if (m < 3743.19) {
                        aliquota += (m - 2995.70) * 0.225;
                        }else {
                            aliquota += (3743.19 - 2995.70) * 0.225;
                            if (m > 3743.19) {
                                aliquota += (m - 3743.19) * 0.275;
                            }
                        }
                    }
                } 
            }
            return aliquota;
        }

double imposto_anual (double m) {
    /* calcula o valor do imposto anual retido na fonte */
    double aliquota = 0;
    if (m <= 18000.00) {
        aliquota = 0;
    
    }else {
        if (m < 26400.00) {
            aliquota = (m - 18000.00) * 0.075;  
        
        }else{
            aliquota += (26400.00 - 18000.00) * 0.075;
            if (m < 36000.00) {
                aliquota += (m - 26400.00) * 0.15;
                }else{
                    aliquota += (36000.00 - 26400.00) * 0.15;
                    if (m < 44400.00) {
                        aliquota += (m - 36000.00) * 0.225;
                        }else {
                            aliquota += (44400.00 - 36000.00) * 0.225;
                            if (m > 44400.00) {
                                aliquota += (m - 44400.00) * 0.275;
                            }
                        }
                    }
                } 
            }
            return aliquota;
        }

void printar(int n, double rendimentos[][15]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 15; j++) {
            printf("%0.2lf	", rendimentos[i][j]);        
        }
        printf("\n");
    }
}

int main() {
    int n;
    double rendimentos[max][15];
    scanf("%d", &n);
    formatar_vetor(n,rendimentos);
    printf("Jan	Fev	Mar	Abr	Mai	Jun	Jul	Ago	Set	Out	Nov	Dez	Retido	Devido	Ajuste\n");
    printar(n, rendimentos);
    return 0;
}