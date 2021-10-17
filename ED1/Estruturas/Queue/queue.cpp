#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

//1) Inicializa��o e Libera��o de uma Fila

// 1.a) fun��o que aloca mem�ria para uma Fila, inicializando seus campos
//		Entrada: void
//		Sa�da: ponteiro para uma lista
Queue *createQueue()
{
    Queue * ptr;
    ptr=(Queue *)malloc(sizeof(Queue));
    if(!ptr) return NULL;
    ptr->first=NULL;
    ptr->last=NULL;
    ptr->size=0;
    return ptr;
}

// 1.b) fun��o que aloca mem�ria para um no, inicializando seus campos
//		Entrada: void
//		Sa�da: ponteiro para uma Node
Node *createNode()
{
    Node * ptr;
    ptr=(Node *)malloc(sizeof(Node));
    if(!ptr) return NULL;
    ptr->next=NULL;
    ptr->info=NULL;
    return ptr;
}
// 1.c) fun��o que aloca mem�ria para um elemento de informa��o Info, inicializando seus campos
//		Entrada: inteiro conte�do do elemento de informa��o
//		Sa�da: ponteiro para um Info
Info *createInfo(int i)
{
    Info * ptr;
    ptr=(Info *) malloc(sizeof(Info));
    if(!ptr) return NULL;
    ptr->value=i;
    return ptr;
}

//1.d) fun��o que libera todo o espa�o de mem�ria usado por uma Fila
//		Entrada: ponteiro para uma fila
//		Sa�da: void

void freeQueue(Queue *queue)
{
    Node * aux, *aux2;
    Info * inf;
    aux=queue->first;
    while(aux){
        free(aux->info);
        aux2=aux->next;
        free(aux);
        aux=aux2;
    }
    free(queue);
}

//2) Informa��es sobre Fila

// 2.a) Fun��o que verifica se uma Fila � vazia
//		Entrada: ponteiro para uma Fila
//		Sa�da: bool (TRUE se a Fila � vazia, FALSE caso contr�rio

bool isEmptyQueue(Queue * queue)
{
    if(queue->size<=0) return 0;
    return 1;
}

// 2.b) Fun��o que Imprime o conteudo da Fila
//		Entrada: ponteiro para uma fila
//		Sa�da: bool (TRUE se a fila � vazia, FALSE caso contr�rio
void printQueue(Queue *queue) {
    Node * aux;
    aux=queue->first;
    while(aux){
        printf("->%d ", aux->info->value);
        aux=aux->next;
    }
}

// 2.c) Fun��o que verifica o tamanho da Fila
//		Entrada: ponteiro para uma fila
//		Sa�da: inteiro >=0 representando o tamanho da fila, -1 caso a fila seja nula
int lengthQueue(Queue *queue)
{
    if(queue->size>0) return queue->size;
    return 0;
}

//3) Opera��es sobre Fila

// 3.c) Fun��o que insere um elemento da fila (na �ltima posi��o)
//		Entrada: ponteiro para uma fila
//		Sa�da: bool (TRUE se o elemento foi inserido, FALSE caso contr�rio

bool insertQueue(Queue *queue, Info *inf)
{
    Node* ptr;
    ptr=createNode();
    if(!ptr) return 0;
    ptr->info=inf;
    if(queue->last)queue->last->next=ptr;
    if(!queue->first)queue->first=ptr;
    queue->last=ptr;
    return 1;
}


// 3.c) Fun��o que retira um elemento da fila (da primeira posi��o)
//		Entrada: ponteiro para uma fila
//		Sa�da: ponteiro para Info com o elemento retirado
Info *removeQueue(Queue *queue) {
    Node * ptr;
    Info * inf;
    ptr=queue->first;
    inf=ptr->info;
    queue->first=ptr->next;
    free(ptr);
    return inf;

}
