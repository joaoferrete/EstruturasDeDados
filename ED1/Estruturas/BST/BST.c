#include <stdio.h>                              //Inclusão das bibliotecas
#include <stdlib.h>

typedef struct{                                 //Estrutura do elemento de informação utilizado em lista e na BST
    long long value;
}Info;

typedef struct tnode{                           //Estrutura de Nó de uma lista
    struct tnode * next;
    Info * info;
}listNode;

typedef struct bstno{                           //Estrutura de uma BST
    struct bstno *left, *right;
    Info * info;
}BST;
typedef BST Node;

typedef struct{                                 //Estrutura da 'cabeça' de uma lista
    listNode * first;
    int size;
}List;

typedef struct qnode{                           //Estrutura node de uma fila;
    struct qnode * next;
    BST * info;
}queueNode;

typedef struct{                                 //Estrutura da 'cabeça' de fila
    queueNode * first;
    int size;
}Queue;

int isEmptyList (List * lst){                   //Função que verifica se uma lista é ou não vazia;
    if(!lst || lst->size==0) return 1;
    return 0;
}

void freeList(List * lst){                      //Função que libera o espaço de memória utilizado pela lista.
    if(!lst) return;
    listNode *aux = lst->first;
    while(lst->first){
        if(lst->first)lst->first=aux->next;
        free(aux->info);
        free(aux);
        aux=lst->first;
    }
    free(lst);
}
Info * createInfo(long long num){               //Função que cria um elemento de informação, aloca espaço e inicializa os campos
    Info * inf=NULL;
    inf=(Info *) malloc(sizeof(Info));
    if(!inf) return NULL;
    inf->value=num;
    return inf;
}

List * createList(){                             //Função que cria uma lista (cabeça) e inicializa seus campos
    List * lst=NULL;
    lst=(List *)malloc(sizeof(List));
    if (!lst) return NULL;
    lst->size=0;
    lst->first=NULL;
    return lst;
}
listNode * createNodeList(Info * inf){           //Função que cria um nó para lista, aloca espaço e inicializa os campos;
    if(!inf) return NULL;
    listNode * node=NULL;
    node=(listNode *) malloc(sizeof(listNode));
    if (!node) return NULL;
    node->next=NULL;
    node->info = inf;
    return node;
}

int insertLastList(List * lst, Info *inf){      //Função que insere um elemento no fim de uma lista
    if(!lst || !inf) return 0;
    if(!lst->first){
        lst->first=createNodeList(inf);
    }else{
        listNode * aux=lst->first;
        while(aux->next) aux=aux->next;
        aux->next=createNodeList(inf);
    }
    lst->size++;
    return 1;

}

Info * deleteFirstList(List * lst){             //Função de apaga o primeiro elemento de uma lista
    if(!lst) return NULL;
    listNode * aux=lst->first->next;
    Info* ret=lst->first->info;
    free(lst->first);
    lst->first=aux;
    lst->size--;
    return ret;
}

Queue * createQueue(){                          //Função que cria a 'cabeça' de uma fila e inicia seus campos
    Queue * q=NULL;
    q=(Queue *) malloc(sizeof(Queue));
    if(!q) return NULL;
    q->first=NULL;
    q->size=0;
    return q;
}

int isEmptyQueue(Queue * queue){                //Função que verifica se uma fila está vazia ou não
    if (!queue || queue->size==0) return 1;
    return 0;
}

queueNode * createNodeQueue(BST * inf){         //Função responsável por criar um nó para uma fila e inicializar os campos, já atribuindo um elemento de informação
    if(!inf) return NULL;
    queueNode * q=NULL;
    q=(queueNode *) malloc(sizeof(queueNode));
    q->info=inf;
    q->next=NULL;
    return q;
}

int insertQueue(Queue * queue, BST * inf){      //Função que insere um elemento numa fila da forma exigida pelo TAD
    if(!queue || !inf) return 0;
    if(!queue->first) queue->first=createNodeQueue(inf);
    else{
        queueNode * aux=queue->first;
        while(aux->next) aux = aux->next;
        aux->next=createNodeQueue(inf);
    }
    queue->size++;
    return 1;
}

BST * deleteQueue(Queue * queue){               //Função que deleta um elemento da fila, da forma exigida pelo TAD
    if(isEmptyQueue(queue)) return NULL;
    BST * ret=NULL;
    queueNode * aux=NULL, * aux2=NULL;
    aux2=queue->first;
    aux=queue->first->next;
    ret=queue->first->info;
    free(aux2);
    queue->first=aux;
    queue->size--;
    return ret;
}

BST* createBST(void){                           //Função que cria um nó para uma BST sem atribuir um elemento de informação
    BST * ptr=NULL;
    ptr=(BST *) malloc(sizeof(BST));
    if(!ptr) return NULL;
    ptr->left=NULL;
    ptr->right=NULL;
    ptr->info=NULL;
    return ptr;
}

Node *createNode(Info * inf){                  //Função que cria um node para BST atribuindo um elemento de informação
    Node * ptr=NULL;
    ptr=(Node *) malloc(sizeof(Node));
    if(!ptr || !inf) return NULL;
    ptr->left=NULL;
    ptr->right=NULL;
    ptr->info=inf;
    return ptr;
}

BST* leftBST(BST * ptr){                        //Função responsável por retornar o ponteiro para a sub-árvore esquerda
    if(!ptr) return ptr;
    return ptr->left;
}
BST * rightBST(BST * ptr){                      //Função responsável por retornar o ponteiro para a sub-árvore direita
    if(!ptr) return ptr;
    return ptr->right;
}

Info * rootBST(BST * ptr){                      //Função responsável por retornar um ponteiro para o elemento de informação da raiz
    if(!ptr) return NULL;
    return ptr->info;
}

long long valueBST(BST * ptr){                  //Função responsável por retornar o valor armazenado pelo elemento de informação de uma raiz;
    if(!ptr) return 0;
    else return rootBST(ptr)->value;
}

int isEmptyBST(BST* ptr){                       //Função que verifica se uma árvore é vazia
    if(!ptr) return 1;
    return 0;
}

BST * searchBST(BST * ptr, Info * inf){         //Função responsável por buscar um elemento na árvore e retornar um ponteiro para ele caso ele esteja presente;
    if(!ptr) return NULL;
    if(rootBST(ptr)->value == inf->value) return ptr;
    else if(rootBST(ptr)->value < inf->value) return searchBST(rightBST(ptr), inf);
    return searchBST(leftBST(ptr), inf);
}

void destroyBST(BST * ptr){                     //Função responsável por apagar toda a árvore;
    if(!ptr) return;
    destroyBST(leftBST(ptr));
    destroyBST(rightBST(ptr));
    free(ptr->info);
    free(ptr);
    return;
}

int heightBST (BST * ptr){                      //Função que retorna a altura de uma árvore
    int r, l;
    if(!ptr) return 0;
    r=1+heightBST(rightBST(ptr));
    l=1+heightBST(leftBST(ptr));
    if(r>l) return r;
    return l;
}

BST * insertBST(BST * ptr, Info * inf){         //Função que insere um elemento na BST de forma ordenada
    if(!ptr) return createNode(inf);
    if(rootBST(ptr)->value < inf->value) ptr->right=insertBST(rightBST(ptr), inf);
    else if (rootBST(ptr)->value > inf->value) ptr->left=insertBST(leftBST(ptr), inf);
    return ptr;
}

BST * findLargestElementBST(BST * ptr){         //Função que retorna um ponteiro para o maior elemento de uma árvore BST
    if(!ptr) return NULL;
    if(ptr && !ptr->right) return ptr;
    return findLargestElementBST(rightBST(ptr));
}

BST * findSmallestElementBST(BST * ptr){        //Função que retorna um ponteiro para o menor elemento de uma árvore BST;
    if(!ptr) return NULL;
    if(ptr && !ptr->left) return ptr;
    return findSmallestElementBST(leftBST(ptr));
}

BST * mirrorBST(BST * ptr){                     //Função que espelha uma BST
    if(!ptr) return NULL;
    BST *aux1=NULL, *aux2=NULL;
    aux1=mirrorBST(rightBST(ptr));
    aux2=mirrorBST(leftBST(ptr));
    ptr->left=aux1;
    ptr->right=aux2;
    return ptr;
}

BST * deleteBST(BST * ptr, Info * inf){         //Função responsável por apagar um elemento de uma árvore
    if(!ptr) return ptr;
    if(rootBST(ptr)->value == inf->value){
        if(!rightBST(ptr)){
            BST * aux=leftBST(ptr);
            free(ptr->info);
            free(ptr);
            return aux;
        }else if(!leftBST(ptr)){
            BST * aux = rightBST(ptr);
            free (ptr->info);
            free(ptr);
            return aux;
        }else{
            BST * aux = findSmallestElementBST(rightBST(ptr));
            rootBST(ptr)->value=aux->info->value;
            ptr->right = deleteBST(rightBST(ptr), rootBST(ptr));
        }
    }else if(rootBST(ptr)->value > inf->value) ptr->left=deleteBST(leftBST(ptr), inf);
    else if(rootBST(ptr)->value < inf->value) ptr->right = deleteBST(rightBST(ptr), inf);
    return ptr;
}

void printBST(BST * ptr){                       //Função responsável por imprimir a árvore através do percurso pre-ordem
    if(!ptr) return;
    printf("%lld ", ptr->info->value);
    printBST(leftBST(ptr));
    printBST(rightBST(ptr));
}

int weightBST(BST * ptr){                       //Função que retorna o peso (quantidade de elementos) de uma árvore
    if(!ptr)return 0;
    return (1 + weightBST(rightBST(ptr)) + weightBST(leftBST(ptr)));
}

int totalExternalNodes(BST * ptr){              //Função que retorna o número de folhas de uma árvore
    if (!ptr) return 0;
    if(!ptr->right && !ptr->left) return 1;
    return totalExternalNodes(rightBST(ptr)) + totalExternalNodes(leftBST(ptr));
}

int totalInternalNodes(BST * ptr){              //Função responsável por retornar o numero de raizes de uma BST
    if (!ptr) return 0;
    if(!ptr->right && !ptr->left) return 0;
    return 1 + totalExternalNodes(rightBST(ptr)) + totalExternalNodes(leftBST(ptr));
}

int isOrderedBST(BST * ptr){                    //Função responsável por verificar se uma BST é, ou não, ordenada
    if(!ptr) return 1;
    if(leftBST(ptr) && rootBST(leftBST(ptr))->value > rootBST(ptr)->value) return 0;
    if(rightBST(ptr) && rootBST(rightBST(ptr))->value < rootBST(ptr)->value) return 0;
    return isOrderedBST(rightBST(ptr)) && isOrderedBST(leftBST(ptr));
}

void auxPreOrderTransversalBST(BST *ptr, List * lst){   //Função que auxilia na criação da lista em percurso pre-order
	if (!ptr || !lst) return;
	insertLastList(lst, createInfo(ptr->info->value));
	auxPreOrderTransversalBST(leftBST(ptr), lst);
	auxPreOrderTransversalBST(rightBST(ptr), lst);
}

List * preOrderTransversalBST(BST * ptr){               //Função que cria uma lista em percurso pre-order
	if (!ptr) return NULL;
	List * lst=createList();
	if(!lst) return NULL;
	auxPreOrderTransversalBST(ptr, lst);
	return lst;
}

void auxInOrderTransversalBST(BST *ptr, List *lst){     //Função responsável por auxiliar na criação de uma lista no percurso in-order
	if (!ptr || !lst) return;
	auxInOrderTransversalBST(leftBST(ptr), lst);
	insertLastList(lst, createInfo(ptr->info->value));
	auxInOrderTransversalBST(rightBST(ptr), lst);
}

List *inOrderTransversalBST(BST *ptr){                  //Função que cria uma lista através do percurso in-Order
	if (!ptr) return NULL;
	List * lst=createList();
	if(!lst) return NULL;
	auxInOrderTransversalBST(ptr, lst);
	return lst;
}

void auxPosOrderTransversalBST(BST *ptr, List *lst){   //Função que auxilia na criação da lista no percurso pos-order
	if (!ptr || !lst) return;
	auxPosOrderTransversalBST(leftBST(ptr), lst);
	auxPosOrderTransversalBST(rightBST(ptr), lst);
	insertLastList(lst, createInfo(ptr->info->value));
}

List *posOrderTransversalBST(BST *ptr){                 //Função que cria e retorna uma lista a partir do percurso pos-order
	if (!ptr) return NULL;
	List * lst=createList();
	if(!lst) return NULL;
	auxPosOrderTransversalBST(ptr, lst);
	return lst;
}

List * levelOrderTransversalBST(BST * ptr){             //Função que cria uma lista a partir do percurso em níveis
	if(!ptr) return NULL;
	List * lst=createList();
	Queue * que=createQueue();
	BST * aux=NULL;
	Info * inf=NULL;
	if(!lst || !que) return NULL;
	insertQueue(que, ptr);
	while(!isEmptyQueue(que)){
		aux=deleteQueue(que);
		inf=createInfo(rootBST(aux)->value);
		insertLastList(lst, inf);
		if(leftBST(aux)) insertQueue(que, leftBST(aux));
		if(rightBST(aux)) insertQueue (que, rightBST(aux));
	}
	free(que);
	return lst;
}

List * takeWhileList(List *lst, Info * inf){            //Função que cria uma nova lista a partir do início até um elemento específico da lista original;
	listNode * ptr=NULL;
	List * lstfin=createList();
	Info * info = NULL;
	if(!lstfin) return NULL;
	for(ptr=lst->first; ptr && ptr->info->value != inf->value; ptr=ptr->next){
		info=createInfo(ptr->info->value);
		insertLastList(lstfin, info);
	}
	return lstfin;
}

List * dropWhileList(List * lst, Info * inf){           //Função que cria uma lista a partir de um elemento até o fim da lista original;
	listNode * ptr=NULL;
	List * lstfin=createList();
	Info * info=NULL;
	if(!lstfin) return NULL;
	for(ptr=lst->first; ptr && ptr->info->value != inf->value; ptr=ptr->next);
	if(ptr){
		for(ptr=ptr->next; ptr; ptr=ptr->next){
			info=createInfo(ptr->info->value);
			insertLastList(lstfin, info);
		}
	}
	return lstfin;

}

BST * treeFromInOrderPreOrderBST(List * preOrder, List * inOrder){  //Função responsável por criar uma árvore a partir dos percursos preOrder e inOrder
	BST *ptr=NULL;
	List *esq=NULL, *dir=NULL;
	Info * inf=NULL;
	if(isEmptyList(preOrder) || isEmptyList(inOrder)) return NULL;
	inf=deleteFirstList(preOrder);
	ptr=createNode(inf);
	if(!ptr)return NULL;
	esq=takeWhileList(inOrder, inf);
	dir=dropWhileList(inOrder, inf);
	ptr->left=treeFromInOrderPreOrderBST(preOrder, esq);
	ptr->right=treeFromInOrderPreOrderBST(preOrder, dir);
	return ptr;
}
void printList(List * lst){                                         //Função responsável por imprimir os elementos de uma lista
    listNode * aux=NULL;
    if(isEmptyList(lst) || !lst->first) return;
    aux=lst->first;
    while(aux){
        printf("%lld ", aux->info->value);
        aux=aux->next;
    }
    printf("\n");
}

int main(){
    BST * bst = NULL, * aux = NULL;
    List * lst = NULL, *lst2 = NULL;
    int a;
    long long b;

    while(1){
        /*printf("\n\n");
        printf("| 1 - Inserir Elementos            |\n");
        printf("| 2 - Remover Elementos            |\n");
        printf("| 3 - Imprimir Árvore (Pre-order)  |\n");
        printf("| 4 - Buscar Elemento              |\n");
        printf("| 5 - Altura da Árvore             |\n");
        printf("| 6 - Maior Elemento               |\n");
        printf("| 7 - Menor Elemento               |\n");
        printf("| 8 - Espelhar Árvore              |\n");
        printf("| 9 - Árvore Vazia?                |\n");
        printf("| 10 - Peso da Árvore              |\n");
        printf("| 11 - Qtd. Nós Internos           |\n");
        printf("| 12 - Qts Nós Externos            |\n");
        printf("| 13 - Está Ordenada?              |\n");
        printf("| 14 - Pre-Order List              |\n");
        printf("| 15 - In-Order List               |\n");
        printf("| 16 - Pos-Order List              |\n");
        printf("| 17 - Level Order List            |\n");
        printf("| 18 - Árvore a partir de listas   |\n");
        printf("| 0 -  Sair                        |\n");*/
        printf("\n\n");
        scanf("%d", &a);
        switch(a){
            case 1:
                //printf("Insira o elemento\n");
                scanf("%lld", &b);
                bst=insertBST(bst, createInfo(b));
                break;
            case 2:
                scanf("%lld", &b);
                bst=deleteBST(bst, createInfo(b));
                break;
            case 3:
                printBST(bst);
                break;
            case 4:
                aux=NULL;
                scanf("%lld", &b);
                aux=searchBST(bst, createInfo(b));
                if(aux) printf("Elemento Encontrado!\n");
                else printf("Elemento Não Encontrado\n");
                break;
            case 5:
                printf("A altura é %d\n", heightBST(bst));
                break;
            case 6:
                printf("O maior elemento é %lld\n", valueBST(findLargestElementBST(bst)));
                break;
            case 7:
                printf("O menor elemento é %lld\n", valueBST(findSmallestElementBST(bst)));
                break;
            case 8:
                mirrorBST(bst);
                printf("A Árvore foi espelhada\n");
                break;
            case 9:
                if(isEmptyBST(bst))printf("ÁRVORE VAZIA\n");
                else printf("ÁRVORE NÃO VAZIA\n");
                break;
            case 10:
                printf("O peso é %d\n", weightBST(bst));
                break;
            case 11:
                printf("O número de nós internos é %d\n", totalInternalNodes(bst));
                break;
            case 12:
                printf("O numero de nós externos é %d\n", totalExternalNodes(bst));
                break;
            case 13:
                if(isOrderedBST(bst))printf("ÁRVORE ORDENADA\n");
                else printf("ÁRVORE NÃO ORDENADA\n");
                break;
            case 14:
                lst=preOrderTransversalBST(bst);
                printList(lst);
                freeList(lst);
                break;
            case 15:
                lst=inOrderTransversalBST(bst);
                printList(lst);
                freeList(lst);
                break;
            case 16:
                lst=posOrderTransversalBST(bst);
                printList(lst);
                freeList(lst);
                break;
            case 17:
                lst2=levelOrderTransversalBST(bst);
                printList(lst2);
                freeList(lst2);
                break;
            case 18:
                //printf("Quantos elementos a árvore terá?\n");
                scanf("%d", &a);
                lst=createList();
                lst2=createList();
                if(!lst || !lst2) break;
                printf("Lista preOrder\n");
                for(int i=0; i<a; i++){
                    scanf("%lld", &b);
                    insertLastList(lst, createInfo(b));
                }
                printList(lst);
                printf("Lista inOrder\n");
                for(int i=0; i<a; i++){
                    scanf("%lld", &b);
                    insertLastList(lst2, createInfo(b));
                }
                printList(lst2);
                destroyBST(bst);
                bst=treeFromInOrderPreOrderBST(lst, lst2);
                freeList(lst);
                freeList(lst2);
                break;
            case 0:
                destroyBST(bst);
                return 0;
            default:
                break;
        }
    }
}
