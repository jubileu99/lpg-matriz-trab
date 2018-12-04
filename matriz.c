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
        for(int j = 0; j < m2.c; j++){
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
Matriz multiesc(Matriz *m1, char *ns){
    int n;
    sscanf(ns,"%d",&n);
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

//0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=0=

char *trans_ij(int i, int j){
    char *len = malloc(sizeof(char) * 255);
    snprintf(len, 254, "%d %d", i, j);
    return len;
}

char *dtos(double nm){
	char *st = malloc(sizeof(char)*50);
	snprintf(st,50,"%.3lf",nm);
	return st;
}

void readFile(Matriz *mt, char *dir){
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
				mt->m[ip][jp] = num;
				jp++;
				if(jp > j){break;}
			}
			ip++;if(ip > i){break;}
	}

	free(line);    // dont forget to free heap memory
	fclose(fh);
}

void writeFile(Matriz *mt, char *filename){
    FILE *fh = fopen(filename, "wt");
    if (fh == NULL){
        printf("file '%s' deu ruim\n", filename);
        return;}
    printf("Writing to %s\n", filename);
    int id = mt->l, jd = mt->c;
    char *tij = trans_ij(id, jd);
    int len_d = strlen(tij);
    fwrite(tij, sizeof(char), len_d, fh);
    fwrite("\n", sizeof(char), 1, fh);
    for (int i = 0; i < id; i++){
        for (int j = 0; j < jd; j++){
            char *stnm = dtos(mt->m[i][j]);
            int dl = strlen(stnm);
            fwrite(stnm, sizeof(char), dl, fh);
            fwrite(" ", sizeof(char), 1, fh);
            //printf("%s ",stnm);
        }
        //printf("\n");
        fwrite("\n", sizeof(char), 1, fh);
    }
    fclose(fh);
}
