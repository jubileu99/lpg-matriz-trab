#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>

#include "matrix_holder.h"

/*
typedef struct{
	double **mat;
	int i;
	int j;
} DynMatrix;

typedef struct{
	DynMatrix *Dm;
	int avaliable;
	int current;
} MatLib;
*/

/*
MatLib *p;

free(p->Dm);

//ou

for(int c=0;c < p->current;c++)
	for(int i=0;i < p->Dm[c]->i;i++)
		free(p->Dm[c]->mat[i]);
free(p->Dm);

*/

void debug(int n){
	printf("\n\nASD %d\n\n",n);
}


void readFile(DynMatrix *mt, char *dir){
	FILE *fh = fopen(dir, "r");

	if (fh == NULL){
		printf("file'%s' does not exist\n", dir);
		return;
	}

	const size_t line_size = 255;
	char* line = malloc(line_size);
	int ip = 0;
	int i,j;
	fgets(line, line_size-1, fh);
	if( sscanf(line,"%d %d",&i,&j) != 2){
		printf("Tamanho de matriz inv�lido\n");
		free(line);
		return;}
	while (fgets(line, line_size-1, fh) != NULL)  {
			int jp = 0;
			double num;
			while(sscanf(line,"%lf",&num) == 1){
				int bs=0;
				for(int c=0;c < 255;c++){	// (1) Procurar fim de arquivo ou linha
					if(line[c] == ' '){
						bs = c;break;}
					if(line[c] == '\n' || line[c] == '\0'){
						bs = -1;break;}}	// (1)
				if(bs == -1){				// (2) Fim de arquivo ou linha aconteceu (bs == -1) reseta a line
					memset(line,0,255);}
				int lt = bs+1;				// (3) apagar a string at� o espaco + 1
				while(lt < 255){
					line[lt-bs-1] = line[lt];//puxa pra traz
					lt++;}
				lt-=bs+1;
				while(lt < 255){
					line[lt] = ' ';			//coloca os espacos no final
					lt++;}					// (3)
				//=====================
				mt->mat[ip][jp] = num;
				jp++;
				if(jp > j){break;}
			}
			ip++;if(ip > i){break;}
	}

	free(line);    // dont forget to free heap memory
	fclose(fh);
}

char *dtos(double nm){
	char *st = malloc(sizeof(char)*50);
	snprintf(st,50,"%.3lf",nm);
	return st;
}

void writeFile(MatLib *mt, int ob_index,char *filename){
	FILE *fh = fopen(filename, "wt");
	if (fh == NULL){
		printf("file'%s' block\n", filename);
		return;
	}
	printf("Writing %d matrix to %s\n",ob_index,filename);
	int id = mt->Dm[ob_index].i, jd = mt->Dm[ob_index].j;
	char *tij = trans_ij(id,jd);
	int len_d = strlen(tij);
	fwrite(tij,sizeof(char),len_d,fh);
	fwrite("\n",sizeof(char),1,fh);
	for(int i=0;i < id;i++){
		for(int j=0;j < jd;j++){
			char *stnm = dtos(mt->Dm[ob_index].mat[i][j]);
			int dl = strlen(stnm);
			fwrite(stnm,sizeof(char),dl,fh);
			fwrite(" ",sizeof(char),1,fh);
			//printf("%s ",stnm);
		}
		//printf("\n");
		fwrite("\n",sizeof(char),1,fh);
	}
	fclose(fh);
}

void ReadToMtrx( MatLib *p, char* filename){
	readFile(&p->Dm[p->current-1],filename);
}

void EndMatrix(MatLib *p){
	for(int c=0;c < p->current-1;c++){
		for(int i=0;i < p->Dm[c].i;i++)
			free(p->Dm[c].mat[i]);
	}
	//free(p->Dm);
}

void outMat(MatLib *p){

	printf("%d matrizes lidas\n",p->current);
	printf("%d blocos no total\n----------\n\n",p->avaliable);
	for(int c=0;c < p->current;c++){
		printf("%d matriz (%d|%d):>\n",c+1,p->Dm[c].i,p->Dm[c].j);
		for(int di=0;di < p->Dm[c].i;di++){
			for(int dj=0;dj < p->Dm[c].j;dj++){
				printf("%.2lf | ",p->Dm[c].mat[di][dj]);
			}
			printf("\n");
		}
		printf("\n");
	}

}

char *trans_ij(int i,int j){
	char *len = malloc(sizeof(char)*255);
	snprintf(len,254,"%d %d",i,j);
	return len;
}


void AddMtrx( MatLib *p,int mode,char* dir){
	int i,j;
		if(mode == 0){//															Criar matriz vazia, com propor��es passadas no dir
			if(sscanf(dir,"%d %d",&i,&j) != 2){
				printf("Tamanho de matriz inv�lido\n");
				return;
			}
			if(p->avaliable < p->current){
				printf("Matriz nao foi inicializada!");
				//StartMatrix()
				return;
			}
			DynMatrix new;//Criar e allocar a nova matriz, com base em numeros, nao em arquivo
			new.i=i;new.j=j;
			new.mat = malloc(sizeof(double*)*i);
			for(int c=0;c<=i;c++)
				new.mat[c] = malloc(sizeof(double)*j);
			p->Dm[p->current] = new;
			p->current++;
			p->Dm = realloc(p->Dm,(sizeof(DynMatrix) ) );
			p->avaliable++;

		}else if(mode == 1){//															Criar matriz com arquivo
			FILE *arqivo;
			if( arqivo = fopen(dir,"rt") ){
				char line[20];
				fgets(line, 20, arqivo);
				if( sscanf(line,"%d %d",&i,&j) != 2){
					printf("Tamanho de matriz inv�lido\n");
					return;
				}

				DynMatrix new;
				//printf("%d avaliable & %d current\n",p->avaliable,p->current);
				if(p->avaliable < p->current){
					printf("Matriz nao foi inicializada!");
					//StartMatrix()
					return;
				}
				//new = malloc(sizeof(DynMatrix) + sizeof(int)*2);
				new.i=i;new.j=j;
				new.mat = malloc(sizeof(double*)*i);
				for(int c=0;c<=i;c++)
					new.mat[c] = malloc(sizeof(double)*j);
				p->Dm[p->current] = new;
				p->current++;
				p->Dm = realloc(p->Dm,sizeof(DynMatrix) + sizeof(int)*2 );
				p->avaliable++;
				ReadToMtrx(p,dir);
			}else{
				printf("Arquivo inexistente\n");
			}
		}else
			printf("Modo invalido!!!\n");

}

void StartMatrix( MatLib *m){
	m->current = 0;
	m->Dm = malloc(sizeof(DynMatrix));
	m->avaliable = 1;
}

