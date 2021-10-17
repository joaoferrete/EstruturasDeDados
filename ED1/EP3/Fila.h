#ifndef EP2_FILA_H
#define EP2_FILA_H

#include "Util.h"

typedef struct fila Fila;
typedef struct node No;

Fila *criaFila();

void liberaFila(Fila *f);

void enqueue(Fila *, No *);

void dequeue(Fila *);

No *front(Fila *);

bool filaVazia(Fila *);

int tamanhoFila(Fila *);

Fila *copiaFila(Fila *);

void imprimeFila(Fila *, int);

void converteElementosFila(Fila *, void (*cb)(No *));

No *criaObj(char * palavra);

char *pegaPalavra(No* obj);

#endif