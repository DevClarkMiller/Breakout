#include "game.h"

void handle_col(Ball* ball, Target* target){
    target->health -=1;
    if(target->health <= 0){
        target->col_on = false;
    }

    //Make the ball bounce now
    ball->y_pos = -ball->y_pos;
}

bool check_ball_collision(Ball* ball, Target* target) {
    if (!ball || !target) return false;
    
    // Calculate the boundaries of the ball
    int ball_right = ball->x + ball->size;
    int ball_bottom = ball->y + ball->size;

    // Calculate the boundaries of the target
    int target_right = target->x + TARGET_L;
    int target_bottom = target->y + TARGET_H;

    // Check for collision
    bool collision_x = ball->x < target_right && ball_right > target->x;
    bool collision_y = ball->y < target_bottom && ball_bottom > target->y;

    return collision_x && collision_y;
}

//TODO: CHECK ONLY NEAR TARGETS FOR A COLLISION
void check_ball_collisions(Ball balls[1], Target targets[NUM_TARGET_ROWS][NUM_TARGETS]){
    //Check for each ball
    for(int b = 0; b < 1; b++){
        for(int i = 0; i < NUM_TARGET_ROWS; i++){
            for(int j = 0; j < NUM_TARGETS; j++){
                Target* target = &targets[i][j];
                if(target->col_on){
                    Ball* ball = &balls[b];
                    if(check_ball_collision(ball, target)){
                        handle_col(ball, target);
                    }
                }
            }
        }
    }
}
