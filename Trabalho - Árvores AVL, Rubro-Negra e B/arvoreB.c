#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MIN 2

struct Nodo {
    int item[MAX + 1];
    int cont;
    struct Nodo *link[MAX + 1];
};

typedef struct Nodo nodo;

nodo *root;

// criação de um novo nodo
nodo* novoNodo(int item, nodo *filho){
    nodo *novo;
    novo = (struct Nodo*) malloc(sizeof(nodo));
    novo->item[1] = item;
    novo->cont = 1;
    novo->link[0] = root;
    novo->link[1] = filho;

    return novo;
}

// inserção
void insere(int item, int pos, nodo *node, nodo *filho){
    int j = node->cont;
    while(j > pos){
        node->item[j+1] = node->item[j];
        node->link[j+1] = node->link[j];
        j--;
    }
    node->item[j+1] = item;
    node->link[j+1] = filho;
    node->cont++;
}

// split nodo
void splitNodo(int item, int *pval, int pos, nodo *node, nodo *filho, nodo **novoNodo){
    int median, j;

    if(pos > MIN){
        median = MIN + 1;
    } else{
        median = MIN;
    }

    *novoNodo = (struct Nodo*) malloc(sizeof(nodo));
    j = median + 1;
    while(j <= MAX){
        (*novoNodo)->item[j - median] = node->item[j];
        (*novoNodo)->link[j - median] = node->link[j];
        j++;
    }
    node->cont = median;
    (*novoNodo)->cont = MAX - median;

    if(pos <= MIN){
        insere(item, pos, node, filho);
    } else{
        insere(item, pos - median, *novoNodo, filho);
    }

    *pval = node->item[node->cont];
    (*novoNodo)->link[0] = node->link[node->cont];
    node->cont--;
}

// setando o valor do nodo
int setValor(int item, int *pval, nodo *node, nodo **filho){
    int pos;
    if(!node){
        *pval = item;
        *filho = NULL;
        return 1;
    }

    if (item < node->item[1]){
        pos = 0;
    } else{
        for (pos = node->cont; item < node->item[pos] && pos > 1; pos--);
        if(item == node->item[pos]){
            printf("Proibido repetir elemento\n");
            return 0;
        }
    }

    if(setValor(item, pval, node->link[pos], filho)){
        if(node->cont < MAX){
            insere(*pval, pos, node, *filho);
        } else{
            splitNodo(*pval, pval, pos, node, *filho, filho);
            return 1;
        }
    }
    return 0;
}

// insere o valor
void insercao(int item){
    int bandeira, i;
    nodo *filho;

    bandeira = setValor(item, &i, root, &filho);
    if(bandeira){
        root = novoNodo(i, filho);
    }
}

// copia o sucessor
void copiaSucessor(nodo *meuNodo, int pos){
    nodo *aux;
    aux = meuNodo->link[pos];

    for(; aux->link[0] != NULL;){
        aux = aux->link[0];
    }

    meuNodo->item[pos] = aux->item[1];
}

void rotacaoDireita(nodo *meuNodo, int pos){
    nodo *x = meuNodo->link[pos];
    int j = x->cont;

    while(j > 0){
        x->item[j + 1] = x->item[j];
        x->link[j + 1] = x->link[j];
    }

    x->item[1] = meuNodo->item[pos];
    x->link[1] = x->link[0];
    x->cont++;

    x = meuNodo->link[pos - 1];
    meuNodo->item[pos] = x->item[x->cont];
    meuNodo->link[pos] = x->link[x->cont];
    x->cont--;
}

void rotacaoEsquerda(nodo *meuNodo, int pos){
    int j = 1;
    nodo *x = meuNodo->link[pos - 1];

    x->cont++;
    x->item[x->cont] = meuNodo->item[pos];
    x->link[x->cont] = meuNodo->link[pos]->link[0];

    x = meuNodo->link[pos];
    meuNodo->item[pos] = x->item[1];
    x->link[0] = x->link[1];
    x->cont--;

    while(j <= x->cont){
        x->item[j] = x->item[j + 1];
        x->link[j] = x->link[j + 1];
    }
}

void merge(nodo *meuNodo, int pos){
    int j = 1;
    nodo *x1 = meuNodo->link[pos], *x2 = meuNodo->link[pos - 1];

    x2->cont++;
    x2->item[x2->cont] = meuNodo->item[pos];
    x2->link[x2->cont] = meuNodo->link[0];

    while(j <= x1->cont){
        x2->cont++;
        x2->item[x2->cont] = x1->item[j];
        x2->link[x2->cont] = x1->link[j];
        j++;
    }

    j = pos;
    while(j < meuNodo->cont){
        meuNodo->item[j] = meuNodo->item[j + 1];
        meuNodo->link[j] = meuNodo->link[j + 1];
        j++;
    }
    meuNodo->cont--;
    free(x1);
}

// ajustando o nodo
void ajustandoNodo(nodo *meuNodo, int pos){
    if(!pos){
        if(meuNodo->link[1]->cont > MIN){
            rotacaoEsquerda(meuNodo, 1);
        } else{
            merge(meuNodo, 1);
        }
    } else{
        if(meuNodo->cont != pos){
            if(meuNodo->link[pos - 1]->cont > MIN){
                rotacaoDireita(meuNodo, pos);
            } else{
                if(meuNodo->link[pos + 1]->cont > MIN){
                    rotacaoEsquerda(meuNodo, pos + 1);
                } else{
                    merge(meuNodo, pos);
                }
            }
        } else{
            if(meuNodo->link[pos - 1]->cont > MIN){
                rotacaoDireita(meuNodo, pos);
            } else{
                merge(meuNodo, pos);
            }
        }
    }
}

// atravessando a arvore
void imprime(nodo *meuNodo){
    int i;
    if(meuNodo){
        for(i = 0; i < meuNodo->cont; i++){
            imprime(meuNodo->link[i]);
            printf("%d ", meuNodo->item[i+1]);
        }
        imprime(meuNodo->link[i]);
    }
}

int main(){
    int item, ch;

    insercao(8);
    insercao(9);
    insercao(10);
    insercao(23);
    insercao(11);
    insercao(15);
    insercao(16);
    insercao(17);
    insercao(18);
    insercao(20);
    
    imprime(root);
    printf("\n");
}