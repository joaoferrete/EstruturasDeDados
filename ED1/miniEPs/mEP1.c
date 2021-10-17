#include <stdio.h>
#include <stdlib.h>

int main(){
    long long int n, a, m, b, j, x, *vet;
    int op;
    scanf("%lld", &n);
    vet = (long long int *) malloc(sizeof(long long int)*n);
    for(a=0; a<n; a++)vet[a] = 0;

    scanf("%lld", &m);

    while(m--){
        scanf("%d", &op);

        if(op==1){
            scanf("%lld", &a);
            scanf("%lld", &b);
            scanf("%lld", &x);
            for(j = a-1; j<b; j++){
                vet[j]+=x;
            }
        }
        else if (op == 2){
            scanf("%lld", &a);
            scanf("%lld", &b);
            scanf("%lld", &x);
            for(j = a-1; j<b; j++){
                vet[j]-=x;
            }
        }
        else{
            scanf("%lld", &a);
            printf("%lld\n", vet[a-1]);
        }
    }
    free(vet);
    return 0;
}