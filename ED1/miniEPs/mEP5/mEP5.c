#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Util.h"
#include "Objetos.h"
#include "Lista.h"
#include "mEP5.h"

/**
 * @brief Verifica se a lista com a expressão matemática (que pode contér números e simbolos)
 * é uma expressão válida. Além disso, ela também deve verificar se os operados são válidos, 
 * ou seja, se são '+' ou '-' (únicos que serão considerados válidos nesse miniEP).
 * Uma expressão deve ser considerada inválida se:
 * - Houver a leitura de dois objetos seguidos do mesmo tipo (por exemplo, dois objetos do tipo STR 
 *   ou dois objetos numéricos);
 * - Terminar com um operador;
 * - Se o operador não for soma (+) ou subtração (-).
 * 
 * @param expressao: lista encadeada com os itens (números e possíveis operadores)
 * @return true ou false
 */
bool expressaoValida(Lista *expressao) {
    if(!expressao || !getPrimeiro(expressao)) {
        return false;
    }
    Objeto *obj = getPrimeiro(expressao);
    Objeto *obj2 = obj->proximo;

    if(!obj2 && obj->tipo != STR) return true;
    else if(!obj2) return false;

    while(obj2) {
        if(obj->tipo == obj2->tipo) return false;
        if(!obj2->proximo && obj2->tipo == STR) return false;
        if(obj->tipo == STR && strcmp(obj->item.vString, "+") != 0 && strcmp(obj->item.vString, "-") != 0) return false;
        obj = obj2;
        obj2 = obj->proximo;
    }
    
    return true;
}

/**
 * @brief Calcula o valor da expressão presente em 'expressão'. Supõem-se que a 
 * expressão é válida. 
 *  
 * Exemplos: 
 * - 10 = -10
 * 10 = 10
 * 10 + -15 = -5 (o '-15' significa o número inteiro -15 e não o operador '-' seguido do número 15)
 * - 10 + 15 = 5
 * -10 - -15 = 5
 * - -10 - -15 = 25
 * + 10 + -15 = -5
 * 3.5 + 10 = 13.5 (note que se um valor for real, o resultado final *deve* ser real)
 * 
 * @param expressao: lista encadeada com os itens (números e possíveis operadores)
 * @return Objeto* 
 */
Objeto *avaliaExpressao(Lista *expressao) {
    Objeto *resultado = criaObjeto();
    Objeto *obj = getPrimeiro(expressao);

    if(obj->tipo != STR) {
        resultado->tipo = obj->tipo;
        if(obj->tipo == INT) resultado->item.vInt=obj->item.vInt;
        else resultado->item.vFloat=obj->item.vFloat;
    }
    else {
        if(strcmp(obj->item.vString, "+") == 0) {
            if(obj->proximo->tipo ==INT) {
                resultado->tipo = INT;
                resultado->item.vInt = obj->proximo->item.vInt;
            }
            else {
                resultado->tipo = FLOAT;
                resultado->item.vFloat = obj->proximo->item.vFloat;
            }
        }
        else if(strcmp(obj->item.vString, "-") == 0) {
            if(obj->proximo->tipo ==INT) {
                resultado->tipo = INT;
                resultado->item.vInt = -obj->proximo->item.vInt;
            }
            else {
                resultado->tipo = FLOAT;
                resultado->item.vFloat = -obj->proximo->item.vFloat;
            }
        }
        obj=obj->proximo;
    }
    if(!obj->proximo) return resultado;

    while(obj->proximo){
        float valor;

        Objeto *obj2 = obj->proximo;
        Objeto *obj3 = obj2->proximo;

        if(strcmp(obj2->item.vString, "+") == 0){
            if(resultado->tipo == INT && obj3->tipo == INT){
                resultado->item.vInt += obj3->item.vInt;
            }
            else if (resultado->tipo == INT && obj3->tipo == FLOAT){
                resultado->tipo = FLOAT;
                valor = (float)resultado->item.vInt ;
                resultado->item.vFloat = valor + obj3->item.vFloat;
            }
            else if (resultado->tipo == FLOAT && obj3->tipo == INT){
                resultado->item.vFloat += (float) obj3->item.vInt;
            }
            else{
                resultado->item.vFloat += obj3->item.vFloat;
            }
        }
        else if(strcmp(obj2->item.vString, "-") == 0){
            if(resultado->tipo == INT && obj3->tipo == INT){
                resultado->item.vInt -= obj3->item.vInt;
            }
            else if (resultado->tipo == INT && obj3->tipo == FLOAT){
                resultado->tipo = FLOAT;
                valor = (float) resultado->item.vInt;   
                resultado->item.vFloat = valor - obj3->item.vFloat;
            }
            else if (resultado->tipo == FLOAT && obj3->tipo == INT){
                resultado->item.vFloat -= (float) obj3->item.vInt;
            }
            else{
                resultado->item.vFloat -= obj3->item.vFloat;
            }
        }
        obj = obj3;
        
    }
    return resultado;
}
