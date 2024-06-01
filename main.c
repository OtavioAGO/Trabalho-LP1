#include <stdio.h>+
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define SC "\e[0m"
#define altura 16
#define largura 32
#define qtdCanos 3
 typedef struct{
    int x,y;
 }pos;
 struct jogador{
    char nome[20];
    int pontos;
 };
pos passaro;
pos canos[3];
void desenhar(){
    char buff[5000];
    strcpy(buff, "\e[17A" );
    for(int y = 0; y <= altura; y++){
        for(int x = 0; x <= largura; x++){
            if (x == 0 || y == 0 || x == largura || y == altura){// BORDAS DA TELA
                strcat(buff, SC "[]");
                continue;
            }
            if(canos)

            if(passaro.y == y&&passaro.x == x){
                strcat(buff, YEL "O>");
            }
            else if(passaro.y == y &&passaro.x == x +1){
                strcat(buff, YEL " (");
            }
            else if(passaro.y == y -1 &&passaro.x == x){
                strcat(buff, YEL "@/");
            }
            else if(passaro.y == y -1 &&passaro.x == x +1){
                strcat(buff, YEL "\\@");
            }
            else{
                strcat(buff, SC "  ");
            }
            fim:;
        }
        printf("\n");
    }
    printf(buff);
}
int bateu(){
    if(passaro.y == 15 || passaro.y == 0){
        return 0;
    }
    for(int i = 0; i < qtdCanos; i++){
        if ((passaro.x < canos[i].x+2 && passaro.x > canos[i].x-2) && (passaro.y < canos[i].y-2 || passaro.y >  canos[i].y+2 )){
            return 0;
        }
    }
}
void posicionarCanos(){
    for(int i =0 ; i < qtdCanos; i++){
        if(canos[i].x == -1){
            if(i == 0){
                canos[i].x == canos[2].x +15;
            }
            else{
                canos[i].x == canos[i-1].x + 15;
            }
            canos[i].y = (rand()%7) + 5;
        }
    }
}
int main()
{
    SetConsoleTitle("PASSARO DEFORMADO QUE PULA");
    passaro.x = 5;
    passaro.y = 10;
    char ch;
    for(int i =0 ; i < qtdCanos; i++){
        canos[i].x = 25 + 15 * i;
        canos[i].y = (rand()%7)+5;
    }
    struct jogador j1;
    int frame = 0;
    desenhar();
    system("pause>nul");
    while(1){
        if(GetAsyncKeyState(VK_SPACE)){
            passaro.y -= 2;
        }
        if (frame == 2){
            passaro.y++;
            for(int i = 0; i < qtdCanos; i++){
                canos[i].x--;
                if(canos[i].x == passaro.x){
                    j1.
                }
            }
            frame = 0;
        }
        bateu();

        desenhar();

        posicionarCanos();

        frame++;

        Sleep(100);
    }

    return 0;
}
