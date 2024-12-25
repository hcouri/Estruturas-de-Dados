#include <stdio.h>
#include <stdlib.h>

void I_somaPar(int v[], int n, int pos, int aux[]){

    int i=0;
    int soma=0;

    if(pos == n){

        for(i=0; i<n; i++)
            soma += v[i];

        if((soma % 2) == 0){
            for(i=0; i<n; i++)
                printf("%d ", v[i]);
            printf("| SOMA = %d\n", soma);
        }
    }

    else{
        for(i=0; i<n; i++){
            v[pos] = aux[i];
            I_somaPar(v, n, pos+1, aux);
        }
    }

}


int main(){
    int v[4];
    int aux[] = {15, 31, 55, 44};

    I_somaPar(v, 4, 0, aux);
}
