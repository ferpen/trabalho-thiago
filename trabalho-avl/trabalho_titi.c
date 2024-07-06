#include "headers.h"
#include <Windows.h>
int main (void){
    FILE *arquivo = fopen("palavras.txt","r");
    arvore *arv;
    int x;
    arv = criaarvore();
    init(arquivo,arv);
    
    return 0;
}