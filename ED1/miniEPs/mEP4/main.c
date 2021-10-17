#include <stdio.h>
#include <stdlib.h>
#include "Lista.h"

void insereLista(Lista *l, int valor) {
    if(l->inicio == NULL) {
        l->inicio = (No*) malloc(sizeof(No));
        l->inicio->id = valor;
        l->inicio->proximo = NULL;
        l->fim = l->inicio;
    }
    
    else{
        No *aux = l->fim;
        aux->proximo = (No *) malloc(sizeof(No));
        aux->proximo->id = valor;
        l->fim = aux->proximo;
        l->fim->proximo = NULL;
    }
}

void libeLista(Lista *l) {
    No *aux = l->inicio;
    No* aux2 = NULL;
    while(aux != NULL) {
        aux2 = aux->proximo;
        free(aux);
        aux = aux2;
    }
}

void imprimeLista(Lista *l) {
    No *aux = l->inicio;
    while (aux != NULL) {
        printf("%d", aux->id);
        if(aux != l->fim) printf(" - ");
        aux = aux->proximo;
    }
    printf("\n");
}

int main(){
    Lista *lista1 = criaLista();
    Lista *lista2 = criaLista();
    Lista *listaResult;
    int i, j, n;
    scanf("%d", &i);
    for (int k = 0; k < i; k++) {
        scanf("%d", &n);
        insereLista(lista1, n);
    }
    scanf("%d", &j);
    for (int k = 0; k < j; k++) {
        scanf("%d", &n);
        insereLista(lista2, n);
    }
    listaResult = juntaLista(lista1, lista2);
    if(listaResult) imprimeLista(listaResult); 
    libeLista(listaResult);
    if(listaResult) free(listaResult);
    listaResult = NULL;
    if(lista1) free(lista1);
    lista1=NULL;
    if(lista2) free(lista2);
    lista2=NULL;
    return 0;
}