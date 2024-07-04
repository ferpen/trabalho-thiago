#include <stdio.h>
#include <stdlib.h>

typedef struct noh{
    int chave;
    char valor[50];
    struct noh *esquerda;
    struct noh *direita;
    int peso;
}noh;

typedef struct arvore{
    int tamanho;
    noh *raiz;
}arvore;

arvore *criaarvore(){                       // o nome define;
    arvore *arv = malloc(sizeof(arvore));
    arv->raiz = NULL;
    arv->tamanho = 0;
    return arv;
}

noh *pegaraiz(arvore *arv){ // função para pegar a raiz da árvore, evita ter que passar a raiz como parametro;
if (arv!=NULL)
    return arv->raiz;
else
    return -1;
}
void rebalancear(arvore *arv){

}

int insert (arvore *arv,int key,char *palavra){  // nome auto explicativo;
 noh *raiz=pegaraiz(arv),*pai=NULL;
    if(raiz!=-1){
        //encontra o lugar na árvore e salva o nó pai;
        while(raiz!=NULL){
            if (raiz->chave<key){
                pai=raiz;
                raiz=raiz->direita;
            }
            else{
                pai=raiz;
                raiz=raiz->esquerda;
            }
        }
        //quando sair aloca a memória para o novo nó e coloca ele como filho (e inicializa os valores do nó novo;
        raiz=malloc(sizeof(noh));
        raiz->chave = key;
        raiz->valor = palavra;
        raiz->peso = 0;
        raiz->direita=NULL;
        raiz->esquerda = NULL;
        if (arv->raiz->peso > 1 || arv->raiz->peso < -1){
            rebalancear(arv)
        }


        return 0;
    }
    else{
        return -1;
    }
}

int init(FILE *arquivo, arvore *arv){
    if (arquivo != NULL && arv !=NULL){
    //declaração de variáveis locais;
    char a[50],*palavra;
    int i=0,key=0;

    while((palavra = fgets(a,50,arquivo)) != NULL){  // esse loop le as palavras do arquivo até chegar ao fim dele;
        while (a[i] != '\n'){                       //esse loop cria uma chave, somando os valores das letras da palavra e armazenando em "key";
            key += (int)a[i];
            i++;
        }
        //insere na árvore os valores;
        insert(arv,key,palavra);

        //reinicia as váriaveis para a proxima palavra;
        key=0;
        i=0;
    }
    return 0;
    }

    else{
        return -1;
    }
}