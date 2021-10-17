/* João Paulo Souza Ferrete e Ramon Pezzin Ton */

#include <stdio.h>  //Inclusão de bibliotecas
#include <stdlib.h>

typedef enum cor{
    /* Definição de tipo usando enumerador para definir as cores na árvore */
    preto,
    vermelho
}cor;

typedef enum boolean{
    /* Definição do tipo booleano para facilitar o tratamento com elementos verdadeiros e falsos */
    false,
    true
}bool;

typedef struct rubro{
    /* Estrutura de árvore rubro-negra */
    void * obj; //Elemento genérico de dado
    cor Cor;    //Cor do nó correspondente  
    struct rubro * esq, *dir, *pai; //Ponteiro para os filhos e para o pai do nó
}rubro;

rubro * externo;    //Definição de variável global Externo



void apagaArvore(rubro * pt);  //Função que libera todo o espaço utilizado por uma árvore
rubro * criarRubro();   //Função que cria um novo nó de árvore rubro-negra
rubro * buscaRubro(rubro * pt, void* obj, int (*compara)(void*, void*));    //Função de busca de elemento em árvore rubro-negra
void rubroIFixUp(rubro **pt, rubro* q); //Função de correção de inserção
void insereRubro(rubro** pt, void* obj, int (*compara)(void*, void*));  //Função de inserção em árvore rubro-negra
void rotacaoEsquerda(rubro ** pt, rubro *w);    //Função que efetua a rotação para a esquerda
void rotacaoDireita(rubro ** pt, rubro *w);     //Função que efetua a rotação para a direita
int alturaRubro (rubro * ptr);      //Função que retorna a altura de uma árvore rubro-negra
void* getObj(rubro * pt);       //Função que retorna o elemento de informação de um nó da árvore
cor getCor(rubro* pt);  //Função que retorna a cor de um nó da árvore
void transferePaiRubro(rubro ** pt, rubro* u, rubro*v); //Função que transfere o pai de um nó para outro
void rubroRFixUp(rubro **pt, rubro* x); //Função de correção de remoção da árvore rubro-negra
void removeRubro(rubro **pt, rubro *z); //Função de remoção na árvore rubro-negra
