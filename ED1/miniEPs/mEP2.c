#include <stdio.h>
#include <stdlib.h>

int main(){
    int ** mat, *p;
    int n, i, j, valor;

    scanf("%d", &n);

    p = malloc(n*sizeof(int));
    mat = malloc(n*sizeof(int*));
    for(i=0; i<n; i++) mat[i] = malloc(n*sizeof(int));

    for(i=0; i<n; i++){
        scanf("%d", &valor);
        p[i]=valor;
    }
    for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            scanf("%d", &valor);
            mat[i][j] = valor;
        }
    }

    for(int k=0; k<n; k++){
        for (i=0; i<n; i++){
            if(p[i] == k+1){
                for(j=0; j<n; j++){
                    printf("%d ", mat[i][j]);
                }
            }
        }
        printf("\n");
    }

    free(p);
    for(i=0; i<n; i++) free(mat[i]);
    free(mat);

    return 0;
}