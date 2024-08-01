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

void draw_solid_box(int x1, int y1, int x2, int y2, int color) {
    for(int y = y1; y < y2; y++)
        DrawHLine (x1, x2, y, color);
}

void DrawBox (int x1, int y1, int x2, int y2, int color) {
    DrawHLine (x1, x2, y1, color);
    DrawHLine (x1, x2, y2, color);
    DrawVLine (x1, y1, y2, color);
    DrawVLine (x2, y1, y2, color);
}

//Takes in a pointer to a target, 
void draw_target(Target* target){
    int color = (target->health == 2) ? COLOR_PURPLE : (target->health == 1) ? COLOR_RED : COLOR_BLACK;
    draw_solid_box(target->x + TARGET_OFFSET , target->y + TARGET_OFFSET, target->x + TARGET_L, target->y + TARGET_H, color);
}

//Recursively iterates over each of the rows in the 2d list
void draw_targets (node_t* rows_node){
    if(rows_node == NULL) { return; }
    node_t* row = (node_t*)rows_node->data; //Casts void pointer to a node pointer

    //Then simple loop to avoid excessive recursion
    for(int j = 0; j < NUM_TARGETS; j++){
        Target* target = (Target*)get_nth(row, j)->data;    //Gets the current target from the column node
        if(target->col_on)
            draw_target(target);
    }

    if(rows_node->next != NULL)
        draw_targets(rows_node->next);
}

void draw_balls(node_t* balls_head) {
    node_t* temp = balls_head;

    while(temp != NULL && temp->data != NULL){
        Ball* ball = (Ball*)(temp->data);
        draw_solid_box(ball->x, ball->y, ball->x + ball->size, ball->y + ball->size, ball->color);
    }   
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