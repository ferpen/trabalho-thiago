#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    char palavra[50];
    struct lista *proximo;
}lista;

typedef struct noh{
    int chave;
    lista *lista;
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

lista *crialista(char *inserida){
    lista *list = malloc(sizeof(lista));
    for (int i=0;i<50;i++){
        list->palavra[i]='\0';  //inicializando a string, se não fizer fica lixo de memória;
    }
    list->proximo = NULL;
    int i=0;
    while (inserida[i]!='\0'){
        list->palavra[i]=inserida[i];      //copia a palavra do ponteiro pra lista;
        i++;
    }
    return list;
}
void inserelista(lista *list,char *inserida){
    while (list->proximo!=NULL){
        list=list->proximo;          //chega no último elemento alocado da lista, portanto essa casa ainda possui valor
    }
    list->proximo=malloc(sizeof(list));   //aloca memória pra próxima casa para guardar os dados
    list->proximo->proximo=NULL;          //seta o ponteiro do recém criado para NULL pra não ter lixo de memória
     for (int i=0;i<50;i++){
        list->proximo->palavra[i]='\0';  //inicializando a string da nova casa da lista, se não fizer fica lixo de memória;
    }
    int i=0;
    while (inserida[i]!='\0'){
        list->proximo->palavra[i]=inserida[i];      //copia a palavra do ponteiro pra lista;
        i++;
    }
}
//potenciação
int potencia(int x){
    int z=1;
    if(x==0){
    return 1;
    }
    else{
        for (int i=0;i<x;i++){
        z=z*2;
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
            if (raiz->chave==key){
                inserelista(raiz->lista,palavra);
                break;
            }
            if (raiz->chave<key){
                pai=raiz;
                raiz=raiz->direita;
            }
            else{
                pai=raiz;
                raiz=raiz->esquerda;
            }
        }
        if(raiz==NULL){
        //quando sair aloca a memória para o novo nó e coloca ele como filho e inicializa os valores do nó novo;
        raiz=malloc(sizeof(noh));
        raiz->chave = key;
        raiz->lista = crialista(palavra);
        raiz->peso = 0;
        raiz->direita=NULL;
        raiz->esquerda = NULL;
        if(raiz->chave>pai->chave){
            pai->direita=raiz;
        }
        else{
            pai->esquerda=raiz;
        }
        }
        return 1;
    }
    else{
        return -1;
    }
}

// pega as palavras do arquivo e armazena na estrutura (sem defeitos no momento)
int init(FILE *arquivo, arvore *arv){
    if (arquivo != NULL && arv !=NULL){
    //declaração de variáveis locais;
    char a[50],*palavra;
    int i=0,key=0,letra;
    short int letras[26];
    while((palavra = fgets(a,50,arquivo)) != NULL){  // esse loop le as palavras do arquivo até chegar ao fim dele;

        //reinicia as váriaveis para a proxima palavra;
        for (i=0;i<26;i++){
            letras[i]=0;
        }
        key=0;
        i=0;

        while (a[i] != '\n'){                       //esse loop cria uma chave, somando os valores das letras da palavra e armazenando em "key";
            letra = ((int)a[i]-97);
            if (letras[letra]==0 && letra>-1){
            key+=potencia(letra);                                  //pega o 2^n;               
            letras[letra]++;                        //marca a letra como utilizada; 
            }
            i++;
        }
        //insere na árvore os valores;
        int t = insert(arv,key,palavra);
        printf("%d/",t);
    }
    return 1;
    }

    else{
        return -1;
    }
}