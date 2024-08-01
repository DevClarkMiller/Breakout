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

// Recursively checks over all the balls and targets for collisions
// TODO: CHECK ONLY NEAR TARGETS FOR A COLLISION
void check_ball_collisions(node_t* ball_node, node_t* target_head){
    if(ball_node == NULL) { return; }   //Base case
    Ball* ball = (Ball*)ball_node->data;

    for(int i = 0; i < NUM_TARGET_ROWS; i++){
        node_t* row_head = get_nth(target_head, i);
        if(row_head != NULL){
            for(int j = 0; j < NUM_TARGETS; j++){
                Target* target = (Target*)get_nth(row_head, j)->data;
                if(target->col_on){
                    if(check_ball_collision(ball, target)){
                        handle_col(ball, target);
                    }
                }
            }
        }
    }

    if(ball_node->next != NULL)
        check_ball_collisions(ball_node->next, target_head);
}