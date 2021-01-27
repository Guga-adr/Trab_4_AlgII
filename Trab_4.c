#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct agenda *no;
struct agenda {
    char descricao[80];
    int dia,mes,ano,hora,min;
    struct agenda *prox;
};

no lista;

void sair() {

}

void inclui_comp() {

}

void menu() {
    char c;
    printf("|----------------------------------------|\n");
    printf("|                 AGENDA                 |\n");
    printf("|           ESCOLHA UMA OPCAO            |\n");
    printf("| 1. Adicionar compromisso               |\n");
    printf("| 2. Remover Compromisso                 |\n");
    printf("| 3. Remover Compromissos de uma data    |\n");
    printf("| 4. Conultar compromissos em uma data   |\n");
    printf("| 5. Procurar compromissos por descricao |\n");
    printf("| 6. Alterar Compromisso por palavra     |\n");
    printf("| 7. Sair e salvar compromissos          |\n");
    printf("|----------------------------------------|\n");
    do {
        printf("Selecione a opcao desejada!");
        c = getch();
    } while(c != 's' && c != 'n');
    switch(c) {
        case '1':
            break;
        case '2':
            break;
        case '3':
            break;
        case '4':
            break;
        case '5':
            break;
        case '6':
            break;
        case '7':
            break;
    }
}

int main() {
    menu();
    system("pause");
}