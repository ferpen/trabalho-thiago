#include <stdio.h>
#include <stdlib.h>

typedef struct noh{
    int chave;
    char *lista;
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

//potenciação
int pow(int x){
    int z=2;
    if(x==0){
    return 1;
    }
    else{
        for (int i=0;i<=x;i++){
        z=z*x;
        }
        return z;
    }
}

noh *pegaraiz(arvore *arv){ // função para pegar a raiz da árvore, evita ter que passar a raiz como parametro;
if (arv!=NULL)
    return arv->raiz;
else
    return NULL;
}
void rebalancear(arvore *arv){

}

int insert (arvore *arv,int key,char *palavra){  // nome auto explicativo;
 noh *raiz=pegaraiz(arv),*pai=NULL;
    if(raiz!=NULL){
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
        raiz->lista = palavra;
        raiz->peso = 0;
        raiz->direita=NULL;
        raiz->esquerda = NULL;

        return 1;
    }
    else{
        return NULL;
    }
}

int init(FILE *arquivo, arvore *arv){
    if (arquivo != NULL && arv !=NULL){
    //declaração de variáveis locais;
    char a[50],*palavra;
    int i=0,key=0,letra;
    bool letras[26];
    while((palavra = fgets(a,50,arquivo)) != NULL){  // esse loop le as palavras do arquivo até chegar ao fim dele;

        //reinicia as váriaveis para a proxima palavra;
        for (i=0;i<26;i++){
            letras[i]=0;
        }
        key=0;
        i=0;

        while (a[i] != '\n'){                       //esse loop cria uma chave, somando os valores das letras da palavra e armazenando em "key";
            letra = (int)a[i]-97;
            if (letras[letra]==0){
            key+=pow(letra);        //pega o 2^n;
            letras[letra]=1;        //marca a letra como utilizada; 
            }
            i++;
        }
        //insere na árvore os valores;
        insert(arv,key,palavra);
    }
    return 1;
    }

    else{
        return NULL;
    }
}