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
    bool col_y = (ball->y >= paddle->y) && (ball->y <= paddle->y + paddle->h);
    bool col_x = (ball->x <= paddle->x + paddle->l) && (ball->x >= paddle->x);

    if(col_x && col_y){
        ball->y_pos = -ball->y_pos;

        //Get the x pos of the collision, then adjust the x_pos of the ball to make it bounce in the direction
        //of the side of the paddle it collided with

        int paddle_half_x = (paddle->x) + (paddle->l / 2);

        if(ball->x < paddle_half_x)
            ball->x_pos = -1;    //Forces it to travel in a negative direction
        else
            ball->x_pos = 1;     //Forces it to travel in a positive direction
    }

    ball->x += ball->x_pos;
    ball->y += ball->y_pos;

    return true;
}

bool move_balls(node_t* ball_node, Paddle* paddle){
    if(ball_node == NULL){ return false; }

    Ball* ball = ball_node->data;
    if(!move_ball(ball, paddle))
        return false;

    if(ball_node->next == NULL)
        return true;

    return move_balls(ball_node->next, paddle);
}

int move_paddle(Paddle* paddle, u32* gcButtonsDown, int cursor_x){
    if(*(gcButtonsDown) & PAD_BUTTON_START)	//Ends game loop
		GAME_OVER = true;
    

    if (PAD_StickX(0) > 18) 
        cursor_x++;
    
    if (PAD_StickX(0) < -18) 
        cursor_x--;
    
    paddle->h = cursor_x;

    return cursor_x;
}

