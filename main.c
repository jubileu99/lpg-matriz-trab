#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"

float **ler_arquivo(int* l,int* c,char* dir){
    FILE *f;
    f = fopen("arquivos/matriz.txt","rt");
    if(f == NULL){ return NULL; };

    fscanf(f,"%d %d",&l,&c);

    float **m = malloc(sizeof(float)**l);
    for (int i = 0; i < l; i++){
        m[i] = malloc(sizeof(float) **c);
    }

    for (int i = 0; i < *l; i++){
        for(int j=0; j < *c; j++){
            fscanf(f,"%f",&m[i][j]);
        }
    }

    fclose(f);

    return m;
}

int main(int argc,char *argv[]){
    int l,c;
    float **m = ler_arquivo(&l,&c,&);  

    if(m == NULL){ return -1; };

    mostra_matriz(m,l,c);
    // float **m3 = transpo(m,l,c);
    // mostra_matriz(m3,l,c);

    desaloca(m,l);

    return 0;
}