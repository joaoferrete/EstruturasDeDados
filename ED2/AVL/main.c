//João Paulo Souza Ferrete e Ramon Pezzin Ton

#include "avl.h"


//Estrutura de informação a ser utilizada pela árvore
typedef struct produto{
    long long codigo; //Chave de busca e inserção na árvore
    char produto[50];
    int quant;
}info;





//Protótipos das funções a serem implementadas no arquivo
void printElemento(void * elem); //Função que imprime os dados de um elemento de informação
info *criarInfo();  //Função que cria o elemento de informação para a inserção na árvore
info *criarInfo2(); //Função que cria o elemento de informação para busca e exclusão
int compara(void * it1, void * it2);//Função de comparação passada por parâmetro
void copia(void ** it1, void ** it2);//Função que faz a troca dos elementos
void imprimeInfo(void *inf); //Função que imprime os dados de um elemento de informação









//Função main que utiliza a árvore
int main(){
    //Declaração de Variáveis
    int l, p=4; 
    info *elemento = NULL;
    AVL * ptr = NULL, * aux  = NULL;

    //Laço de repetição que mantem o programa em execução
    while( p != 0){
        //Impressão do menu
        printf("\n\n      ---- MENU ----\n");
        printf("Escolha uma das opções abaixo: \n");
        printf("1 - Inserir um elemento na arvore!\n");
        printf("2 - Remover um elemento da arvore!\n");
        printf("3 - Procurar um elemento na arvore!\n");
        printf("4 - Imprimir a arvore!\n");
        printf("0 - Sair do programa!\n\n");
        scanf("%d",&l);

        //Switch-case para escolha das opções do meu
        switch (l)
        {
        case 1:
            //Caso que corresponde a inserção de um elemento na árvore

            printf("\nQual elemento deseja inserir: \n");
            elemento = criarInfo();         //Cria o elemento de informação a ser inserido
            printElemento(elemento);        //Imprime as informações do item que será inserido na árvore

            printf("\nAperte ENTER para continuar"); //Solicita um char para que a execução continue
            getchar();
            getchar();

            ptr = inserirAVL(ptr,elemento, &compara);  //A função insere o elemento na arvore 'ptr', 
            //                                           retorna a arvore resultante e tem como parametro a
            //                                           função de comparação do elemento de informação

            printf("\nElemento adicionado! \n");
            getchar();
            break;

        case 2:
            //Caso que corresponde a opção de remoção de um item da arvore

            printf("\nQual elemento deseja remover: \n");
            elemento=criarInfo2();      //Criação do elemento de informação a ser buscado, contendo apenas a chave de busca
            aux=procuraAVL(ptr, elemento, &compara); //Verificação de o elemento buscado existe ou não
            
            if(aux) {
                //Caso o elemento a ser removido exista
                printElemento(aux->info);   //Impressão dos dados do elemento e a solicitação de um char
                printf("\nAperte ENTER para continuar");
                getchar();
                getchar();
           
            }else {
                //Caso o elemento a ser removido nao exista
                printf("\n---ELEMENTO NÃO ENCONTRADO---\n");
                //É impresso que o elemento não foi encontrado, libera-se o elemento de informação criado e volta para o menu
                if(elemento) free(elemento);
                break;
            }
            //O elemento buscado é passado por parametro para que seja feita e exclusão, junto com a função de comparação
            //E de cópia, retornando a arvore resultante
            ptr = removeAVL(ptr, elemento, &compara, &copia);
            
            //E liberado o espaço utilizado pelo elemento de busca
            if(elemento) free(elemento);
            printf("\nELEMENTO REMOVIDO!");
            printf("\nAperte ENTER para continuar");
            getchar();
            break;
        
        case 3:
            //Caso que corresponde a opção de busca 
            printf("\nQual elemento deseja procurar: \n");
            elemento=criarInfo2();          //Cria-se o elemento de informação com a chave para fazer a busca
            aux=procuraAVL(ptr, elemento, &compara);    //É feita a busca, passando por parametro o elemento com a chave e
            //                                           a função de comparação e é retornado um ponteiro para o elemento buscado

            if(aux) {
                //Caso o elemento buscado exista (retorno diferente de null)
                printElemento(aux->info);   //Imprime-se os dados desse elemento
                printf("\nAperte ENTER para continuar");
                getchar();  //Solicita um CHAR para continuar
                getchar();

            }else printf("\n---ELEMENTO NÃO ENCONTRADO---\n");//Caso contrário, o elemento não foi encontrado

            if(elemento) free(elemento);    //É liberado o elemento de busca
            break;

        case 4:
            //Caso que corresponde a opção de impressão da arvore

            printf("\n---IMPRIMINDO ARVORE---\n");
            if(ptr)imprimeArvore(ptr, &imprimeInfo);    //Caso a árvore exista, é chamada a função de impressão, com a função
            //                                            de impressão de elemento de informação por parâmetro

            else printf("ARVORE VAZIA\n");              //Caso a árvore esteja nula é impresso a mensagem de árvore vazia

            printf("\nAperte ENTER para continuar");  
            getchar();
            getchar();
            break;

        case 0:
            //Opção que corresponde a opção de sair do programa

            if(ptr) apagaAVL(ptr);    //Caso exista uma arvore, ela será liberada
            printf("\n----Programa Finalizado!!----\n");    //impressão da informação de programa encerrado
            p = 0;      //P recebe  valor da condição de parada
            break;
       }
    }

}








//Declaração das funções utilizadas

info *criarInfo(){
    //Função que cria um elemento de informação para ser inserido na árvore
    info *elemento;
    elemento= (info*)mallocSafe(sizeof(info));  //Alocação do espaço para um elemento de informação

    //Solicitação dos dados necessários para um elemento de informação
    printf("Digite o codigo: ");
    scanf("%lld",&elemento->codigo);
    printf("Digite o nome do produto: ");
    scanf("%s", elemento -> produto);
    printf("Digite a quantidade do estoque: ");
    scanf("%d",&elemento -> quant);

    //Retorno do ponteiro para o elemento de informação criado
    return elemento;
}

info *criarInfo2(){
    //Função que cria um elemento de informação para busca ou remoção

    info *elemento = (info*)mallocSafe(sizeof(info));   //Alocação de espaço para o elemento de informação
    printf("Digite o codigo: ");                        //Solicitação da inserção do código-chave do elemento 
    scanf("%lld",&elemento->codigo);

    return elemento;    //Retorno de ponteiro para o espaço alocado
}

void printElemento(void * elem){
    //Função responsável pela impressão das informações de um elemento de informação

    info* inf = (info *) elem;  //Casting de um elemento genérico para um elemento do tipo info

    //Impressão dos dados sobre o elemento passado
    printf("\n---SOBRE O PRODUTO---\n");
    printf("Código do produto: %lld\n",inf->codigo);
    printf("Nome produto: %s\n", inf->produto);
    printf("Quantidade do Produto: %d\n", inf->quant);
}

int compara(void * it1, void * it2){
    //Função que compara dois elementos de informação

    info * item1 = (info *) it1; //Casting de elementos genéricos para o tipo de elemento de informação
    info * item2 = (info*) it2;

    if(!item1 && !item2) return 0;  //Caso ambos elementos não existam, eles são iguais, portanto se retorna 0
    else if(!item1) return 1;       //Caso o primeiro elemento nao exista, entao o segundo elemento é maior, se retornando 1
    else if(!item2) return -1;      //Caso o segundo elemeto não exista, entao o primeiro elemento é maior, se retornando -1
    else if(item1->codigo > item2->codigo) return -1;   //Caso o código do primeiro item seja maior se retorna -1
    else if(item2->codigo > item1->codigo) return 1;    //Caso o código do segundo item seja paior se retorna 1
    else return 0;  //Caso eles sejam iguais se retorna 0
}

void copia(void ** it1, void ** it2){
    //Função que efetua a troca entre os dados de dois elementos. Os parametros são ponteiros de ponteiros para poder efetuar a troca

    info * item1 = (info *) *it1; //Casting dos elementos genéricos para o tipo de informação
    info * item2 = (info*) *it2;
    
    info * aux = mallocSafe(sizeof(info));  //Alocação do espaço de elemento de informação auxiliar

    //Troca dos códigos
    aux->codigo=item2->codigo;
    item2->codigo=item1->codigo;
    item1->codigo=aux->codigo;

    //Troca dos nomes
    strcpy(aux->produto, item2->produto);
    strcpy(item2->produto, item1->produto);
    strcpy(item1->produto, aux->produto);

    //troca das quantidades
    aux->quant=item2->quant;
    item2->quant = item1->quant;
    item1->quant=aux->quant;

    //Atribuição dos novos valores no campo de memória original
    *it1 = item1;
    *it2 = item2;

    //Libera-se o elemento auxiliar
    free(aux);
}

void imprimeInfo(void *inf){
    //Função para impressão da chave de um elemento de informação
    info * elemento = (info *) inf; //Casting para o tipo de informação
    printf("%lld\n\n", elemento->codigo);//Impressão da chave do elemento para utilização na impressão da árvore
}