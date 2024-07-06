#include "headers.h"
int main (void){
    FILE *arquivo = fopen("palavras.txt","r");
    arvore *arv;

    arv = criaarvore();
    init(arquivo,arv);
    emordem(arv->raiz);
    int x=altura(arv->raiz);
    printf("%d",x);
   // while (b!=2){
   // b=menu();
   // }
    return 0;
}