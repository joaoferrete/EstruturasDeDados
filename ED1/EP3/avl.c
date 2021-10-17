//João Paulo Souza Ferrete e Ramon Pezzin Ton
#include "avl.h"


AVL * encontraMenor(AVL * ptr){
    //Função que retorna um ponteiro para o menor elemento de uma árvore
    if(!ptr) return NULL;   //Caso a arvore seja vazia, retorna NULL
    if(ptr && !ptr->left) return ptr;   //Caso não exista elemento a esquerda, ou seja, não exista elemento menor, retorna-se aquele elemento
    return encontraMenor(ptr->left);//chamada recursiva caso nenhum dos casos anteriores seja satisfeito
}

AVL * criaArvore(char * inf){
    //Função que aloca espaço para uma nova raiz de árvore, inicia seus campos e atribui o elemento passado por parametro
    //como elemento de informação
    AVL * raiz = (AVL *) mallocSafe(sizeof(AVL));
    raiz->balance = 0;
    raiz->left = NULL;
    raiz->right = NULL;
    raiz->info = mallocSafe(strlen(inf)+1);
    strcpy(raiz->info, inf);
    return raiz;
}


AVL * procuraAVL(AVL * ptr, char * inf){
    //Função responsável pela busca de um elemento na árvore, utilizando para comparação a função 'compara' passada por parametro
    if(!ptr) return NULL; //Caso a arvore esteja vazia retorna Nulo
    if(strcmp(ptr->info, inf)==0) return ptr;  //Caso a raiz atual seja o elemento buscado se retorna um ponteiro para ela
    else if(strcmp(ptr->info, inf)<0) return procuraAVL(ptr->right, inf); //Caso o elemento buscado seja maior que o
    //                                                                              elemento atual, se faz a busca pela direita
    return procuraAVL(ptr->left, inf);//Caso contrario, se faz a busca pela direita
}

void sugestoes(AVL* pt, char *palavra, Fila ** f){
    if (!pt) return;
    if(distanciaEdicao(pt->info, palavra)< 6) enqueue(*f, criaObj(pt->info));
    if(strcmp(pt->info, palavra)<0)  sugestoes(pt->right, palavra, f);
    else sugestoes(pt->left, palavra, f);
}

char * getInfo(AVL * pt){
    return pt->info;
}

bool encontraAVL(AVL * ptr, char* inf){
    if(!ptr) return false; //Caso a arvore esteja vazia retorna Nulo
    if(strcmp(ptr->info, inf)==0) return true;  //Caso a raiz atual seja o elemento buscado se retorna um ponteiro para ela
    else if(strcmp(ptr->info, inf)<0) return encontraAVL(ptr->right, inf); //Caso o elemento buscado seja maior que o
    //                                                                              elemento atual, se faz a busca pela direita
    return encontraAVL(ptr->left, inf);
}

void apagaAVL(AVL * ptr){ 
    //Função que libera todo o espaço utilizado por uma arvore
    if(!ptr) return;
    apagaAVL(ptr->left);  //Liberando a subarvore esquerda
    apagaAVL(ptr->right); //Liberando a subarvore direita
    free(ptr->info);    //Liberando elemento de informação
    free(ptr);  //liberando raiz da arvore
}

int alturaAVL (AVL * ptr){
    //Função que retorna a altura de uma árvore
    int r, l;
    if(!ptr) return 0;  //Caso a árvore seja nula a altura é 0
    r=1+alturaAVL(ptr->right);  //Caso a árvore nao seja nula, a altura dela pela direita é 1+altura da sub-arvore direita
    l=1+alturaAVL(ptr->left);   //Mesmo caso anterior
    if(r>l) return r;   //A altura da árvore é o maior dos dos valores
    return l;
}

void balanceiaAVL(AVL * avl){
    //Função que calcula o balanço de uma árvore a partir do calculo da altura
    if(!avl) return;
    int a = alturaAVL(avl->left)- alturaAVL(avl->right); //O balanço é calculado a partir da altura 
    //                                                      da sub-arvore direita - esquerda
    avl->balance=a; 
}

void imprimeArvore(AVL * ptr){
    //Função responsável por imprimir uma árvore que recebe como parâmetro um ponteiro para árvore e uma função
    //para impressão de elemento genérico de informação
    if(!ptr){
        return;
    }
    int i, nivel = alturaAVL(ptr); //Nivel passa a ser a altura da árvore

    if(ptr){
        imprimeArvore(ptr->left);
        for(i=0; i<nivel; i++) printf("\t");
        printf("%s\n", ptr->info);
        imprimeArvore(ptr->right);
    }
}

AVL * SimplesDireita(AVL * avl){
    //Função que faz a rotação simples a esquerda
    AVL * a = avl->left;    //É criado uma variável auxiliar que recebe a raiz da sub-arvore esquerda
    avl->left=a->right;    //O filho esquerdo da raiz desbalanceada aponta para o filho direito da variável auxiliar
    a->right=avl;   //O filho direito da variável auxiliar passa a apontar para a raiz 'desbalanceada'
    balanceiaAVL(avl);    //É feito um novo balanceamento
    balanceiaAVL(a);
    return a;   //A nova raiz da árvore passa a ser a raiz apontada pela variavel auxiliar
}

AVL * DuplaDireita(AVL * avl){
    //Função responsável ṕela rotação dupla à direita
    AVL * a=avl->left, * b = avl->left->right;  //A variável auxiliar 'a' recebe o filho esquerdo da raiz desbalanceada
    //                                          e a variável auxiliar 'b' recene o filho direito da raiz apontada pela variavel 'a'
    avl->left=b->right; //O filho esquerdo do nó desbalanceado passa a ser o filho direiro da raiz 'b'
    a->right=b->left;   //O filho direito da raiz 'a' passa a ser o filho esquerdo da raiz 'b'
    b->left = a;        //O filho esquerdo da raiz 'b' passa a ser a raiz a
    b->right = avl;     //O filho direito da raiz 'b' passa a ser o nó que estava desbalanceado
    balanceiaAVL(avl);    //É feito o rebalanceamento dos nós após os reapontamentos
    balanceiaAVL(a);
    balanceiaAVL(b);
    return b;   //É retornada a raiz b como raiz da arvore 
}

AVL * SimplesEsquerda(AVL * avl){
    //Função que executa a rotação simples a esquerda
    AVL *a = avl->right;    //A variável auxiliar 'a' recebe o filho a direita da raiz desbalanceada
    avl->right=a->left; //O filho a direita da raiz desbalanceada passa a ser o filho a esquerda da raiz a
    a->left = avl;  //O filho a esquerda da raiz 'a' passa a ser a raiz 'desbalanceada'
    balanceiaAVL(avl);    //É feito um novo balanceamento para as sub-arvores
    balanceiaAVL(a);
    return a;   //A sub-arvore apontada por 'a' é devolvida como raiz, substituindo a subarvore apontada por 'avl'
}

AVL * DuplaEsquerda(AVL * avl){
    //Função que faz a rotação dupla a esquerda, de forma similar a rotação dupla a direita
    AVL * a = avl->right, * b=avl->right->left; //A variavel auxiliar 'a' recebe o filho a direita do nó desbalanceado,
    //                                            Enquanto a variável 'b' recebe o filho a esquerda da variável 'a'
    a->left = b->right; //O filho a esquerda da árvore 'a' passa a ser o filho a direita de 'b'
    avl->right = b->left;   //O filho a direita da raiz desbalanceada passa a ser o filho da esquerda da raiz 'b'
    b->left=avl;    //O filho a esquerda, entao, da raiz 'b' passa a ser a raiz desbalanceada
    b->right=a; //E o filho da direita de b passa a ser a raiz 'a'
    balanceiaAVL(avl);    //É feito o balanceamento das subarvores
    balanceiaAVL(a);
    balanceiaAVL(b);
    return b;   //A subarvore b é retornada como raiz da subarvore anteriormente desbalanceada
}

AVL * inserirAVL(AVL * ptr, char * inf){
    //Função responsável pela inserção de um novo elemento de informação na árvore, e recebe como parâmetro um ponteiro para
    //arvore, um ponteiro para o elemento de informação e uma função de comparação
    if(!ptr) return criaArvore(inf);    //Caso a árvore, ou sub-árvore, não exista, é criado uma raiz com o elemento de informação

    if(strcmp(ptr->info, inf)<0){
        //Caso o elemento a ser inserido seja maior que o elemento da raiz atual
        ptr->right=inserirAVL(ptr->right, inf);    //É feita a chamada recursiva para a inserção do elemento da subarvore direita
        balanceiaAVL(ptr->right); //Depois da inserção é feito o rebalanceamento das asvores                             
        balanceiaAVL(ptr);
        if(ptr->right->balance < 0 && ptr->balance < -1) ptr = SimplesEsquerda(ptr); //Verificação de desbalanceamentos
        else if (ptr->right->balance > 0 && ptr->balance < -1) ptr = DuplaEsquerda(ptr);
    }
    else if (strcmp(ptr->info, inf)>0){
        //Caso o elemento a ser inserido seja menor que o elemento da raiz atual
        ptr->left=inserirAVL(ptr->left, inf);  //Chamada recursiva para inserção na subarvore esquerda
        balanceiaAVL(ptr->left);  //rebalanceamento
        balanceiaAVL(ptr);
        if(ptr->left->balance > 0 && ptr->balance > 1) ptr = SimplesDireita(ptr);  //Caso a sub-árvore esquerda seja pesada para a esquerda e a raiz atual esteja desbalanceada para a esquerda
        else if (ptr->left->balance < 0 && ptr->balance > 1) ptr = DuplaDireita(ptr); //Caso a sub-árvore esquerda esteja pesada para a direita e a raiz atual esteja desbalanceada para a esquerda
    }
    //Caso o elemento a ser inserido seja igual a um elemento já inserido, só é retornado o ponteiro para esse elemento,
    //sem a inserção.
    return ptr;
}

AVL * removeAVL(AVL * ptr, char * inf){ 
    //Função responsável pela remoção de elementos na árvore
    if(!ptr) return ptr; //Caso a arvore seja vazia, retorna-se ela mesma

    if(!procuraAVL(ptr, inf)) return ptr;   //Caso o elemento a ser deletado nao seja encontrado, nada é feito

    if(strcmp(ptr->info, inf)==0){
        //Se o elemento a ser removido é o elemento atual
        if(!ptr->right){
            //Caso esse elemento não tenha filho a direita
            AVL * aux=ptr->left;    //Uma variavel auxiliar recebe o seu filho a esquerda
            free(ptr->info);    //É liberado o elemento de informação e o espaço alocado da raiz
            free(ptr);
            balanceiaAVL(aux);    //É feito o rebalanceamento do filho a esquerda
            return aux;  //O filho a esquerda é retornado como raiz da subarvore

        }else if(!ptr->left){
            //Caso esse elemento não possua filho a esquerda 
            AVL * aux = ptr->right; //A variável auxiliar recebe o filho a direita da raiz para não se perder a subarvore
            free (ptr->info);   //É liberado todo o espaço alocado para aquela raiz
            free(ptr);
            balanceiaAVL(aux);    //É feito o rebalanceamento
            return aux;     //É retornado a variavel auxiliar como raiz da subarvore

        }else{
            //Caso o elemento possua os dois filhos
            AVL * aux = encontraMenor(ptr->right); //A variável auxiliar recebe o melhor elemento da subarvore esquerda
            strcpy(ptr->info, aux->info);  //É feita a troca dos elementos de informação entre a variável auxiliar e a raiz
            ptr->right = removeAVL(ptr->right, inf);    //É chamada a função de apagar para a subarvore direita
            //                                                  que cairá em um dos casos anteriores, já que o elemento será uma folha
            
            balanceiaAVL(ptr->left); //È feito novamente o balanço
            balanceiaAVL(ptr);
            if(ptr->left && ptr->left->balance >= 0 && ptr->balance > 1) ptr = SimplesDireita(ptr); //Caso a árvore esteja 
            //                                              desbalanceada para a esquerda, é feita a rotação simples direita;
            else if (ptr->left && ptr->left->balance < 0 && ptr->balance > 1) ptr = DuplaDireita(ptr); //Caso a árvore esteja 
            //desbalanceada para a esquerda e a sua sub-arvore esquerda esteja pesada para a direita, é feita a rotação dupla direita
        
        }

    }else if(strcmp(ptr->info, inf)>0) {
        //Caso o elemento a ser deletado seja menor que o elemento atual
        ptr->left=removeAVL(ptr->left, inf);    //É feita a chamada recursiva com a subarvore esquerda
        balanceiaAVL(ptr->left);  //Depois da chamada, é feito o rebalanceamento
        balanceiaAVL(ptr);
        if(ptr->right && ptr->right->balance <= 0 && ptr->balance < -1) ptr = SimplesEsquerda(ptr); //É vista a necessidade rotação
        else if (ptr->right && ptr->right->balance > 0 && ptr->balance < -1) ptr = DuplaEsquerda(ptr);
    }

    else if(strcmp(ptr->info, inf)<0) {
        //Caso o elemento a ser deletado seja maior que o elemento atual é feito o processo de maneira similar ao anterior
        ptr->right = removeAVL(ptr->right, inf);
        balanceiaAVL(ptr);
        balanceiaAVL(ptr->left);
        if(ptr->left && ptr->left->balance >= 0 && ptr->balance > 1) ptr=SimplesDireita(ptr);
        else if (ptr->left && ptr->left->balance < 0 && ptr->balance > 1) ptr=DuplaDireita(ptr);
    }
    //É retornado o ponteiro para que seja atribuido ao restante da árvore na chamada recursiva
    return ptr;
}


