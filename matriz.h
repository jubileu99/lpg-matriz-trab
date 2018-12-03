typedef struct{
    float **m;
    int l,c;
    int status;
}Matriz;

float **aloca(int l,int c);
void desaloca(Matriz *m1);
void mostra_matriz(Matriz m1);
Matriz transpo(Matriz *m1);
Matriz soma(Matriz *m1,Matriz *m2);
Matriz sub(Matriz *m1, Matriz *m2);
Matriz multi(Matriz *m1, Matriz *m2);
Matriz multiesc(Matriz *m1, int n);
int iguais(Matriz *m1,Matriz *m2);
int simetrica(Matriz *m1);