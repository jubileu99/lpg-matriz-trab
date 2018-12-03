#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"
#include <string.h>

void ler_arquivo(Matriz *m1){

    FILE *f;
    f = fopen("arq1.txt","rt");
    if(f == NULL){
        m1->status = -1;
    }else{
        fscanf(f,"%d %d",&m1->l,&m1->c);
        m1->m = aloca(m1->l,m1->c);
        for (int i = 0; i < m1->l; i++){
            for(int j=0; j < m1->c; j++){
                fscanf(f,"%f",&m1->m[i][j]);
            }
        }
    }

    fclose(f);
}

int main(int argc,char *argv[]){
    //if(argc == 3 && strcmp(argv[1],"transpo") == 0){
        Matriz m1;
        printf("opa\n");
        ler_arquivo(&m1);
        if(m1.status == -1){
            printf("Erro ao ler arquivo!. Verifique os arquivos de entrada\n");
            return -1;
        }
        Matriz m2 = transpo(&m1);
        mostra_matriz(m2);
        printf("opa1\n");
        desaloca(&m1);
        desaloca(&m2);
        //escrever_arquivo(m3,argv[3]);
    //}

    return 0;
}