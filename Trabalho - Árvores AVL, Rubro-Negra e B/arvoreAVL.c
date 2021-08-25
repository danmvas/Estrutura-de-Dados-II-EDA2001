#include <stdio.h>
#include <stdlib.h>

int interacoes = 0;

struct Nodo{
    int chave;
    struct Nodo *esquerda;
    struct Nodo *direita;
    int altura;    
}; typedef struct Nodo nodo;

int altura(nodo *N){
    if(N == NULL){
        return 0;
    }
    return N->altura;
}

int max(int a, int b){
    return (a > b)? a : b;
}

nodo* novoNodo(int chave){
    interacoes++;
    struct Nodo* novo = (struct Nodo*) malloc(sizeof(struct Nodo));
    novo->chave = chave;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1;

    return(novo);
}

nodo* rotacaoDireita(nodo* node){
    interacoes++;
    struct Nodo* x = node->esquerda;
    struct Nodo* T2 = x->direita;

    //rotação
    x->direita = node;
    node->esquerda = T2;

    //novas alturas
    node->altura = max(altura(node->esquerda), altura(node->direita))+1;
    x->altura = max(altura(x->esquerda), altura(x->direita))+1;

    //retorna a árvore rotacionada
    return x;
}

nodo* rotacaoEsquerda(nodo* node){
    interacoes++;
    struct Nodo* x = node->direita;
    struct Nodo* T2 = x->esquerda;

    //rotação
    x->esquerda = node;
    node->direita = T2;

    //novas alturas
    node->altura = max(altura(node->esquerda), altura(node->direita))+1;
    x->altura = max(altura(x->esquerda), altura(x->direita))+1;

    //retorna a árvore rotacionada
    return x;
}

int balanco(nodo* N){
    if(N == NULL)
        return 0;
    return altura(N->esquerda) - altura(N->direita) && interacoes++; 
}

nodo* inserir(nodo* node, int chave){
    interacoes++;
    // 1° insere normalmente
    if(node == NULL)
        return novoNodo(chave);

    if(chave < node->chave){
        node->esquerda = inserir(node->esquerda, chave);
    }
    else if(chave > node->chave){
        node->direita = inserir(node->direita, chave);
    } else{
        return node;
    }

    // 2° atualiza a altura do nodo ancestral
    node->altura = 1 + max(altura(node->esquerda), altura(node->direita));

    // 3° obtem o valor de balanco do ancestral para verificar se o nó
    // se tornou desequilibrado
    int balance = balanco(node);

    // se estiver desbalanceado, têm-se 4 casos

    // caso de balanço à esquerda esquerda
    if(balance > 1 && chave < node->esquerda->chave)
        return rotacaoDireita(node);

    // caso de balanço à direita direita
    if(balance < -1 && chave > node->direita->chave)
        return rotacaoEsquerda(node);

    // caso de balanço à esquerda direita
    if(balance > 1 && chave > node->esquerda->chave){
        node->esquerda = rotacaoEsquerda(node->esquerda);
        return rotacaoDireita(node);
    }

    // caso de balanço à direita esquerda
    if(balance < -1 && chave < node->direita->chave){
        node->direita = rotacaoDireita(node->direita);
        return rotacaoEsquerda(node);
    }

    // returna o nodo sem mudanças
    return node;

}

void preOrdenacao(nodo* root){
    if(root != NULL){
        printf("%d ", root->chave);
        preOrdenacao(root->esquerda);
        preOrdenacao(root->direita);
    }
}

nodo* root = NULL;
int *vetor;
int posicoes = 0;

void inorder(nodo* trav)
{
	if (trav == NULL)
		return;
	inorder(trav->esquerda);
	//printf("%d ", trav->chave);
    vetor[posicoes++] = trav->chave;
	inorder(trav->direita);
}


 void insertion_sort(int *v, int n) {
   interacoes++;
   int aux;
   for (int i = 0; i < n; i++) {
     int j=i;
     while ((j>0) &&(v[j-1]>v[j])) {
       aux=v[j];
       v[j]=v[j-1];
       v[j-1]=aux;
       j--;
     }
   }
 }

///////////////////////////////////////////////////////////////////////////////////////

int main(){
    int item; //recebe o valor aleatório para adicionar à árvor
    int tamAmostra = 63; //quantidade de nodes a serem adicionadas
    nodo *values; // armazena os nodes
    values = (nodo*)malloc(tamAmostra*sizeof(nodo));
    vetor = (int*)malloc(tamAmostra*sizeof(int));

    
    //serão geradas 10 árvores
    for (int j = 0; j < 10; j++){
        printf("---------------------------------------------\n");
        printf("\t\tCaso medio\n\n");
        printf("Tamanho dos Conjuntos | Esforco Computacional\n");

        //determina a quantidade de nodes
        int tamAmostra = rand() % 100;
        values = (nodo*)realloc(values, tamAmostra*sizeof(nodo));
        vetor = (int*)realloc(vetor, tamAmostra*sizeof(int));

        //para cada árvore, adiciona seus nodes com valores aleatórios
        for(int i=0; i < tamAmostra; i++){
            item = rand() % 1000;

            //insere o node
            root = inserir(root,item);
        }
        
        printf("\t   %d         | \t%d\n", tamAmostra, interacoes);
        interacoes = 0;
        inorder(root);
        
    
        printf("---------------------------------------------\n");
        printf("\t\tPior Caso (decrescente)\n\n");
        printf("Tamanho dos Conjuntos | Esforco Computacional\n");
    
        //para cada árvore, adiciona os mesmos nodes em ordem crescente
        for(int i=0; i < tamAmostra; i++){
            item = vetor[i];
            root = inserir(root,item);
        }
        
        printf("\n\t   %d         | \t%d\n", tamAmostra, interacoes);
        interacoes = 0;
        posicoes = 0;
        root = NULL;
    }
    //inorder(root);

    return 0;
}