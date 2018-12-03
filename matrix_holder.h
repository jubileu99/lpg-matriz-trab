#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

typedef struct{
	double **mat;
	int i;
	int j;
	char *ij;
} DynMatrix;

typedef struct{
	DynMatrix *Dm;
	int avaliable;
	int current;
} MatLib;

char *trans_ij(int i,int j);

void debug(int n);

void readFile(DynMatrix *mt, char *dir);

int charlen(double nm);

void writeFile(MatLib *mt, int ob_index,char *filename);

void ReadToMtrx( MatLib *p, char* filename);

void EndMatrix(MatLib *p);

void outMat(MatLib *p);

void AddMtrx( MatLib *p,int mode,char* dir);

void StartMatrix( MatLib *m);