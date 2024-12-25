#include <stdio.h>
#include <stdlib.h>

void I_valor_combinacoes(int aux[], int n, int max[],int valor_combinacoes, int soma, int v[], int comeco){

    int i=0;
    if(soma == valor_combinacoes){
           puts("");
           for(i=0; i<n; i++)
                printf("| Moedas de %d: %d ", aux[i],v[i]);
           puts("");
    }

    if(soma > valor_combinacoes)
        return;


    else{
        for(i=comeco; i<n; i++){
            if(v[i] < max[i]){
                v[i]++;
                I_valor_combinacoes(aux, n, max, valor_combinacoes, soma+aux[i], v, i);
                v[i]--;
            }
        }

    }

}

int main(){
    int v[5] = {0};
    int aux[] = {1, 5, 10, 25, 50};

    int valor = 0;
    printf("Digite o valor: ");
    scanf("%d", &valor);

    int max[5] = {valor/1, valor/5, valor/10, valor/25, valor/50};
    int soma=0;
    I_valor_combinacoes(aux, 5, max, valor, 0, v, 0);
}
