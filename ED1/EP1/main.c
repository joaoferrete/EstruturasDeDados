#include <stdio.h> 
#include <stdlib.h> 

#include "Imagem.h"
#include "Grafico.h"

int main(int argc, char *argv[]) {

    Imagem* imagem = NULL; //Ponteiro para a imagem
    char *nomeArq = NULL;  //Nome do arquivo

    if(argc == 2) {
        nomeArq = argv[1];
    }
    else {
        fprintf(stderr, "Uso\n$ %s <nome arq. imagem>\n", argv[0]);
        return 0;
    }

    imagem = carregaImagem(nomeArq);

    if (imagem == NULL) {
        AVISO("Erro ao carregar a imagem");
        return 0;
    }

    inicializa(&argc, argv, imagem);

    return 0;
}


