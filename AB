#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct arvore{
    int info;
    struct arvore* esq;
    struct arvore* dir;
}arvore;

arvore* LerArvore(FILE* arq){
    char c;
    int num;

    fscanf(arq,"%c", &c);
    fscanf(arq,"%d", &num);

    if(num == -1){
        fscanf(arq, "%c", &c);
        return NULL;
    }
    else{
        arvore* a = (arvore*)malloc(sizeof(arvore));
        a->info = num;
        a->esq = LerArvore(arq);
        a->dir = LerArvore(arq);
        fscanf(arq, "%c", &c);
        return a;
    }
}

void Pre_ordem(arvore* a){
    if(a == NULL)
        return;

    printf("%d ", a->info);
    Pre_ordem(a->esq);
    Pre_ordem(a->dir);
}

void Em_ordem(arvore* a){
    if(a == NULL)
        return;

    Em_ordem(a->esq);
    printf("%d ", a->info);
    Em_ordem(a->dir);
}

void Pos_ordem(arvore* a){
    if(a == NULL)
        return;

    Pos_ordem(a->esq);
    Pos_ordem(a->dir);
    printf("%d ", a->info);
}

int Existe(arvore* a, int x){
    if(a == NULL)
        return 0;

    if(a->info == x)
        return 1;

    return Existe(a->esq, x) || Existe(a->dir, x);
}

int ContaNo(arvore* a){
    if(a == NULL)
        return 0;
    else
        return 1 + ContaNo(a->esq) + ContaNo(a->dir);

}

void ImprimeFolha(arvore* a){
    if(a == NULL)
        return;

    if(a->esq == NULL && a->dir == NULL) // a!= NULL && a->esq == NULL && a->dir == NULL
        printf("%d ", a->info);

    ImprimeFolha(a->esq);
    ImprimeFolha(a->dir);
}

int AlturaArvore(arvore* a){
    if(a == NULL)
        return 0;
    else
        return 1 + fmax( AlturaArvore(a->esq) , AlturaArvore(a->dir) );
}

void ImprimeNivel(arvore* a, int cont, int n){
    if(a == NULL)
        return;

    if(cont != n){
        ImprimeNivel(a->esq, cont+1, n);
        ImprimeNivel(a->dir, cont+1, n);
    }
    else
        printf("%d ", a->info);
}

int ContaNivel(arvore* a, int cont, int n){
    if(a == NULL)
        return 0;
    if(cont == n)
        return 1;
    else
        return ContaNivel(a->esq, cont+1, n) + ContaNivel(a->dir, cont+1, n);
}

bool VerificaCompleta(arvore* a){
    if(a == NULL)
        return true;

    int h = AlturaArvore(a);
    if(pow(2, h-2) == ContaNivel(a, 0, h-2))
        return true;
    else
        return false;
}

bool VerificaCheia(arvore* a){
    if(a == NULL)
        return true;

    int h = AlturaArvore(a);
    if( pow(2, h-1) == ContaNivel(a, 0, h-1) )
        return true;
    else
        return false;
}

int VerificaOrdenada(arvore* a){
    if(a == NULL)
        return 1;
    if(a->esq == NULL && a->dir == NULL)
        return 1;

    if(a->esq != NULL && a->dir == NULL)
        if(a->esq->info <= a->info)
            return 1 && VerificaOrdenada(a->esq);
    if(a->esq == NULL && a->dir != NULL)
        if(a->info < a->dir->info)
            return 1 && VerificaOrdenada(a->dir);


    if(a->esq->info <= a->info && a->info < a->dir->info)
        return 1 && ( VerificaOrdenada(a->esq) && VerificaOrdenada(a->dir) );

    return 0;
}

int VerificaBalanciada(arvore* a){
    if(a == NULL)
        return 1;

    int ha = AlturaArvore(a->esq);
    int hb = AlturaArvore(a->dir);
    if(ha == hb || ha+1 == hb || ha-1 == hb)
        return 1 && (VerificaBalanciada(a->esq) && VerificaBalanciada(a->dir) );

    return 0;
}

void ImprimeNivelNo(arvore* a, int cont, int x){
    if(a == NULL)
        return;
    if(a->info == x){
        printf("Nivel: %d \n", cont);
        return;
    }

    ImprimeNivelNo(a->esq, cont+1, x);
    ImprimeNivelNo(a->dir, cont+1, x);
}

arvore* Destruir(arvore* a){
    if(a != NULL){
        a->esq = Destruir(a->esq);
        a->dir = Destruir(a->dir);
        free(a);
    }
    return NULL;
}

void ImprimeLargura(arvore* a, int h){
    if(a == NULL)
        return;
    if(h == 0)
        return;

    ImprimeLargura(a, h-1);
    ImprimeNivel(a, 0, h-1);
    printf("\n");
}

int Conta_x(arvore* a, int x){
    if(a == NULL)
        return 0;
    if(a->info < x)
       return Conta_x(a->dir, x);
    if(a->info > x)
        return Conta_x(a->esq, x);

    return 1 + Conta_x(a->esq, x);
}

arvore* Inserir(arvore* a, int x){
    if(a == NULL){
        a = (arvore*)malloc(sizeof(arvore));
        a->info = x;
        a->esq = NULL;
        a->dir = NULL;
    }

    else if(a->info >= x)
        a->esq = Inserir(a->esq, x);
    else
        a->dir = Inserir(a->dir, x);

    return a;
}



int Igual(arvore* a, arvore* b){
    if(a == NULL && b == NULL)
        return 1;
    if(a == NULL && b != NULL)
        return 0;
    if(a != NULL && b == NULL)
        return 0;

    if(a->info == b->info){
        return 1 + (Igual(a->esq, b->esq) && Igual(a->dir, b->dir) );
    }
    else
        return 0;
}



int ocorrencias(arvore* a, int x){
    if(a == NULL)
        return 0;
    if(x == a->info)
        return 1 + ocorrencias(a->esq, x);
    if(x < a->info)
        return ocorrencias(a->esq, x);
    else
        return ocorrencias(a->dir, x);

}

int main(){

    FILE* arq = NULL;
    arvore* a = NULL;
 while(1){
    int opcao = 0;

    printf("\n1) Ler arvore\n");
    printf("2) Imprimir arvore\n");
    printf("3) Verificar se existe elemento na arvore\n");
    printf("4) Contar elementos na arvore\n");
    printf("5) Imprimir nos folha da arvore\n");
    printf("6) Verificar se a arvore e balanciada\n");
    printf("7) Verificar se a arvore e cheia\n");
    printf("8) Imprimir o nivel de um no x\n");
    printf("9) Sair\n");

    printf("Escolha uma opcao\n");
    scanf("%d", &opcao);

    switch(opcao){

        case 1:{
           char nome_arquivo[100];
           printf("\nDigite o nome do arquivo\n");
           scanf("%s", nome_arquivo);

           arq = fopen(nome_arquivo, "r");
           a = LerArvore(arq);
           fclose(arq);
        break;
        }

        case 2:{
            int opcao_imprimir = 0;

            printf("\n1) pre-ordem\n");
            printf("2) em-ordem\n");
            printf("3) pos-ordem\n");
            printf("4) em largura\n");

            printf("Escolha uma opcao\n");
            scanf("%d", &opcao_imprimir);

            switch(opcao_imprimir){

                case 1:
                  puts("");
                  Pre_ordem(a);
                  puts("");
                break;

                case 2:
                  puts("");
                  Em_ordem(a);
                  puts("");
                break;

                case 3:
                  puts("");
                  Pos_ordem(a);
                  puts("");
                break;

                case 4:{
                  int h = AlturaArvore(a);
                  puts("");
                  ImprimeLargura(a, h);
                break;
                }
            }
         break;
        }

        case 3:{
            int x = 0;//implementar um scanf
            int existe = 0;

            printf("Digite o elemento: \n");
            scanf("%d", &x);
            existe = Existe(a, x);

            if(a == NULL)
                printf("\nA arvore esta vazia\n");

            else if(existe == 1)
                printf("\nO elemento existe na arvore\n");
            else
                printf("\nO elemento nao existe na arvore\n");

         break;
        }

        case 4:
            printf("\nNumero de nos: %d\n", ContaNo(a));
         break;


        case 5:
            puts("");
            ImprimeFolha(a);
            puts("");
         break;

        case 6:
            if(VerificaBalanciada(a))
                printf("A arvore e balanciada\n");
            else
                printf("A arvore nao e balanciada\n");
            break;

         case 7:
             if(VerificaCheia(a))
                printf("A arvore e cheia\n");
             else
                printf("A arvore nao e cheia\n");

          break;

          case 8:{
            int no_x = 0;
             printf("Digite o no que deseja saber o nivel: \n");
             scanf("%d", &no_x);

             ImprimeNivelNo(a, 0, no_x);
           break;
          }

        case 9:
            a = Destruir(a);
            exit(0);
    }
 }
}
