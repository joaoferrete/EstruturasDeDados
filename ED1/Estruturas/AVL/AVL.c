#include <stdio.h>                                          //Inclusão das bibliotecas
#include <stdlib.h>
#include <string.h>

#define MAXHASH 89                                          //Macro que referencia a quantidade casas na HashTable;

typedef struct{                                             //Estrutura do elemento de informação utilizado em árvores e nas listas
    long long value;
    char * word;
}Info;

typedef struct tnode{                                       //Estrutura de nó para lista;
    struct tnode * next;
    Info * info;
}listNode;

typedef struct AVLno{                                       //Estrutura de nó da árvore AVL
    struct AVLno *left, *right;
    Info * info;
    int balance;
}AVL;
typedef AVL Node;


typedef struct{                                            //Estrutura de cabeça para a lista;
    listNode * first;
    int size;
}List;

typedef struct qnode{                                      // Estrutura de Nó para fila;
    struct qnode * next;
    AVL * info;                                            //O elemento de informação é um ponteiro para árvore, utilizado para auxiliar na criação da lista em niveis
}queueNode;

typedef struct{                                            //Estrutura para a cabeça de uma fila;
    queueNode * first;
    int size;
}Queue;

typedef struct{                                            // Estrutura da HashTable
    AVL * tree;
    long long size;
}HashT;

int hash(Info * inf){                                       //Função responsável por retornar a posição na hashtable que representa a árvore em que o elemento deverá ser inserido
    return (inf->value % MAXHASH);
}

int isEmptyList (List * lst){                               //Função que verifica se a lista está vazia;
    if(!lst || lst->size==0) return 1;
    return 0;
}

void freeList(List * lst){                                  //Função que libera o espaço de memória utilizado pela lista.
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
Info * createInfo(char * word){                             // Função responsável por criar um elemento de informação, inicializando seus campos e definindo o valor correspondente em inteiro;
    Info * inf = NULL;
    int a=0;
    inf=(Info *) malloc(sizeof(Info));
    if(!inf) return NULL;
    inf->word=(char *) malloc(sizeof(char)*strlen(word)+1);
    strcpy(inf->word, word);
    for(int i=0; i<strlen(word); i++){
        a+=(int)word[i];
    }
    inf->value=a;
    return inf;
}

List * createList(){                                        //Função responsável por criar e alocar espaço para uma cabeça de lista;
    List * lst=NULL;
    lst=(List *)malloc(sizeof(List));
    if (!lst) return NULL;
    lst->size=0;
    lst->first=NULL;
    return lst;
}
listNode * createNodeList(Info * inf){                      //Função responsável por criar, alocar espaço e inicializar os campos de um node para lista
    if(!inf) return NULL;
    listNode * node;
    node=(listNode *) malloc(sizeof(listNode));
    if (!node) return NULL;
    node->next=NULL;
    node->info = inf;
    return node;
}

int insertLastList(List * lst, Info *inf){                  //Função que insere um elemento no fim de uma lista
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

Info * deleteFirstList(List * lst){                         //Função responsável por deletar o primeiro elemento de uma lista e retornar seu elemento de informação;
    if(!lst) return NULL;
    listNode * aux=lst->first->next;
    Info* ret=lst->first->info;
    free(lst->first);
    lst->first=aux;
    lst->size--;
    return ret;
}

Queue * createQueue(){                                      //Função    responsável por criar e alocar espaço para uma cabeça de fila;
    Queue * q;
    q=(Queue *) malloc(sizeof(Queue));
    if(!q) return NULL;
    q->first=NULL;
    q->size=0;
    return q;
}

int isEmptyQueue(Queue * queue){                            //Função que verifica se a fila está vazia ou não
    if (!queue || queue->size==0 || !queue->first) return 1;
    return 0;
}

queueNode * createNodeQueue(AVL * inf){                     //Função que cria um nó para fila, aloca o espaço necessário e inicia os campos
    if(!inf) return NULL;
    queueNode * q;
    q=(queueNode *) malloc(sizeof(queueNode));
    q->info=inf;
    q->next=NULL;
    return q;
}

int insertQueue(Queue * queue, AVL * inf){                  //Função que insere um elemento em uma fila;
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

AVL * deleteQueue(Queue * queue){                           //Função que apaga um elemento de uma fila e retorna o ponteiro para a árvore que é o elemento de informação
    if(isEmptyQueue(queue)) return NULL;
    AVL * ret;
    queueNode * aux, * aux2;
    aux2=queue->first;
    aux=queue->first->next;
    ret=queue->first->info;
    free(aux2);
    queue->first=aux;
    queue->size--;
    return ret;
}

AVL* createAVL(void){                                       //Função que aloca espaço para um nó de árvore;
    AVL * ptr;
    ptr=(AVL *) malloc(sizeof(AVL));
    if(!ptr) return NULL;
    ptr->left=NULL;
    ptr->right=NULL;
    ptr->info=NULL;
    ptr->balance=0;
    return ptr;
}

Node *createNode(Info * inf){                               //Função que cria e aloca espaço para uma AVL e inicia seus campos, já com o elemento de informação;
    Node * ptr;
    ptr=(Node *) malloc(sizeof(Node));
    if(!ptr || !inf) return NULL;
    ptr->left=NULL;
    ptr->right=NULL;
    ptr->info=inf;
    ptr->balance=0;
    return ptr;
}

AVL* leftAVL(AVL * ptr){                                    //Função que retorna o ponteiro para a sub-árvore esquerda
    if(!ptr) return ptr;
    return ptr->left;
}
AVL * rightAVL(AVL * ptr){                                  //Função que retorna o ponteiro para a sub-árvore direita
    if(!ptr) return ptr;
    return ptr->right;
}

Info * rootAVL(AVL * ptr){                                  //Função que retorna o ponteiro para o elemento de informação de uma raiz;
    if(!ptr) return NULL;
    return ptr->info;
}

long long valueAVL(AVL * ptr){                              //Função que retorna o campo value do elemento de informação de uma árvore
    if(!ptr) return 0;
    else return rootAVL(ptr)->value;
}

char * wordAVL (AVL * ptr){                                 //Função que retorna o campo word do elemento de informação de uma árvore
    if (!ptr) return NULL;
    return rootAVL(ptr)->word;
}

int isEmptyAVL(AVL* ptr){                                   //Função responsável por verificar se uma árvore está ou nao vazia
    if(!ptr) return 1;
    return 0;
}

AVL * searchAVL(AVL * ptr, Info * inf){                     //Função responsável por buscar um elemento na árvore e retornar um ponteiro para o mesmo
    if(!ptr) return NULL;
    if(strcmp(wordAVL(ptr), inf->word)==0) return ptr;
    else if(strcmp(wordAVL(ptr), inf->word)<0) return searchAVL(rightAVL(ptr), inf);
    return searchAVL(leftAVL(ptr), inf);
}

void destroyAVL(AVL * ptr){                                 //Função responsável por dar free em todos os elementos de uma árvore;
    if(!ptr) return;
    destroyAVL(leftAVL(ptr));
    destroyAVL(rightAVL(ptr));
    free(ptr->info->word);
    free(ptr->info);
    free(ptr);
    return;
}

int heightAVL (AVL * ptr){                                  //Função que retorna a altura de uma árvore
    int r, l;
    if(!ptr) return 0;
    r=1+heightAVL(rightAVL(ptr));
    l=1+heightAVL(leftAVL(ptr));
    if(r>l) return r;
    return l;
}

void balanceAVL(AVL * avl){                                 //Função que atualiza o campo balanço da raiz de uma árvore
    if(!avl) return;
    int a = heightAVL(leftAVL(avl))- heightAVL(rightAVL(avl));
    avl->balance=a;
}

AVL * LRrotation(AVL * avl){                                //Função responsável por fazer a rotação LR e atualizar os campos balance das raizes envolvidas
    AVL * a=avl->left, * b = avl->left->right;
    avl->left=b->right;
    a->right=b->left;
    b->left = a;
    b->right = avl;
    balanceAVL(avl);
    balanceAVL(a);
    balanceAVL(b);
    return b;
}

AVL * RLrotation(AVL * avl){                                //Função responsável por fazer a rotação RL e atualizar os campos balance das raizes envolvidas
    AVL * a = avl->right, * b=avl->right->left;
    a->left = b->right;
    avl->right = b->left;
    b->left=avl;
    b->right=a;
    balanceAVL(avl);
    balanceAVL(a);
    balanceAVL(b);
    return b;
}

AVL * LLrotation(AVL * avl){                                //Função responsável por fazer a rotação LL e atualizar os campos balance das raizes envolvidas
    AVL * a = avl->left;
    avl->left=a->right;
    a->right=avl;
    balanceAVL(avl);
    balanceAVL(a);
    return a;
}

AVL * RRrotation(AVL * avl){                                //Função responsável por fazer a rotação RR e atualizar os campos balance das raizes envolvidas
    AVL *a = avl->right;
    avl->right=a->left;
    a->left = avl;
    balanceAVL(avl);
    balanceAVL(a);
    return a;
}

AVL * insertAVL(AVL * ptr, Info * inf){                     //Função responsável por inserir elementos na árvore de forma ordenada e fazer rotações, caso necessário.
    if(!ptr) return createNode(inf);
    if(strcmp(rootAVL(ptr)->word, inf->word)<0) {
        ptr->right=insertAVL(rightAVL(ptr), inf);
        balanceAVL(ptr->right);                             //Atualização do balanço das arvores;
        balanceAVL(ptr);
        if(ptr->right->balance < 0 && ptr->balance < -1) ptr=RRrotation(ptr); //Caso a sub-árvore direita seja pesada para a direita e a raiz atual esteja desbalanceada para a direita
        else if (ptr->right->balance > 0 && ptr->balance < -1) ptr=RLrotation(ptr); //Caso a sub-árvore direita seja pesada para a esquerda e a raiz atual esteja desbalanceada para a direita
    }
    else if (strcmp(rootAVL(ptr)->word, inf->word)>0){
        ptr->left=insertAVL(leftAVL(ptr), inf);
        balanceAVL(ptr->left);
        balanceAVL(ptr);
        if(ptr->left->balance > 0 && ptr->balance > 1) ptr=LLrotation(ptr);  //Caso a sub-árvore esquerda seja pesada para a esquerda e a raiz atual esteja desbalanceada para a esquerda
        else if (ptr->left->balance < 0 && ptr->balance > 1) ptr=LRrotation(ptr); //Caso a sub-árvore esquerda esteja pesada para a direita e a raiz atual esteja desbalanceada para a esquerda
    }
    return ptr;
}

AVL * findLargestElementAVL(AVL * ptr){                     //Função que retorna o ponteiro para o maior elemento de uma árvore
    if(!ptr) return NULL;
    if(ptr && !ptr->right) return ptr;
    return findLargestElementAVL(rightAVL(ptr));
}

AVL * findSmallestElementAVL(AVL * ptr){                   //Função que retorna o ponteiro para o menor elemento da arvore
    if(!ptr) return NULL;
    if(ptr && !ptr->left) return ptr;
    return findSmallestElementAVL(leftAVL(ptr));
}

AVL * mirrorAVL(AVL * ptr){                                //Função que espelha uma árvore
    if(!ptr) return NULL;
    AVL *aux1, *aux2;
    aux1=mirrorAVL(rightAVL(ptr));
    aux2=mirrorAVL(leftAVL(ptr));
    ptr->left=aux1;
    ptr->right=aux2;
    return ptr;
}

AVL * deleteAVL(AVL * ptr, Info * inf){                     //Função que apaga um elemento da árvore a faz rotações, se necessário;
    if(!ptr) return ptr;
    if(!searchAVL(ptr, inf)) return ptr;
    if(strcmp(rootAVL(ptr)->word, inf->word)==0){
        if(!rightAVL(ptr)){
            AVL * aux=leftAVL(ptr);
            free(ptr->info);
            free(ptr);
            balanceAVL(aux);                                //Atualiza o balanço de Aux
            return aux;
        }else if(!leftAVL(ptr)){
            AVL * aux = rightAVL(ptr);
            free (ptr->info);
            free(ptr);
            balanceAVL(aux);
            return aux;
        }else{
            AVL * aux = findSmallestElementAVL(rightAVL(ptr));
            rootAVL(ptr)->value=aux->info->value;
            strcpy(rootAVL(ptr)->word, aux->info->word);
            ptr->right = deleteAVL(rightAVL(ptr), rootAVL(ptr));
            balanceAVL(ptr->left);                          //È feito novamente o balanço
            balanceAVL(ptr);
            if(ptr->left && ptr->left->balance >= 0 && ptr->balance > 1) ptr=LLrotation(ptr); //Caso a árvore esteja desbalanceada para a esquerda, é feita a rotação LL;
            else if (ptr->left && ptr->left->balance < 0 && ptr->balance > 1) ptr=LRrotation(ptr); //Caso a árvore esteja desbalanceada para a esquerda e a sua sub-arvore esquerda esteja pesada para a direita, é feita a rotação LR
        }
    }else if(strcmp(rootAVL(ptr)->word, inf->word)>0) {
        ptr->left=deleteAVL(leftAVL(ptr), inf);
        balanceAVL(ptr->left);
        balanceAVL(ptr);
        if(ptr->right && ptr->right->balance <= 0 && ptr->balance < -1) ptr=RRrotation(ptr);
        else if (ptr->right && ptr->right->balance > 0 && ptr->balance < -1) ptr=RLrotation(ptr);
    }

    else if(strcmp(rootAVL(ptr)->word, inf->word)<0) {
        ptr->right = deleteAVL(rightAVL(ptr), inf);
        balanceAVL(ptr);
        balanceAVL(ptr->left);
        if(ptr->left && ptr->left->balance >= 0 && ptr->balance > 1) ptr=LLrotation(ptr);
        else if (ptr->left && ptr->left->balance < 0 && ptr->balance > 1) ptr=LRrotation(ptr);
    }
    return ptr;
}

void printAVL(AVL * ptr){                                   //Função que imprime os elementos de uma árvore na sequencia pre-order
    if(!ptr) return;
    printf("%s, ", ptr->info->word);
    printAVL(leftAVL(ptr));
    printAVL(rightAVL(ptr));
}

int weightAVL(AVL * ptr){                                   //Função que retorna a quantidade de elementos (peso) de uma árvore
    if(!ptr)return 0;
    return (1 + weightAVL(rightAVL(ptr)) + weightAVL(leftAVL(ptr)));
}

int totalExternalNodes(AVL * ptr){                          //Função que retorna a quantidade de folhas de uma árvore;
    if (!ptr) return 0;
    if(!ptr->right && !ptr->left) return 1;
    return totalExternalNodes(rightAVL(ptr)) + totalExternalNodes(leftAVL(ptr));
}

int totalInternalNodes(AVL * ptr){                          //Função que retorna a quantidade de pais de uma árvore;
    if (!ptr) return 0;
    if(!ptr->right && !ptr->left) return 0;
    return 1 + totalExternalNodes(rightAVL(ptr)) + totalExternalNodes(leftAVL(ptr));
}

int isOrderedAVL(AVL * ptr){                                //Função que verifica se uma árvore está ordenada
    if(!ptr) return 1;
    if(leftAVL(ptr) && strcmp(rootAVL(leftAVL(ptr))->word, rootAVL(ptr)->word)>0) return 0;
    if(rightAVL(ptr) && strcmp(rootAVL(rightAVL(ptr))->word, rootAVL(ptr)->word)<0) return 0;
    return isOrderedAVL(rightAVL(ptr)) && isOrderedAVL(leftAVL(ptr));
}

void auxPreOrderTransversalAVL(AVL *ptr, List * lst){       //Função que auxilia na criação da lista pre-order da árvore;
	if (!ptr || !lst) return;
	insertLastList(lst, createInfo(ptr->info->word));
	auxPreOrderTransversalAVL(leftAVL(ptr), lst);
	auxPreOrderTransversalAVL(rightAVL(ptr), lst);
}

List * preOrderTransversalAVL(AVL * ptr){                   //Função que cria uma lista pre-order da árvore;
	if (!ptr) return NULL;
	List * lst=createList();
	if(!lst) return NULL;
	auxPreOrderTransversalAVL(ptr, lst);
	return lst;
}

void auxInOrderTransversalAVL(AVL *ptr, List *lst){         //Função que auxilia na criação da lista inOrder da árvore
	if (!ptr || !lst) return;
	auxInOrderTransversalAVL(leftAVL(ptr), lst);
	insertLastList(lst, createInfo(ptr->info->word));
	auxInOrderTransversalAVL(rightAVL(ptr), lst);
}

List *inOrderTransversalAVL(AVL *ptr){                      //Função que cria uma lista em ordem de uma árvore
	if (!ptr) return NULL;
	List * lst=createList();
	if(!lst) return NULL;
	auxInOrderTransversalAVL(ptr, lst);
	return lst;
}

void auxPosOrderTransversalAVL(AVL *ptr, List *lst){        //Função que auxilia na criação de uma lista pos-order de uma árvore
	if (!ptr || !lst) return;
	auxPosOrderTransversalAVL(leftAVL(ptr), lst);
	auxPosOrderTransversalAVL(rightAVL(ptr), lst);
	insertLastList(lst, createInfo(ptr->info->word));
}

List *posOrderTransversalAVL(AVL *ptr){                     //Função que cria uma árvore em sequencia pós-order de uma árvore
	if (!ptr) return NULL;
	List * lst=createList();
	if(!lst) return NULL;
	auxPosOrderTransversalAVL(ptr, lst);
	return lst;
}

List * levelOrderTransversalAVL(AVL * ptr){                 //Função que cria uma lista a partir do percurso em níveis da árvore
	if(!ptr) return NULL;
	List * lst=createList();
	Queue * que=createQueue();
	AVL * aux;
	Info * inf;
	if(!lst || !que) return NULL;
	insertQueue(que, ptr);                                  //O primeiro elemento da árvore é adicionado na fila
	while(!isEmptyQueue(que)){
		aux=deleteQueue(que);
		inf=createInfo(rootAVL(aux)->word);
		insertLastList(lst, inf);
		if(leftAVL(aux)) insertQueue(que, leftAVL(aux));
		if(rightAVL(aux)) insertQueue (que, rightAVL(aux));
	}
	free(que);
	return lst;
}

List * takeWhileList(List *lst, Info * inf){                //Função que cria uma lista a partir do início da lista original até um elemento qualquer;
	listNode * ptr;
	List * lstfin=createList();
	Info * info;
	if(!lstfin) return NULL;
	for(ptr=lst->first; ptr && strcmp(ptr->info->word, inf->word)!= 0; ptr=ptr->next){
		info=createInfo(ptr->info->word);
		insertLastList(lstfin, info);
	}
	return lstfin;
}

List * dropWhileList(List * lst, Info * inf){               //Função que cria uma nova lista a partir de um elemento qualquer até o fim da lista (auxilia na função seguinte);
	listNode * ptr;
	List * lstfin=createList();
	Info * info;
	if(!lstfin) return NULL;
	for(ptr=lst->first; ptr && strcmp(ptr->info->word, inf->word)!= 0; ptr=ptr->next);
	if(ptr){
		for(ptr=ptr->next; ptr; ptr=ptr->next){
			info=createInfo(ptr->info->word);
			insertLastList(lstfin, info);
		}
	}
	return lstfin;

}

AVL * treeFromInOrderPreOrderAVL(List * preOrder, List * inOrder){ //Função que cria uma árvore a partir dos percursos pre-order e in-order delas;
	AVL *ptr=NULL;
	List *esq, *dir;
	Info * inf;
	if(isEmptyList(preOrder) || isEmptyList(inOrder)) return NULL;
	inf=deleteFirstList(preOrder);
	ptr=createNode(inf);
	if(!ptr)return NULL;
	esq=takeWhileList(inOrder, inf);
	dir=dropWhileList(inOrder, inf);
	ptr->left=treeFromInOrderPreOrderAVL(preOrder, esq);
	ptr->right=treeFromInOrderPreOrderAVL(preOrder, dir);
	return ptr;
}
void printList(List * lst){                                         //Função que imprime todos os elementos de uma lista
    listNode * aux;
    if(isEmptyList(lst) || !lst->first) return;
    aux=lst->first;
    while(aux){
        printf("%s, ", aux->info->word);
        aux=aux->next;
    }
    printf("\n");
}

AVL * hashSearch(HashT * a, Info * inf){                            //Função que retorna a árvore correspondente ao elemento de informação passado
    if(!a || ! inf) return NULL;
    return a[hash(inf)].tree;
}

void helpInsert(HashT hs[MAXHASH], char * b)                        //Função que chama a função de inserção
{
    Info * inf;
    AVL * avl;
    inf=createInfo(b);
    avl=hashSearch(hs, inf);
    avl=insertAVL(avl, inf);
    hs[hash(inf)].tree=avl;
    hs[hash(inf)].size++;

}

int elementosHash(HashT * hs, int a){                               //Função que retorna a quantidade de elementos de uma árvore em uma posição da hash
    if (a>=MAXHASH || a<0) return -1;
    return hs[a].size;
}

void helpDelete(HashT hs[MAXHASH], char * b)                        //Função que chama a função de deleção;
{
    Info * inf;
    AVL * avl;
    inf=createInfo(b);
    avl=hashSearch(hs, inf);
    avl=deleteAVL(avl, inf);
    hs[0].tree=avl;
    hs[hash(inf)].tree=avl;
    hs[hash(inf)].size--;

}

void helpSearch(HashT hs[MAXHASH], char * b){                       //Função que chama a função de busca;
    Info * inf=NULL;
    AVL * avl=NULL, * aux=NULL;
    inf=createInfo(b);
    avl=hashSearch(hs, inf);
    aux=searchAVL(avl, createInfo(b));
    if(aux) printf("Elemento Encontrado!\n");
    else printf("Elemento Não Encontrado\n");
}

void startHash(HashT * hs){                                         //Função que inicia os campos de um vetor de HashTable
    for(int i=0; i<MAXHASH; i++){
        hs[i].size=0;
        hs[i].tree=NULL;
    }
}

int main(){
    AVL  * aux = NULL;                                 //Declaração de variáveis
    List * lst = NULL, *lst2 = NULL;
    Info * inf;
    int exe,a;
    char b[55];
    HashT hs[MAXHASH];
    startHash(hs);                                                  //Inicialização dos campos da Hash


    while(1){
        /*printf("\n\n");
        printf("| 1 - Inserir Elementos            |\n");
        printf("| 2 - Remover Elementos            |\n");
        printf("| 3 - Imprimir Árvores (Pre-order) |\n");
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
        printf("| 19 - Imprimir uma árvore         |\n");
        printf("| 0 -  Sair                        |\n");*/
        printf("\n");
        scanf("%d", &a);
        switch(a){
            case 1:
                //printf("Insira o elemento\n");
                scanf("%s", b);
                helpInsert(hs, b);
                break;
            case 2:
                //printf("Insira o elemento\n");
                scanf("%s", b);
                helpDelete(hs, b);
                break;
            case 3:
                for(int i=0; i<MAXHASH; i++){
                    if(i<0 || i>=MAXHASH) break;
                    printf("Árvore %d\n", i);
                    printAVL(hs[i].tree);
                    printf("\n");
                }
                break;
            case 4:
                aux=NULL;
                //printf("Insira o elemento\n");
                scanf("%s", b);
                helpSearch(hs, b);
                break;
            case 5:
                //printf("Qual árvore deseja verificar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                printf("A altura é %d\n", heightAVL(hs[a].tree));
                break;
            case 6:
                //printf("Qual árvore deseja verificar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                printf("O maior elemento é %s\n", wordAVL(findLargestElementAVL(hs[a].tree)));
                break;
            case 7:
                //printf("Qual árvore deseja verificar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                printf("O menor elemento é %s\n", wordAVL(findSmallestElementAVL(hs[a].tree)));
                break;
            case 8:
                //printf("Qual árvore deseja espelhar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                mirrorAVL(hs[a].tree);
                printf("A Árvore foi espelhada\n");
                break;
            case 9:
                //printf("Qual árvore deseja verificar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                if(isEmptyAVL(hs[a].tree))printf("ÁRVORE VAZIA\n");
                else printf("ÁRVORE NÃO VAZIA\n");
                break;
            case 10:
                //printf("Qual árvore deseja verificar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                printf("O peso é %d\n", weightAVL(hs[a].tree));
                break;
            case 11:
                //printf("Qual árvore deseja verificar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                printf("O número de nós internos é %d\n", totalInternalNodes(hs[a].tree));
                break;
            case 12:
                //printf("Qual árvore deseja verificar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                printf("O numero de nós externos é %d\n", totalExternalNodes(hs[a].tree));
                break;
                case 13:
                //printf("Qual árvore deseja verificar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                if(isOrderedAVL(hs[a].tree))printf("ÁRVORE ORDENADA\n");
                else printf("ÁRVORE NÃO ORDENADA\n");
                break;
            case 14:
                //printf("Qual árvore deseja verificar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                lst=preOrderTransversalAVL(hs[a].tree);
                printList(lst);
                freeList(lst);
                break;
            case 15:
                //printf("Qual árvore deseja verificar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                lst=inOrderTransversalAVL(hs[a].tree);
                printList(lst);
                freeList(lst);
                break;
            case 16:
                //printf("Qual árvore deseja verificar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                lst=posOrderTransversalAVL(hs[a].tree);
                printList(lst);
                freeList(lst);
                break;
            case 17:
                //printf("Qual árvore deseja verificar? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                lst2=levelOrderTransversalAVL(hs[a].tree);
                printList(lst2);
                freeList(lst2);
                break;
            case 18:
                //printf("Qual árvore deseja inserir? (0 <= x <= %d)\n", MAXHASH-1);
                scanf("%d", &exe);
                if(exe<0 || exe>=MAXHASH) break;
                //printf("Quantos elementos a árvore terá?\n");
                scanf("%d", &a);
                lst=createList();
                lst2=createList();
                if(!lst || !lst2) break;
                printf("Lista preOrder\n");
                for(int i=0; i<a; i++){
                    scanf("%s", b);
                    insertLastList(lst, createInfo(b));
                }
                printList(lst);
                printf("Lista inOrder\n");
                for(int i=0; i<a; i++){
                    scanf("%s", b);
                    insertLastList(lst2, createInfo(b));
                }
                printList(lst2);
                destroyAVL(hs[exe].tree);
                hs[exe].tree=treeFromInOrderPreOrderAVL(lst, lst2);
                freeList(lst);
                freeList(lst2);
                break;

            case 19:
                //printf("Qual árvore deseja imprimir?\n");
                scanf("%d", &a);
                if(a<0 || a>=MAXHASH) break;
                printAVL(hs[a].tree);
                break;
            case 0:
                for(int i=0; i<MAXHASH; i++){
                    destroyAVL(hs[i].tree);
                }
                return 0;
            default:
                break;
        }
    }
}
