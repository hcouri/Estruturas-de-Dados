#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
    int destino;
    int custo;
    struct lista* prox;
}lista;

void inicializar(lista** g, int n){
    for(int i=0; i<=n; i++)
        g[i] = NULL;
}


lista* InserirLista(lista* l, int d, int c){
    lista* no = (lista*)malloc(sizeof(lista));
    no->destino = d;
    no->custo = c;
    no->prox = l;

    return no;
}

void InserirAresta(lista** g, int origem, int destino, int custo){
    g[origem] = InserirLista(g[origem], destino, custo);
}


void ImprimirLista(lista* l){
    if(l != NULL){
        printf("-(%d, %d)", l->destino, l->custo);
        ImprimirLista(l->prox);
    }
}

void ImprimirGrafo(lista**g, int n){
    printf("Grafo: ");
    for(int i=1; i<=n; i++){
        printf("\n\t%d", i);
        ImprimirLista(g[i]);
    }
}


lista* RemoverLista(lista* l, int d, int c){
   lista* de_tras = NULL;
   lista* da_frente = l;

    while(da_frente != NULL){
        if((da_frente->destino == d) && (da_frente->custo == c)){
            if(de_tras == NULL){
                l = da_frente->prox;
                free(da_frente);
                return l;
            }
            else{
                de_tras->prox = da_frente->prox;
                free(da_frente);
                return l;
            }
        }
        de_tras = da_frente;
        da_frente = da_frente->prox;
    }
    return l; //caso nao encontre ou a lista for vazia
}

void RemoverAresta(lista** g, int origem, int destino, int custo){
    g[origem] = RemoverLista(g[origem], destino, custo);
}



void ImprimeGrau_E(lista** g, int n, int origem){
        int cont_E = 0;


        for(int i=1; i<=n; i++){
          lista* l = g[i];

          while(l != NULL){
            if(l->destino == origem)
                cont_E++;
            l = l->prox;
          }
        }

        printf("\nGrau de Entrada: %d\n", cont_E);

}

void ImprimeGrau_S(lista* l){
    int cont_S = 0;
    while(l != NULL){
        cont_S++;
        l = l->prox;
    }

    printf("\nGrau de Saida: %d\n", cont_S);
}

void ImprimeGrau_E_S_Vertice(lista** g, int n, int origem){
    ImprimeGrau_E(g, n, origem);
    ImprimeGrau_S(g[origem]);
}



void Verifica_Grafo_Completo(lista** g, int n){

    int cont_Arestas = 0;

    for(int i=1; i<=n; i++){
        lista* l = g[i];
        while(l != NULL){
            cont_Arestas++;
            l = l->prox;
        }
    }
    if(cont_Arestas == n*(n-1))
        printf("\nO grafo e completo\n");
    else
        printf("\nO grafo nao e completo\n");

}



lista* Free_Lista(lista* l){
    while(l != NULL){
        lista* aux = l;
        l = l->prox;
        free(aux);
    }
    return l;
}

lista** Free_Grafo(lista** g, int n){

    //tenho que dar free em g[0] até g[n]
    for(int i=0; i<=n; i++)
        g[i] = Free_Lista(g[i]);

    free(g); //libero o vetor de ponteiros g  QUE É um ponteiro para uma area de memoria ->>> (g = (lista**)malloc((n+1)*sizeof(lista*));)
    return NULL;
}



int existe(int* vet, int valor, int pos){
    for(int i=0; i<pos; i++)
        if(vet[i] == valor)
            return 1;
    return 0;
}

void Caminhos(lista** g, int b, int* vet, int pos){

    if(vet[pos-1] == b){ //chegou ao destino
        puts("");
        for(int i=0; i<pos; i++)
            printf("%d ", vet[i]);
    }

    else{
        lista* p = g[vet[pos-1]];
        while(p != NULL){
            if(!existe(vet, p->destino, pos)){
                vet[pos] = p->destino;
                Caminhos(g, b, vet, pos+1);
            }
            p = p->prox;
        }
    }
}



void Imprime_V_MaisCurto(int* v_MaisCurto, int mn){ //nao preciso passar int* mn pois nao vou altera-lo nesta funcao
    puts("");
    for(int i=0; i<mn; i++)
        printf("%d ", v_MaisCurto[i]);
}

void Caminho_MaisCurto(lista** g, int b, int* vet, int pos, int* mn, int* v_MaisCurto){
    if(vet[pos-1] == b){
        if(pos < *mn){
            *mn = pos;
            for(int i=0; i<pos; i++)
                v_MaisCurto[i] = vet[i];
        }
    }

    else{
        lista* p = g[vet[pos-1]];
        while(p != NULL){
            if(!existe(vet, p->destino, pos)){
                vet[pos] = p->destino;
                Caminho_MaisCurto(g, b, vet, pos+1, mn, v_MaisCurto);
            }
            p = p->prox;
        }
    }
}


void Imprime_V_MenorCusto(int* v_MenorCusto, int tam){
    puts("");
    for(int i=0; i < tam; i++)
        printf("%d ", v_MenorCusto[i]);
}

void Caminho_MenorCusto(lista** g, int b, int* vet, int pos, int* menor_custo, int* v_MenorCusto, int custo_atual, int* tam){
    if(vet[pos-1] == b){
        if(custo_atual < *menor_custo){
            *menor_custo = custo_atual;
            *tam = pos;
            for(int i=0; i<pos; i++)
                v_MenorCusto[i] = vet[i];
        }
    }

    else{
        lista* p = g[vet[pos-1]];
        while(p != NULL){
            if(!existe(vet, p->destino, pos)){
                vet[pos] = p->destino;
                Caminho_MenorCusto(g, b, vet, pos+1, menor_custo, v_MenorCusto, custo_atual + p->custo, tam);
            }
            p = p->prox;
        }
    }
}

int main(){

    lista** g;
    int n = 0;

    printf("\nDigite o numero de nos: ");
    scanf("%d", &n);
    g = (lista**)malloc((n+1)*sizeof(lista*));
    inicializar(g, n);



    while(1){

        printf("\n1) Inserir uma aresta no grafo\n");
        printf("2) Remover uma aresta do grafo\n");
        printf("3) Imprimir grafo\n");
        printf("4) Imprimir os graus de entrada e saida de um vertice\n");
        printf("5) Verificar se um grafo e completo\n");
        printf("6) Imprimir todos os caminhos entre uma origem e um destino\n");
        printf("7) Imprimir o caminho mais curto(com menor numero de arestas)\n");
        printf("8) Imprimir o caminho de menor custo(menor soma dos custos das arestas\n");
        printf("9) Sair\n");

        int opcao = 0;
        printf("\nEscolha uma opcao\n");
        scanf("%d", &opcao);

        switch(opcao){

            case 1:{
                int origem, destino, custo = 0;
                printf("\nDigite origem destino custo, nesta ordem(para inserir): ");
                scanf("%d %d %d", &origem, &destino, &custo);
                InserirAresta(g, origem, destino, custo);

                break;
            }


            case 2:{
                int origem, destino, custo = 0;
                printf("\nDigite origem destino custo, nesta ordem(para remover): ");
                scanf("%d %d %d", &origem, &destino, &custo);
                RemoverAresta(g, origem, destino, custo);


                break;
            }


            case 3:{
                ImprimirGrafo(g, n);

                break;
            }


            case 4:{
                int vertice = 0;
                printf("\nDigite o vertice: ");
                scanf("%d", &vertice);

                ImprimeGrau_E_S_Vertice(g, n, vertice);

                break;
            }

            case 5:{
                Verifica_Grafo_Completo(g, n);

                break;
            }

            case 6:{
                int origem = 0;
                int destino = 0;
                printf("\nDigite a origem e destino: ");
                scanf("%d %d", &origem, &destino);

                int* vet = (int*)malloc(n*sizeof(int));
                vet[0] = origem;
                Caminhos(g, destino, vet, 1); //pos proxima possicao A INSERIR  || pos-1 ultima posicao INSERIDA

                free(vet);
                break;
            }

            case 7:{
                int origem = 0;
                int destino = 0;
                printf("\nDigite a origem e destino: ");
                scanf("%d %d", &origem, &destino);

                int* vet = (int*)malloc(n*sizeof(int));
                vet[0] = origem;

                int* v_aux = (int*)malloc(n*sizeof(int));
                int mn = n;
                Caminho_MaisCurto(g, destino, vet, 1, &mn, v_aux);
                Imprime_V_MaisCurto(v_aux, mn);

                free(vet);
                free(v_aux);
                break;
            }

            case 8:{
                int origem = 0;
                int destino = 0;
                printf("\nDigite a origem e destino: ");
                scanf("%d %d", &origem, &destino);

                int* vet = (int*)malloc(n*sizeof(int));
                vet[0] = origem;

                int* v_aux = (int*)malloc(n*sizeof(int));
                int menor_custo = 10000;  //numero que, certamente, fara com que :  custo < numero_exagerado
                int custo_atual = 0;
                int tam = 0; //vou coletar tam dentro de Caminho_MenorCusto, por referencia para imprimir v_aux ate tam
                Caminho_MenorCusto(g, destino, vet, 1, &menor_custo, v_aux, custo_atual, &tam);
                Imprime_V_MenorCusto(v_aux, tam);

                free(vet);
                free(v_aux);
                break;
            }

            case 9:{
                g = Free_Grafo(g, n); //preciso desalocar vet e v_aux nos casos 6,7 e 8
                return 0;
            }
        }
    }
}
