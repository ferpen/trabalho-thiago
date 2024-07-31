#include "headers.h"
int main (void){
    FILE *arquivo = fopen("palavras.txt","r");
    arvore *arv;
    char pesquisa[255];
    int x;
    arv = criaarvore();
    init(arquivo,arv);
    while (x!=2){
    	int i;
        for (i=0;i<200;i++){
        pesquisa[i]='\0';
        }
        x=menu();
        printf("O programa foi encerrado!");
        if(x==1){
        system("cls");
        printf("Digite as letras que deseja procurar:\n");
        fflush(stdin);
        gets(pesquisa);
        x=criarchave(pesquisa);
        listarpalavras(x,arv);
        }
    }
    return 0;
}
