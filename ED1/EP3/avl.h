//João Paulo Souza Ferrete e Ramon Pezzin Ton

//Inclusão das bibliotecas utilizadas no programa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Util.h"
#include "Fila.h"

//Definição da estrutura de arvore
typedef struct AVL{
    struct AVL *left, *right;
    char * info;
    int balance;
}AVL;

//Prototipos das funções implementadas e explicadas no arquivo 'avl.c'

AVL * encontraMenor(AVL * ptr);    //Função que encontra o menor elemento de uma árvore
AVL * criaArvore(char * inf);   //Função que cria uma raiz de árvore a partir de um elemento generico de informação
AVL * procuraAVL(AVL * ptr, char * inf);   //Função que busca um elemento numa árvore
void apagaAVL(AVL * ptr); //Função que libera todo o espaço utilizado por uma árvore
int alturaAVL (AVL * ptr);  //Função que retorna a altura de uma árvore
void balanceiaAVL(AVL * avl); //Função que faz a atualização do balanço de uma arvore
void imprimeArvore(AVL * ptr); //Função que imprime uma árvore
AVL * SimplesDireita(AVL * avl);    //Função que faz a rotação simples a direita
AVL * DuplaDireita(AVL * avl);  //Função que faz a rotação dupla a direita
AVL * SimplesEsquerda(AVL * avl);   //Função que faz a rotação simples a esquerda
AVL * DuplaEsquerda(AVL * avl); //Função que faz a rotação dupla a esquerda
AVL * inserirAVL(AVL * ptr, char * inf);  //Função que insere um elemento de informação na árvore
AVL * removeAVL(AVL * ptr, char * inf); //Função que remove um elemento de informação da árvore
bool encontraAVL(AVL * ptr, char* inf);
void sugestoes(AVL* pt, char *palavra, Fila ** f);
