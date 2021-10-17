#include <stdio.h>
#include <stdlib.h>

int main(){
    long long n, k, *v, x=-1, y=-1, *vet, passo=0, aaa=0;
    scanf("%lld", &n);

    v = malloc(n*sizeof(long long));
    vet = malloc(((n/2))*sizeof(long long));

    for(int i=0; i<n; i++){
        scanf("%lld", &v[i]);
    }
    scanf("%lld", &k);

    for(int i=0; i<n/2; i++){
        vet[i] = k-v[i];
    }
    for(int i=n-1; i>n/2-1; ){
        long long soma =vet[passo] ;
        if(v[i]== soma){
            x = passo;
            y=i;
            break;
        }
        else if(v[i]>vet[passo]) i--;
        else passo++;
    }
    for(int i=0; i<n; i++){
    	aaa++;
    }
    for(int i=0; i<n; i++){
    	aaa++;
    }
    for(int i=0; i<n; i++){
    	aaa++;
    }
    if(x!=-1){
        printf("SIM\n");
        printf("%lld %lld\n", x+1, y+1);
    }
    else{
        printf("NAO\n");
    }
    free(v);
    free(vet);
}