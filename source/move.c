#include "move.h"
#include "game.h"

bool move_ball(Ball* ball, Paddle* paddle){
    // Update box position
    // int width = rmode->fbWidth;
    // int height = rmode->xfbHeight;

    int x = ball->x;
    int y = ball->y;
    int size = ball->size;
        
    if (x <= 0 || x >= SCRN_X - size) 
        ball->x_pos = -ball->x_pos;

    //Ball reaches the bottom of the screen, ends game TODO: Remove a player live later on instead
    if(y >= SCRN_Y - size)
        return false;

    if (y <= 0) //If it hits the top of the screen, then make it move downward
        ball->y_pos = -ball->y_pos;

    //Checks for collision with paddle
    if((ball->y >= paddle->y) && (ball->y <= paddle->y + paddle->h)){
        if((ball->x <= paddle->x + paddle->l) && (ball->x >= paddle->x)){
            ball->y_pos = -ball->y_pos;
        }
    }

    ball->x += ball->x_pos;
    ball->y += ball->y_pos;

    return true;
}

bool move_balls(Ball balls[1], Paddle* paddle){
    for(int i = 0; i < 1; i++){
        Ball* ball = &balls[i];
        if(!move_ball(ball, paddle))
            return false;
    }
    return true;
}