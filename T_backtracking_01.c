#include <stdio.h>
#include <stdlib.h>

void I_Aux_char(char v[], int n, int pos, char aux[]){
    int i=0;

    if(pos == n){
        int cont_a = 0;
        int cont_resto = 0;

        for(i=0; i<n; i++){
            if(v[i] == 'a')
                cont_a++;
            else
                cont_resto++;
        }

        if(cont_a > cont_resto){
            for(i=0; i<n; i++)
                printf("%c ", v[i]);
            puts("");
        }
    }

    else{
        for(i=0; i<n; i++){
            v[pos] = aux[i];
            I_Aux_char(v, n, pos+1, aux);
        }
    }
}


int main(){
    char v[3];
    char aux[] = {'a', 'e', 'i'};

    I_Aux_char(v, 3, 0, aux);
}
