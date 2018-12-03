#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"


void mostra_matriz(Matriz m1){
    for (int i = 0; i < m1.l; i++){
        for (int j = 0; j < m1.c; j++){
            printf("[%d][%d] : %f\t", i, j,m1.m[i][j]);
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

void desaloca(Matriz *m1){
    for(int i = 0; i < m1->l; i++){ 
        free(m1->m[i]);
    }
    free(m1->m);
}

/*
    transposta : numero de l vira o de c, ordem altera, 3x2 vira 2x3, but se for quadrado nao altera.
*/

Matriz transpo(Matriz *m1){
    Matriz m2;
    m2.c = m1->l;
    m2.l = m1->c;
    m2.m = aloca(m2.l, m2.c);

    for(int i = 0; i < m2.l; i++){
        for(int j = 0; i < m2.c; j++){
            m2.m[i][j] = m1->m[j][i];
        }
    }

    return m2;
}

/*
    soma de matrizes = mesma ordem, so somar posi. com posi.
*/

Matriz soma(Matriz *m1, Matriz *m2){
    Matriz m3;
    m3.m = aloca(m3.l,m3.c);

    for(int i = 0; i < m1->l; i++){
        for(int j = 0; i < m1->c; j++){
            m3.m[i][j] = m1->m[i][j] + m2->m[i][j];
        }
    }

    return m3;
}

/*
    subtracao de matrizes = mesma ordem, so sub posi. com posi.
*/

Matriz sub(Matriz *m1, Matriz *m2){
    Matriz m3;
    m3.m = aloca(m1->l, m1->c);

    for(int i = 0; i < m1->l; i++){
        for(int j = 0; i < m1->c; j++){
            m3.m[i][j] = m1->m[i][j] - m2->m[i][j];
        }
    }

    return m3;
}
/*
    multiplacao : precisa-se checar a ordem antes, A[2x3]  B[3x2] , col de A = linha de B, a ordem da matriz resultante R[2x2]
    K = Numero de colunas de A ou o numero de linhas de B 
*/

Matriz multi(Matriz *m1,Matriz *m2){
    Matriz m3;
    m3.m = aloca(m1->l, m2->c);

    for(int i = 0; i < m1->l; i++){
        for(int j = 0; i < m2->c; j++){
            m3.m[i][j] = 0;
            for(int k = 0; k < m1->c; k++){
                m3.m[i][j] += m1->m[i][k]*m2->m[k][j];
            }
        }
    }

    return m3;
}
/*

    Multiplicacao por escaalar 

*/
Matriz multiesc(Matriz *m1, int n){
    Matriz m3;
    m3.m = aloca(m1->l, m1->c);

    for(int i = 0; i < m1->l; i++){
        for(int j = 0; j < m1->c; j++){
            m3.m[i][j] = m1->m[i][j]*n;
        }
    }

    return m3;
}
/*

    Matrizes iguais

    0 = nao iguais
    1 = iguais
    -1 = erro de ordem

*/
int iguais(Matriz *m1,Matriz *m2){

    if(m1->c != m2->c || m1->l != m2->l){
        return -1;
    }

    int cont = 0,total = m1->l*m1->c;

    for(int i = 0; i < m1->l; i++){
        for(int j = 0; j < m1->c; j++){
            if(m1->m[i][j] == m2->m[i][j]){
                cont++;
            }
        }
    }
    if(cont == total)
        return 1;
    else
        return 0;
}
/*

    Matriz simetrica, faz a transposta e verifica se a transposta é igual a original.

    1 = simetrica
    0 = nao é simetrica

*/

int simetrica(Matriz *m1){
    Matriz m2 = transpo(m1);

    if(iguais(m1,&m2))
        return 1;
    else
        return 0;
}