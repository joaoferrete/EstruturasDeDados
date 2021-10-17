#include <stdio.h>
#include <stdlib.h>

#include "Util.h"
#include "Objetos.h"
#include "Lista.h"
#include "mEP5.h"

int main() {
    Lista *expressao = criaLista();
    String str = malloc(25*sizeof(char));

    //Faz a leitura enquanto não chegar no EOF (end-of-file)
    while(scanf("%s", str) == 1) {
        //printf("%s ", str);
        if(ehNumeroInteiro(str)) {
            //printf("(int)\n");

            /**
             * Converte o str para inteiro (usando a função atoi),
             * cria o objeto inteiro e o insere na lista.
             * Para saber mais sobre a função atoi: 
             * https://www.cplusplus.com/reference/cstdlib/atoi/
             */ 
            insereLista(expressao, criaObjetoInteiro(atoi(str)));
        }
        else if(ehNumeroReal(str)) {
            //printf("(double)\n");

            /**
             * Converte o str para double (usando a função atof),
             * cria o objeto inteiro e o insere na lista.
             * Para saber mais sobre a função atof:
             * https://www.cplusplus.com/reference/cstdlib/atof/ 
             */
            insereLista(expressao, criaObjetoReal(atof(str)));
        }
        else {
            //printf("(str)\n");

            /**
             * Cria o objeto string e o insere na lista
             */ 
            insereLista(expressao, criaObjetoString(str));
        }
    }

    /**
     * Verifica se a expressão está correta.
     * Se estiver, calcula-se o resultado da expressão
     */
    if(expressaoValida(expressao)) {
        imprimeLista(expressao, imprimeItemObjeto);
        printf("= ");
        Objeto *resultado = avaliaExpressao(expressao);
        imprimeItemObjeto(resultado);
        printf("\n");
        liberaObjeto(resultado);
    }
    else {
        printf("Expressao invalida!\n");
    }

    free(str);
    liberaLista(expressao);
    return 0;
}

