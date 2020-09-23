#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "academia.h"

struct Academia {
    char nome[50];
    char horario[100];
    char personal[700];
    int lote;
    int quadra;
	int feito;
    struct Academia *proximo;
    struct Academia *anterior;
};

int menu(char opcao, Academia *Atual) {
	system("cls");
    printf(" Opcoes:");
    printf("\n < > - Navegar.");
    printf("\n a - Alterar.");
    printf("\n ! - Apagar aluno.");
    printf("\n + - Inserir horario.");
    printf("\n S - Sair.\n");

    if(Atual == NULL) {
        printf("\n\n Lista de alunos vazia.");
    }else {
        printf("\n Nome: %s", Atual->nome);
        printf("\n Horario: %s", Atual->horario);
        printf("\n Precisa de personal? %s", Atual->personal);
        printf("\n Lote %d", Atual->lote);
        printf("\n Quadra: %d", Atual->quadra);
    }
    printf("\n\n Digite aqui: ");
    opcao = getch();
    return(opcao);
}

void LerArquivo(FILE *Arquivo, Academia **AcademiaAtual, Academia **Primeiro, int *cont) {
    int I;
    char opcao;
    Academia *Aux;
    int Cont = 0;

    Arquivo = fopen("Academia", "rb");

    if(Arquivo == NULL) {
        return;
    }
    *cont = fgetc(Arquivo);

    while(!feof(Arquivo) && Cont < (*cont)) {
        Aux = malloc(sizeof(Academia));
        fread(Aux, sizeof(struct Academia), 1, Arquivo);

        ordenar(Primeiro, &Aux, AcademiaAtual);
        Cont++;
    }
    fclose(Arquivo);
}

void novo_aluno(Academia **Atual, Academia **Primeiro, int *cont) {
    system("cls");
	fflush(stdin);

	Academia *Nova = NULL;
    Nova = malloc(sizeof(Academia));

    printf("\nNome do morador: ");
    gets(Nova->nome);
    fflush(stdin);

    printf("\nHorario: ");
    gets(Nova->horario);
    fflush(stdin);

    printf("\nPrecisa de personal? ");
    gets(Nova->personal);
    fflush(stdin);

    printf("\nLote: ");
    scanf("%d", &(Nova->lote));
    fflush(stdin);
	
	printf("\nQuadra: ");
    scanf("%d", &(Nova->quadra));
    fflush(stdin);

    Nova->feito = 0;

    *cont = (*cont) + 1;

    ordenar(Primeiro, &Nova, Atual);
}

void ordenar(Academia **Primeiro, Academia **Nova, Academia **Atual) {
    int Cont = 0;
    Academia *aux = *Primeiro;

    if(*Primeiro == NULL) {
        (*Nova)->anterior = *Nova;
        (*Nova)->proximo = *Nova;

        *Atual = *Nova;
        *Primeiro = *Nova;
    }else if((*Primeiro)->proximo == *Primeiro) {
        (*Nova)->proximo = *Primeiro;
        (*Nova)->anterior = *Primeiro;
        (*Primeiro)->proximo = *Nova;
        (*Primeiro)->anterior = *Nova;

        if(strcmp((*Primeiro)->nome, (*Nova)->nome) > 0) {
            *Primeiro = *Nova;
        }
    }
    else {
        while(strcmp(aux->nome, (*Nova)->nome) <= 0) {
            aux = aux->proximo;
            Cont++;
            if(aux == *Primeiro) {
                break;
            }
        }

        aux->anterior->proximo = *Nova;
        (*Nova)->anterior = aux->anterior;
        aux->anterior = *Nova;
        (*Nova)->proximo = aux;

        if(Cont == 0) {
            *Primeiro = *Nova;
        }
    }
}

void Adiciona(Academia **Atual) {
    if(*Atual != NULL) {
        (*Atual)->feito = ((*Atual)->feito) +1;
    }
}

void apagar(Academia **Atual, Academia **Primeiro, int *cont) {
    Academia *aux;
	system("cls");
    if((*Atual) == NULL) {
        printf("Nao tem aluno para apagar.");
        getch();
    }
    else if((*Atual)->proximo == *Atual) {
        free(*Atual);
        *Atual = NULL;
        *Primeiro = NULL;
        *cont = (*cont) - 1;
    }
    else {
        if(*Atual == *Primeiro) {
            aux = (*Atual)->proximo;
            (*Atual)->anterior->proximo = aux;
            aux->anterior = (*Atual)->anterior;
            free(*Atual);
            *Atual = aux;
            *Primeiro = aux;
        }
        else {
            aux = (*Atual)->proximo;
            (*Atual)->anterior->proximo = aux;
            aux->anterior = (*Atual)->anterior;
            free(*Atual);
            *Atual = aux;
        }
        *cont = (*cont) - 1;
    }
}

void alterar(Academia **Atual, Academia **Primeiro) {
    char Op;
	system("cls");	
    if(*Atual != NULL) {
        Academia *aux = *Atual;
        printf(" Alteracao dos dados do(a): %s\n\n", (*Atual)->nome);

        printf("\n Alterar o horario? (S/N)\n");
        Op = getch();
        if(Op == 'S' || Op == 's') {
            printf("\n Novo horario: ");
            printf("\n >> ");
            gets(aux->horario);
        }

        printf("\n Alterar opcao de personal? (S/N)\n");
        Op = getch();
        if(Op == 'S' || Op == 's') {
            printf("\n Nova opcao de personal: ");
            printf("\n >> ");
            gets(aux->personal);
        }

        printf("\n Alterar o lote? (S/N)\n");
        Op = getch();
        if(Op == 'S' || Op == 's') {
            printf("\n Novo lote: ");
            printf("\n >>");
            scanf("%d", &aux->lote);
        }
        if((*Atual) == *Primeiro) {
            *Primeiro = aux;
        }
        *Atual = aux;
        
        printf("\n Alterar a quadra? (S/N)\n");
        Op = getch();
        if(Op == 'S' || Op == 's') {
            printf("\n Nova quadra: ");
            printf("\n >>");
            scanf("%d", &aux->quadra);
        }
        if((*Atual) == *Primeiro) {
            *Primeiro = aux;
        }
        *Atual = aux;
    }
}

void navegar(int direcao, Academia **Atual) {
    if(*Atual != NULL) {
        if(direcao == 1) {
            *Atual = (*Atual)->anterior;
        }
        else if(direcao == 2) {
            *Atual = (*Atual)->proximo;
        }
    }
}

void SalvaArquivo(FILE *Arquivo, Academia **Primeiro, int *cont) {
    Academia *Aux;

    Aux = *Primeiro;

    remove("Academia");

    if(*Primeiro != NULL) {
        Arquivo = fopen("Academia", "wb");

        if(Arquivo == NULL) {
           
        }
        fputc((*cont), Arquivo);
        do {
            fwrite(Aux, sizeof(struct Academia), 1, Arquivo);
            Aux = Aux->proximo;
        }while(Aux != *Primeiro);
        fclose(Arquivo);
    }
}









