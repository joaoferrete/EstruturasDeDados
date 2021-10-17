#include <stdio.h>
#include <stdlib.h>

#include "Fila.h"

struct fila {
    Objeto *inicio;
    Objeto *fim;
    int n;
};

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
        Objeto* obj;
        while(f->inicio){
            obj = f->inicio->proximo;
            free(f->inicio);
            f->inicio = obj;
        }
    }
    free(f);    
}

/* Insere um novo objeto a fila */
void enqueue(Fila *fila, Objeto *objeto) {
    if(!fila || !objeto) return;
    fila->n++;
    if(fila->inicio == NULL) fila->inicio = objeto;
    else fila->fim->proximo = objeto;
    fila->fim = objeto; 
}

/*Remove (apaga) o primeiro elemento da fila */
void dequeue(Fila *f) {
    if(!f || !f->inicio) return;
    f->n--;
    Objeto * aux = f->inicio;
    f->inicio = aux->proximo;
    liberaObjeto(aux);
}

/* Retorna o primeiro elemento da fila */
Objeto *front(Fila *f) {
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
    Objeto *aux2, * aux = f->inicio;
    while(aux) {
        enqueue(fila2, copiaObjeto(aux));
        aux2 = aux;
        aux = aux->proximo;
    }
    return fila2;
}

/* Fução que imprime os elementos da fila 
 * Essa função pode ajudar a detectar problemas nos objetos da fila
 * Para imprimir um objeto, use a função imprimeObjeto.
 */
void imprimeFila(Fila *f, int tipo) {
    if(!f || f->n==0) return;
    Objeto *aux = f->inicio;
    while(aux){
        imprimeObjeto(aux, tipo);
        aux=aux->proximo;
    }
    printf("\n");
}

/* Função de Alta Ordem que recebe uma fila e uma função (cb).
 * Para cada objeto da fila, aplique a função cb ao objeto.
 */
void converteElementosFila(Fila *f, void (*cb)(Objeto *)) {
    if(!f || f->n == 0) return ;
    Objeto * aux = f->inicio;
    while(aux) {
        cb(aux);
        aux = aux->proximo;
    }
}