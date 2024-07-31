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

//----------Fun���es de iniciar as estruturas---------------------
arvore *criaarvore(){ 
    arvore *arv = malloc(sizeof(arvore));
    arv->raiz = NULL;
    arv->tamanho = 0;
    return arv;
}

lista *crialista(char *inserida){
    lista *list = malloc(sizeof(lista));
    int i = 0;
    for (i=0;i<50;i++){
        list->palavra[i]='\0';  //inicializando a string, se n�o fizer fica lixo de mem�ria;
    }
    list->proximo = NULL;
    i=0;
    while (inserida[i]!='\0'){
        list->palavra[i]=inserida[i];      //copia a palavra do ponteiro pra lista;
        i++;
    }
    return list;
}

int inserelista(lista *list,char *inserida){
	int i=0;
    while (list->proximo!=NULL){
        list=list->proximo;          //chega no �ltimo elemento alocado da lista, portanto essa casa ainda possui valor
    }
    list->proximo=malloc(sizeof(lista));   //aloca mem�ria pra pr�xima casa para guardar os dados
    list=list->proximo;
    list->proximo=NULL;          //seta o ponteiro do rec�m criado para NULL pra n�o ter lixo de mem�ria
     for (i=0;i<50;i++){
        list->palavra[i]='\0';  //inicializando a string da nova casa da lista, se n�o fizer fica lixo de mem�ria;
    }
    i=0;
    while (inserida[i]!='\0'){
        list->palavra[i]=inserida[i];      //copia a palavra do ponteiro pra lista;
        i++;
    }
    return 1;
}

//-----------MISC------------------
//Potencia��o
int potencia(int x){
    int z=1;
    int i;
    if(x==0){
    return 1;
    }
    else{
        for (i=0;i<x;i++){
        z=z*2;
        }
        return z;
    }
}
noh *pegaraiz(arvore *arv){ // fun��o para pegar a raiz da �rvore, evita ter que passar a raiz como parametro;
if (arv!=NULL)
    return arv->raiz;
else
    return NULL;
}


//------------------Fun��es Principais--------------------

//Fun��o de inser��o na arvore binaria
int insert (arvore *arv,int key,char *palavra){ 
 noh *raiz=pegaraiz(arv),*pai=NULL;

    if(raiz!=NULL){
        //encontra o lugar na �rvore e salva o n� pai;
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
        //quando sair aloca a mem�ria para o novo n� e coloca ele como filho e inicializa os valores do n� novo;
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

// Fun��o que carrega as palavras do arquivo na �rvore
int init(FILE *arquivo, arvore *arv){
    if (arquivo != NULL && arv !=NULL){
    //declara��o de vari�veis locais;
    char a[50],*palavra;
    int i=0,key=0;
    short int letras[26]={0},st,letra;
    while((palavra = fgets(a,50,arquivo)) != NULL){  // esse loop le as palavras do arquivo at� chegar ao fim dele;
        //reinicia as v�riaveis para a proxima palavra;
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
        //insere na �rvore os valores;
        insert(arv,key,palavra);
    }
    return 1;
    }
    else{
        return -1;
    }
}

//parte interativa com o usu�rio
int menu(){
    int x;
    system ("cls");
    printf("Escolha a opcao desejada do menu:\n\n");
    printf("(1) Procurar palavras\n");
    printf("(2) Sair do programa\n");
    scanf("%d",&x);
    return x;
}

//parte do acesso aos valores da �rvore
int criarchave(char *pesquisa){
    int chave=0;
    short int i=0,letras[26]={0},letra=0;

    while(pesquisa[i]!='\0'){
    letra=((int)pesquisa[i]-97);
    if (letra<0){
        letra+=32;
    }
    if (letra>=0 && letra <= 25 && letras[letra]==0){
        chave+=potencia(letra);
        letras[letra]++;
    }
    i++;
    }
    return chave;
}

//Fun��o que lista as palavras em determinada chave
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
        printf("Resultado:\n");
        while (list!=NULL){
            printf("%s\n",list->palavra);
            list=list->proximo;
        }
    }
    else{
        printf("Nenhuma palavra da estrutura possui essa combinacao de letras!\n");
    }
    printf("Pressione qualquer tecla para voltar ao menu!\n");
    char ret;
    fflush(stdin);
    getch(ret);
}
