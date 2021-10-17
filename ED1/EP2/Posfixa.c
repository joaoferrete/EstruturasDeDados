#include <stdio.h>
#include <stdlib.h>

#include "Posfixa.h"
#include "Pilha.h"

/* A função recebe uma fila de objetos em notação infixa e converte (retorna) 
 * a correspondente em notação pós-fixa.
 * Para evitar problemas de vazamento de memória e/ou falha de segmentação, faça 
 * cópia dos objetos. 
 * Lembre-se que a função 'desempilha' (Pilha.h) e 'dequeue' (Fila.h)
 * fazem a desalocação dos objetos(liberaObjeto)
 */
Fila *infixaParaPosfixa(Fila *infixa) {
    if(!infixa) return NULL;

    Fila *posfixa = criaFila();
    Pilha *temp = criaPilha();
    Objeto * auxinfixa, *auxretira, *insere, *insere2;
    auxinfixa = front(infixa);
    
    while(auxinfixa){
        insere = copiaObjeto(auxinfixa);

        if(auxinfixa->categoria == FLOAT || auxinfixa->categoria == INT) enqueue(posfixa, insere);
        else if (auxinfixa->categoria == ABRE_PARENTESES) empilha(temp, insere);

        else if (auxinfixa->categoria == FECHA_PARENTESES){
            auxretira = topoPilha(temp);
            free(insere);
            while(auxretira && auxretira->categoria != ABRE_PARENTESES){
                insere = copiaObjeto(auxretira);
                enqueue(posfixa, insere);
                desempilha(temp);
                auxretira = topoPilha(temp);
            }
            desempilha(temp);
        }
        else if(getPrecedenciaOperadores(auxinfixa->categoria)==1){
            auxretira = topoPilha(temp);
            while(auxretira && getPrecedenciaOperadores(auxretira->categoria)>=1){
                insere2 = copiaObjeto(auxretira);
                enqueue(posfixa, insere2);

                desempilha(temp);
                auxretira = topoPilha(temp);
            }
            empilha(temp, insere);
        }

        else if(getPrecedenciaOperadores(auxinfixa->categoria) == 2){
            auxretira = topoPilha(temp);
            while(auxretira && getPrecedenciaOperadores(auxretira->categoria)>=2){
                insere2 = copiaObjeto(auxretira);
                enqueue(posfixa, insere2);

                desempilha(temp);
                auxretira = topoPilha(temp);
            }
            empilha(temp, insere);
        }
        else if(getPrecedenciaOperadores(auxinfixa->categoria) == 3){
            auxretira = topoPilha(temp);
            while(auxretira && getPrecedenciaOperadores(auxretira->categoria)>3){
                insere2 = copiaObjeto(auxretira);
                enqueue(posfixa, insere2);

                desempilha(temp);
                auxretira = topoPilha(temp);
            }
            empilha(temp, insere);
        }
        auxinfixa = auxinfixa->proximo;
    }
    auxretira = topoPilha(temp);
    while(auxretira){
        insere = copiaObjeto(auxretira);
        enqueue(posfixa, insere);

        desempilha(temp);
        auxretira = topoPilha(temp);
    }
    liberaPilha(temp);
    return posfixa;
}

void imprimePosFixa(Fila *posfixa) {
    Fila *f = copiaFila(posfixa);
    while(!filaVazia(f)) {
        Objeto *obj = front(f);
        imprimeObjeto(obj, POSFIXA);
        dequeue(f);

    }
    printf("\n");
    liberaFila(f);
}
