#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Util.h"

/**
 * @brief Verifica se o string 'str' contém um número inteiro.
 * 
 * @param str: String a ser testado
 * @return true ou false
 */
bool ehNumeroInteiro(String str) {
    int len = strlen(str);
	if (len == 0)
		return false;
	//Verifica se o primeiro simbolo do possivel número é o + ou - (menos unário)
	//Se for, iniciamos a verificação na posição 1. 
	int i = ((str[0] == '+' || str[0] == '-') ? 1 : 0);

	//Se não tiver mais caracteres, significa que não existem dígitos
	if (i == len) 
		return false;

	//Verifica se todos os outros caracteres são dígitos
	while (i < len) {
		if ( !isdigit(str[i]) )
			return false;
		i++;
	}
	return true;
}

/**
 * @brief Verifica se o string 'str' contém um número real.
 * 
 * @param str: String a ser testado
 * @return true ou false
 */
bool ehNumeroReal(String str) {
    /**
     * 
     * 
     */
    int len = strlen(str);
	bool hasDecimal = false;
	if (len == 0)
		return false;
	//Verifica se o primeiro simbolo do possivel número é o + ou - (menos unário)
	//Se for, iniciamos a verificação na posição 1.
	int i = ((str[0] == '+' || str[0] == '-') ? 1 : 0);

	//Se não tiver mais caracteres, significa que não existem dígitos
	if (i == len)
		return false;

	//Verifica se todos os outros caracteres são dígitos ou '.'
	while (i < len) {
        if ( (!isdigit(str[i]) && str[i] != '.') )
            return false;
        if (str[i] == '.' && hasDecimal) { // Garante que o string só contenha um '.'
			return false;
		}
		if (str[i] == '.')
			hasDecimal = true;
		i++;
    }
	return hasDecimal;
}