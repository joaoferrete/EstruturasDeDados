#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Avalia.h"
#include "Categorias.h"
#include "Pilha.h"
#include "Util.h"


/* Recebe uma fila de objetos em notação pós-fixa, avalia e retorna o resultado da expressação */
Objeto *avalia(Fila *posFixa) {
    if(!posFixa) return NULL;
    Objeto * auxfila, *auxpilha1, *auxpilha2, *resultado;
    Pilha * p = criaPilha();
    auxfila = front(posFixa);
    while(auxfila){
        if(auxfila->categoria == FLOAT || auxfila->categoria == INT) empilha(p, copiaObjeto(auxfila));
        else if (auxfila->categoria == OPER_ADICAO){
            auxpilha1 = topoPilha(p);
            auxpilha2 = auxpilha1->proximo;
            resultado = criaObjeto();
            if(auxpilha1->categoria == FLOAT && auxpilha2->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = auxpilha1->valor.vFloat + auxpilha2->valor.vFloat;
            }
            else if(auxpilha1->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = auxpilha1->valor.vFloat + auxpilha2->valor.vInt;
            }
            else if(auxpilha2->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = auxpilha1->valor.vInt + auxpilha2->valor.vFloat;
            }
            else{
                resultado->categoria = INT;
                resultado->valor.vInt = auxpilha1->valor.vInt + auxpilha2->valor.vInt;
            }
            desempilha(p);
            desempilha(p);
            empilha(p, resultado);
        }
        else if (auxfila->categoria == OPER_SUBTRACAO){
            auxpilha1 = topoPilha(p);
            auxpilha2 = auxpilha1->proximo;
            resultado = criaObjeto();
            if(auxpilha1->categoria == FLOAT && auxpilha2->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = auxpilha2->valor.vFloat - auxpilha1->valor.vFloat;
            }
            else if(auxpilha2->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = auxpilha2->valor.vFloat - auxpilha1->valor.vInt;
            }
            else if(auxpilha1->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = auxpilha2->valor.vInt - auxpilha1->valor.vFloat;
            }
            else{
                resultado->categoria = INT;
                resultado->valor.vInt = auxpilha2->valor.vInt - auxpilha1->valor.vInt;
            }
            desempilha(p);
            desempilha(p);
            empilha(p, resultado);
        }
        else if (auxfila->categoria == OPER_MULTIPLICACAO){
            auxpilha1 = topoPilha(p);
            auxpilha2 = auxpilha1->proximo;
            resultado = criaObjeto();
            if(auxpilha1->categoria == FLOAT && auxpilha2->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = auxpilha1->valor.vFloat * auxpilha2->valor.vFloat;
            }
            else if(auxpilha1->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = auxpilha1->valor.vFloat * auxpilha2->valor.vInt;
            }
            else if(auxpilha2->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = auxpilha1->valor.vInt * auxpilha2->valor.vFloat;
            }
            else{
                resultado->categoria = INT;
                resultado->valor.vInt = auxpilha1->valor.vInt * auxpilha2->valor.vInt;
            }
            desempilha(p);
            desempilha(p);
            empilha(p, resultado);
        }
        else if (auxfila->categoria == OPER_DIVISAO){
            auxpilha1 = topoPilha(p);
            auxpilha2 = auxpilha1->proximo;
            resultado = criaObjeto();
            if(auxpilha1->categoria == FLOAT && auxpilha2->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = auxpilha2->valor.vFloat / auxpilha1->valor.vFloat;
            }
            else if(auxpilha2->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = auxpilha2->valor.vFloat / auxpilha1->valor.vInt;
            }
            else if(auxpilha1->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = auxpilha2->valor.vInt / auxpilha1->valor.vFloat;
            }
            else{
                resultado->categoria = INT;
                resultado->valor.vInt = auxpilha2->valor.vInt / auxpilha1->valor.vInt;
            }
            desempilha(p);
            desempilha(p);
            empilha(p, resultado);
        }
        else if (auxfila->categoria == OPER_RESTO_DIVISAO){
            auxpilha1 = topoPilha(p);
            auxpilha2 = auxpilha1->proximo;
            resultado = criaObjeto();
           
            if(auxpilha1->categoria == FLOAT && auxpilha2->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = fmod(auxpilha2->valor.vFloat, auxpilha1->valor.vFloat);
            }
            else if(auxpilha2->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = fmod(auxpilha2->valor.vFloat,(double) auxpilha1->valor.vInt);
            }
            else if(auxpilha1->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = fmod((double)auxpilha2->valor.vInt, auxpilha1->valor.vFloat);
            }
            else{
                resultado->categoria = INT;
                resultado->valor.vInt = auxpilha2->valor.vInt % auxpilha1->valor.vInt;
            }
        
            desempilha(p);
            desempilha(p);
            empilha(p, resultado);
        }
        else if (auxfila->categoria == OPER_EXPONENCIACAO){
            auxpilha1 = topoPilha(p);
            auxpilha2 = auxpilha1->proximo;
            resultado = criaObjeto();
            if(auxpilha1->categoria == FLOAT && auxpilha2->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = pow(auxpilha2->valor.vFloat, auxpilha1->valor.vFloat);
            }
            else if(auxpilha1->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = pow(auxpilha2->valor.vFloat, auxpilha1->valor.vInt);
            }
            else if(auxpilha2->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = pow(auxpilha2->valor.vInt, auxpilha1->valor.vFloat);
            }
            else{
                resultado->categoria = INT;
                resultado->valor.vInt = pow(auxpilha2->valor.vInt, auxpilha1->valor.vInt);
            }
            desempilha(p);
            desempilha(p);
            empilha(p, resultado);
        }
        else if (auxfila->categoria == OPER_MENOS_UNARIO){
            auxpilha1 = topoPilha(p);
            resultado = criaObjeto();
            if(auxpilha1->categoria == FLOAT){
                resultado->categoria = FLOAT;
                resultado->valor.vFloat = -auxpilha1->valor.vFloat;
            }
            else{
                resultado->categoria = INT;
                resultado->valor.vInt = -auxpilha1->valor.vInt;
            }
            desempilha(p);
            empilha(p, resultado);
        }
        auxfila = auxfila->proximo;
    }
    resultado = copiaObjeto(topoPilha(p));
    liberaPilha(p);

    return resultado;
}
