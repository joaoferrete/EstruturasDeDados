#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Objetos.h"

Objeto *criaObjeto() {
    Objeto *obj = malloc(sizeof(Objeto));
    obj->tipo = INDEFINIDO;
    obj->item.vString = NULL;
    obj->proximo = NULL;
    return obj;
}

Objeto *criaObjetoInteiro(int valor) {
    Objeto *obj = malloc(sizeof(Objeto));
    obj->tipo = INT;
    obj->item.vInt = valor;
    obj->proximo = NULL;
    return obj;
}

Objeto *criaObjetoReal(double valor) {
    Objeto *obj = malloc(sizeof(Objeto));
    obj->tipo = FLOAT;
    obj->item.vFloat = valor;
    obj->proximo = NULL;
    return obj;
}

Objeto *criaObjetoString(char *palavra) {
    Objeto *obj = malloc(sizeof(Objeto));
    obj->tipo = STR;
    obj->item.vString = malloc((strlen(palavra) + 1) * sizeof(char));
    strcpy(obj->item.vString, palavra);
    obj->proximo = NULL;
    return obj;
}

void liberaObjeto(Objeto *obj) {
    if(obj == NULL) return;
    if (obj->tipo == STR && obj->item.vString)
        free(obj->item.vString);
    free(obj);
}

void imprimeInformacaoObjeto(Objeto *obj) {
    if (obj == NULL)
        return;
    if(obj->tipo == INT) {
        printf("Inteiro com valor: %d\n", obj->item.vInt);
    }
    else if (obj->tipo == FLOAT) {
        printf("Real com valor: %.5lf\n", obj->item.vFloat);
    }
    else if (obj->tipo == STR) {
        printf("String com valor: %s\n", obj->item.vString);
    }
    else {
        printf("Tipo não reconhecido\n");
    }
}

void imprimeItemObjeto(Objeto *obj) {
    if (obj == NULL)
        return;
    if(obj->tipo == INT) {
        printf("%d ", obj->item.vInt);
    }
    else if (obj->tipo == FLOAT) {
        printf("%.5lf ", obj->item.vFloat);
    }
    else if (obj->tipo == STR) {
        printf("%s ", obj->item.vString);
    }
    else {
        printf("Tipo não reconhecido ");
    }
}