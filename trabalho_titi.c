#include "headers.h"
int main (void){
    FILE *arquivo = fopen("palavras.txt","r");
    arvore *arv;
    short int b=0;
    arv = criaarvore();
    init(arquivo,arv);

   // while (b!=2){
   // b=menu();
   // }
    return 0;
}