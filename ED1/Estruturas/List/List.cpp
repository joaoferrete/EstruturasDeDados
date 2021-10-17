#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

//1*) Inicializa��o e Libera��o de uma lista

// 1.a) fun��o que aloca mem�ria para uma lista,
//		inicializando seus campos
//		Entrada: void
//		Sa�da: ponteiro para uma lista
List *createList()
{
   List * pt;
   pt=(List *)malloc(sizeof(List));
   if(!pt) return NULL;
   pt->size=0;
   pt->first=NULL;
   return pt;
}

// 1.b) fun��o que aloca mem�ria para um no,
//		inicializando seus campos
//		Entrada: void
//		Sa�da: ponteiro para uma Node
Node *createNode()
{
    Node * pt;
    pt=(Node *)malloc(sizeof(Node));
    if(!pt) return NULL;
    pt->next=NULL;
    pt->info=NULL;
    return pt;
}
// 1.c) fun��o que aloca mem�ria para um elemento
//		de informa��o Info, inicializando seus campos
//		Entrada: inteiro conte�do do elemento de informa��o
//		Sa�da: ponteiro para um Info
Info *createInfo(int i)
{
    Info * pt;
    pt=(Info*)malloc(sizeof(Info));
    if(!pt)return NULL;
    pt->value=i;
    return pt;
}

//1.d *) fun��o que libera todo o espa�o de
//		mem�ria espa�o de mem�ria usado por uma lista
//		Entrada: ponteiro para uma lista
//		Sa�da: void

void freeList(List *lst)
{
    Node * aux, *aux2;
    aux2=lst->first;
    while(aux2){
        aux=aux2;
        free (aux->info);
        aux2=aux->next;
        free (aux);
    }
    free(lst);
}




//2) Informa��es sobre lista

// 2.a*) Fun��o que verifica se uma list � vazia
//		Entrada: ponteiro para uma lista
//		Sa�da: bool (TRUE se a lista � vazia,
//				 FALSE caso contr�rio)

bool isEmptyList(List * lst)
{
    if(lst->size==0 || !lst) return 1;
    return 0;
}

// 2.b*) Fun��o que Imprime o conteudo da lista
//		Entrada: ponteiro para uma lista
//		Sa�da: bool (TRUE se a lista � vazia, FALSE caso contr�rio
void printList(List *lst) {
    Node* aux;
    aux=lst->first;
    while(aux){
        printf("->%d ", aux->info->value);
        aux=aux->next;
    }

}

// 2.c*) Fun��o que verifica o tamanho da lista
//		Entrada: ponteiro para uma lista
//		Sa�da: inteiro >=0 representando o
//		tamanho da lista, -1 caso a lista seja nula
int lengthList(List *lst)
{
    if(!lst) return -1;
    else if(lst->size==0)return 0;
    return lst->size;
}

// 2.d*) Fun��o que encontra um elemento na lista
//		Entrada: ponteiro para uma lista
//		Sa�da: ponteiro para Info com o elemento
//		encontrado, NULL caso contr�rio
Info* findList(List *lst, Info *inf) {
    Node * ptr;
    ptr=lst->first;
    while(ptr){
        if(ptr->info->value == inf->value) return ptr->info;
        ptr=ptr->next;
    }
    return NULL;
}

// 2.e*) Fun��o que encontra a posi��o de um elemento na lista
//		Entrada: ponteiro para uma lista
//		Sa�da: 	-inteiro maior que 0 (Zero) que representa
//				a posi��o do elemento na lista.
//				-0 (Zero) caso o elemento n�o se encontre
int posList(List *lst, Info *inf)
{
    Node * pt;
    int i=1;
    pt=lst->first;
    while(pt){
        if(pt->info->value == inf->value) return i;
        pt=pt->next;
        i++;
    }
    return 0;
}

// 2.f*) Fun��o verifica se um elemento est� presente na lista
//		Entrada: ponteiro para uma lista
//		Sa�da: 	- inteiro maior que 0 (Zero) caso o
//				 elemento esteja presente na lista
//				-0 (Zero) caso contr�rio
int isInList(List *lst, Info *inf)
{
    Node * pt;
    pt=lst->first;
    while(pt){
        if(pt->info->value == inf->value) return 1;
        pt=pt->next;
    }
    return 0;
}


//3) Opera��es sobre lista

// 3.a*) Fun��o que insere um elemento na primeira
//		posi��o da lista
//		Entrada: ponteiro para uma lista n�o nula
//		Sa�da: bool (TRUE se o elemento foi inserido,
//		FALSE caso contr�rio

bool insertFirstList(List *lst, Info *inf)
{
    Node * aux, *aux2;
    if(isEmptyList(lst)){
        aux=createNode();
        if(!aux) return 0;
        aux->info=inf;
        lst->first=aux;
        lst->size++;
        return 1;
    }
    aux=createNode();
    if(!aux) return 0;
    aux->info=inf;
    aux2=lst->first;
    lst->first=aux;
    aux->next=aux2;
    lst->size++;
    return 1;

}

// 3.b*) Fun��o que insere um elemento na �ltima
//		posi��o da lista
//		Entrada: ponteiro para uma lista
//		Sa�da: bool (TRUE se o elemento foi
//			 inserido, FALSE caso contr�rio)

bool insertLastList(List *lst, Info *inf)
{
    Node * aux, *aux2;
    aux=createNode();
    if(!aux) return 0;
    aux->info=inf;
    lst->size++;
    if(isEmptyList(lst)){
        lst->first=aux;
        return 1;
    }
    aux2=lst->first;
    while(aux2->next!=NULL) aux2=aux2->next;
    aux2->next = aux;
    return 1;
}


// 3.c) Fun��o que deleta o elemento da primeira
//		posi��o da lista
//		Entrada: ponteiro para uma lista
//		Sa�da: ponteiro para Info com o elemento deletado
Info *deleteFirstList(List *lst) {
    Node *aux;
    Info * inf;
    if(!lst || isEmptyList(lst)) return NULL;
    aux=lst->first;
    lst->first=aux->next;
    inf=aux->info;
    free(aux);
    lst->size--;
    return inf;
}

// 3.d) Fun��o que deleta o elemento da lista
//		Entrada: ponteiro para uma lista e um ponteiro
//		para Info representando o elemento a ser deletado
//		Sa�da: ponteiro para Info com o elemento deletado
Info* deleteInfoList(List *lst, Info *inf) {
    Node *aux, *aux2;
    Info * info;
    if(!lst || isEmptyList(lst)) return NULL;
    aux=lst->first;
    if(lst->size==1 && aux->info->value==inf->value){
        lst->first=aux->next;
        info=aux->info;
        free(aux);
        lst->size--;
        return info;
    }else if(lst->size==1) return NULL;
    while(aux->next && (aux->next->info->value != inf->value)) aux=aux->next;
    if(!aux->next)return NULL;
    aux2=aux->next;
    aux->next=aux2->next;
    info=aux2->info;
    free(aux2);
    lst->size--;
    return info;

}

// 3.e) Fun��o que deleta o elemento de uma posi��o espec�fica da lista
//		Entrada: ponteiro para uma lista e um inteiro indicando
//		a posi��o do elemento a ser deletado
//		Sa�da: ponteiro para Info com o elemento deletado
Info* deletePositionList(List *lst, int pos)
{
    Node *aux, *aux2;
    Info * inform;
    int i=2;
    if(!lst || isEmptyList(lst) || pos>lst->size) return NULL;
    if(pos==1) return deleteFirstList(lst);
    aux=lst->first;
    while(i<lst->size && i!=pos){
        aux=aux->next;
        i++;
    }
    aux2=aux->next;
    if(!aux2) return NULL;
    aux->next=aux2->next;
    inform=aux2->info;
    free(aux2);
    lst->size--;
    return inform;
}

// 3.f) Fun��o que inverte uma lista
//		Entrada: ponteiro para uma lista
//		Sa�da: void.
void reverseList(List *lst)
{
    Node *prev=NULL, *cur, *nex;
    if(!lst || isEmptyList(lst)) return;
    cur=lst->first;
    while(cur){
        nex=cur->next;
        cur->next=prev;
        prev=cur;
        cur=nex;
    }
    lst->first=prev;

}

// 3.g) Fun��o que ordena crescente uma lista
//		Entrada: ponteiro para uma lista
//		Sa�da: void.
void sortList(List *lst) {


}
// 3.h) Fun��o que deleta o elemento da �ltima posi��o da lista
//		Entrada: ponteiro para uma lista
//		Sa�da: ponteiro para Info com o elemento deletado
Info *deleteLastList(List *lst) {
    Node *aux, *aux2;
    Info * inform;
    if(!lst || isEmptyList(lst)) return NULL;
    if(lst->size==1) return deleteFirstList(lst);
    aux=lst->first;
    while(aux->next->next) aux=aux->next;
    aux2=aux->next;
    aux->next=aux2->next;
    inform=aux2->info;
    free(aux2);
    lst->size--;
    return inform;

}
