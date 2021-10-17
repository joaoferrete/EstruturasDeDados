#include <stdio.h>
#include <stdlib.h>

#include "Pilha.h"

typedef struct pilha {
    Objeto *inicio;
    int n;
} Pilha;

Pilha *criaPilha(){
    Pilha *p = mallocSafe(sizeof(Pilha));
    p->inicio  = NULL;
    p->n = 0;
    return p;
}

/* Faz a desalocação da pilha */
void liberaPilha(Pilha *p) {
    if(!p) return;
    Objeto *aux;
    if(p->inicio){
        while(p->inicio){
            aux = p->inicio->proximo;
            free(p->inicio);
            p->inicio = aux;
        }
    }
    free(p);
}

/* Insere um novo objeto a pilha */
void empilha(Pilha *p, Objeto *no) {
    if(!p || !no) return;
    no->proximo = p->inicio;
    p->inicio = no;
    p->n++;
}

/* Remove (apaga) o último elemento da pilha */
void desempilha(Pilha *p){
    Objeto * aux;
    aux = p->inicio;
    p->inicio = aux->proximo;
    free(aux);
    p->n--;
    
}

/* Retorna o objeto do topo da pilha */
Objeto *topoPilha(Pilha *p){
    if (!p) return NULL;
    return p->inicio;
}

/* Verifica se a pilha está vazia */
bool pilhaVazia(Pilha *p){
    return (p==NULL || p->n == 0);
}

/* Retorna o número de elementos na pilha */
int tamanhoPilha(Pilha *p) {
    if (pilhaVazia(p)) return 0;
    return p->n;
}

/* Fução que imprime os elementos da pilha 
 * Essa função pode ajudar a detectar problemas nos objetos da pilha
 * Para imprimir um objeto, use a função imprimeObjeto.
 */
void imprimePilha(Pilha *pilha, int tipo) {
    if(!pilha || pilha->n == 0) return;
    Objeto *aux = pilha->inicio;
    while(aux){
        imprimeObjeto(aux, tipo);
        aux=aux->proximo;
    }
    printf("\n");
}