#include "headers.h"
int main (void){
    FILE *arquivo = fopen("palavras.txt","r");
    arvore *arv;
    char pesquisa[200];
    int x;
    arv = criaarvore();
    init(arquivo,arv);
    while (x!=2){
        for (int i=0;i<200;i++){
        pesquisa[i]='\0';
        }
        x=menu();
        if(x==1){
        system("cls");
        printf("digite a sua pesquisa:\n");
        scanf("%s",pesquisa);
        x=criarchave(pesquisa);
        listarpalavras(x,arv);
        }
    }
    return 0;
}