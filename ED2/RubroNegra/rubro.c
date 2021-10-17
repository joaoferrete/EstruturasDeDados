/* João Paulo Souza Ferrete e Ramon Pezzin Ton */

//Inclusão de bibliotecas e do arquivo rubro.h
#include <stdio.h>
#include <stdlib.h>
#include "rubro.h"


rubro * criarRubro(){
    /* Função que cria um novo nó de árvore rubro negra e o retorna */

    rubro* pt = (rubro *) malloc(sizeof(rubro));    //Alocação do novo nó
    if(!pt) return NULL;    //Caso o nó não seja alocado, interrompe-se a execução da função

    pt->dir = pt->esq = pt->pai = externo;  //Faz com que todos os ponteiros, inicialmente, apontem para o nó externo
    pt->Cor = vermelho;     //Um novo nó inserido é sempre vermelho, para não violar regras da Rubro-negra
    
    return pt;   //Retorno do novo elemento alocado
}

void apagaArvore(rubro * pt){
    /* Função que libera todo o espaço alocado por uma árvore */

    if(!pt || pt == externo) return;    //Caso o ponteiro seja NULL ou seja o nó externo, então não precisa fazer nada
    
    apagaArvore(pt->dir);   //Chamada recursiva para liberar a subarvore direita
    apagaArvore(pt->esq);   //Chamada recursiva para liberar a subarvore esquerda

    free(pt->obj);  //Liberação do elemento de informação
    free(pt);   //Liberação do nó da árvore
}

rubro * encontraMaiorRubro(rubro* pt){
    /* Função que encontra e retorna um ponteiro para o maior elemento de uma árvore */

    if(pt == externo) return externo;   //Caso o ponteiro aponte para externo, então se retorna o próprio externo
    if(pt->dir == externo) return pt;   //Caso o filho direito do ponteiro aponte para externo, então ele é o maior, retornando ele
    return encontraMaiorRubro(pt->dir); //Se não, se retorna o maior elemento da subárvore direita
}

int alturaRubro (rubro * ptr){
    /*Função que retorna a altura de uma árvore*/

    int r, l;
    if(!ptr || ptr == externo) return 0;  //Caso a árvore seja nula a altura é 0

    r=1+alturaRubro(ptr->dir); //Caso a árvore nao seja nula, a altura dela pela direita é 1+altura da sub-arvore direita
    l=1+alturaRubro(ptr->esq);   //Mesmo caso anterior
    if(r>l) return r;   //A altura da árvore é o maior dos dos valores
    return l;
}

void* getObj(rubro * pt){
    /* Função que retorna um ponteiro para o elemento de informação de tipo genérico da árvore */

    if(!pt || pt == externo) return externo;    //Caso o ponteiro seja o nó externo, então é retornado o nó externo
    return pt->obj; //Caso contrário, é retornado o ponteiro para o elemento de informação do nó
}

cor getCor(rubro* pt){
    /* Função que retorna a cor de um nó da árvore */
    return pt->Cor;
}

rubro* buscaRubro(rubro * pt, void* obj, int (*compara)(void*, void*)){
    /* Função que busca um elemento dentro da árvore rubro negra e retorna um ponteiro
    para o mesmo. Recebe por parâmetro um ponteiro para a raiz da árvore, um elemento de
    informação de tipo genérico e uma função para a comparação dos elementos */

    if (!pt || !obj || pt == externo) return NULL;  //Caso algum dos ponteiros seja nulo ou a arvore seja o externo, se retorna NULL
    
    if (compara(obj, pt->obj) == 0) return pt;  //Caso o elemento do nó da árvore seja igual ao buscado, então ele é retornado
    if(compara(obj, pt->obj)<0) return buscaRubro(pt->dir, obj, compara);   //Caso o elemento da árvore seja menor ao buscado, entao a busca deve ser feita pela subarvore direita
    return buscaRubro(pt->esq, obj, compara);   //Caso contrário, o elemento da árvore é maior ao buscado, fazendo a busca agora pela subárvore esquerda 
}

void rotacaoEsquerda(rubro ** pt, rubro *w){
    /* Função que faz a rotação a esquerda da árvore rubro-negra, recebendo por parâmetro
    um ponteiro para o ponteiro da raiz da árvore e um ponteiro para o nó que se deseja rotacionar */

    if(!*pt || !w || *pt == externo || w == externo) return;    //Caso os nós sejam o nó externo ou sejam NULL, entao a função é interrompida
    
    rubro *v;
    
    v = w->dir; //v recebe o filho direito de w
    w->dir = v->esq;    //O filho a direita de w passa a ser o filho a esquerda de v
    
    if(v->esq!=externo) v->esq->pai = w;    //Caso o filho a esquerda de v nao seja o nó externo, w passa a ser o pai do antigo filho esquerdo de v
    if(v!=externo) v->pai = w->pai;     //Se v nao for o nó externo, o pai dele passa a ser o msm pai de w
    if(w->pai == externo) *pt = v;      //Se o pai de w for o externo, então ele é a raiz da arvore, entao o ponteiro da raiz passa a apontar para v
    else{   //Caso w não seja a raiz da árvore
        if(w == w->pai->esq) w->pai->esq = v;   //Se w for o filho esquerdo , entao o filho esquerdo do pai passa a apontar para v
        else w->pai->dir = v;   //Caso w seja filho direito, entao o pai passa a apontar para v
    }
    v->esq = w; //W passa a ser o filho esquerdo de v
    w->pai = v; //v passa a ser o pai de w
} 

void rotacaoDireita(rubro ** pt, rubro *w){
    /* Função que efetua a rotação à direita, em relação ao nó apontado por w. 
    Acontece de forma similar a rotação à esquerda, com a troca de ponteiros */
    if(!*pt || !w || *pt == externo || w == externo) return;
    
    rubro *v;
    
    v = w->esq;
    w->esq = v->dir;
    if(v->dir!=externo) v->dir->pai = w;
    if(v!=externo) v->pai = w->pai;
    if(w->pai == externo) *pt = v;
    else{
        if(w == w->pai->dir) w->pai->dir = v;
        else w->pai->esq = v;
    }
    v->dir = w;
    w->pai = v;
} 

void rubroIFixUp(rubro **pt, rubro* q){
    /* Função que faz a verificação e correção de características da rubro-negra após a inserção
    de um novo nó. Ela recebe por parâmetro o ponteiro para a raiz da árvore e o nó inserido*/

    if(!*pt || !q || *pt == externo || q == externo) return;

    rubro *pai, *avo, *t;
    while(q->pai->Cor == vermelho){ /*Enquanto o pai do nó inserido for vermelho, ou seja, 
                                    como cada nó inserido é vermelho, há violação de regras*/
        pai = q->pai;
        avo = q->pai->pai;
        if(pai == avo->esq){    //Caso o pai do nó inserido seja filho a esquerda
            t = avo->dir;
            if(t->Cor == vermelho){     //Caso o irmão do pai do nó inserido também seja vermelho
                pai->Cor = t->Cor = preto;  //Então eles passam a ser vermelho
                avo->Cor = vermelho;    //O avô passa a ser vermelho
                q = avo;    //A verificação, agora, passa a ser pelo avô
            }
            else{ //Caso o tio do nó inserido não seja vermelho
                if(q == pai->dir){  //Se o nó foi inserido à direita do pai
                    q = pai;    //O nó principal passa a ser o pai
                    rotacaoEsquerda(pt, q); //É feita uma rotação à esquerda a partir do pai do nó inserido
                }
                q->pai->Cor = preto;    //O pai do nó inserido passa a ser preto
                avo->Cor = vermelho;    //O avo passa a ser vermelho
                rotacaoDireita(pt, avo);    //Rotação a direita com foco no avo do nó inserido
            }
        }else{  //Caso o pai do nó inserido seja filho à direita
        /* Acontece de forma simétrica à anterior */

            t = avo->esq;
            if(t->Cor == vermelho){
                pai->Cor = t->Cor = preto;
                avo->Cor = vermelho;
                q = avo;
            }
            else{
                if(q == pai->esq){
                    q = pai;
                    rotacaoDireita(pt, q);
                }
                q->pai->Cor = preto;
                avo->Cor = vermelho;
                rotacaoEsquerda(pt, avo);
            }
        }
    }
    (*pt)->Cor = preto; //Garantindo que o nó continua preto
}

void insereRubro(rubro** pt, void* elem, int (*compara)(void*, void*)){
    /* Função que insere um elemento de informação na árvore. Recebe por parâmetro
    um ponteiro para o ponteiro da raiz da árvore, um elemento de tipo generico
    de informação e uma função de comparação de elementos */

    if(!elem) return;

    rubro *x, *v, *q;

    q = criarRubro();   //Criar um novo nó
    
    q->obj = elem;      //O campo de objeto do novo nó passa a ser o elemento passado por parâmetro
    v = externo;    
    x = *pt;

    while(x != externo){
        /*Laço para encontrar o nó onde deve ser inserido o novo nó*/
        if(compara(elem, x->obj) == 0) return;
        v = x;
        if(compara(elem, x->obj) < 0) x = x->dir;
        else x = x->esq;
    }
    /* Inserção do novo nó na árvore */
    q->pai = v; 
    if(v == externo) *pt = q;
    else{
        if(compara(elem, v->obj) < 0) v->dir = q;
        else v->esq = q;
    }
    rubroIFixUp(pt, q); //Chamada da função de correção da árvore 
}

void transferePaiRubro(rubro ** pt, rubro* u, rubro*v){
    /* Função que recebe por parâmetro a raiz da árvore e dois ponteiros para nós,
    e efetua a troca dos pais do ponteiro u para o ponteiro v */

    if(!pt || *pt == externo ) return;

    if(u->pai == externo) *pt = v;
    else {
        if(u == u->pai->esq) u->pai->esq = v;
        else u->pai->dir = v;
    }
    v->pai = u->pai;
}

void rubroRFixUp(rubro **pt, rubro* x){
    /* Função que corrige os problemas após a remoção de um elemento na árvore rubro-negra.
    Recebe por parâmetro um ponteiro para a raiz e o filho do elemento removido */

    if(!pt || *pt == externo) return;

    rubro *w;

    while(x!=*pt && x->Cor == preto){ 
        /* Caso x não seja a raiz da árvore e a cor de x seja preto, ou seja, há violação */

        if(x == x->pai->esq){   //Caso x seja filho a esquerda do seu pai
            w = x->pai->dir;    //w passa a ser o irmão de x
            if(w->Cor == vermelho){ //Caso a cor do irmão de X seja vermelho
                w->Cor = preto; //A cor de w passa a ser preto
                x->pai->Cor = vermelho; //A cor do pai de w a x passa a ser vermelho, corrigindo o erro de coloração
                rotacaoEsquerda(pt, x->pai);    //É feita uma rotação a esquerda, a partir do pai de X
                w = x->pai->dir;    //W passa a ser o novo filho a direita do pai de X
            }
            if(w->esq->Cor == preto && w->dir->Cor == preto){   //Caso os dois filhos de w sejam pretos
                w->Cor = vermelho;  //W passa a ser vermelho
                x = x->pai; //O novo nó a ser verificado é o pai de x
            }
            else{   //Caso os dois filhos de w não sejam pretos

                if (w->dir->Cor == preto){  //Caso o filho a direita de w seja preto
                    w->esq->Cor = preto;
                    w->Cor = vermelho;
                    rotacaoDireita(pt, w);
                    w = x->pai->dir;
                }
                w->Cor = x->pai->Cor;
                x->pai->Cor = preto;
                w->dir->Cor = preto;
                rotacaoEsquerda(pt, x->pai);
                x = *pt;
            }
        }
        else{   //Caso X seja filho a direita do seu pai.
        /* Acontece de maneira simétrica à anterior */
            w = x->pai->esq;
            if(w->Cor == vermelho){
                w->Cor = preto;
                x->pai->Cor = vermelho;
                rotacaoDireita(pt, x->pai);
                w = x->pai->esq;
            }
            if(w->dir->Cor == preto && w->esq->Cor == preto){
                w->Cor = vermelho;
                x = x->pai;
            }
            else{ 
                if (w->esq->Cor == preto){
                    w->dir->Cor = preto;
                    w->Cor = vermelho;
                    rotacaoEsquerda(pt, w);
                    w = x->pai->esq;
                }
                w->Cor = x->pai->Cor;
                x->pai->Cor = preto;
                w->esq->Cor = preto;
                rotacaoDireita(pt, x->pai);
                x = *pt;
            }
        }
        
    }
    x->Cor = preto; //Garantindo q a raiz continua preta
    


}

void removeRubro(rubro **pt, rubro *z){
    /* Função que efetua a remoção de um elemento em uma árvore rubro-negra.
    Recebe por parâmetro um ponteiro para a raiz da árvore e um ponteiro para
    o elemento que será removido */

    rubro *x, *y;
    cor yColor;

    y = z;
    yColor = y->Cor;
    if(z->esq == externo){  //Caso o elemento a ser removido não possua filho a esquerda
        x = z->dir; //x passa a ser o filho a direita do nó a ser removido
        transferePaiRubro(pt, z, z->dir);   //É feita a transferencia de pai do elemento a ser removido para seu filho esquerdo
        free(z->obj);   //É liberado o espaço utilizado pelo elemento a ser apagado    
        free(z);
    }
    else if (z->dir == externo){    //Caso z não possua filho à direita
    /* Acontece de forma simular à anterior */
        x = z->esq;
        transferePaiRubro(pt, z, z->esq);
        free(z->obj);
        free(z);
    }
    else{   //Caso z possua os dois filhos

        y = encontraMaiorRubro(z->esq); //y recebe o sucessor de z, neste caso, o maior elemento da sub-arvore esquerda
        yColor=y->Cor;  //yColor recebe a cor de y
        x = y->esq;     //X passa a ser o filho a esquerda de y, já que ele não possui filho a direita, pois é o maior

        if(y->pai == z) x->pai = y; //Caso o sucessor de z seja filho direto de z, então x passa a ser filho de y
        else{   //Caso o sucessor de z não seja filho de z
            transferePaiRubro(pt, y, x);    //X passa a ocupar o lugar de y
            y->esq = z->esq;    //O filho a esquerda de y passa a ser os filhos a esquerda de Z
            y->esq->pai = y;    
        }
        transferePaiRubro(pt, z, y);    //Y passa a substituir z;
        y->dir = z->dir;    //O filho a direita de y passa a ser o filho a direita de z
        y->dir->pai = y;
        y->Cor = z->Cor;    //Y passa a ter a cor de Z
        free(z->obj);    //É liberado o espaço utilizado por z
        free(z);
    }
    
    if(yColor == preto) rubroRFixUp(pt, x); /*Caso o nó alterado de lugar/apagado seja de cor preta, então houve violação
                                            Sendo necessário a chamada da função de correção */
    (*pt)->Cor = preto;     //Garantindo q a raiz continua preto
    externo->pai=externo->dir=externo->esq=externo; //Garantindo os ponteiros de externo para ele mesmo
}
