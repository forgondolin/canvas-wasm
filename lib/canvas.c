// retornar círculos para js
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <emscripten.h>

#define NUM_CIRCLES 100 

struct Circle {
 int x;
 int y;
 int r;
 int cr;  //vermelho
 int cg;  //verde
 int cb;  //azul        
};

//animação do círculo
struct CircleAnimationData {
 int x;
 int y;
 int r;
 int xv;  //velocidade de x
 int yv;  //velocidade de y
 int xd;  //direção x (booleano)
 int yd;  //direção y (booleano)
};

struct Circle circle[NUM_CIRCLES];
struct CircleAnimationData animationData[NUM_CIRCLES];

int getRand(max){
    return (rand() % max);
}

int main(){

    srand(time(NULL))

    for(int i =0; i <NUM_CIRCLES; i++){
        int raio = getRand(50);
        int x = getRand(1000) + raio;  
        int y = getRand(1000) + raio;
        
        animationData[i].x = x;
        animationData[i].y = y;
        animationData[i].r = raio;
        animationData[i].xv = getRand(10);
        animationData[i].xy = getRand(10);
        animationData[i].xd = 1;
        animationData[i].yd = 1;


        circles[i].x = x;
        circles[i].y = y;
        circles[i].r = raio;
        circles[i].cr = getRand(255);
        circles[i].cg = getRand(255);
        circles[i].cb = getRand(255);
    }

    printf("Começar círculos \n");
    EM_ASM({render($0, $1); } NUM_CIRCLES*6, 6 );
}

struct Circle * getCircles( int canvasWidth, int canvasHeight) {

    for(int i=0;i<NUM_CIRCLES;i++){
        //colisão
        if( (animationData[i].x + animationData[i].r) >= canvasWidth ) animationData[i].xd = 0;

        if( (animationData[i].x - animationData[i].r) <= 0 ) animationData[i].xd = 1;
                        
        if( (animationData[i].y - animationData[i].r) <= 0 ) animationData[i].yd = 1;
                            
        if( (animationData[i].y - animationData[i].r) >= canvasHeight ) animationData[i].yd = 0;

        if(animationData[i].xd == 1 )  {
            animationData[i].x += animationData[i].xv;
        }
        else{
            animationData[i].x -= animationData[i].xv;
        }

          if(animationData[i].yd == 1 )  {
            animationData[i].y += animationData[i].yv;
        }
        else{
            animationData[i].y -= animationData[i].yv;
        }

        circles[i].x = animationData.[i].x;
        circles[i].y = animationData.[i].y;
        
    }
    return circles;
}