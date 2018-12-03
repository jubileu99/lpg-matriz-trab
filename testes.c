#include <stdio.h>

void main(int argc,char *argv[]){
    int m1[3][3] = {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };
    int m2[3][3] = {
        {1,1,1},
        {1,1,1},
        {1,1,1}
    };
    int m3[3][3];

    int l = 3, c = 3;

    int cont = 0,total = l*c;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(m1[i][j] == m2[i][j]){
                cont++;
            }
            //printf("[%d,%d] : %d \t ", i, j, m3[i][j]);
        }
        //printf("\n");
    }
    if(cont == total){
        printf("iguais \n");
    }else{
        printf("dife \n");
    }
}