#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define SC "\e[0m"
#define altura 16
#define largura 32
#define qtdCanos 3
#define MAX_LINE_LENGTH 100

typedef struct {
    int x, y;
} pos;

typedef struct {
    char nome[20];
    int pontos;
} Jogador;

pos passaro;
pos canos[3];

enum {
    BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY,
    DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

enum {
    _BLACK = 0, _BLUE = 16, _GREEN = 32, _CYAN = 48, _RED = 64,
    _MAGENTA = 80, _BROWN = 96, _LIGHTGRAY = 112, _DARKGRAY = 128, _LIGHTBLUE = 144,
    _LIGHTGREEN = 160, _LIGHTCYAN = 176, _LIGHTRED = 192, _LIGHTMAGENTA = 208, _YELLOW = 224, _WHITE = 240
};

void reposicionarCursor() {
    COORD coord = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void desenhar(int pontos) {
    reposicionarCursor();
    char buff[5000];
    strcpy(buff, "");
    char pontuacao[50];
    sprintf(pontuacao, "Pontos: %d\n", pontos);
    strcat(buff, pontuacao);

    for (int y = 0; y <= altura; y++) {
        for (int x = 0; x <= largura; x++) {
            if (x == 0 || y == 0 || x == largura || y == altura) { // BORDAS DA TELA
                strcat(buff, SC "[]");
                continue;
            }
            for (int i = 0; i < qtdCanos; i++) {
                if (canos[i].x >= x - 1 && canos[i].x <= x + 1 && (canos[i].y == y - 3 || canos[i].y == y + 3)) {
                    strcat(buff, GRN "||");
                    goto fim;
                } else if (canos[i].x == x - 1 && canos[i].y == y - 4) {
                    strcat(buff, GRN "|/");
                    goto fim;
                } else if (canos[i].x == x && (canos[i].y <= y - 4 || canos[i].y >= y + 4)) {
                    strcat(buff, GRN "||");
                    goto fim;
                } else if (canos[i].x == x + 1 && canos[i].y == y - 4) {
                    strcat(buff, GRN "\\|");
                    goto fim;
                } else if (canos[i].x == x - 1 && canos[i].y == y + 4) {
                    strcat(buff, GRN "|\\");
                    goto fim;
                } else if (canos[i].x == x + 1 && canos[i].y == y + 4) {
                    strcat(buff, GRN "/|");
                    goto fim;
                } else if (canos[i].x == x - 1 && (canos[i].y == y - 5 || canos[i].y == y + 5)) {
                    strcat(buff, GRN "| ");
                    goto fim;
                } else if (canos[i].x == x + 1 && (canos[i].y == y - 5 || canos[i].y == y + 5)) {
                    strcat(buff, GRN " |");
                    goto fim;
                }
            }
            if (passaro.y == y && passaro.x == x) {
                strcat(buff, YEL "O>");
            } else if (passaro.y == y && passaro.x == x + 1) {
                strcat(buff, YEL " (");
            } else if (passaro.y == y - 1 && passaro.x == x) {
                strcat(buff, YEL "@/");
            } else if (passaro.y == y - 1 && passaro.x == x + 1) {
                strcat(buff, YEL "\\@");
            } else {
                strcat(buff, SC "  ");
            }
        fim:;
        }
        strcat(buff, "\n");
    }
    printf(buff);
}

bool bateu() {
    if (passaro.y == 15 || passaro.y == 0) {
        return false;
    }
    for (int i = 0; i < qtdCanos; i++) {
        if (((passaro.x < canos[i].x + 2 && passaro.x > canos[i].x - 2) || (passaro.x + 1 < canos[i].x + 2 && passaro.x + 1 > canos[i].x - 2)) && (passaro.y < canos[i].y - 2 || passaro.y > canos[i].y + 2 || passaro.y - 1 < canos[i].y - 2 || passaro.y - 1 > canos[i].y + 2)) {
            return false;
        }
    }
    return true;
}

void posicionarCanos() {
    for (int i = 0; i < qtdCanos; i++) {
        if (canos[i].x == -1) {
            if (i == 0) {
                canos[i].x = canos[2].x + 15;
            } else {
                canos[i].x = canos[i - 1].x + 15;
            }
            canos[i].y = (rand() % 7) + 5;
        }
    }
}

void textColor(int letra, int fundo) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), letra + fundo);
}

void linhaCol(int lin, int col) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD) { col - 1, lin - 1 });
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void box(int lin1, int col1, int lin2, int col2) {
    int i, j, tamlin, tamcol;

    // tamanho da caixa
    tamlin = lin2 - lin1;
    tamcol = col2 - col1;

    // bordas superior, inferior
    for (i = col1; i <= col2; i++) {
        linhaCol(lin1, i);
        printf("%c", 196);
        linhaCol(lin2, i);
        printf("%c", 196);
    }

    // bordas esquerda, direita
    for (i = lin1; i <= lin2; i++) {
        linhaCol(i, col1);
        printf("%c", 179);
        linhaCol(i, col2);
        printf("%c", 179);
    }

    // Preencher a caixa com espaços
    for (i = lin1 + 1; i < lin2; i++) {
        for (j = col1 + 1; j < col2; j++) {
            linhaCol(i, j);
            printf(" ");
        }
    }

    // Desenhar os cantos
    linhaCol(lin1, col1);
    printf("%c", 218);
    linhaCol(lin1, col2);
    printf("%c", 191);
    linhaCol(lin2, col1);
    printf("%c", 192);
    linhaCol(lin2, col2);
    printf("%c", 217);
}

void mostrarTelaMorte() {
    system("cls");
    printf("\t\n    VOCE MORREU    \n");
    Sleep(2000);
    system("cls");
}

int menu(int lin1, int col1, int qtd, char lista[][40]) {
    int opc = 2, lin2, col2, linha, i, tamMaxItem, tecla; // começa na segunda opção

    // Encontrar o comprimento máximo dos itens do menu
    tamMaxItem = strlen(lista[0]);
    for (i = 1; i < qtd; i++) {
        if (strlen(lista[i]) > tamMaxItem) {
            tamMaxItem = strlen(lista[i]);
        }
    }

    lin2 = lin1 + (qtd * 2 + 2);
    col2 = col1 + tamMaxItem + 4;

    // caixa
    textColor(BLACK, _GREEN);
    setlocale(LC_ALL, "C");
    box(lin1, col1, lin2, col2);
    setlocale(LC_ALL, "");

    // Loop do menu
    while (1) {
        linha = lin1 + 2;
        for (i = 0; i < qtd; i++) {
            if (i + 1 == opc) textColor(BLACK, _WHITE);
            else textColor(WHITE, _GREEN);
            linhaCol(linha, col1 + 2);
            printf("%s", lista[i]);
            linha += 2;
        }

        // Aguardar entrada do usuário
        linhaCol(1, 1);
        tecla = getch();

        // Manipular entrada do usuário
        if (tecla == 27) { // Tecla ESC
            opc = 0;
            break;
        } else if (tecla == 13) { // Tecla ENTER
            break;
        } else if (tecla == 72) { // Seta para cima
            opc--;
            if (opc == 1) opc--; // Pular a primeira opção
            if (opc < 2) opc = qtd;
        } else if (tecla == 80) { // Seta para baixo
            opc++;
            if (opc == 1) opc++; // Pular a primeira opção
            if (opc > qtd) opc = 2;
        }
    }
    return opc;
}

Jogador* lerPlacar(const char* nomeArquivo, int* qtdLinhas) {
    FILE* ptr = fopen(nomeArquivo, "r");
    if (ptr == NULL) {
        printf("Erro ao abrir o arquivo de placar.\n");
        return NULL;
    }

    Jogador* placar = NULL;
    *qtdLinhas = 0;
    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, ptr) != NULL) {
        placar = realloc(placar, (*qtdLinhas + 1) * sizeof(Jogador));
        if (placar == NULL) {
            printf("Erro ao alocar memória.\n");
            exit(1);
        }
        sscanf(buffer, "%s %d", placar[*qtdLinhas].nome, &placar[*qtdLinhas].pontos);
        (*qtdLinhas)++;
    }
    fclose(ptr);
    return placar;
}

void liberarPlacar(Jogador* placar) {
    free(placar);
}

void salvarPontuacao(const char* nomeArquivo, const char* nomeJogador, int pontos) {
    FILE* ptr = fopen(nomeArquivo, "a");
    if (ptr == NULL) {
        printf("Erro ao abrir o arquivo de placar.\n");
        return;
    }
    fprintf(ptr, "%s %d\n", nomeJogador, pontos);
    fclose(ptr);
}

int compararJogadores(const void* a, const void* b) {
    Jogador* jogadorA = (Jogador*)a;
    Jogador* jogadorB = (Jogador*)b;
    return jogadorB->pontos - jogadorA->pontos;
}

int main(){
    int qtdLinhas;
    Jogador* placar = lerPlacar("placar.txt", &qtdLinhas);
    srand(time(NULL));
    SetConsoleTitle("Certamente não é o Flappy Bird");
    int opc;
    FILE *ptr;
    char lista[4][40] = { "Flappy Bird","Jogar", "Rank", "Sair" };

    setlocale(LC_ALL, "");
    while (true) {
        opc = menu(10, 10, 4, lista);
        if (opc == 2) {
            system("@cls||clear");
            system("color 0F");
            passaro.x = 5;
            passaro.y = 10;
            for (int i = 0; i < qtdCanos; i++) {
                canos[i].x = 25 + 15 * i;
                canos[i].y = (rand() % 7) + 5;
            }
            Jogador j1;  // Inicialize a estrutura jogador
            j1.pontos = 0;      // Inicialize a pontuação

            printf("Digite seu nome: ");
            scanf("%s", j1.nome); // Recebe o nome do jogador

            // Limpar a tela após a entrada do nome do jogador
            system("@cls||clear");

            for (int i = 0; i <= altura; i++) // ABRE A TELA PRO JOGO
            {
                printf("\n");
            }
            int frame = 0;
            desenhar(j1.pontos);
            system("pause>nul");
            while (1) {
                if (bateu()) {
                    if (GetAsyncKeyState(VK_UP)) {
                        passaro.y -= 2;
                    }
                    if (frame == 2) {
                        passaro.y++;
                        for (int i = 0; i < qtdCanos; i++) {
                            canos[i].x--;
                            if (canos[i].x == passaro.x) {
                                j1.pontos += 1; // Incrementa a pontuação
                            }
                        }
                        frame = 0;
                    }
                    desenhar(j1.pontos);
                    posicionarCanos();
                    frame++;
                    Sleep(100);
                } else {
                    while (passaro.y < 32) {
                        passaro.y++;
                        desenhar(j1.pontos); // Desenha o cenário novamente com a pontuação
                        posicionarCanos(); // Atualiza os canos
                        Sleep(100);
                    }
                    mostrarTelaMorte();
                    salvarPontuacao("placar.txt", j1.nome, j1.pontos); // Salva a pontuação
                    break;
                }
            }
            system("@cls||clear");
            continue;
        } else if (opc == 3) {
            system("@cls||clear");
            system("color 0F");
            Jogador* placar = lerPlacar("placar.txt", &qtdLinhas);
            if (placar != NULL) {
                qsort(placar, qtdLinhas, sizeof(Jogador), compararJogadores);
                for (int i = 0; i < qtdLinhas; i++) {
                    printf("%d. %s %d - Pontos\n", i + 1, placar[i].nome, placar[i].pontos); // Adicione a numeração
                }
                liberarPlacar(placar);
            } else {
                printf("Nenhuma pontuação disponível.\n");
            }
            printf("Pressione qualquer tecla para voltar ao menu");
            getch();
            system("@cls||clear");
            continue;
        } else if (opc == 4) {
            break;
        }
    }

    textColor(WHITE, _BLACK);
    linhaCol(24, 1);
    printf("");
}
