#include "draw.h"

void DrawHLine (int x1, int x2, int y, int color) {
    int i;
    y = 320 * y;
    x1 >>= 1;
    x2 >>= 1;
    for (i = x1; i <= x2; i++) {
        u32 *tmpfb = xfb;
        tmpfb[y+i] = color;
    }
}
void DrawVLine (int x, int y1, int y2, int color) {
    int i;
    x >>= 1;
    for (i = y1; i <= y2; i++) {
        u32 *tmpfb = xfb;
        tmpfb[x + (640 * i) / 2] = color;
    }
}
void DrawBox (int x1, int y1, int x2, int y2, int color) {
    DrawHLine (x1, x2, y1, color);
    DrawHLine (x1, x2, y2, color);
    DrawVLine (x1, y1, y2, color);
    DrawVLine (x2, y1, y2, color);
}

//Takes in a pointer to a target, 
void draw_target(Target* target){
    DrawBox(target->x + TARGET_OFFSET , target->y + TARGET_OFFSET, target->x + TARGET_L, target->y + TARGET_H, (target->health == 1) ? COLOR_PURPLE : COLOR_RED);
}

//Takes in an array to draw each of the targets in that array
void draw_targets (Target targets[NUM_TARGET_ROWS][NUM_TARGETS]){
    for(int i = 0; i < NUM_TARGET_ROWS; i++){
        for(int j = 0; j < NUM_TARGETS; j++){
            draw_target(&targets[i][j]);
        }
    }
}

bool draw_ball (Ball* ball, Paddle* paddle){
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
    DrawBox(ball->x, ball->y, ball->x + ball->size, ball->y + ball->size, COLOR_WHITE);
    return true;
}

bool draw_balls (Ball balls[1], Paddle* paddle){
    for(int i = 0; i < 1; i++){
        if(!draw_ball(&balls[i], paddle)){
            return false;
        }
    }

    return true;
}

void clear_screen(u32 color) {
    // Assuming `xfb` is your framebuffer and `rmode` contains screen resolution
    int x, y;
    int width = rmode->fbWidth;
    int height = rmode->xfbHeight;

    // Loop through each pixel and set it to the color
    for (y = 0; y < height; y++) {
        for (x = 0; x < width; x++) {
            xfb[y * width + x] = color;
        }
    }
}