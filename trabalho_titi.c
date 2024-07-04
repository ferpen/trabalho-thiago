#include "headers.h"

//a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z
int main (void){
    FILE *arquivo = fopen("palavras.txt","r");
    arvore *arv;
    arv = criaarvore();
    init(arquivo,arv);

    return 0;
}