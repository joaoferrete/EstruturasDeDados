/* João Paulo Souza Ferrete e Ramon Pezzin Ton */
/* Trabalho de Estrutura de Dados II - Ciência da Computação */

#include "huffman.h" //Inclusão do arquivo que inclui as bibliotecas e as estruturas necessárias



void * mallocSafe(size_t tam){
    /* Função que aloca um espaço de memória e retorna um ponteiro
    para ela caso o espaço tenha sido alocado com sucesso */

    void * a = malloc(tam);
    if(!a){
        printf("ERRO: SEM MEMORIA!\n");
        exit(1);
    }
    return a;
}

void imprimeVetor(No * vet, long long tam){
    /* Função responsável por imprimir um vetor, incluindo o caractere representado,
    e a quantidade de vezes que ele aparece no texto */

    for(long long i=0; i<tam; i++){
        if (vet[i].caractere == '\n') printf(" [\\n : %lld] ", vet[i].freq);
        else printf(" [%c : %lld] ", vet[i].caractere, vet[i].freq);
    }
    printf("\n");
}

void imprimeVetorCod(No * vet, long long tam){
    /* Função que imprime um vetor, imprimindo, também o código binário
    que corresponde àquele caractere */

    for(long long i=0; i<tam; i++){
        if(vet[i].caractere == '\n') printf(" [%lld : \\n : ", vet[i].freq);
        else printf(" [%lld : %c : ",vet[i].freq, vet[i].caractere);
        for(int j=0; j<vet[i].tamCod; j++){ //Laço para impressão do código do caractere a partir do algoritmo de Huffman
            printf("%d", vet[i].codigo[j]);
        }
        printf("] ");
    }
    printf("\n");
}

long long pai(long long i){
    /* Retorna o pai de um elemento num heap */
    return (long long)i/2;
}
long long esquerdo(long long i){
    /* Retorna o filho esquerdo de um elemento em um heap */
    return 2*i+1;
}
long long direito(long long i){
    /* Retorna o filho direito de um elemento em um heap */
    return 2*i+2;
}

void minHeapify (No* vet, long long i, long long tam){
    /* Função que gera as propriedades de heap minimo em um array a partir da posição i*/

    long long l, r, menor;
    No aux;
    menor=i;
    l=esquerdo(i);
    r=direito(i);
    if((l<tam) && (vet[l].freq<vet[menor].freq))menor=l;
    if((r<tam) && (vet[r].freq<vet[menor].freq)) menor=r;
    if(menor!=i){
        aux=vet[i];
        vet[i]=vet[menor];
        vet[menor]=aux;
        minHeapify(vet, menor, tam);
    }
}

void construirheapmin(No* vet, long long tam){
    /* Função que cria um heap minimo a partir de um array passado por parâmetro */

    long long i;
    for (i= (long long)(tam/2)-1; i>=0;i--){
        minHeapify(vet, i, tam);
    }
}

No * insereFrequencia(char * nomeArquivo, long long *tam){
    /* Função que lê o arquivo e guarda as frequencias de aparição de um caractere em um array */

    FILE * arquivo = fopen(nomeArquivo, "r");   //Abrindo o arquivo

    char carac;
    long long i=0, j=0, n=4, verif;

    if(!arquivo){
        /* Caso não seja possível abrir o arquivo, o programa é encerrado */
        printf("Não foi possível abrir o arquivo!\n");
        exit(1);
    }

    No * vet = (No *) mallocSafe(sizeof(No)*n); //Alocação do vetor que irá armazenar os elementos

    while(1){
        carac = (char)fgetc(arquivo); //Leitura do caractere no arquivo;
        if(carac == EOF) break; //Verificação de fim do arquivo
        
        if(i==0){ //Verificação para o primeiro caractere lido
            vet[0].freq=1;
            vet[0].caractere = carac;
            vet[0].tree = NULL;
            i++;
        }
        else{
            for(j=0; j<i; j++){ //Laço para verificar se o caractere já foi inserido
                if(vet[j].caractere == carac) {
                    vet[j].freq++;  //Atualização do numero de ocorrências
                    verif=1;
                }
            }
            if(!verif){ //Caso o elemento não tenha sido inserido ainda
                if(n==i){
                    vet = (No *) realloc(vet, sizeof(No)*(n+1));    //Realocação do vetor, caso necessário
                    n++;
                }
                vet[i].caractere = carac; 
                vet[i].freq=1;
                vet[i].tree = NULL;
                i++;
            }
        }
        verif = 0;
        
    }
    *tam = n;   //Variável de tamanho, na função que chamou, recebe o tamanho do vetor
    fclose(arquivo);    //Fechar arquivo
    construirheapmin(vet, n);   //Criar heap minimo do vetor com as frequencias
    return vet;
    
}

Arvore * criaArvore(char carac, long long freq){
    /* Função que recebe um caractere e a frequencia dele, e adiciona-os
    em um nó de árvore para utilização no código de Huffman */

    Arvore * t = (Arvore *) mallocSafe(sizeof(Arvore));
    if(!t) return NULL;
    t->caractere = carac;
    t->freq = freq;
    t->dir = t->esq = NULL;
    return t;
}

No * copiaVet(No * vet, long long tam){
    /* Função que faz uma cópia dos elementos de frequencia e o caractere
    de um vetor passado por parâmetro */

    No * vetor = (No*)mallocSafe(tam*sizeof(No));
    for(int i=0; i<tam; i++){
        vetor[i].caractere = vet[i].caractere;
        vetor[i].freq = vet[i].freq;
        vetor[i].tree = vet[i].tree;
    }
    return vetor;
}

Arvore * algoritmoHuffman(No *vetor, long long tam){
    /* Função que monta a árvore do algoritmo de Huffman */

    long long i, n=tam;
    Arvore *x, *y, *z;

    No* vet = copiaVet(vetor, tam); //Cria uma cópia do vetor de elementos, que será desfeito para a criação da árvore

        for(i=0; i<n-1; i++){   //Para cada elemento do vetor
            z = criaArvore(' ', 0);     //Criando nó interno da árvore, que não possui caractere
            
            if(!vet[0].tree) x = criaArvore(vet[0].caractere, vet[0].freq); //Caso seja um nó folha
            else x = vet[0].tree;   //Caso seja um nó interno
            z->esq = x;
            
            vet[0] = vet[tam-1];
            tam--;
            vet = (No *) realloc(vet, tam*sizeof(No));  //Diminuição do tamanho do array
            construirheapmin(vet, tam);

            if(!vet[0].tree) y = criaArvore(vet[0].caractere, vet[0].freq);
            else y = vet[0].tree;
            z->dir = y;
            z->freq = x->freq+y->freq;
            
            /* Reinserção do nó atual no array */
            vet[0].caractere = z->caractere;  
            vet[0].freq = z->freq;
            vet[0].tree = z;
            construirheapmin(vet, tam); //O heap é refeito
    }
    free(vet);
    return z;
}

int altura (Arvore * ptr){
    /*Função que retorna a altura de uma árvore*/

    long long r, l;
    if(!ptr ) return 0;  //Caso a árvore seja nula a altura é 0

    r=1+altura(ptr->dir); //Caso a árvore nao seja nula, a altura dela pela direita é 1+altura da sub-arvore direita
    l=1+altura(ptr->esq);   //Mesmo caso anterior
    if(r>l) return r;   //A altura da árvore é o maior dos dos valores
    return l;
}

void invertelista(int* vet, long long tam){
    /* Função que inverte uma lista passada por parâmetro */

    int aux;
    int n=tam-1;
    for(int i=0; i<tam/2; i++){
        aux = vet[i];
        vet[i]= vet[n-i];
        vet[n-i] = aux;
    }
}

void imprimeArvore(Arvore * ptr){
    /*Função responsável por imprimir uma árvore, e recebe como parâmetro um ponteiro para a árvore*/

    if(!ptr) return;  //Caso a árvore esteja vazia se encerra a função
    int i, nivel = altura(ptr); //Nivel passa a ser a altura da árvore

    if(ptr){//Se a árvore não for nula
        imprimeArvore(ptr->esq);    //Chamada recursiva para impressão da subárvore esquerda

        for(i=0; i<nivel; i++) printf("\t");   //Impressão da tabulação de acordo com o nivel
        if (ptr->caractere == '\n') printf("[\\n : %lld]\n", ptr->freq);
        else printf("[%c : %lld]\n", ptr->caractere, ptr->freq);  //Impressão do caractere e da frequencia de aparição
        
        imprimeArvore(ptr->dir);     //Chamada recursiva para impressão da subárvore direita
    }
}

int codigo(char carac, int *tamCod, int * cod, Arvore * pt, int tamMax){
    /* Função que insere o código binário de um em um vetor a partir da árvore gerada no algoritmo de huffman */
    
    if(!pt) return 0;   //Caso o nó seja nulo, se retorna 0, informando que o nó não foi encontrado
    else if (pt->caractere == carac && !pt->dir && !pt->esq) return 1;  //Caso seja um nó folha, e o caractere 
                                                                        //seja igual, se retorna 1 informando que foi encontrado

    int esq=0, dir=0;

    esq = codigo(carac, tamCod, cod, pt->esq, tamMax);  //Chamada recursiva para verificar se o caractere buscado está a esquerda
    dir = codigo(carac, tamCod, cod, pt->dir, tamMax);  //Chamada recursiva para verificar se o caractere está à direita

    if(esq){
        /* Caso o nó esteja à esquerda */

        if(*tamCod>tamMax) {
            /* Caso haja necessidade de realocação do array do código */
            tamMax+=20;
            cod = (int *) realloc((cod), sizeof(int)*(tamMax));
        }
        cod[*tamCod] = 0;   //Como foi para a esquerda, então o código correspondente é 0
        *tamCod+=1;
        return 1;   //Retorna 1 para dizer que encontrou
    }
    else if (dir){
        /* Caso encontre pela direita, acontece de forma simila à esquerda */

        if(*tamCod>tamMax) {
            tamMax+=20;
            cod = (int *) realloc((cod), sizeof(int)*(tamMax));
        }
        cod[*tamCod] = 1;   //Codigo correspondente é 1
        *tamCod+=1;
        return 1;
    }
    else return 0;  
}

No * pegaCod(No* vetor, long long n, Arvore* raiz){
    /* Função que adiciona o código para cada elemento do vetor */

    long long i;
    char carac;

    No * vet = copiaVet(vetor, n);

    for(i=0; i<n; i++){
        carac = vet[i].caractere;

        int *cod = (int *) mallocSafe(sizeof(int)*20);  //Alocação do array que irá conter o código
        int tamCod=0;

        codigo(carac, &tamCod, cod, raiz, 19);   //Chamada da função que irá inserir o código no array
        
        invertelista(cod, tamCod);  //Inverte-se a lista retornada pela função,já que ela é feita de baixo para cima
        vet[i].codigo = cod;    //Atribuição
        vet[i].tamCod = tamCod;
    }
    return vet;
}

long long calculaTamVet(No *vet, long long n){
    /* Função que calcula o tamanho do vetor de elementos 'unsigned char' que deverá
    ser alocado para compreender todo o texto compactado a partir do tamanho do código
    de cada caractere e sua frequencia*/

    long long soma=0;

    for(long long i=0; i<n; i++){
        soma+=(vet[i].freq * vet[i].tamCod);
    }
    if(soma%8==0)return soma/8;
    return (soma/8)+1;
}

long long calculaBit(No *vet, long long n){
    /* Função que calcula a quantidade de bits necessário para compactar todo o texto */

    long long soma=0;

    for(long long i=0; i<n; i++){
        soma+=(vet[i].freq * vet[i].tamCod);
    }
    return soma;
}

unsigned char * vetorSaida(No* vet, long long n, long long *tamBit, char * nomeArq){
    /* Função que cria o vetor de saída e faz as alterações nos bits de cada posição */

    *tamBit = calculaBit(vet, n);
    long long tamVet = calculaTamVet(vet, n);   //Calculo do tamanho que deve ser alocado
    unsigned char *vetSaida = (unsigned char *) mallocSafe(tamVet); //Alocação do vetor de saida
    memset(vetSaida, 0, tamVet);    //Inicialização de todos os campos com 0

    unsigned char aux;
    int pos=0, desl=0, posbyte=0, posbit=0;

    FILE * arq = fopen(nomeArq, "r");   //Abre-se o arquivo, para ver a sequencia em que os bits deverão ser gravados
    while(1){
        char carac = (char)fgetc(arq);
        if(carac == EOF) break; //Indicação de fim do arquivo

        int i=0;
        for(i=0; vet[i].caractere!=carac && i<n ; i++); //Encontrar a posição no vetor que contém o caractere correspondente
        for (int j=0; j<vet[i].tamCod && i<n; j++){       
            /* Para cada posição no vetor que comtém o código binário, é feita a manipulação
            de bits em um vetor de char para guardar os bits */
            posbyte = pos/8;
            posbit = pos%8;
            desl = 7-posbit;

            aux = vet[i].codigo[j];
            aux = aux<<desl;
            vetSaida[posbyte] = vetSaida[posbyte] | aux;
            
            pos++;
        }
        
        
    }
    fclose(arq);
    return vetSaida;
}

void binCode(unsigned char * vet, long long tam, Arvore *raiz, char * nomeArq){
    /* Função que, a partir no vetor com os bits manibulados e da árvore gerada pelo
    algoritmo de huffman, recria o arquivo que foi compactado */

    unsigned char aux;
    int pos=0, desl=0, posbyte=0, posbit=0;

    Arvore * auxT = raiz;
    
    FILE * arq = fopen(nomeArq, "w");   //Abertura do arquivo para a gravação dos elementos

    for(int i=0; i<tam; i++){   //Laço para verificar todos os bits
        //Manipulação dos bits para descobrir qual o bit armazenado

        posbyte = pos/8;
        posbit = pos%8;
        desl = 7-posbit;

        aux = 1;
        aux = aux<<desl;
        aux= vet[posbyte]&aux;
        aux = aux>>desl; 

        pos++;
        
        if(aux==0) auxT = auxT->esq;    //Se o bit armazenado for 0, fazemos a árvore descer para a esquerda
        else if (aux==1) auxT = auxT->dir;  //Se o bit for 1, fazemos a árvore descer pela direita
        if(!auxT->esq && !auxT->dir){
            /* Caso seja um nó folha, imprimimos no arquivo o caractere encontrado
            e fazendo auxT voltar ao inicio da árvore */
            fprintf(arq,"%c", auxT->caractere);
            auxT=raiz;
        }
    }
    fclose(arq);
}

void descomprimir(char * nomeArq){
    /* Função responsável por descombrimir um arquivo de nome passado por parâmetro
    e salvar o resultado em outro arquivo */

    FILE * arq = fopen(nomeArq, "rb");  //Abrindo o arquivo compactado

    if(!arq){
        /* Caso não seja possível abri o arquivo, a função é encerrada */
        printf("Não foi possível abrir o arquivo!\n");
        return;
    }

    long long tamBin, tamVetor;
    long long tamVetSaida;
    No* vetor;
    unsigned char *vetSaida;

    fread(&tamBin, sizeof(long long), 1, arq);  //Leitura da quantidade de bits no arquivo
    fread(&tamVetor, sizeof(long long), 1, arq);    //Leitura do tamanho do vetor com os elementos e as frequencias
    vetor = (No *) mallocSafe(sizeof(No)* tamVetor);    //Alocação do vetor
    fread(vetor, sizeof(No), tamVetor, arq);    //Leitura do vetor no arquivo

    
    fread(&tamVetSaida, sizeof(long long), 1, arq); //Leitura do tamanho do vetor de saída

    vetSaida = (unsigned char *) mallocSafe(tamVetSaida);   //Alocação do vetor
    memset(vetSaida, 0, tamVetSaida);   //Inicialização dos campos do vetor
    fread(vetSaida, sizeof(unsigned char), tamVetSaida, arq);   //Leitura do vetor

    fclose(arq);

    Arvore * raiz = algoritmoHuffman(vetor, tamVetor);  //Criação da árvore a partir das frequencias com o algoritmo de huffman
    vetor = pegaCod(vetor, tamVetor, raiz); //Criação do vetor com os códigos binários

    printf("Deseja imprimir o código de Huffman para o arquivo inserido/ (s/n) ");
    char a;
    getchar();
    scanf("%c", &a);
    if(a=='s' || a=='S'){
        /* Caso o usuário deseje, é impresso todos os códigos gerados a partir do algoritmo,
        antes de recriar o arquivo */
        printf("\nImprimindo a ocorrência dos caracteres\n");
        imprimeVetor(vetor, tamVetor);

        printf("\n\nImprimindo a árvore do código de Huffman\n\n");
        imprimeArvore(raiz);

        printf("\n\nImprimindo os códigos de cada caractere\n");
        imprimeVetorCod(vetor, tamVetor);

        printf("\n");
    }
    

    char nomeSaida[50];
    printf("\nInsira o nome do arquivo de saída: ");
    scanf("%s", nomeSaida); //Solicitação do nome do arquivo de saida

    binCode(vetSaida, tamBin, raiz, nomeSaida); //Chamada da função de decodificação 

    free(vetor);
    free(vetSaida);
    printf("Arquivo descompactado com sucesso!\n");

}

void salvar(long long tamBin, long long tamVetor, No* vetor, unsigned char *vetSaida, char* nomeSaida, long long tamVetSaida){
    /* Função que salva no arquivo os dados necessários para descompactar */
    
    FILE * arq = fopen(nomeSaida, "wb");    //Abertura do arquivo
    if(!arq){
        /* Verificação de abertura do arquivo */
        printf("Não foi possível criar o arquivo!\n");
        exit(1);
    }
    /* Gravação dos elementos no arquivo compactado */
    fwrite(&tamBin, sizeof(long long), 1, arq);
    fwrite(&tamVetor, sizeof(long long), 1, arq);
    fwrite(vetor, sizeof(No), tamVetor, arq);
    fwrite(&tamVetSaida, sizeof(long long), 1, arq);
    fwrite(vetSaida, sizeof(unsigned char), tamVetSaida, arq);

    fclose(arq);
}

void comprimir(){
    /* Função responsável por comprimir um arquivo, e mostrar as opções
    possíveis a partir desta função */

    char nomeArq[50];
    printf("Digite o nome do arquivo que deseja comprimir: ");
    scanf("%s", nomeArq);   //Leitura do arquivo a ser comprimido

    printf("\nCarregando arquivo...\n");

    Arvore *raiz;
    No* vetor, *vetorfim;

    long long tamVetor, tamCodBin, tamvetSaida;
    unsigned char * vetSaida;
    char nomeSaida[50];

    vetor = insereFrequencia(nomeArq, &tamVetor);   //Criação do vetor de frequencias
    raiz = algoritmoHuffman(vetor, tamVetor);   //Criação da árvore
    vetorfim = pegaCod(vetor, tamVetor, raiz);  //Criação do vetor com os códigos binários
    tamvetSaida=calculaTamVet(vetorfim, tamVetor);  //Determinação do tamanho do vetor de saida
    vetSaida = vetorSaida(vetorfim, tamVetor, &tamCodBin, nomeArq); //Criação do vetor de saída
    

    int op, op2, men=1;
    while(men){
        /* Laço que garante a impressão do menu após a abertura de um arquivo a ser compactado */

        printf("\n\n----------MENU----------\n");
        printf("1 - Comprimir um Arquivo\n");
        printf("2 - Imprimir contagem de ocorrência\n");
        printf("3 - Imprimir código de Huffman\n");
        printf("4 - Testar Algoritmo de Decodificação\n");
        printf("5 - Gerar arquivo Comprimido\n");
        printf("6 - Descomprimir Arquivo\n");
        printf("0 - Sair\n");
        scanf("%d", &op);

        switch(op){
            case 1:
                /* Caso o usuário escolha a opção 1 é chamada a função comprimir novamente
                para que seja inserido um novo arquivo para ser compactado*/

                free(vetor);
                free(vetSaida);
                free(vetorfim);
                comprimir();
                men=0;
                break;
            
            case 2:
                /* Caso o usuário escolha a opção 2, é chamada função de impressão 
                do vetor apenas com as ocorrências */

                printf("\nImprimindo as ocorrências dos caracteres\n");
                imprimeVetor(vetor, tamVetor);
                printf("\n\n");
                break;
            
            case 3:
                /* Caso seja escolhida a opção 3, o usuário pode solicitar a impressão
                dos códigos dos caracteres ou da árvore */
            
                printf("\n\nImprimindo código de Huffman\n");
                printf("1 - Imprimir árvore\n");
                printf("2 - Imprimir caracteres e seus códigos\n");
                scanf("%d", &op2);
                switch(op2){
                    case 1:
                        printf("Imprimindo Arvore\n");
                        imprimeArvore(raiz);
                        printf("\n\n");
                        break;
                    
                    case 2:
                        printf("Imprimindo os caracteres e seus codigos:  ");
                        printf("[freq : carac : cod]\n\n");
                        imprimeVetorCod(vetorfim, tamVetor);
                        printf("\n\n");
                        break;
                }
                break;

            case 4:
                /* Caso seja escolhida a opção 4, o usuário pode 
                criar um arquivo de saída com a codificação feita, sem a necessidade
                de criar um arquivo compactado */
        
                printf("Digite o nome do arquivo de saída: ");
                scanf("%s", nomeSaida);
                binCode(vetSaida, tamCodBin,  raiz, nomeSaida);
                break;

            case 5:
                /* Caso seja escolhida a opção 5, então solicitamos o nome do arquivo compactado
                e chamamos a função salvar */

                printf("\nInsira o nome do arquivo de saída: ");
                scanf("%s", nomeSaida);
                salvar(tamCodBin,tamVetor,vetor, vetSaida, nomeSaida, tamvetSaida);
                printf("Arquivo salvo com sucesso!\n");
                men=0;
                free(vetor);
                free(vetSaida);
                free(vetorfim);
                break;
            
            case 6:
                /* Caso seja escolhida a opção 6, então solicitamos o nome do arquivo a ser descompactado
                e chamamos a função descomprimir */

                printf("\n\nInsira o nome do arquivo que deseja decomprimir: ");
                scanf("%s", nomeSaida);
                descomprimir(nomeSaida);
                break;
            
            case 0:
                /* O programa é encerrado */

                free(vetor);
                free(vetSaida);
                free(vetorfim);
                exit(1);
                break;
        }

    }

}
