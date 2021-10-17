/* João Paulo Souza Ferrete e Ramon Pezzin Ton */
/* Trabalho de Estrutura de Dados 2 - Ciência da Computação */


#include "huffman.h"  //Inclusão do arquivo .h com as bibliotecas


int main(){
    /* Função principal que tem as opções de compactar e descompactar, e a opção de sair */

    int op, enq = 1;
    char nomearq[50];

    while(enq){
        /* Impressão do menu inicial */
        printf("\n\n--------MENU--------\n");
        printf("1 - Compactar um arquivo\n");
        printf("2 - Descompactar um arquivo\n");
        printf("0 - Sair do programa\n");
        scanf("%d", &op);

        /* Switch Case pra cada opção do programa */
        switch(op){
            case 1:
                comprimir();
                break;
            case 2:
                printf("Insira o nome do arquivo que deseja descompactar: ");
                scanf("%s", nomearq);
                descomprimir(nomearq);
                break;
            case 0:
                enq=0;
                return 0;
                break;
            default:
                break;  
        }
    }
}