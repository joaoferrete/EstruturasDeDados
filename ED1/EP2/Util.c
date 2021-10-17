/*
 * ESTE ARQUIVO NÃO PRECISA SER MODIFICADO, APENAS ENTENDA O QUE CADA FUNÇÃO FAZ
 */
#include <stdlib.h> 
#include <stdio.h>  

#include "Util.h"
#include "Categorias.h"

static char *operador[MAX_SIMBOLOS] = {
        /* 7 operadores aritmeticos */
        "^"  /*  0 "operador exponenciacao" */
        ,"%" /*  1 "operador resto de divisao" */
        ,"*" /*  2 "operador aritmetico multiplicacao" */
        ,"/" /*  3 "operador aritmetico divisao" */
        ,"+" /*  4 "operador aritmetico adicao" */
        ,"-" /*  5 "operador aritmetico subtracao" */
        ,"_" /*  6 "operador aritmetico \"menos unario\"" */
        /* parenteses */
        ,"(" /*  7 "abre  parenteses" */
        ,")" /*  8 "fecha parenteses" */
};

/* Fonte:  http://www.ime.usp.br/~pf/algoritmos/aulas/aloca.html */
void *mallocSafe(size_t nbytes) {
    void *ptr;

    ptr = malloc(nbytes);
    if (ptr == NULL) {
        ERRO(Socorro !malloc devolveu NULL !);
        exit(EXIT_FAILURE);
    }

    return ptr;
}

/*------------------------------------------------------------*/
/* Tabela com uma representacao da precedencia dos operadores
 * atraves de valores inteiros. 
 * Quanto maior o valor, maior a precedencia.
 *
 *  http://www.ime.usp.br/~pf/algoritmos/apend/precedence.html
 */
int getPrecedenciaOperadores(int op) {
    switch (op)
    {
    case OPER_ADICAO:
    case OPER_SUBTRACAO:
        return 1;
    case OPER_DIVISAO:
    case OPER_RESTO_DIVISAO:
    case OPER_MULTIPLICACAO:
        return 2;

    case OPER_EXPONENCIACAO:
    case OPER_MENOS_UNARIO:
        return 3;
    }
    return -1;
}

char *getOperador(int i) {
    if (i < 0 || i > MAX_SIMBOLOS) {
        printf("ERRO: Categoria inválida\n");
        return " ";
    }
    return operador[i];
}