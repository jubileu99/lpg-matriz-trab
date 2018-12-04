#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"
#include <string.h>

/*
Matriz transpo(Matriz *m1);
Matriz soma(Matriz *m1,Matriz *m2);
Matriz sub(Matriz *m1, Matriz *m2);
Matriz multi(Matriz *m1, Matriz *m2);
Matriz multiesc(Matriz *m1, int n);
int iguais(Matriz *m1,Matriz *m2);
int simetrica(Matriz *m1);
*/

int main(int argc,char argv[]){
    //Pegando os argumentos da commandline
	
	if(strcmp(argv[1],"transpo") == 0 && argc == 4){
        	Matriz m1;
        	readFile(&m1,argv[2]);
        	Matriz m2 = transpo(&m1);
		writeFile(&m2,argv[3]);
	}else if(strcmp(argv[1],"soma") == 0 && argc == 5){
        	Matriz m1,m2,m3;
		printf("soma aqui");
        	readFile(&m1,argv[2]);
        	readFile(&m2,argv[3]);
        	m3 = soma(&m1,&m2);
        	writeFile(&m3,argv[4]);
	}else if(strcmp(argv[1],"sub") == && argc == 5){
        	Matriz m1, m2, m3;
        	printf("sub aqui");
        	readFile(&m1, argv[2]);
        	readFile(&m2, argv[3]);
        	m3 = sub(&m1, &m2);
        	writeFile(&m3, argv[4]);
    	}else if(strcmp(argv[1],"multi") == 0 && argc == 5){
        	Matriz m1, m2, m3;
        	printf("multi aqui");
        	readFile(&m1, argv[2]);
        	readFile(&m2, argv[3]);
        	m3 = multi(&m1, &m2);
        	writeFile(&m3, argv[4]);
    	}else if(strcmp(argv[1],"multiesc") == 0 && argc == 5){
        	Matriz m1, m2;
        	printf("multiesc aqui");
        	readFile(&m1, argv[2]);
        	m2 = multiesc(&m1,argv[3]);
        	writeFile(&m2, argv[4]);
    	}else if(strcmp(argv[1],"iguais") == 0 && argc == 4){
        	Matriz m1, m2;
        	printf("iguais aqui");
        	readFile(&m1, argv[2]);
        	readFile(&m1, argv[3]);
        	if (iguais(&m1,&m2))
            		printf("Iguais");
        	else
            		printf("Diferentes");
    	}else if(strcmp(argv[1],"simetrica") == && argc == 3){
        	Matriz m1;
        	readFile(&m1, argv[2]);
        	if(simetrica(&m1))
            		printf("Simetrica");
        	else
            		printf("nao simetricas");
    	}else{
		printf("Metodo invalido");
		//EndMatrix(&newlib);
	}

}
