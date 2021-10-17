/* João Paulo Souza Ferrete e Ramon Pezzin Ton */

#include "rubro.h"  //Inclusão do arquivo da Rubro Negra

/* Definição da estrutura-objeto do programa*/
typedef struct artigo{
    int id;
    int ano;
    char autor[200];
    char titulo[200];
    char revista[200];
    char DOI[200];
    char palavraChave[200];
}Artigo;


int comparaArt(void* ob1, void* ob2){
    /*Função de comparação entre elementos do tipo Artigo*/

    int a = ((Artigo*)ob1)->id; //Atribuição dos valores do ID para a variável int
    int b = ((Artigo*)ob2)->id;

    if(a>b) return -1;  //Caso o primeiro elemento seja maior que o segundo é retornado -1
    if(a<b) return 1;   //Caso O segundo elemento seja maior que o primeiro, então é retornado 1
    return 0;   //Caso os elementos sejam iguais é retornado 0

}

Artigo * insereArtigo(){
    /*Função que cria um novo elemento do tipo Arquivo para ser inserido na árvore*/

    Artigo *a = (Artigo *) malloc(sizeof(Artigo));  //Alocação do artigo

    printf("Insira o ID do artigo: ");      //Solicitação do ID e dos outros atributos
    scanf("%d", &a->id);
    printf("Insira o Título do artigo: ");
    scanf("%s", a->titulo);
    printf("Insira o nome do autor: ");
    scanf("%s", a->autor);
    printf("Insira o ano de publicação: ");
    scanf("%d", &a->ano);
    printf("Insira o nome da revista: ");
    scanf("%s", a->revista);
    printf("Insira o DOI: ");
    scanf("%s", a->DOI);
    printf("Insira as palavras-chave: ");
    scanf("%s", a->palavraChave);

    return a;   //Retorna o ponteiro para o novo elemento criado
}

Artigo * pesquisaArt(){
    /*Função que cria um elemento de informação para fazer a busca ou deleção, contendo apenas o ID*/

    Artigo *a = (Artigo *) malloc(sizeof(Artigo));  //Alocação do ponteiro para o elemento Artigo
    printf("Insira o ID do artigo: ");  
    scanf("%d", &a->id);    //Inserção do ID para efetuar a busca

    return a;   //Retorno do ponteiro alocado
}

void imprimeArtigo(void *obj){
    /*Função que imprime todos os atributos de um artigo recebido por parâmetro*/

    Artigo *a = (Artigo *) obj; //Casting do elemento de tipo genético para o tipo Artigo

    //Impressão de todos os atributos
    printf("ID: %d\n", a->id);
    printf("Titulo: %s\n", a->titulo);
    printf("Autor: %s\n", a->autor);
    printf("Ano: %d\n", a->ano);
    printf("Revista: %s\n", a->revista);
    printf("DOI: %s\n", a->DOI);
    printf("Palavra-chave: %s\n", a->palavraChave);
}

void imprimeArvore(rubro * ptr){
    /*Função responsável por imprimir uma árvore que recebe como parâmetro um ponteiro para árvore*/

    if(!ptr || ptr == externo) return;  //Caso a árvore esteja vazia ou seja igual ao externo
    int i, nivel = alturaRubro(ptr); //Nivel passa a ser a altura da árvore

    if(ptr){//Se a árvore não for nula
        imprimeArvore(ptr->esq);    //Chamada recursiva para impressão da subárvore esquerda

        for(i=0; i<nivel; i++) printf("\t");    //Impressão de tabulação de acordo com o nível
        Artigo *a = (Artigo *) getObj(ptr);     //Casting de tipo genérico para tipo Artigo
        if(getCor(ptr) == vermelho) printf("[%d : rubro]\n\n", a->id);  //Impressão do ID para nós rubros
        else printf("[%d : negro]\n\n", a->id); //Impressão do ID para nós negros
        
        imprimeArvore(ptr->dir);     //Chamada recursiva para impressão da subárvore direita
    }
}



int main(){
    
    externo = (rubro *) malloc(sizeof(rubro));  //Alocação de memória para o nó externo
    externo->Cor = preto;   //A cor do externo é sempre negra
    externo->pai = externo->dir = externo->esq = externo;   //Todos os ponteiros de externo apontam para ele mesmo

    bool ba=true;   //Variável bool para garantir a execução do laço de repetição
    //Declaração de variáveis
    int op;     
    rubro *aux, *pt = externo;
    Artigo * art;
    char a;

    //Laço para impressão do menu e solicitação de opção
    while(ba){
        printf("\n\n--------MENU--------\n");
        printf("1 - Inserir artigo\n");
        printf("2 - Remover artigo\n");
        printf("3 - Pesquisar artigo\n");
        printf("4 - Imprimir Árvore\n");
        printf("0 - SAIR\n");
        printf("--------------------\n");
        scanf("%d", &op);

        switch (op){
            case 1:
                //Caso escolhida a opção de inserir artigo

                art = insereArtigo();   //É criado um novo Artigo, e solicitado a o usuário que insira os elementos
                insereRubro(&pt, art, &comparaArt); //O novo elemento é inserido na árvore pt;
                printf("\n\nELEMENTO INSERIDO!\n");
                
                getchar();
                getchar();
                break;
            
            case 2:
                //Caso o usuário escolha a opção de deletar um artigo

                art = pesquisaArt();    //Alocação e inserção de um elemento para busca contendo apenas o ID

                aux = buscaRubro(pt, art, &comparaArt);     //É efetuada a busca, e o ponteiro resultante é atribuído à aux
                if(!aux) printf("\nElemento não encontrado!\n");    //Se aux for Nulo, então o elemento nao foi encontrado
                else{   //Caso contrário o elemento foi encontrado

                    printf("\n\nElemento Encontrado: \n");
                    imprimeArtigo(getObj(aux)); //É impresso todas as informações do artigo encontrado

                    printf("Deseja apaga-lo? (s/n):  ");    //Solicita ao usuário uma confirmação para a deleção
                    getchar();
                    scanf("%c", &a);
                    if(a=='s' || a=='S'){   //Caso o usuário deseje remover

                        removeRubro(&pt, aux);  //Função de deleção, passando um ponteiro para o nó a ser apagado

                        printf("\n\nElemento apagado!\n");

                        getchar();
                        getchar();
                    }
                }
                free(art);  //O elemento de informação para a busca é liberado
                break;

            
            
            case 3:
                //Caso o usuário insira a opção de busca

                art = pesquisaArt();    //Elemento de informação apenas com o ID para a busca

                aux = buscaRubro(pt, art, &comparaArt); //Execução da busca

                if(!aux) printf("Elemento não encontrado!\n");  //Caso aux seja nulo, então elemento nao foi encontrado
                else{   //Elemento encontrado

                    printf("\n\nElemento Encontrado: \n");
                    imprimeArtigo(getObj(aux));//Impressão dos elementos do artigo
                }
                getchar();
                getchar();

                free(art);
                break;

            case 4:
                //Caso o usuário deseje imprimir a árvore

                printf("Imprimindo árvore: \n\n");
                imprimeArvore(pt);
                getchar();
                getchar();
                break;

            case 0:
                //Caso o usuário deseje sair do programa

                apagaArvore(pt);    //Função que libera todo o espaço utilizado pela árvore
                free(externo);  //Espaço alocado para o nó externo é liberado
                ba=false;   //Condição de parada do laço
        }
    }
}
