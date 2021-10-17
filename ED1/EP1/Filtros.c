#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Imagem.h"
#include "Filtros.h"

void escurecerImagem(Imagem *img){
    int v;
    printf("Digite o fator de escurecimento: ");
    scanf("%d", &v);

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED]   = (((int)pixel.cor[RED]   - v) >= 0 ? (pixel.cor[RED]   - v) : 0);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] - v) >= 0 ? (pixel.cor[GREEN] - v) : 0);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE]  - v) >= 0 ? (pixel.cor[BLUE]  - v) : 0);
            recolorePixel(img, h, w, pixel);
        }
    }
}

void clarearImagem(Imagem *img){
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'clarearImagem'); //Retire esssa mensagem ao implementar a fução
    int v;
    printf("Digite o fator de clareamento: ");
    scanf("%d", &v);

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED]   = (((int)pixel.cor[RED]   + v) <= 255 ? (pixel.cor[RED]   + v) : 255);
            pixel.cor[GREEN] = (((int)pixel.cor[GREEN] + v) <= 255 ? (pixel.cor[GREEN] + v) : 255);
            pixel.cor[BLUE]  = (((int)pixel.cor[BLUE]  + v) <= 255 ? (pixel.cor[BLUE]  + v) : 255);
            recolorePixel(img, h, w, pixel);
        }
    }
}

void escalaDeCinzaImagem(Imagem *img){
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'escalaDeCinzaImagem'); //Retire esssa mensagem ao implementar a fução
    int v;

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            v = (((int)pixel.cor[RED] + (int)pixel.cor[GREEN] + (int)pixel.cor[BLUE])/3);
            pixel.cor[RED]   = v;
            pixel.cor[GREEN] = v;
            pixel.cor[BLUE]  = v;
            recolorePixel(img, h, w, pixel);
        }
    }

}

void filtroSobel(Imagem *img){
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'filtroSobel'); //Retire esssa mensagem ao implementar a fução

    /* Dicas:
     * 1) Se quiser, pode ignorar as bordas das imagens
     * 2) Para o pixel na posição (h, w), obtenha os outros 8 pixels vizinhos e aplique a matriz gx e gy
     *    em cada banda de cor do pixel. Combine o valor obtido por gx e gy e modifique o pixel de img.
     *    Lembre-se que a obtenção dos pixels deve ser a partir de uma cópia da imagem.
     * 3) Verifique se o novo valor obtido para a banda de cor é um valor válido (entre 0 e 255).
    */

    Imagem *copia = copiaImagem(img);

    for (int h = 1; h < obtemAltura(img)-1; h++) {
        for (int w = 1; w < obtemLargura(img)-1; w++) {
            Pixel pixel = obtemPixel(img, h, w);

            //Y

            int redy = (int) ((obtemPixel(copia, h-1, w-1).cor[RED] * 1)   +
                              (obtemPixel(copia, h-1, w).cor[RED] * 2)     +
                              (obtemPixel(copia, h-1, w+1).cor[RED] * 1)   +
                              (obtemPixel(copia, h+1, w-1).cor[RED]* (-1)) +
                              (obtemPixel(copia, h+1, w).cor[RED]* (-2))   +
                              (obtemPixel(copia, h+1, w+1).cor[RED]* (-1)) );

            int greeny = (int) ((obtemPixel(copia, h-1, w-1).cor[GREEN] * 1)   +
                                (obtemPixel(copia, h-1, w).cor[GREEN] * 2)     +
                                (obtemPixel(copia, h-1, w+1).cor[GREEN] * 1)   +
                                (obtemPixel(copia, h+1, w-1).cor[GREEN]* (-1)) +
                                (obtemPixel(copia, h+1, w).cor[GREEN]* (-2))   +
                                (obtemPixel(copia, h+1, w+1).cor[GREEN]* (-1)) );

            int bluey = (int) ((obtemPixel(copia, h-1, w-1).cor[BLUE] * 1)   +
                               (obtemPixel(copia, h-1, w).cor[BLUE] * 2)     +
                               (obtemPixel(copia, h-1, w+1).cor[BLUE] * 1)   +
                               (obtemPixel(copia, h+1, w-1).cor[BLUE]* (-1)) +
                               (obtemPixel(copia, h+1, w).cor[BLUE]* (-2))   +
                               (obtemPixel(copia, h+1, w+1).cor[BLUE]* (-1)) );

            //X

            int redx = (int) ((obtemPixel(copia, h-1, w-1).cor[RED] * 1)   +
                              (obtemPixel(copia, h, w-1).cor[RED] * 2)     +
                              (obtemPixel(copia, h+1, w-1).cor[RED] * 1)   +
                              (obtemPixel(copia, h-1, w+1).cor[RED]* (-1)) +
                              (obtemPixel(copia, h, w+1).cor[RED]* (-2))   +
                              (obtemPixel(copia, h+1, w+1).cor[RED]* (-1)) );

            int greenx = (int) ((obtemPixel(copia, h-1, w-1).cor[GREEN] * 1)   +
                                (obtemPixel(copia, h, w-1).cor[GREEN] * 2)     +
                                (obtemPixel(copia, h+1, w-1).cor[GREEN] * 1)   +
                                (obtemPixel(copia, h-1, w+1).cor[GREEN]* (-1)) +
                                (obtemPixel(copia, h, w+1).cor[GREEN]* (-2))   +
                                (obtemPixel(copia, h+1, w+1).cor[GREEN]* (-1)) );

            int bluex = (int) ((obtemPixel(copia, h-1, w-1).cor[BLUE] * 1)   +
                               (obtemPixel(copia, h, w-1).cor[BLUE] * 2)     +
                               (obtemPixel(copia, h+1, w-1).cor[BLUE] * 1)   +
                               (obtemPixel(copia, h-1, w+1).cor[BLUE]* (-1)) +
                               (obtemPixel(copia, h, w+1).cor[BLUE]* (-2))   +
                               (obtemPixel(copia, h+1, w+1).cor[BLUE]* (-1)) );

            int redz = (redy>=redx ? redy : redx);
            int greenz = (greeny >= greenx ? greeny : greenx);
            int bluez = (bluey>=bluex ? bluey : bluex);

            pixel.cor[RED]   = (redz <= 255 ? (redz <= 0 ? 0 : redz) : 255 );
            pixel.cor[GREEN] = (greenz <= 255 ? (greenz <= 0 ? 0 : greenz) : 255 );
            pixel.cor[BLUE]  = (bluez <= 255 ? (bluez <= 0 ? 0 : bluez) : 255 );

            recolorePixel(img, h, w, pixel);
        }
    }
    
    liberaImagem(copia);

}

void deteccaoBordasLaplace(Imagem *img) {
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'deteccaoBordasLaplace'); //Retire esssa mensagem ao implementar a fução
    /* Siga as mesmas dicas do filtro de Sobel */


    Imagem *copia = copiaImagem(img);

    for (int h = 1; h < obtemAltura(img)-1; h++) {
        for (int w = 1; w < obtemLargura(img)-1; w++) {
            Pixel pixel = obtemPixel(img, h, w);

            //Y

            int redy = (int) ((obtemPixel(copia, h-1, w).cor[RED] * (-1))+
                              (obtemPixel(copia, h, w-1).cor[RED] * (-1))+
                              (obtemPixel(copia, h, w).cor[RED] * 4)     +
                              (obtemPixel(copia, h, w+1).cor[RED]* (-1)) +
                              (obtemPixel(copia, h+1, w).cor[RED]* (-1)) );

            int greeny = (int) ((obtemPixel(copia, h-1, w).cor[GREEN] * (-1))+
                              (obtemPixel(copia, h, w-1).cor[GREEN] * (-1))+
                              (obtemPixel(copia, h, w).cor[GREEN] * 4)     +
                              (obtemPixel(copia, h, w+1).cor[GREEN]* (-1)) +
                              (obtemPixel(copia, h+1, w).cor[GREEN]* (-1)) );

            int bluey = (int) ((obtemPixel(copia, h-1, w).cor[BLUE] * (-1))+
                              (obtemPixel(copia, h, w-1).cor[BLUE] * (-1))+
                              (obtemPixel(copia, h, w).cor[BLUE] * 4)     +
                              (obtemPixel(copia, h, w+1).cor[BLUE]* (-1)) +
                              (obtemPixel(copia, h+1, w).cor[BLUE]* (-1)) );

            pixel.cor[RED]   = (redy <= 255 ? (redy <= 0 ? 0 : redy) : 255 );
            pixel.cor[GREEN] = (greeny <= 255 ? (greeny <= 0 ? 0 : greeny) : 255 );
            pixel.cor[BLUE]  = (bluey <= 255 ? (bluey <= 0 ? 0 : bluey) : 255 );

            recolorePixel(img, h, w, pixel);
        }
    }

	liberaImagem(copia);
}

void meuFiltro(Imagem *img){
    //AVISO(Filtros.c: Ainda nao implementei a funcao 'meuFiltro'); //Retire esssa mensagem ao implementar a fução
    /*
    int v,e,a;
    printf("Digite o fator de vermelho a ser adicionado: ");
    scanf("%d", &v);
    printf("Digite o fator de verde a ser adicionado: ");
    scanf("%d", &e);
    printf("Digite o fator de azul a ser adicionado: ");
    scanf("%d", &a);

    for (int h = 0; h < obtemAltura(img); h++) {
        for (int w = 0; w < obtemLargura(img); w++) {
            Pixel pixel = obtemPixel(img, h, w);
            pixel.cor[RED]   = ( (int)pixel.cor[RED]   + v );
            pixel.cor[GREEN] = ( (int)pixel.cor[GREEN] + v );
            pixel.cor[BLUE]  = ( (int)pixel.cor[BLUE]  + v );

            pixel.cor[RED] = ()

            recolorePixel(img, h, w, pixel);
        }
    }


    */


}
