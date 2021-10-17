/* João Paulo Souza Ferrete e Ramon Pezzin Ton */
/* Trabalho de Estrutura de Dados 2 - Ciência da Computação */

/* Inclusão das bibliotecas */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definição da estrutura de árvore para o código de Huffman */
typedef struct tree{
    struct tree *esq;
    struct tree *dir;
    long long freq;  //Contém a quantidade de vezes que um caractere se repete
    char caractere; //Contém o caractere correspondente
} Arvore;

/* Definição da estrutura de No para a criação do vetor utilizado na implementação */
typedef struct node{
    long long freq;
    char caractere;
    Arvore * tree;
    int * codigo;
    int tamCod;
} No;

/* Cabeçalho das funções implementadas */
void * mallocSafe(size_t tam);
void imprimeVetor(No * vet, long long tam);
void imprimeVetorCod(No * vet, long long tam);
void minHeapify (No* vet, long long i, long long tam);
void construirheapmin(No* vet, long long tam);
No * insereFrequencia(char * nomeArquivo, long long *tam);
Arvore * criaArvore(char carac, long long freq);
No * copiaVet(No * vet, long long tam);
Arvore * algoritmoHuffman(No *vetor, long long tam);
int altura (Arvore * ptr);
void invertelista(int* vet, long long tam);
void imprimeArvore(Arvore * ptr);
int codigo(char carac, int *tamCod, int * cod, Arvore * pt, int tamMax);
No * pegaCod(No* vet, long long n, Arvore* raiz);
long long calculaTamVet(No *vet, long long n);
long long calculaBit(No *vet, long long n);
unsigned char * vetorSaida(No* vet, long long n, long long *tamBit, char * nomeArq);
void binCode(unsigned char * vet, long long tam, Arvore *raiz, char * nomeArq);
void descomprimir(char * nomeArq);
void salvar(long long tamBin, long long tamVetor, No* vetor, unsigned char *vetSaida, char* nomeSaida, long long tamVetSaida);
void comprimir();
