#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int total_elementos = 0;

int IndiceFilhoEsq(int x){
    int indice = (2 * x) + 1;
    if(x >= total_elementos || indice >= total_elementos)
        return -1;
    else
        return indice;
}

int IndiceFilhoDir(int x){
    int indice = (2 * x) + 2;
    if(x >= total_elementos || indice >= total_elementos)
        return -1;
    else
        return indice;
}

int IndicePai(int x){
    int indice = (int) floor((x-1)/2);
    if(x <= 0 || x >= total_elementos)
        return -1;
    else
        return indice;
}

void AjustarSubindo(int* heap, int pos){
    if(pos != -1){
        int pai = IndicePai(pos);
        if(pai != -1){
            if(heap[pos] < heap[pai]){
                int aux = heap[pos];
                heap[pos] = heap[pai];
                heap[pai] = aux;
                AjustarSubindo(heap, pai);
            }
        }
    }
}

void Inserir(int* heap, int x){
    heap[total_elementos] = x;
    total_elementos++;

    AjustarSubindo(heap, total_elementos - 1);
}

void AjustarDescendo(int* heap, int pos){
    if(pos != -1 && IndiceFilhoEsq(pos) != -1){
        //Descobrindo o menor filho
        int IndiceMenorFilho = IndiceFilhoEsq(pos);
        if(IndiceFilhoDir(pos) != -1 && heap[IndiceFilhoDir(pos)] < heap[IndiceMenorFilho])
            IndiceMenorFilho = IndiceFilhoDir(pos);
        //verificando se existe filho menor que o atual
        if(heap[IndiceMenorFilho] < heap[pos] ){
            int aux = heap[pos];
            heap[pos] = heap[IndiceMenorFilho];
            heap[IndiceMenorFilho] = aux;
            AjustarDescendo(heap, IndiceMenorFilho);
        }
    }
}

int Remover(int* heap){
    if(total_elementos == 0)
        return -1;
    else{
        int retorno = heap[0];
        heap[0] = heap[total_elementos - 1];
        heap[total_elementos - 1] = 0; //tirando o lixo de mem. Pois estou sempre imprimindo a heap com o tamanho max(12)
        total_elementos--;
        AjustarDescendo(heap, 0);
        return retorno;
    }
}

void ImprimirHeap(int* heap){
    for(int i=0; i<12; i++)
        printf("%d ", heap[i]);
}

int main(){
    int heap[12] = {0};

    while(1){

        printf("\n1) Inserir na Heap\n");
        printf("2) Remover na Heap\n");
        printf("3) Imprimir Heap\n");
        printf("4) Sair\n");
        printf("Escolha uma opcao:\n");

        int opcao = 0;
        scanf("%d", &opcao);

        switch(opcao){
            case 1:{
                printf("\nDIGITE O ELEMENTO PARA INSERIR: ");
                int x_inserir = 0;
                scanf("%d", &x_inserir);
                Inserir(heap, x_inserir);
                break;
            }
            case 2:{
                int y_removido = Remover(heap);
                printf("\nELEMENTO REMOVIDO: %d", y_removido);
                break;
            }
            case 3:
                ImprimirHeap(heap);
                break;
            case 4:
                exit(-1); //nao temos aloc. dinamica
                break;

        }

    }
}
