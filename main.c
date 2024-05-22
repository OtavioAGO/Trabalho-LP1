#include <stdio.h>
#include <stdlib.h>
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define SC "\e[0m"
#define altura 16
#define largura 32
#define qtdCanos 3
 typedef struct{
    int x,y;
 }pos;
pos passaro;
pos canos[3];

int bateu(){
    if(passaro.y == 15){
        return 0;
    }
    for(int i = 0; i < qtdCanos; i++){
        if ((passaro.x < x+2 && passaro.x > x-2) && (passaro.y ))
    }
}
int main()
{

    return 0;
}
