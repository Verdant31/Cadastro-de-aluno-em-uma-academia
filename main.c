#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "academia.h"

int main(void) {
    FILE *Arquivo;
    char opcao;
    int cont = 0;

    Academia *Primeiro = NULL;
    Academia *Atual = NULL;

    LerArquivo(Arquivo, &Atual, &Primeiro, &cont);

    do {
        opcao = menu(opcao, Atual);
        switch(opcao) {
            case '<':
            navegar(1, &Atual);
            break;

            case '>':
            navegar(2, &Atual);
            break;

            case '+':
            novo_aluno(&Atual, &Primeiro, &cont);
            break;

            case '!':
            apagar(&Atual, &Primeiro, &cont);
            break;

            case 'a':
            alterar(&Atual, &Primeiro);
            break;
        }
    }
    while(opcao != 'S');

    SalvaArquivo(Arquivo, &Primeiro, &cont);

    return 0;
}

