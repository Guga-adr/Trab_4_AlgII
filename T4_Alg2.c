//Dupla:
//Gustavo Amaral Duarte Rego - RA: 201025817
//Virgílio Santinho - RA: 201025558

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>



#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13



typedef struct Compromisso *no;
struct Compromisso {
    int Dia, Mes, Ano;
    int Hora, Minuto;
    char Descricao[81];
    struct Compromisso *prox;
};
typedef struct {
    int numele;
    no Primeiro, Ultimo;
} Descritor;



void gotoxy(int x, int y);
void desqua (int xe, int xd, int ys, int yi);
void linver (int x, int ys, int yi);
void linhor (int xe, int xd, int y);
void inter (int x, int y);
void escolhefuncao (Descritor *lista, int esc);
void SalvaDados (Descritor *lista);
void MostraAgenda (Descritor *lista);
void MostraCompromissosPalavra(Descritor lista);
void MostraCompromissosData (Descritor lista);
void ExcluiCompromissos (Descritor *lista);
void ExcluiCompromissosPalavra (Descritor *lista);
void ExcluiCompromissosData (Descritor *lista);
void ExcluiCompromissoInicioDaLista (Descritor *lista);
void RemoveInicioDaLista (Descritor *lista);
void AlteraCompromissos (Descritor *lista);
void AlteraCompromissosPalavra (Descritor *lista);
void AlteraCompromissosData (Descritor *lista);
void InsereCompromisso (Descritor *lista);
void InsereInicioDaLista (Descritor *lista, struct Compromisso *Dados);
void InsereFinalDaLista (Descritor *lista, struct Compromisso *Dados);
void InsereOrdenadamenteNaLista (Descritor *lista, struct Compromisso *Dados);



int main () {
    int esc, tecla;
    struct Compromisso CompromissoAuxiliar;
    Descritor lista;
    FILE *arquivo;
    system("COLOR 70");
    lista.numele = 0;
    lista.Ultimo = lista.Primeiro = NULL;
    if ((arquivo = fopen("Compromissos.txt", "r")) == NULL) {
        printf("\n Arquivo n%co encontrado.", 198);
        esc = getch();
        exit(0);
    }
    while (fscanf(arquivo, "%d %d %d %d %d %[^\n]s", &CompromissoAuxiliar.Dia, &CompromissoAuxiliar.Mes, &CompromissoAuxiliar.Ano, &CompromissoAuxiliar.Hora, &CompromissoAuxiliar.Minuto, &CompromissoAuxiliar.Descricao) != EOF) InsereFinalDaLista(&lista, &CompromissoAuxiliar);
    fclose(arquivo);
    do {
        system("cls");
        printf("\n O que deseja fazer?\n    Inserir novos compromissos\n    Alterar compromissos\n    Excluir compromissos\n    Mostrar compromissos\n    Salvar agenda\n    Sair do programa");
        desqua(0, 119, 0, 29);
        esc = 2;
        gotoxy(1, esc);
        printf("->");
        do {
            tecla = getch();
            switch (tecla) {
                case KEY_UP: if (esc>2) {gotoxy(1, esc); printf("  "); gotoxy(1, --esc); printf("->");} break;
                case KEY_DOWN: if (esc<7) {gotoxy(1, esc); printf("  "); gotoxy(1, ++esc); printf("->");} break;
                case ENTER: escolhefuncao(&lista, esc); break;
            }
        } while (tecla != ENTER);
    } while (esc != 7);
}



void escolhefuncao (Descritor *lista, int esc) {
    switch (esc) {
        case 2: InsereCompromisso(lista); break;
        case 3: AlteraCompromissos(lista); break;
        case 4: ExcluiCompromissos(lista); break;
        case 5: MostraAgenda(lista); break;
        case 6: SalvaDados(lista); break;
        case 7: exit(0); break;
    }
}
void SalvaDados (Descritor *lista) {
    no NoAtual = lista->Primeiro;
    FILE *arquivo;
    arquivo = fopen("Compromissos.txt", "w");
    while (NoAtual) {
        fprintf(arquivo, "%.2d %.2d %.4d %.2d %.2d %s\n", NoAtual->Dia, NoAtual->Mes, NoAtual->Ano, NoAtual->Hora, NoAtual->Minuto, NoAtual->Descricao);
        NoAtual = NoAtual->prox;
    }
    fclose(arquivo);
    linhor(0, 119, 9);
    gotoxy(1, 10);
    printf("Agenda salva.");
    gotoxy(1, 12);
    printf("Pressione qualquer tecla para continuar.");
    int a = getch();
}
void MostraAgenda (Descritor *lista) {
    int esc, tecla;
    do {
        system("cls");
        printf("\n Quais compromissos deseja visualizar?\n    Compromissos com uma palavra espec%cfica em sua descri%c%co\n    Compromissos em determinada data\n    Sair desta fun%c%co", 161, 135, 198, 135, 198);
        desqua(0, 119, 0, 29);
        esc = 2;
        gotoxy(1, esc);
        printf("->");
        do {
            tecla = getch();
            switch (tecla) {
                case KEY_UP: if (esc>2) {gotoxy(1, esc); printf("  "); gotoxy(1, --esc); printf("->");} break;
                case KEY_DOWN: if (esc<4) {gotoxy(1, esc); printf("  "); gotoxy(1, ++esc); printf("->");} break;
                case ENTER: if (esc==2) MostraCompromissosPalavra(*lista); if (esc==3) MostraCompromissosData(*lista); break;
            }
        } while (tecla != ENTER);
    } while (esc != 4);
}
void MostraCompromissosPalavra(Descritor lista) {
    int aux, LinhaAtual = 4;
    char Palavra[81];
    no NoAtual = lista.Primeiro;
    system("cls");
    if (!NoAtual) {
        printf("\n Lista vazia.\n\n Pressione qualquer tecla para continuar.");
        desqua(0, 119, 0, 4);
        gotoxy(41, 3);
        aux = getch();
        return;
    }
    aux = 1;
    printf("\n Digite a palavra que deseja procurar:");
    desqua(0, 119, 0, 4);
    gotoxy(1, 2);
    fflush(stdin);
    fgets(Palavra, 81, stdin);
    fflush(stdin);
    Palavra[strlen(Palavra)-1] = '\0';
    system("cls");
    desqua(0, 119, 0, 4);
    while (NoAtual) {
        if (strstr(NoAtual->Descricao, Palavra)!=NULL) {
            aux = 0;
            gotoxy(1, LinhaAtual-3); printf("Data: %.2d/%.2d/%.4d     Hora: %.2d:%.2d          ", NoAtual->Dia, NoAtual->Mes, NoAtual->Ano, NoAtual->Hora, NoAtual->Minuto);
            gotoxy(1, LinhaAtual-2); printf("Descri%c%co: %s", 135, 198, NoAtual->Descricao);
            desqua(0, 119, LinhaAtual, LinhaAtual+4);
            linhor(0, 119, LinhaAtual);
            gotoxy(1, LinhaAtual+1); printf("Pressione qualquer tecla para retornar.");
            LinhaAtual += 4;
        }
        NoAtual = NoAtual->prox;
    }
    if (aux==1) {
        gotoxy(1, 1);
        printf("N%co foi encontrado um compromisso com essa palavra.", 198);
        gotoxy(1, 3);
        printf("Pressione qualquer tecla para retornar.");
    }
    aux = getch();
}
void MostraCompromissosData (Descritor lista) {
    int aux, aux2, LinhaAtual = 4;
    unsigned long long int Data = 0, Data2;
    no NoAtual = lista.Primeiro;
    system("cls");
    if (!NoAtual) {
        printf("\n Lista vazia.\n\n Pressione qualquer tecla para continuar.");
        desqua(0, 119, 0, 4);
        gotoxy(41, 3);
        aux = getch();
        return;
    }
    aux2 = 1;
    printf("\n Digite a data que deseja consultar: __/__/____");
    desqua(0, 119, 0, 4);
    gotoxy(37, 1); aux = getch()-48; Data += aux*10; gotoxy(37, 1); printf("%d", aux); aux = getch()-48; Data += aux; gotoxy(38, 1); printf("%d", aux);
    gotoxy(40, 1); aux = getch()-48; Data += aux*1000; gotoxy(40, 1); printf("%d", aux); aux = getch()-48; Data += aux*100; gotoxy(41, 1); printf("%d", aux);
    gotoxy(43, 1); aux = getch()-48; Data += aux*10000000; gotoxy(43, 1); printf("%d", aux); gotoxy(44, 1); aux = getch()-48; Data += aux*1000000; gotoxy(44, 1); printf("%d", aux); aux = getch()-48; Data += aux*100000; gotoxy(45, 1); printf("%d", aux); aux = getch()-48; Data += aux*10000; gotoxy(46, 1); printf("%d", aux);
    system("cls");
    desqua(0, 119, 0, 4);
    Data2 = NoAtual->Dia+NoAtual->Mes*100+NoAtual->Ano*10000;
    while (NoAtual && Data2<=Data) {
        if (Data2 == Data) {
            aux2 = 0;
            gotoxy(1, LinhaAtual-3); printf("Data: %.2d/%.2d/%.4d     Hora: %.2d:%.2d          ", NoAtual->Dia, NoAtual->Mes, NoAtual->Ano, NoAtual->Hora, NoAtual->Minuto);
            gotoxy(1, LinhaAtual-2); printf("Descri%c%co: %s", 135, 198, NoAtual->Descricao);
            desqua(0, 119, LinhaAtual, LinhaAtual+4);
            linhor(0, 119, LinhaAtual);
            gotoxy(1, LinhaAtual+1); printf("Pressione qualquer tecla para retornar.");
            LinhaAtual += 4;
        }
        NoAtual = NoAtual->prox;
        if (NoAtual) Data2 = NoAtual->Dia+NoAtual->Mes*100+NoAtual->Ano*10000;
    }
    if (aux2==1) {
        gotoxy(1, 1);
        printf("N%co foi encontrado um comprimisso nessa data.", 198);
        gotoxy(1, 3);
        printf("Pressione qualquer tecla para retornar.");
    }
    aux = getch();
}
void ExcluiCompromissos (Descritor *lista) {
    int esc, tecla;
    do {
        system("cls");
        printf("\n Quais compromissos deseja excluir?\n    Compromissos com uma palavra espec%cfica em sua descri%c%co\n    Compromissos em determinada data\n    Sair desta fun%c%co", 161, 135, 198, 135, 198);
        desqua(0, 119, 0, 29);
        esc = 2;
        gotoxy(1, esc);
        printf("->");
        do {
            tecla = getch();
            switch (tecla) {
                case KEY_UP: if (esc>2) {gotoxy(1, esc); printf("  "); gotoxy(1, --esc); printf("->");} break;
                case KEY_DOWN: if (esc<4) {gotoxy(1, esc); printf("  "); gotoxy(1, ++esc); printf("->");} break;
                case ENTER: if (esc==2) ExcluiCompromissosPalavra(lista); if (esc==3) ExcluiCompromissosData(lista); break;
            }
        } while (tecla != ENTER);
    } while (esc != 4);
}
void ExcluiCompromissosPalavra (Descritor *lista) {
    int aux, LinhaAtual = 4, numero;
    char Termo[81];
    no NoAtual = lista->Primeiro, NoAnterior;
    system("cls");
    if (!NoAtual) {
        printf("\n Lista vazia.\n\n Pressione qualquer tecla para continuar.");
        desqua(0, 119, 0, 4);
        gotoxy(41, 3);
        aux = getch();
        return;
    }
    desqua(0, 119, 0, 4);
    printf("Escreva a palavra que deseja procurar: ");
    fflush(stdin);
    fgets(Termo, 81, stdin);
    fflush(stdin);
    Termo[strlen(Termo)-1] = '\0';
    aux = 0;
    while (NoAtual) {
        if (strstr(NoAtual->Descricao, Termo)!=NULL) {
            aux++;
            gotoxy(1, LinhaAtual-3); printf("                                                                          ");
            gotoxy(1, LinhaAtual-3); printf("%d%c compromisso encontrado com o termo %s", aux, 167, Termo);
            gotoxy(1, LinhaAtual-2); printf("Data: %.2d/%.2d/%.4d     Hora: %.2d:%.2d          ", NoAtual->Dia, NoAtual->Mes, NoAtual->Ano, NoAtual->Hora, NoAtual->Minuto);
            gotoxy(1, LinhaAtual-1); printf("Descri%c%co: %s", 135, 198, NoAtual->Descricao);
            desqua(0, 119, LinhaAtual, LinhaAtual+4);
            linhor(0, 119, LinhaAtual);
            gotoxy(1, LinhaAtual+1); printf("Insira o numero do elemento a ser removido: ");
            LinhaAtual += 4;
        }
        NoAtual = NoAtual->prox;
    }
    if (aux==0) {
        gotoxy(1, 1);
        printf("N%co foi encontrado um compromisso com essa palavra.", 198);
        gotoxy(1, 3);
        printf("Pressione qualquer tecla para retornar.");
    }
    else scanf("%d", &numero);
    
    if (numero==1) {
        ExcluiCompromissoInicioDaLista(lista);
        printf("%cO %d%c compromisso que continha o termo\n%c\"%s\" foi exclu%cdo.", 186, numero, 167, 186, Termo, 161);
        aux = getch();
        return;
    }
    aux = 1;
    NoAnterior = NULL;
    NoAtual = lista->Primeiro;
    while (aux<=numero && NoAtual) {
        if (aux == numero) {
            NoAnterior->prox = NoAtual->prox;
            free(NoAtual);
            printf("%cO %d%c compromisso que continha o termo\n%c\"%s\" foi exclu%cdo.", 186, numero, 167, 186, Termo, 161);
            aux = getch();
            return;
        }
        aux++;
        NoAnterior = NoAtual;
        NoAtual = NoAtual->prox;
    }
    aux = getch();
}
void ExcluiCompromissosData (Descritor *lista) {
    int aux, dia = 0, mes = 0, ano = 0;
    no NoAtual = lista->Primeiro, NoAnterior;
    system("cls");
    if (!NoAtual) {
        printf("\n Lista vazia.\n\n Pressione qualquer tecla para continuar.");
        desqua(0, 119, 0, 4);
        gotoxy(41, 3);
        aux = getch();
        return;
    }
    desqua(0, 119, 0, 4);
    printf("Insira a data cujos compromissos deseja excluir: __/__/____");
    gotoxy(50, 1); aux = getch()-48; dia += aux*10; gotoxy(50, 1); printf("%d", aux); aux = getch()-48; dia += aux; gotoxy(51, 1); printf("%d", aux);
    gotoxy(53, 1); aux = getch()-48; mes += aux*10; gotoxy(53, 1); printf("%d", aux); aux = getch()-48; mes += aux; gotoxy(54, 1); printf("%d", aux);
    gotoxy(56, 1); aux = getch()-48; ano += aux*1000; gotoxy(56, 1); printf("%d", aux); aux = getch()-48; ano += aux*100; gotoxy(57, 1); printf("%d", aux); aux = getch()-48; ano += aux*10; gotoxy(58, 1); printf("%d", aux); aux = getch()-48; ano += aux; gotoxy(59, 1); printf("%d", aux);
    desqua(0, 119, 4, 9);
    linhor(0, 119, 4);
    gotoxy(1, 5);
    aux = 0;
    while (NoAtual && NoAtual->Dia == dia && NoAtual->Mes == mes && NoAtual->Ano == ano) {
        ExcluiCompromissoInicioDaLista(lista);
        NoAtual = lista->Primeiro;
        aux = 1;
    }
    while (NoAtual) {
        NoAnterior = NoAtual;
        NoAtual = NoAtual->prox;
        no NoAux = NoAtual;
        if (NoAtual && NoAux->Dia == dia && NoAux->Mes == mes && NoAux->Ano == ano) {
            free(NoAux);
            NoAnterior->prox = NoAtual->prox;
            aux = 1;
        }
    }
    if (aux == 1) printf("Todos os compromissos do dia %.2d/%.2d/%.4d foram exclu%cdos da agenda.", dia, mes, ano, 161);
    else printf("N%co foi encontrado um compromisso nessa data.", 198);
    aux = getch();
}
void ExcluiCompromissoInicioDaLista (Descritor *lista) {
    if (lista) {
        no aux = lista->Primeiro;
        lista->Primeiro = aux->prox;
        free(aux);
    }
}
void AlteraCompromissos (Descritor *lista) {
    int esc, tecla;
    do {
        system("cls");
        printf("\n Quais compromissos deseja alterar?\n    Compromissos com uma palavra espec%cfica em sua descri%c%co\n    Compromissos em determinada data\n    Sair desta fun%c%co", 161, 135, 198, 135, 198);
        desqua(0, 119, 0, 29);
        esc = 2;
        gotoxy(1, esc);
        printf("->");
        do {
            tecla = getch();
            switch (tecla)
            {
                case KEY_UP: if (esc>2) {gotoxy(1, esc); printf("  "); gotoxy(1, --esc); printf("->");} break;
                case KEY_DOWN: if (esc<4) {gotoxy(1, esc); printf("  "); gotoxy(1, ++esc); printf("->");} break;
                case ENTER: if (esc==2) AlteraCompromissosPalavra(lista); if (esc==3) AlteraCompromissosData(lista); break;
            }
        } while (tecla != ENTER);
    } while (esc != 4);
}
void AlteraCompromissosPalavra (Descritor *lista) {
    int aux, LinhaAtual = 4, numero, aux2;
    char Termo[81];
    no NoAtual = lista->Primeiro;
    system("cls");
    if (!NoAtual) {
        printf("\n Lista vazia.\n\n Pressione qualquer tecla para continuar.");
        desqua(0, 119, 0, 4);
        gotoxy(41, 3);
        aux = getch();
        return;
    }
    desqua(0, 119, 0, 4);
    printf("Insira a palavra que deseja buscar: ");
    fflush(stdin);
    fgets(Termo, 81, stdin);
    fflush(stdin);
    Termo[strlen(Termo)-1] = '\0';
    aux = 0;
    while (NoAtual) {
        if (strstr(NoAtual->Descricao, Termo)!=NULL) {
            aux++;
            gotoxy(1, LinhaAtual-3); printf("                                                                          ");
            gotoxy(1, LinhaAtual-3); printf("%d%c compromisso encontrado com o termo %s", aux, 167, Termo);
            gotoxy(1, LinhaAtual-2); printf("Data: %.2d/%.2d/%.4d     Hora: %.2d:%.2d          ", NoAtual->Dia, NoAtual->Mes, NoAtual->Ano, NoAtual->Hora, NoAtual->Minuto);
            gotoxy(1, LinhaAtual-1); printf("Descri%c%co: %s", 135, 198, NoAtual->Descricao);
            desqua(0, 119, LinhaAtual, LinhaAtual+4);
            linhor(0, 119, LinhaAtual);
            gotoxy(1, LinhaAtual+1); printf("Insira o numero do elemento a ser alterado: ");
            LinhaAtual += 4;
        }
        NoAtual = NoAtual->prox;
    }
    if (aux==0) {
        gotoxy(1, 1);
        printf("N%co foi encontrado um compromisso com essa palavra.", 198);
        gotoxy(1, 3);
        printf("Pressione qualquer tecla para retornar.");
    }
    else scanf("%d", &numero);
    NoAtual = lista->Primeiro;
    while (numero>=1 && NoAtual) {
        if (numero == 1) {
            do {
                system("cls");
                printf("\n Data: %.2d/%.2d/%.2d     Hor%crio: %.2d:%.2d\n Descri%c%co: %s\n\n O que deseja fazer?\n    Alterar data\n    Alterar hor%crio\n    Alterar descri%c%co\n    Sair", NoAtual->Dia, NoAtual->Mes, NoAtual->Ano, 160, NoAtual->Hora, NoAtual->Minuto, 135, 198, NoAtual->Descricao, 160, 135, 198);
                desqua(0, 119, 0, 9);
                LinhaAtual = 5;
                gotoxy(1, LinhaAtual);
                printf("->");
                do {
                    aux = getch();
                    switch (aux) {
                        case KEY_UP: if (LinhaAtual>5) {gotoxy(1, LinhaAtual); printf("  "); gotoxy(1, --LinhaAtual); printf("->");} break;
                        case KEY_DOWN: if (LinhaAtual<8) {gotoxy(1, LinhaAtual); printf("  "); gotoxy(1, ++LinhaAtual); printf("->");} break;
                        case ENTER: switch (LinhaAtual) {
                            case 5: desqua(0, 119, 9, 13); linhor(0, 119, 9); gotoxy(1, 10); printf("Insira a nova data:  __/__/____"); gotoxy(22, 10); aux2 = getch()-48; gotoxy(22, 10); printf("%d", aux2); NoAtual->Dia = aux2*10; aux2 = getch()-48; gotoxy(23, 10); printf("%d/", aux2); NoAtual->Dia += aux2; aux2 = getch()-48; NoAtual->Mes = aux2*10; gotoxy(25, 10); printf("%d", aux2); aux2 = getch()-48; NoAtual->Mes += aux2; gotoxy(26, 10); printf("%d/", aux2); aux2 = getch()-48; NoAtual->Ano = aux2*1000; gotoxy(28, 10); printf("%d", aux2); aux2 = getch()-48; NoAtual->Ano += aux2*100; gotoxy(29, 10); printf("%d", aux2); aux2 = getch()-48; NoAtual->Ano += aux2*10; gotoxy(30, 10); printf("%d", aux2); aux2 = getch()-48; NoAtual->Ano += aux2; gotoxy(1, 12); printf("Data alterada. Pressione qualquer bot%co para continuar.", 198); aux2 = getch(); break;
                            case 6: desqua(0, 119, 9, 13); linhor(0, 119, 9); gotoxy(1, 10); printf("Insira o novo hor%crio: __:__", 160); gotoxy(24, 10); aux2 = getch()-48; NoAtual->Hora = aux2*10; gotoxy(24, 10); printf("%d", aux2); aux2 = getch()-48; NoAtual->Hora += aux2; gotoxy(25, 10); printf("%d:", aux2); aux2 = getch()-48; NoAtual->Minuto = aux2*10; gotoxy(27, 10); printf("%d", aux2); aux2 = getch()-48; NoAtual->Minuto += aux2; gotoxy(28, 10); printf("%d", aux2); gotoxy(1, 12); printf("Hor%crio alterado. Pressione qualquer tecla para continuar.", 160); aux2 = getch(); break;
                            case 7: desqua(0, 119, 0, 13); linhor(0, 119, 9); gotoxy(1, 10); printf("Insira a nova descri%c%co: ", 135, 198); fflush(stdin); fgets(NoAtual->Descricao, 81, stdin); NoAtual->Descricao[strlen(NoAtual->Descricao)-1] = '\0'; gotoxy(1, 12); printf("Descri%c%co alterada. Pressione qualquer tecla para continuar.", 135, 198); aux2 = getch(); break;
                            case 8: return;
                        }break;
                    }
                } while (aux!=ENTER);
            } while (numero!=8);
            aux = getch();
            return;
        }
        NoAtual = NoAtual->prox;
        numero--;
    }

    aux = getch();
}
void AlteraCompromissosData (Descritor *lista) {
    int aux, aux2, numero, LinhaAtual = 4, dia, mes, ano;
    no NoAtual = lista->Primeiro;
    system("cls");
    if (!NoAtual) {
        printf("\n Lista vazia.\n\n Pressione qualquer tecla para continuar.");
        desqua(0, 119, 0, 4);
        gotoxy(41, 3);
        aux = getch();
        return;
    }
    desqua(0, 119, 0, 4);
    printf("Insira a data cujos compromissos deseja alterar: __/__/____");
    gotoxy(50, 1); aux = getch()-48; dia = aux*10; gotoxy(50, 1); printf("%d", aux); aux = getch()-48; dia += aux; gotoxy(51, 1); printf("%d/", aux);
    aux = getch()-48; mes = aux*10; gotoxy(53, 1); printf("%d", aux); aux = getch()-48; mes += aux; gotoxy(54, 1); printf("%d/", aux);
    aux = getch()-48; ano = aux*1000; gotoxy(56, 1); printf("%d", aux); aux = getch()-48; ano += aux*100; gotoxy(57, 1); printf("%d", aux); aux = getch()-48; ano += aux*10; gotoxy(58, 1); printf("%d", aux); aux = getch()-48; ano += aux; gotoxy(59, 1); printf("%d", aux);
    system("cls");
    desqua(0, 119, 0, 4);
    aux = 0;
    while (NoAtual) {
        if (dia == NoAtual->Dia && mes == NoAtual->Mes && ano == NoAtual->Ano) {
            aux++;
            gotoxy(1, LinhaAtual-3); printf("                                                                          ");
            gotoxy(1, LinhaAtual-3); printf("%d%c compromisso encontrado na data %.2d/%.2d/%.2d", aux, 167, dia, mes, ano);
            gotoxy(1, LinhaAtual-2); printf("Data: %.2d/%.2d/%.4d     Hora: %.2d:%.2d          ", NoAtual->Dia, NoAtual->Mes, NoAtual->Ano, NoAtual->Hora, NoAtual->Minuto);
            gotoxy(1, LinhaAtual-1); printf("Descri%c%co: %s", 135, 198, NoAtual->Descricao);
            desqua(0, 119, LinhaAtual, LinhaAtual+4);
            linhor(0, 119, LinhaAtual);
            gotoxy(1, LinhaAtual+1); printf("Insira o numero do elemento a ser alterado: ");
            LinhaAtual += 4;
        }
        NoAtual = NoAtual->prox;
    }
    if (!aux) {
        gotoxy(1, 1);
        printf("N%co foi encontrado um comprimisso nessa data.", 198);
        gotoxy(1, 3);
        printf("Pressione qualquer tecla para retornar.");
        aux = getch();
        return;
    }
    else scanf("%d", &numero);
    NoAtual = lista->Primeiro;
    while (NoAtual && numero>=1) {
        if (numero == 1) {
            do {
                system("cls");
                printf("\n Data: %.2d/%.2d/%.2d     Hor%crio: %.2d:%.2d\n Descri%c%co: %s\n\n O que deseja fazer?\n    Alterar data\n    Alterar hor%crio\n    Alterar descri%c%co\n    Sair", NoAtual->Dia, NoAtual->Mes, NoAtual->Ano, 160, NoAtual->Hora, NoAtual->Minuto, 135, 198, NoAtual->Descricao, 160, 135, 198);
                desqua(0, 119, 0, 9);
                LinhaAtual = 5;
                gotoxy(1, LinhaAtual);
                printf("->");
                do {
                    aux = getch();
                    switch (aux) {
                        case KEY_UP: if (LinhaAtual>5) {gotoxy(1, LinhaAtual); printf("  "); gotoxy(1, --LinhaAtual); printf("->");} break;
                        case KEY_DOWN: if (LinhaAtual<8) {gotoxy(1, LinhaAtual); printf("  "); gotoxy(1, ++LinhaAtual); printf("->");} break;
                        case ENTER: switch (LinhaAtual) {
                            case 5: desqua(0, 119, 9, 13); linhor(0, 119, 9); gotoxy(1, 10); printf("Insira a nova data:  __/__/____"); gotoxy(22, 10); aux2 = getch()-48; gotoxy(22, 10); printf("%d", aux2); NoAtual->Dia = aux2*10; aux2 = getch()-48; gotoxy(23, 10); printf("%d/", aux2); NoAtual->Dia += aux2; aux2 = getch()-48; NoAtual->Mes = aux2*10; gotoxy(25, 10); printf("%d", aux2); aux2 = getch()-48; NoAtual->Mes += aux2; gotoxy(26, 10); printf("%d/", aux2); aux2 = getch()-48; NoAtual->Ano = aux2*1000; gotoxy(28, 10); printf("%d", aux2); aux2 = getch()-48; NoAtual->Ano += aux2*100; gotoxy(29, 10); printf("%d", aux2); aux2 = getch()-48; NoAtual->Ano += aux2*10; gotoxy(30, 10); printf("%d", aux2); aux2 = getch()-48; NoAtual->Ano += aux2; gotoxy(1, 12); printf("Data alterada. Pressione qualquer bot%co para continuar.", 198); aux2 = getch(); break;
                            case 6: desqua(0, 119, 9, 13); linhor(0, 119, 9); gotoxy(1, 10); printf("Insira o novo hor%crio: __:__", 160); gotoxy(24, 10); aux2 = getch()-48; NoAtual->Hora = aux2*10; gotoxy(24, 10); printf("%d", aux2); aux2 = getch()-48; NoAtual->Hora += aux2; gotoxy(25, 10); printf("%d:", aux2); aux2 = getch()-48; NoAtual->Minuto = aux2*10; gotoxy(27, 10); printf("%d", aux2); aux2 = getch()-48; NoAtual->Minuto += aux2; gotoxy(28, 10); printf("%d", aux2); gotoxy(1, 12); printf("Hor%crio alterado. Pressione qualquer tecla para continuar.", 160); aux2 = getch(); break;
                            case 7: desqua(0, 119, 0, 13); linhor(0, 119, 9); gotoxy(1, 10); printf("Insira a nova descri%c%co: ", 135, 198); fflush(stdin); fgets(NoAtual->Descricao, 81, stdin); NoAtual->Descricao[strlen(NoAtual->Descricao)-1] = '\0'; gotoxy(1, 12); printf("Descri%c%co alterada. Pressione qualquer tecla para continuar.", 135, 198); aux2 = getch(); break;
                            case 8: return;
                        }break;
                    }
                } while (aux!=ENTER);
            } while (numero!=8);
            aux = getch();
            return;
        }
        NoAtual = NoAtual->prox;
        numero--;
    }
    aux = getch();
}
void InsereCompromisso (Descritor *lista) {
    int str[4];
    struct Compromisso NovoCompromisso;
    linhor(0, 119, 9);
    gotoxy(1, 10); printf("Favor inserir os dados do novo compromisso:");
    gotoxy(1, 12); printf("Data: __/__/____     Hora: __:__");
    gotoxy(1, 14); printf("Descri%c%co: ________________________________________________________________________________", 135, 198);
    gotoxy(7, 12); str[0] = getch()-48; gotoxy(7, 12); printf("%d", str[0]); str[1] = getch()-48; gotoxy(8, 12); printf("%d", str[1]); NovoCompromisso.Dia = str[0]*10+str[1];
    gotoxy(10, 12); str[0] = getch()-48; gotoxy(10, 12); printf("%d", str[0]); str[1] = getch()-48; gotoxy(11, 12); printf("%d", str[1]); NovoCompromisso.Mes = str[0]*10+str[1];
    gotoxy(13, 12); str[0] = getch()-48; gotoxy(13, 12); printf("%d", str[0]); str[1] = getch()-48; gotoxy(14, 12); printf("%d", str[1]); str[2] = getch()-48; gotoxy(15, 12); printf("%d", str[2]); str[3] = getch()-48; gotoxy(16, 12); printf("%d", str[3]); NovoCompromisso.Ano = str[0]*1000+str[1]*100+str[2]*10+str[3];
    gotoxy(28, 12); str[0] = getch()-48; gotoxy(28, 12); printf("%d", str[0]); str[1] = getch()-48; gotoxy(29, 12); printf("%d", str[1]); NovoCompromisso.Hora = str[0]*10+str[1];
    gotoxy(31, 12); str[0] = getch()-48; gotoxy(31, 12); printf("%d", str[0]); str[1] = getch()-48; gotoxy(32, 12); printf("%d", str[1]); NovoCompromisso.Minuto = str[0]*10+str[1];
    gotoxy(12, 14); fgets(NovoCompromisso.Descricao, 81, stdin);
    fflush(stdin);
    NovoCompromisso.Descricao[strlen(NovoCompromisso.Descricao)-1] = '\0';
    if (lista->numele == 0 || NovoCompromisso.Dia+NovoCompromisso.Mes*100+NovoCompromisso.Ano*10000<lista->Primeiro->Dia+lista->Primeiro->Mes*100+lista->Primeiro->Ano*10000) InsereInicioDaLista(lista, &NovoCompromisso);
    else InsereOrdenadamenteNaLista(lista, &NovoCompromisso);
    gotoxy(1, 20);
    printf("Compromisso agendado.");
    str[0] = getch();
}
void InsereInicioDaLista (Descritor *lista, struct Compromisso *Dados) {
    no aux = (struct Compromisso*) malloc(sizeof(struct Compromisso));
    aux->Dia = Dados->Dia;
    aux->Mes = Dados->Mes;
    aux->Ano = Dados->Ano;
    aux->Hora = Dados->Hora;
    aux->Minuto = Dados->Minuto;
    strcpy(aux->Descricao, Dados->Descricao);
    aux->prox = lista->Primeiro;
    lista->Primeiro = aux;
    if (lista->numele == 0) lista->Ultimo = aux;
    lista->numele++;
}
void InsereFinalDaLista (Descritor *lista, struct Compromisso *Dados) {
    no aux = (struct Compromisso*) malloc(sizeof(struct Compromisso));
    aux->Dia = Dados->Dia;
    aux->Mes = Dados->Mes;
    aux->Ano = Dados->Ano;
    aux->Hora = Dados->Hora;
    aux->Minuto = Dados->Minuto;
    strcpy(aux->Descricao, Dados->Descricao);
    aux->prox = NULL;
    if (lista->numele == 0) lista->Primeiro = aux;
    else lista->Ultimo->prox = aux;
    lista->Ultimo = aux;
    lista->numele++;
}
void InsereOrdenadamenteNaLista (Descritor *lista, struct Compromisso *Dados) {
    no aux1 = lista->Primeiro, r;
    no aux = (struct Compromisso*) malloc(sizeof(struct Compromisso));
    aux->Dia = Dados->Dia;
    aux->Mes = Dados->Mes;
    aux->Ano = Dados->Ano;
    aux->Hora = Dados->Hora;
    aux->Minuto = Dados->Minuto;
    strcpy(aux->Descricao, Dados->Descricao);
    if (Dados->Dia+Dados->Hora*100+Dados->Ano*10000 < aux1->Dia+aux1->Mes*100+aux1->Ano*10000) {
        InsereInicioDaLista(lista, aux);
        return;
    }
    else if (aux1->Dia+aux1->Mes*100+aux1->Ano*10000 == Dados->Dia+Dados->Mes*100+Dados->Ano*10000 && Dados->Minuto+Dados->Hora*100 <= aux1->Minuto+aux1->Hora*100) {
            InsereInicioDaLista(lista, aux);
            return;
        }
    while (aux1 != NULL && aux1->Dia+aux1->Mes*100+aux1->Ano*10000 < Dados->Dia+Dados->Mes*100+Dados->Ano*10000) {
        r = aux1;
        aux1 = aux1->prox;
    }
    while (aux1 != NULL && aux1->Dia+aux1->Mes*100+aux1->Ano*10000 == Dados->Dia+Dados->Mes*100+Dados->Ano*10000 && aux1->Minuto+aux1->Hora*100 < Dados->Minuto+Dados->Hora*100) {
        r = aux1;
        aux1 = aux1->prox;
    }
    aux->prox = aux1;
    r->prox = aux;
    if (aux1 == NULL) lista->Ultimo = aux;
    lista->numele++;
}
void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void desqua (int xe, int xd, int ys, int yi) {
    int cxe;
    gotoxy(xe, ys); printf("%c", 201);
    gotoxy(xe, yi); printf("%c", 200);
    gotoxy(xd, ys); printf("%c", 187);
    gotoxy(xd, yi); printf("%c", 188);
    gotoxy(xe+1, ys);
    for (cxe=xe+1; cxe<xd; cxe++) printf("%c", 205);
    gotoxy(xe+1, yi);
    for (cxe=xe+1; cxe<xd; cxe++) printf("%c", 205);
    for (ys++; ys<yi; ys++) {
        gotoxy(xe, ys); printf("%c", 186);
        gotoxy(xd, ys); printf("%c", 186);
    }
    gotoxy(1, 1);
}
void linver (int x, int ys, int yi) {
    gotoxy(x, ys);
    printf("%c", 203);
    for (ys++; ys<yi; ys++) {
        gotoxy(x, ys);
        printf("%c", 186);
    }
    gotoxy(x, yi);
    printf("%c", 202);
}
void linhor (int xe, int xd, int y) {
    gotoxy(xe, y);
    printf("%c", 204);
    for (xe++; xe<xd; xe++) printf("%c", 205);
    printf("%c", 185);
}
void inter (int x, int y) {
    gotoxy(x, y);
    printf("%c", 206);
}
