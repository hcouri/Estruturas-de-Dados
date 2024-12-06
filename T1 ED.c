#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int info;
    struct lista* prox;
}lista;


lista* InserirNoFinal(lista* l, int x){
    if(l == NULL){
        lista* no = (lista*)malloc(sizeof(lista));
        no->info = x;
        no->prox = NULL;
        return no;
    }

     l->prox = InserirNoFinal(l->prox, x);
      return l;
}

int SomaLista(lista* l){
    if(l == NULL)
     return 0;

    return l->info + SomaLista(l->prox);
}

int ContaNumero(lista* l, int x){
    if(l == NULL)
        return 0;

    if(l->info  == x)
        return 1 + ContaNumero(l->prox, x);

    return ContaNumero(l->prox, x);
}

lista* RemoveElemento(lista* l, int x){
    if(l->info == x)

    l->prox = RemoveElemento(l, x);
}

int main(){

    lista* l = NULL;

    l = InserirNoFinal(l, 10);
    l = InserirNoFinal(l, 40);
    l = InserirNoFinal(l, 30);
    l = InserirNoFinal(l, 40);
    l = InserirNoFinal(l, 50);
    l = InserirNoFinal(l, 50);
    l = InserirNoFinal(l, 40);

    printf("%d", ContaNumero(l, 40) );
}
