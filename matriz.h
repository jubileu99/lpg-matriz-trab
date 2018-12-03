typedef struct{
    float **m;
    int l,c
}Matriz;

void mostra_matriz(float **m,int l,int c);
float **transpo(float **m1,int l,int c);
float **soma(float **m1,float **m2,int l,int c);
float **sub(float **m1, float **m2, int l, int c);
float **multi(float **m1, float **m2, int l, int c, int l_a);
float **multiesc(float **m1,int l,int c,int n);
float **iguais(float **m1, float **m2, int l, int c);
float **simetrica(float **m1, int l, int c);