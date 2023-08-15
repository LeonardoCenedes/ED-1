#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tcol 8
#define tlin 8

typedef  struct n{
    int elem,lin,col;
    struct n *dir,*bai;
}no;

typedef struct m{
    no *lins[tlin], *cols[tcol];
}mt;

void inimt(mt *mat){
    for(int i=0;i<tlin;i++){
        mat->lins[i] = NULL;
    }
    for(int i=0;i<tcol;i++){
        mat->cols[i] = NULL;
    }
}

void inserirmt(mt *mat, int lin,int col,int elem){
    if(lin<0 || col<0 ||lin>=tlin || col>=tcol){
        printf("Numero invalido\n");
        return;
    }
    no *nv = malloc(sizeof(no));
    nv->bai = NULL;
    nv->dir = NULL;
    nv->col = col;
    nv->lin = lin;
    nv->elem = elem;

    if(mat->lins[lin] == NULL){
        mat->lins[lin] = nv;
    }
    else {
        no *aux = mat->lins[lin];
        while(aux->dir!=NULL && aux->dir->col < col){
            aux=aux->dir;
        }
        nv->dir = aux->dir;
        aux->dir = nv;
    }
    if(mat->cols[col] == NULL){
        mat->cols[col] = nv;
    }
    else{
        no *aux = mat->cols[col];
        while(aux->bai!=NULL && aux->bai->lin < lin){
            aux = aux->bai;
        }
        nv->bai = aux->bai;
        aux->bai = nv;
    }
}

void removermt(mt *mat, int lin, int col){
    no *aux = mat->cols[col];
    no *ant = NULL;
    while(aux!=NULL && aux->lin <lin){
        ant = aux;
        aux->bai;
    }
    if(ant != NULL){
        ant->bai = aux->bai;
    }
    else{
        mat->cols[col] = aux->bai;
    }
    free(aux);
    aux = mat->lins[lin];
    ant=NULL;
    while(aux!=NULL && aux->col < col){
        ant = aux;
        aux = aux->dir;
    }
    if(ant!=NULL){
        ant->dir = aux->dir;
    }
    else{
        mat->lins[lin] = aux->dir;
    }
    free(aux);
}

void imp(mt *mat){
    for(int i=0;i<tlin;i++){
        no *aux = mat->lins[i];
        for(int j=0;j<tcol;j++){
            if(aux!=NULL && aux->col==j){
                printf(" %d ", aux->elem);
                aux=aux->dir;
            }
            else{
                printf(" 0 ");
            }
        }
        printf("\n");
    }
}

void somark(mt *mat, int lin, int valork) {
    if (lin < 0 || lin >= tlin) {
        printf("Linha inválida\n");
        return;
    }
    for (int col = 0; col < tcol; col++) {
        no *aux = mat->lins[lin];
        no *ant = NULL;
        int found = 0;
        while (aux != NULL && aux->col < col) {
            ant = aux;
            aux = aux->dir;
        }
        if (aux != NULL && aux->col == col) {
            int nk = aux->elem + valork;

            if (nk == 0) {
                if (ant != NULL) {
                    ant->dir = aux->dir;
                } else {
                    mat->lins[lin] = aux->dir;
                }

                free(aux);
            } else {
                aux->elem = nk;
            }
        } else {
            int nk = valork;

            if (nk != 0) {
                no *nv = malloc(sizeof(no));
                nv->bai = NULL;
                nv->dir = NULL;
                nv->col = col;
                nv->lin = lin;
                nv->elem = nk;

                if (ant != NULL) {
                    ant->dir = nv;
                } else {
                    mat->lins[lin] = nv;
                }

                nv->dir = aux;
            }
        }
    }
}

int main()
{
    mt mat;
    inimt(&mat);
    inserirmt(&mat,0,1,0);
    inserirmt(&mat,0,2,3);
    inserirmt(&mat,1,0,2);
    inserirmt(&mat,2,1,2);
    inserirmt(&mat,5,1,9);
    inserirmt(&mat,7,3,6);
    inserirmt(&mat,4,8,2);
    inserirmt(&mat,3,6,9);
    inserirmt(&mat,1,5,7);
    inserirmt(&mat,3,2,1);
    imp(&mat);
    int lin, valork;
    scanf("%d %d", &lin, &valork);
    somark(&mat, lin, valork);
    printf("Matriz após a soma:\n");
    imp(&mat);
    return 0;
}
