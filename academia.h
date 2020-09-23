#ifndef ACADEMIA_H_INCLUDED
#define ACADEMIA_H_INCLUDED

typedef struct Academia Academia;

int menu(char opcao, Academia *Atual);
void LerArquivo(FILE *Arquivo, Academia **AcademiaAtual, Academia **Primeiro, int *cont);
void navegar(int direcao, Academia **Atual);
void novo_aluno(Academia **Atual, Academia **Primeiro, int *cont);
void ordenar(Academia **Primeiro, Academia **novo_aluno, Academia **Atual);
void Adiciona(Academia **Atual);
void apagar(Academia **Atual, Academia **Primeiro, int *cont);
void alterar(Academia **Atual, Academia **Primeiro);
void SalvaArquivo(FILE *Arquivo, Academia **Primeiro, int *cont);


#endif // ACADEMIA_H_INCLUDED
