#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Fila.h"
#include "Util.h"

struct node{
    struct node * proximo;
    char* palavra;
};  

struct fila {
    No *inicio;
    No *fim;
    int n;
};

No *criaObj(char * palavra){
    No * o = mallocSafe(sizeof(No));
    o->palavra = mallocSafe(strlen(palavra)+1);
    strcpy(o->palavra, palavra);
    return o;
}
char *pegaPalavra(No* obj){
    return obj->palavra;
}

No* copiaObjeto(No * obj){
    No * o = mallocSafe(sizeof(No));
    o->palavra = mallocSafe(strlen(obj->palavra)+1);
    strcpy(o->palavra, obj->palavra);
    return o;

}

Fila *criaFila() {
    Fila *f = mallocSafe(sizeof(Fila));
    f->inicio = f->fim = NULL;
    f->n = 0;
    return f;
}

/* Faz a desalocação da fila */
void liberaFila(Fila *f) {
    if(!f) return;
    
    if(f->inicio){
        No* obj;
        while(f->inicio){
            obj = f->inicio->proximo;
            free(f->inicio);
            f->inicio = obj;
        }
    }
    free(f);    
}

/* Insere um novo No a fila */
void enqueue(Fila *f, No *o) {
    if(!f || !o) return;
    f->n++;
    if(!f->inicio){
        f->inicio = o;
        o->proximo = NULL;
    }else f->fim->proximo = o;
    f->fim = o;
}

/*Remove (apaga) o primeiro elemento da fila */
void dequeue(Fila *f) {
    if(!f || !f->inicio) return;
    f->n--;
    No * aux = f->inicio;
    f->inicio = aux->proximo;
    free(aux->palavra);
    free(aux);
}

/* Retorna o primeiro elemento da fila */
No *front(Fila *f) {
    if(!f)return NULL;

    return f->inicio;
}

/* Verifica se a fila está vazia */
bool filaVazia(Fila *f) {
    return (f==NULL || f->n == 0);
}

/* Retorna o número de elementos na fila */
int tamanhoFila(Fila *f) {
    if (filaVazia(f)) return 0;
    return f->n;
}

/* Retorna uma cópia da fila passada como parâmetro */
Fila *copiaFila(Fila *f) {
    Fila * fila2 = criaFila();
    No *aux2, * aux = f->inicio;
    while(aux) {
        enqueue(fila2, copiaObjeto(aux));
        aux2 = aux;
        aux = aux->proximo;
    }
    return fila2;
}


/* Função de Alta Ordem que recebe uma fila e uma função (cb).
 * Para cada No da fila, aplique a função cb ao No.
 */
void converteElementosFila(Fila *f, void (*cb)(No *)) {
    if(!f || f->n == 0) return ;
    No * aux = f->inicio;
    while(aux) {
        cb(aux);
        aux = aux->proximo;
    }
}