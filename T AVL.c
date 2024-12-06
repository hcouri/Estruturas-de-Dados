#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct arvore{
    int info;
    int FB;
    struct arvore* esq;
    struct arvore* dir;
}AVL;

AVL* LerArvore(FILE* arq){
    char c;
    int num;

    fscanf(arq,"%c", &c);
    fscanf(arq,"%d", &num);

    if(num == -1){
        fscanf(arq, "%c", &c);
        return NULL;
    }
    else{
        AVL* a = (AVL*)malloc(sizeof(AVL));
        a->info = num;
        a->esq = LerArvore(arq);
        a->dir = LerArvore(arq);
        fscanf(arq, "%c", &c);
        return a;
    }
}

void Pre_ordem(AVL* a){
    if(a == NULL)
        return;

    printf("%d ", a->info);
    Pre_ordem(a->esq);
    Pre_ordem(a->dir);
}

void Em_ordem(AVL* a){
    if(a == NULL)
        return;

    Em_ordem(a->esq);
    printf("%d ", a->info);
    Em_ordem(a->dir);
}

void Pos_ordem(AVL* a){
    if(a == NULL)
        return;

    Pos_ordem(a->esq);
    Pos_ordem(a->dir);
    printf("%d ", a->info);
}

void ImprimeNivel(AVL* a, int cont, int n){
    if(a == NULL)
        return;

    if(cont != n){
        ImprimeNivel(a->esq, cont+1, n);
        ImprimeNivel(a->dir, cont+1, n);
    }
    else
        printf("%d ", a->info);
}

void ImprimeLargura(AVL* a, int h){
    if(a == NULL)
        return;
    if(h == 0)
        return;

    ImprimeLargura(a, h-1);
    ImprimeNivel(a, 0, h-1);
    printf("\n");
}

int Existe(AVL* a, int x){
    if(a == NULL)
        return 0;

    if(a->info == x)
        return 1;
    if(x <= a->info)
       return Existe(a->esq, x);
    else
       return Existe(a->dir, x);
}

void ImprimeFolha_Menor(AVL* a, int x){
    if(a == NULL)
        return;

    if(a->esq == NULL && a->dir == NULL){
      if(a->info < x)
          printf("%d ", a->info);
    }

      if(x <= a->info)
        ImprimeFolha_Menor(a->esq, x);
      else{
        ImprimeFolha_Menor(a->esq, x);
        ImprimeFolha_Menor(a->dir, x);
      }
}

void ImprimeNivelNo(AVL* a, int cont, int x){
    if(a == NULL)
        return;
    if(a->info == x){
        printf("Nivel: %d\n", cont);
        return;
    }
    if(x <= a->info)
        ImprimeNivelNo(a->esq, cont+1, x);
    else
        ImprimeNivelNo(a->dir, cont+1, x);
}

int AlturaArvore(AVL* a){
    if(a == NULL)
        return 0;
    else
        return 1 + fmax(AlturaArvore(a->esq), AlturaArvore(a->dir));
}

AVL* Destruir(AVL* a){
    if(a != NULL){
        a->esq = Destruir(a->esq);
        a->dir = Destruir(a->dir);
        free(a);
    }
    return NULL;
}

AVL* RotacaoEsqSimples(AVL *r){

    AVL *a = r;
    AVL *b=a->dir;
    a->dir = b->esq;
    b->esq = a;

    if (b->FB == 1){
     a->FB = 0;
     b->FB = 0;
    }

    else{
        a->FB = 1;
        b->FB = -1;
    }

 r=b;
 return r;
}

AVL *RotacaoEsqDupla(AVL *r){

    AVL *a = r;
    AVL *c = a->dir;
    AVL *b = c->esq;
    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;

        switch(b->FB){
        case -1:
            a->FB = 0;
            c->FB = 1;
        break;

        case 0:
            a->FB = 0;
            c->FB = 0;
        break;

        case +1:
            a->FB = -1;
            c->FB = 0;
        break;

        }

 b->FB = 0;
 r = b;
 return r;
}

AVL* RotacaoEsq (AVL *r){
    if (r->dir->FB == -1)
     r = RotacaoEsqDupla(r);
    else
     r = RotacaoEsqSimples(r);
 return r;
}

AVL *RotacaoDirSimples (AVL *r){
    AVL *a = r->esq;
    AVL *b = r;
    b->esq = a->dir;
    a->dir = b;

    if (a->FB == -1){
     a->FB = 0;
     b->FB = 0;
    }

    else{
     a->FB = 1;
     b->FB = -1;
    }
 r = a;
 return r;
}

AVL *RotacaoDirDupla(AVL *r){
    AVL *c = r;
    AVL *a = c->esq;
    AVL *b = a->dir;
    c->esq = b->dir;
    a->dir = b->esq;
    b->esq = a;
    b->dir = c;

        switch(b->FB){
        case -1:
            a->FB = 0;
            c->FB = 1;
        break;

        case 0:
         a->FB = 0;
         c->FB = 0;
        break;

        case +1:
         a->FB = -1;
         c->FB = 0;
        break;
        }

 b->FB = 0;
 r = b;
 return r;
}

AVL *RotacaoDir (AVL *r){
    if (r->esq->FB == 1)
     r = RotacaoDirDupla(r);
    else
     r = RotacaoDirSimples(r);
return r;
}

AVL *Inserir(AVL *r, int x, int *hMudou){

    if (r == NULL){
        r = (AVL*) malloc (sizeof(AVL));
        r->info = x;
        r->esq = NULL;
        r->dir = NULL;
        r->FB = 0;
        *hMudou = 1;
    }

    else{
        if (x <= r->info){
         r->esq = Inserir(r->esq,x,hMudou);

        if (*hMudou == 1){
         switch (r->FB){

         case -1:
            r = RotacaoDir(r);
            *hMudou = 0;
         break;

         case 0:
            r->FB = -1;
            *hMudou = 1;
         break;

         case +1:
            r->FB = 0;
            *hMudou = 0;
         break;
        }
       }
       }

      else{
        r->dir = Inserir (r->dir,x,hMudou);
            if(*hMudou == 1){
                switch (r->FB){
                case -1:
                    r->FB = 0;
                    *hMudou = 0;
                break;

                case 0:
                    r->FB = +1;
                    *hMudou = 1;
                break;

                case +1:
                    r = RotacaoEsq (r);
                    *hMudou = 0;
                break;
                }
            }
      }
    }
 return r;
}

AVL* Remover (AVL *r, int x, int *hMudou){
 if (r != NULL){
    if (r->info == x){

    //Verificar se é folha
    if (r->esq == NULL && r->dir == NULL){
        free (r);
        *hMudou = 1;
        return NULL;
    }

    //Verificar se um dos filhos é nulo
    else if (r->esq == NULL || r->dir == NULL){
        AVL *aux;

    if (r->esq == NULL)
        aux = r->dir;
    else
        aux = r->esq;

    free(r);
    *hMudou = 1;
    return aux;
    }

    //Nenhum filho nulo

    else{
        AVL *maiorEsq = r->esq;

    while (maiorEsq->dir != NULL)
        maiorEsq = maiorEsq->dir;

    r->info = maiorEsq->info;
    r->esq = Remover(r->esq,r->info,hMudou);

    if (*hMudou == 1){
    switch(r->FB){
        case -1:
            r->FB = 0;
            *hMudou = 1;
        break;

        case 0:
            r->FB = 1;
            *hMudou = 0;
        break;

        case +1:{
            int aux = r->dir->FB;
            r = RotacaoEsq(r);
             if (aux == 0)
              *hMudou = 0;
             else
              *hMudou = 1;
        break;
        }
    }
    }
    }
    }


    else if (x < r->info){
        r->esq = Remover(r->esq, x, hMudou);

    if (*hMudou == 1){
    switch(r->FB){

        case -1:
            r->FB = 0;
            *hMudou = 1;
        break;

        case 0:
            r->FB = 1;
            *hMudou = 0;
        break;

        case +1:{
            int aux = r->dir->FB;
            r = RotacaoEsq(r);
             if (aux == 0)
              *hMudou = 0;
             else
              *hMudou = 1;
        break;
        }
    }
    }
    }

    else{
        r->dir = Remover(r->dir, x, hMudou);

    if(*hMudou == 1){
    switch(r->FB){

        case +1:
            r->FB = 0;
            *hMudou = 1;
        break;

        case 0:
            r->FB = -1;
            *hMudou = 0;
        break;

        case -1:{
            int aux = r->esq->FB;
            r = RotacaoDir(r);
             if (aux == 0)
              *hMudou = 0;
             else
            *hMudou = 1;
        break;
        }
    }
    }
    }
return r;
 }
}

int main(){

    FILE* arq = NULL;
    AVL* a = NULL;
    int hMudou = 0;
 while(1){
    int opcao = 0;

    printf("\n1) Ler arvore\n");
    printf("2) Imprimir arvore\n");
    printf("3) Verificar se existe elemento na arvore\n");
    printf("4) Imprimir o nivel de um No x\n");
    printf("5) Imprimir nos folha da arvore menores que x\n");
    printf("6) Inserir No\n");
    printf("7) Remover No\n");
    printf("8) Sair\n");

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
            int x = 0;
            int existe = 0;

            printf("DIGITE O ELEMENTO:");
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

        case 4:{
            int nivel_no = 0;

            printf("DIGITE O NO:");
            scanf("%d", &nivel_no);

            puts("");
            ImprimeNivelNo(a, 0, nivel_no);
            puts("");
        }
         break;


        case 5:{
            int folha_menor_q_x = 0;

            printf("DIGITE O VALOR X:");
            scanf("%d", &folha_menor_q_x);

            puts("");
            ImprimeFolha_Menor(a, folha_menor_q_x);
            puts("");
        }
         break;

        case 6:{
            int valor_inserir = 0;

            printf("\nDIGITE O VALOR PARA INSERIR:");
            scanf("%d", &valor_inserir);

            a = Inserir(a, valor_inserir, &hMudou);
            break;
        }

         case 7:{
            int valor_remover = 0;

            printf("\nDIGITE O VALOR PARA REMOVER:");
            scanf("%d", &valor_remover);

            if(a == NULL){
                printf("\nA ARVORE ESTA VAZIA\n");
                break;
            }
            a = Remover(a, valor_remover, &hMudou);
          break;
         }

          case 8:{
            a = Destruir(a);
            exit(0);
           break;
          }

    }
 }
}
