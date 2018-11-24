#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"


void mostra_matriz(float **m,int l,int c){
    for (int i = 0; i < l; i++){
        for (int j = 0; j < l; j++){
            printf("[%d][%d] : %f\t", i, j,m[i][j]);
        }
        printf("\n");
    }
}

float **aloca(int l,int c){
    float **m3 = malloc(sizeof(float)*l);
    for(int i = 0; i < l; i++){
        m3[i] = malloc(sizeof(float)*c);
    }

    return m3;
}

void desaloca(float **m,int l){
    for(int i = 0; i < l; i++){ 
        free(m[i]);
    }
    free(m);
}

/*
    transposta : numero de l vira o de c, ordem altera, 3x2 vira 2x3, but se for quadrado nao altera.
*/

float **transpo(float **m1,int l,int c){
    float **m3 = aloca(c,l);

    for(int i = 0; i < c; i++){
        for(int j = 0; i < l; j++){
            m3[i][j] = m1[j][i];
        }
    }

    return m3;
}

/*
    soma de matrizes = mesma ordem, so somar posi. com posi.
*/

float **soma(float **m1,float **m2,int l,int c){
    float **m3 = aloca(l,c);

    for(int i = 0; i < l; i++){
        for(int j = 0; i < c; j++){
            m3[i][j] = m1[i][j] + m2[i][j];
        }
    }

    return m3;
}

/*
    subtracao de matrizes = mesma ordem, so sub posi. com posi.
*/

float **sub(float **m1, float **m2, int l, int c){
    float **m3 = aloca(l, c);

    for(int i = 0; i < l; i++){
        for(int j = 0; i < c; j++){
            m3[i][j] = m1[i][j] - m2[i][j];
        }
    }

    return m3;
}
/*
    multiplacao : precisa-se checar a ordem antes, A[2x3]  B[3x2] , col de A = linha de B, a ordem da matriz resultante R[2x2] 
*/

float **multi(float **m1, float **m2, int l, int c){
    float **m3 = aloca(l, c);

    for(int i = 0; i < l; i++){
        for(int j = 0; i < c; j++){
            for(int k = 0; k < l; k++){
                m3[i][j] += m1[i][j+k]*m2[j+k][j];
            }
        }
    }

    return m3;
}