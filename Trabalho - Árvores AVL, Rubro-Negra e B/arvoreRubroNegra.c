#include <stdio.h>
#include <stdlib.h>

int interacoes = 0;

// Structure to represent each
// node in a red-black tree
struct node {
	int d; // data
	int c; // 1-red, 0-black
	struct node* p; // parent
	struct node* r; // right-child
	struct node* l; // left child
};

// global root for the entire tree
struct node* root = NULL;
int *vetor; //cria uma cópia ordenada da árvore para inserir como pior caso
int posicoes = 0;

// function to perform BST insertion of a node
struct node* bst(struct node* trav, struct node* temp)
{
	// If the tree is empty,
	// return a new node
	if (trav == NULL)
		return temp;

	// Otherwise recur down the tree
	if (temp->d < trav->d)
	{
		trav->l = bst(trav->l, temp);
		trav->l->p = trav;
	}
	else if (temp->d > trav->d)
	{
		trav->r = bst(trav->r, temp);
		trav->r->p = trav;
	}
    interacoes++;

	// Return the (unchanged) node pointer
	return trav;
}

// Function performing right rotation
// of the passed node
void rightrotate(struct node* temp)
{
	struct node* left = temp->l;
	temp->l = left->r;
	if (temp->l)
		temp->l->p = temp;
	left->p = temp->p;
	if (!temp->p)
		root = left;
	else if (temp == temp->p->l)
		temp->p->l = left;
	else
		temp->p->r = left;
	left->r = temp;
	temp->p = left;
    interacoes++;
}

// Function performing left rotation
// of the passed node
void leftrotate(struct node* temp)
{
	struct node* right = temp->r;
	temp->r = right->l;
	if (temp->r)
		temp->r->p = temp;
	right->p = temp->p;
	if (!temp->p)
		root = right;
	else if (temp == temp->p->l)
		temp->p->l = right;
	else
		temp->p->r = right;
	right->l = temp;
	temp->p = right;
    interacoes++;
}

// This function fixes violations
// caused by BST insertion
void fixup(struct node* root, struct node* pt)
{
	struct node* parent_pt = NULL;
	struct node* grand_parent_pt = NULL;

	while ((pt != root) && (pt->c != 0)
		&& (pt->p->c == 1))
	{
		interacoes++;
        parent_pt = pt->p;
		grand_parent_pt = pt->p->p;

		/* Case : A
			Parent of pt is left child
			of Grand-parent of
		pt */
		if (parent_pt == grand_parent_pt->l)
		{

			struct node* uncle_pt = grand_parent_pt->r;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if (uncle_pt != NULL && uncle_pt->c == 1)
			{
				grand_parent_pt->c = 1;
				parent_pt->c = 0;
				uncle_pt->c = 0;
				pt = grand_parent_pt;
			}

			else {

				/* Case : 2
					pt is right child of its parent
					Left-rotation required */
				if (pt == parent_pt->r) {
					leftrotate(parent_pt);
					pt = parent_pt;
					parent_pt = pt->p;
				}

				/* Case : 3
					pt is left child of its parent
					Right-rotation required */
				rightrotate(grand_parent_pt);
				int t = parent_pt->c;
				parent_pt->c = grand_parent_pt->c;
				grand_parent_pt->c = t;
				pt = parent_pt;
			}
		}

		/* Case : B
			Parent of pt is right
			child of Grand-parent of
		pt */
		else {
			struct node* uncle_pt = grand_parent_pt->l;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt->c == 1))
			{
				grand_parent_pt->c = 1;
				parent_pt->c = 0;
				uncle_pt->c = 0;
				pt = grand_parent_pt;
			}
			else {
				/* Case : 2
				pt is left child of its parent
				Right-rotation required */
				if (pt == parent_pt->l) {
					rightrotate(parent_pt);
					pt = parent_pt;
					parent_pt = pt->p;
				}

				/* Case : 3
					pt is right child of its parent
					Left-rotation required */
				leftrotate(grand_parent_pt);
				int t = parent_pt->c;
				parent_pt->c = grand_parent_pt->c;
				grand_parent_pt->c = t;
				pt = parent_pt;
			}
		}
	}

	root->c = 0;
}

// Function to print inorder traversal
// of the fixated tree
void inorder(struct node* trav)
{
	if (trav == NULL)
		return;
	inorder(trav->l);
	//printf("%d ", trav->d);
    vetor[posicoes++] = trav->d;
	inorder(trav->r);
}

// driver code
int main(){
    int item; //recebe o valor aleatório para adicionar à árvor
    int tamAmostra = 63; //quantidade de nodes a serem adicionadas
    int *values; // armazena os nodes
    values = malloc(tamAmostra*sizeof(struct node));
    vetor = malloc(tamAmostra*sizeof(int));

    
    //serão geradas 10 árvores
    for (int j = 0; j < 2; j++){
        printf("---------------------------------------------\n");
        printf("\t\tCaso medio\n\n");
        printf("Tamanho dos Conjuntos | Esforco Computacional\n");

        //determina a quantidade de nodes
        int tamAmostra = rand() % 100;
        values = realloc(values, tamAmostra*sizeof(struct node));
        vetor = realloc(vetor, tamAmostra*sizeof(int));

        //para cada árvore, adiciona seus nodes com valores aleatórios
        for(int i=0; i < tamAmostra; i++){
            item = rand() % 1000;

            //prepara o node para ser inserido
            struct node* temp = (struct node*)malloc(sizeof(struct node));
            temp->r = NULL;
            temp->l = NULL;
            temp->p = NULL;
            temp->d = item; //recebe o valor aleatório
            temp->c = 1; //cor vermelha

            //insere o node
            root = bst(root, temp);
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
            //printf("%i ", item);

            //prepara o node para ser inserido
            struct node* temp = (struct node*)malloc(sizeof(struct node));
            temp->r = NULL;
            temp->l = NULL;
            temp->p = NULL;
            temp->d = item; //recebe o valor aleatório
            temp->c = 1; //cor vermelha

            //insere o node
            root = bst(root, temp);
        }
        
        printf("\n\t   %d         | \t%d\n", tamAmostra, interacoes);
        interacoes = 0;
        posicoes = 0;
        root = NULL;
    }
    //inorder(root);

    return 0;
}
