#include <stdio.h>
#include <stdlib.h>

//--------Definindo estruturas (lista e arvore binaria de busca)-------------

typedef struct lista{
    char palavra[50];
    struct lista *proximo;
}lista;

typedef struct noh{
    int chave;
    lista *lista;
    struct noh *esquerda;
    struct noh *direita;
}noh;

typedef struct arvore{
    int tamanho;
    noh *raiz;
}arvore;

//----------Funçções de iniciar as estruturas---------------------
arvore *criaarvore(){ 
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

int inserelista(lista *list,char *inserida){
    while (list->proximo!=NULL){
        list=list->proximo;          //chega no último elemento alocado da lista, portanto essa casa ainda possui valor
    }
    list->proximo=malloc(sizeof(lista));   //aloca memória pra próxima casa para guardar os dados
    list=list->proximo;
    list->proximo=NULL;          //seta o ponteiro do recém criado para NULL pra não ter lixo de memória
     for (int i=0;i<50;i++){
        list->palavra[i]='\0';  //inicializando a string da nova casa da lista, se não fizer fica lixo de memória;
    }
    int i=0;
    while (inserida[i]!='\0'){
        list->palavra[i]=inserida[i];      //copia a palavra do ponteiro pra lista;
        i++;
    }
    return 1;
}

//-----------MISC------------------
//Potenciação
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


//------------------Funções Principais--------------------

//Função de inserção na arvore binaria
int insert (arvore *arv,int key,char *palavra){ 
 noh *raiz=pegaraiz(arv),*pai=NULL;

    if(raiz!=NULL){
        //encontra o lugar na árvore e salva o nó pai;
        while(raiz!=NULL){
            if (raiz->chave==key){
                inserelista(raiz->lista,palavra);
                return 1;
            }
            else if (raiz->chave<key){
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
        raiz->direita=NULL;
        raiz->esquerda = NULL;
        if(raiz->chave>pai->chave){
            pai->direita=raiz;
        }
        else{
            pai->esquerda=raiz;
        }
        arv->tamanho++;
        }
        return 1;
    }
    else{
        raiz=malloc(sizeof(noh));
        arv->raiz=raiz;
        raiz->chave = key;
        raiz->lista = crialista(palavra);
        raiz->direita=NULL;
        raiz->esquerda = NULL;
        arv->tamanho++;
    }
    return 1;
}

// Função que carrega as palavras do arquivo na árvore
int init(FILE *arquivo, arvore *arv){
    if (arquivo != NULL && arv !=NULL){
    //declaração de variáveis locais;
    char a[50],*palavra;
    int i=0,key=0;
    short int letras[26]={0},st,letra;
    while((palavra = fgets(a,50,arquivo)) != NULL){  // esse loop le as palavras do arquivo até chegar ao fim dele;
        //reinicia as váriaveis para a proxima palavra;
        for (i=0;i<26;i++){
            letras[i]=0;
        }
        key=0;
        i=0;
        st=0;
        while (a[i] != '\0'){                       //esse loop cria uma chave, somando os valores das letras da palavra e armazenando em "key";
            letra = ((int)a[i]-97);
            if(letra<0){
                letra+=32;
            }
            if (letras[letra]==0){
            key+=potencia(letra);                                  //pega o 2^n;               
            letras[letra]++;                        //marca a letra como utilizada; 
            }
            i++;
        }
        //insere na árvore os valores;
        insert(arv,key,palavra);
    }
    return 1;
    }
    else{
        return -1;
    }
}

//parte interativa com o usuário
int menu(){
    int x;
    system ("cls");
    printf("digite o numero da opcao desejada:\n");
    printf("1-procurar palavras\n");
    printf("2-sair\n");
    scanf("%d",&x);
    return x;
}

//parte do acesso aos valores da árvore
int criarchave(char *pesquisa){
    int chave=0;
    short int i=0,letras[26]={0},letra=0;

    while(pesquisa[i]!='\0'){
    letra=((int)pesquisa[i]-97);
    if (letra<0){
        letra+=32;
    }
    if (letras[letra]==0){
        chave+=potencia(letra);
        letras[letra]++;
    }
    i++;
    }
    return chave;
}

//Função que lista as palavras em determinada chave
void listarpalavras(int key,arvore *arv){
    noh *no=pegaraiz(arv);
    lista *list;
    while (no->chave!=key){
        if(no->chave<key){
            no=no->direita;
        }
        else{
            no=no->esquerda;
        }
        if(no==NULL){
            break;
        }
    }
    if(no!=NULL){
        list=no->lista;
        printf("resultado:\n");
        while (list!=NULL){
            printf("%s\n",list->palavra);
            list=list->proximo;
        }
    }
    else{
        printf("nenhuma palavra da estrutura possui essa combinacao de letras\n");
    }
    printf("digite 1 para voltar ao menu\n");
    scanf("%d",&key);
}