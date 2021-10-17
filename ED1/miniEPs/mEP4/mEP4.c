#include <stdio.h>
#include <stdlib.h>

#include "Lista.h"

Lista *criaLista() {
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->fim = NULL;
    return lista;
}

Lista *juntaLista(Lista *l1, Lista *l2) {
    Lista *resultado = criaLista();

    if(!l1 || !l1->inicio){
        if (l2) {
            resultado->inicio = l2->inicio;
            resultado->fim = l2->fim;
        }
        return resultado;
    }
    if(!l2 || !l2->inicio){
        if (l1) {
            resultado->inicio = l1->inicio;
            resultado->fim = l1->fim;
        }
        return resultado;
    }

    No *aux1 = l1->inicio;
    No *aux2 = l2->inicio;
    No *aux3 = NULL;


    if(aux1->id > aux2->id) {
        resultado->inicio = aux2;
        resultado->fim = aux2;
        aux3=resultado->inicio;
        aux2=aux2->proximo;
    }
    else {
        resultado->inicio = aux1;
        resultado->fim = aux1;
        aux3=resultado->inicio;
        aux1=aux1->proximo;
    }

    while(aux1 && aux2) {
        if(aux1->id > aux2->id) {
            aux3->proximo = aux2;
            aux2 = aux2->proximo;
            resultado->fim = aux3;
        }
        else {
            aux3->proximo = aux1;
            aux1 = aux1->proximo;
            resultado->fim = aux3;
        }
        aux3 = aux3->proximo;
    }
    if(aux1) {
        aux3->proximo = aux1;
        resultado->fim = l1->fim;
    }
    else if(aux2) {
        aux3->proximo = aux2;
        resultado->fim = l2->fim;
    }
    return resultado;
}
