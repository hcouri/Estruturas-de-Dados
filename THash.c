#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Aluno{
    int disponibilidade;
    int mat;
    char nome[50];
    char curso[40];
}Aluno;

#define TAM_HASH 13


int hash(int ma){
    ma = ma % 1000;
    return ma % TAM_HASH;
}

void inicializar(char* nomeArq){
    FILE* arq = fopen(nomeArq, "wb");

    Aluno a;
    a.disponibilidade = 1;
    strcpy(a.nome, "");
    strcpy(a.curso, "");


    for(int i=0; i < TAM_HASH; i++)
        fwrite(&a, sizeof(Aluno), 1, arq);

    fclose(arq);
}

int AcharPosicao(char* nomeArq, int ma){
    int pos = hash(ma);
    Aluno a;
    FILE* arq = fopen(nomeArq, "rb");

    fseek(arq, pos*sizeof(Aluno), SEEK_SET);
    fread(&a, sizeof(Aluno), 1, arq);

    while(a.disponibilidade == 0){
        pos = (pos+1) % TAM_HASH;
        fseek(arq, pos*sizeof(Aluno), SEEK_SET);
        fread(&a, sizeof(Aluno), 1, arq);
    }
    fclose(arq);
    return pos;
}

void Inserir(char* nomeArq, int ma, char* n, char* c){
    int pos = AcharPosicao(nomeArq, ma);

    FILE* arq = fopen(nomeArq, "r+b");

    Aluno a;
    a.mat = ma;
    strcpy(a.nome , n);
    strcpy(a.curso , c);
    a.disponibilidade = 0;

    fseek(arq, pos*sizeof(Aluno), SEEK_SET);
    fwrite(&a, sizeof(Aluno), 1, arq);

    fclose(arq);
}

int AcharPosicaoBusca(char* nomeArq, int ma){
    int pos = hash(ma);
    Aluno a;
    FILE* arq = fopen(nomeArq, "rb");

    fseek(arq, pos*sizeof(Aluno), SEEK_SET);
    fread(&a, sizeof(Aluno), 1, arq);

    while(a.disponibilidade == 0 && a.mat != ma){ //nao entra em loop pois sempre há espaco para armazenar
        pos = (pos+1) % TAM_HASH;
        fseek(arq, pos*sizeof(Aluno), SEEK_SET);
        fread(&a, sizeof(Aluno), 1, arq);
    }
    fclose(arq);
    return pos;
}

int main(){

    char  arq[30];
    printf("\nDigite o nome que deseja para o arquivo\n");
    scanf("%s", arq);
    inicializar(arq);

    while(1){
        int opcao = 0;

        printf("\n1) Inserir novo aluno(matricula, nome, curso)\n");
        printf("2) Imprimir aluno\n");
        printf("3) Imprimir hash\n");
        printf("4) Sair\n");

        printf("Escolha uma opcao\n");
        scanf("%d", &opcao);

        switch(opcao){

            case 1:{
                Aluno a;
                printf("Matricula Nome Curso:\n");
                scanf("%d %49[^\n] %39[^\n]", &a.mat, a.nome, a.curso); //matricula enter nome enter curso enter
                Inserir(arq, a.mat, a.nome, a.curso);

            break;
            }


            case 2:{
                int matricula_aux = 0;
                printf("Matricula:\n");
                scanf("%d", &matricula_aux);

                int indice = AcharPosicaoBusca(arq, matricula_aux);

                FILE* arq_leitura = fopen(arq, "rb");
                Aluno a;

                fseek(arq_leitura, indice*sizeof(Aluno), SEEK_SET);
                fread(&a, sizeof(Aluno), 1, arq_leitura);
                fclose(arq_leitura);

                if(a.disponibilidade ==  0 && a.mat == matricula_aux)
                    printf("%d %s %s\n", a.mat, a.nome, a.curso);
                else
                    printf("\nAluno nao encontrado\n");
            break;
            }

            break;

            case 3:{
                FILE* arq_leitura = fopen(arq, "rb");
                Aluno a;

                puts("");

                for(int i=0; i<TAM_HASH; i++){
                    fseek(arq_leitura, i*sizeof(Aluno), SEEK_SET);
                    fread(&a, sizeof(Aluno), 1, arq_leitura);

                    printf("%d %s %s\n", a.disponibilidade, a.nome, a.curso);
                }
                fclose(arq_leitura);

            break;
            }


            case 4:
                exit(0);
            break;
        }
    }
}
