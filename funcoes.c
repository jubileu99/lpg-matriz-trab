#include <stdio.h>
#include <stdlib.h>

#include "matrix_holder.h"
#include "funcoes.h"

void test(MatLib *newlib){
	printf("TEST");
	AddMtrx(newlib,1,"db/db1.txt");	// adiciona a primeira matriz
	transpor(newlib);
	outMat(newlib);				// Debug pra printar tudo
	EndMatrix(newlib);
}

void transpo(MatLib *p,char *dir1){
	AddMtrx(p,1,dir1);
	transpor(p);
	outMat(p);
	EndMatrix(p);
}

void transpor(MatLib *p){
	char len[255];
	snprintf(len,254,"%d %d",p->Dm[0].j,p->Dm[0].i);
	AddMtrx(p,0,len);
	for(int i=0;i < p->Dm[0].i;i++)
		for(int j=0;j < p->Dm[0].j;j++)
			p->Dm[1].mat[j][i] = p->Dm[0].mat[i][j];
}

void sub(MatLib *p){
	int i_f1 = p->Dm[0].i;
	int j_f1 = p->Dm[0].j;
	int i_f2 = p->Dm[1].i;
	int j_f2 = p->Dm[1].j;

	if(i_f1 != i_f2 || j_f1 != j_f2){
		printf("Nao eh de mesma ordem");
		return;
	}

	AddMtrx(p,0, trans_ij(i_f1,j_f1) );
	for(int i=0;i < i_f1;i++)
		for(int j=0;j < j_f1;j++)
			p->Dm[2].mat[i][j] = p->Dm[0].mat[i][j] - p->Dm[1].mat[i][j];
}

void sub_(MatLib *newlib,char *dir1, char *dir2){
	AddMtrx(newlib,1,dir1);
	AddMtrx(newlib,1,dir2);
	sub(newlib);
	outMat(newlib);
	EndMatrix(newlib);
}