#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

void printar_arranhaceu(int tam_grade, int** vetor_arranhaceu);
int verifica_violacao(int tam_grade, int** vetor_arranhaceu, int lin, int col, int numero);

//*função principal alvo da recursão
int arranhaceu(int tam_grade, int** vetor_arranhaceu, int lin, int col) { 

    //caso de parada //*ok
    if (lin == (tam_grade + 1) && col == (1)) {
        return true;
    }
    
    int verifica = verifica_violacao(tam_grade, vetor_arranhaceu, lin, col, (vetor_arranhaceu[lin][col]));

    for (int numero = vetor_arranhaceu[lin][col]; numero <= tam_grade + 1; numero++) {
        vetor_arranhaceu[lin][col] = numero;

        
        if (numero == tam_grade + 1) {
            vetor_arranhaceu[lin][col] = 0;
            return false;
        }

        verifica = verifica_violacao(tam_grade, vetor_arranhaceu, lin, col, numero);

        if (verifica == true){
            if (col < tam_grade) {
                if(arranhaceu(tam_grade, vetor_arranhaceu, lin, (col+1))==true){
                    return true;
                }
            } else {
                if(arranhaceu(tam_grade, vetor_arranhaceu, (lin+1), 1)==true){
                    return true;
                }
            }
        }
    }

    //TODO: se a celula != 0 --> celula +1
    //TODO: se movimento inválido (verifica_violação == 1) --> volta para a celula e sobrescreve

    //vetor_arranhaceu[lin][col] = 8;

    //?recursão

    return verifica;
}

//função print
void printar_arranhaceu(int tam_grade, int** vetor_arranhaceu) { //*ok
    for (int i = 1; i < (tam_grade + 1); i++) {
        for (int j = 1; j < (tam_grade + 1); j++) {
            printf("%d ", vetor_arranhaceu[i][j]);
        }
        printf("\n");
    }
}

int verifica_violacao(int tam_grade, int** vetor_arranhaceu, int lin, int col, int numero) {

    int col_dif_zero = 0, lin_dif_zero = 0, altura_lin = 0, altura_col = 0, total_lin = 0, total_col = 0;
    

    if (numero == false) {
        return false;
    } 

    for (int i = 1; i < (tam_grade + 1); i++) {

        if (vetor_arranhaceu[lin][i] != 0) { //verifica se posição da linha diferente de 0
            lin_dif_zero++;
        }
        if (vetor_arranhaceu[lin][i] > altura_lin) { //verifica quantos arranhaceus estão sendo vistos
                altura_lin = vetor_arranhaceu[lin][i];
                total_lin += 1;
        }
       
        if (vetor_arranhaceu[i][col] != 0) { //verifica se posição da linha diferente de 0
            col_dif_zero++;
        }
        if (vetor_arranhaceu[i][col] > altura_col) { //verifica quantos arranhaceus estão sendo vistos
            altura_col = vetor_arranhaceu[i][col];
            total_col += 1;
        }


        if ((vetor_arranhaceu[lin][i] == numero && i != col) || (lin_dif_zero == (tam_grade) && total_lin != vetor_arranhaceu[lin][0])) { //verfica se ta repetindo na coluna
            return false;
        }
        
        if ((vetor_arranhaceu[i][col] == numero && i != lin) || (col_dif_zero == (tam_grade) && total_col != vetor_arranhaceu[0][col])) { //verfica se ta repetindo na linha
            return false;
        }


    }

    col_dif_zero = 0;
    lin_dif_zero = 0;
    altura_lin = 0;
    altura_col = 0;
    total_lin = 0;
    total_col = 0;

    for (int i = tam_grade; i > 0; i--) {
        if (vetor_arranhaceu[lin][i] != 0) { //verifica se posição da linha diferente de 0
            lin_dif_zero++;
        }
        if (vetor_arranhaceu[lin][i] > altura_lin) { //verifica quantos arranhaceus estão sendo vistos
                altura_lin = vetor_arranhaceu[lin][i];
                total_lin += 1;
        }
       
        if (vetor_arranhaceu[i][col] != 0) { //verifica se posição da linha diferente de 0
            col_dif_zero++;
        }
        if (vetor_arranhaceu[i][col] > altura_col) { //verifica quantos arranhaceus estão sendo vistos
            altura_col = vetor_arranhaceu[i][col];
            total_col += 1;
        }

        if (lin_dif_zero == tam_grade && total_lin != vetor_arranhaceu[lin][tam_grade+1]) { //verfica se ta repetindo na coluna
            return false;
        }
        
        if (col_dif_zero == tam_grade && total_col != vetor_arranhaceu[tam_grade+1][col]) { //verfica se ta repetindo na linha
            return false;
        }

    }


    return true;
}


int main() {
    int tam_grade; //n
    scanf("%d", &tam_grade);
    
    int** vetor_arranhaceu = (malloc((tam_grade + 2) * sizeof(int*)));
    for (int i = 0; i < tam_grade + 2; i++) {
        vetor_arranhaceu[i] = malloc((tam_grade + 2) * sizeof(int)); 
    }

    for (int i = 0; i < (tam_grade + 2); i++) {
        for (int j = 0; j < (tam_grade + 2); j++) {
            scanf("%d", &vetor_arranhaceu[i][j]);
        }
    }
    
    arranhaceu(tam_grade, vetor_arranhaceu, 1, 1);
    printar_arranhaceu(tam_grade, vetor_arranhaceu);

}