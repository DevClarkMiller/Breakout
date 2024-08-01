#ifndef MOVE_H
#define MOVE_H

#include "game.h"

bool move_ball(Ball* ball, Paddle* paddle);

bool move_balls(node_t* ball_node, Paddle* paddle);

int move_paddle(Paddle* paddle, u32* gcButtonsDown, int cursor_x);

#endif