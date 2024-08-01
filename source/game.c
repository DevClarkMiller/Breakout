#include "game.h"

bool check_ball_collision(Ball* ball, Target* target){
    //Checks ball clips into the bounds of a target

    if((ball->y <= target->y + TARGET_H) && (ball->y >= target->y)){
        if((ball->x <= target->x + TARGET_L) && (ball->x >= target->x)){
            return true;
        }
    }
    return false;
}

//TODO: CHECK ONLY NEAR TARGETS FOR A COLLISION
Target* check_ball_collisions(Ball balls[1], Target targets[NUM_TARGET_ROWS][NUM_TARGETS]){
    //Check for each ball
    for(int b = 0; b < 1; b++){
        for(int i = 0; i < NUM_TARGET_ROWS; i++){
            for(int j = 0; j < NUM_TARGETS; j++){
                Target* target = &targets[i][j];
                if(target->col_on){
                    if(check_ball_collision(&balls[b], target))
                        return target;
                }
            }
        }
    }

    return (Target*)0;
}
