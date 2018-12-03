#include <stdio.h>

void main(int argc,char *argv[]){
    int m1[3][3] = {
        {5,6,7},
        {6,7,1},
        {1,1,1}
    };
    int m2[3][3] = {
        {3,3,3},
        {2,5,6},
        {-1,7,0}
    };
    int m3[3][3];

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            m3[i][j] = m1[i][j]*3;
            printf("[%d,%d] : %d \t ", i, j, m3[i][j]);
        }
        printf("\n");
    }
}