#ifndef __LISTA_H
#define __LISTA_H

typedef struct no {
	int id;             //Idenficador do vagão
    struct no *proximo; //Próximo vagão
} No;

typedef struct  lista {
    No *inicio; //Aponta para o primeiro nó da lista
    No *fim;    //Aponta para o último nó da lista
} Lista;

Lista *criaLista();

Lista* juntaLista(Lista *l1, Lista *l2);

#endif