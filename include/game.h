#ifndef GAME_H
#define GAME_H

#include <globals.h>

#define SCRN_X 640
#define SCRN_Y 480

#define NUM_TARGETS 40  //Accounts for a gap in between each of the targets, 
#define NUM_TARGET_ROWS 3
#define TARGET_OFFSET 5
#define COORD_FAIL -999

static const int TARGET_L = 15;
static const int TARGET_H = 10;

struct PADDLE{
	int l;	//Length
	int h;	//Height
	int x;
	int y;
	int speed;
};

typedef struct PADDLE Paddle;

struct BALL{
	int x_pos;
	int y_pos;
	int size;
	int x;
	int y;
	int speed;
	int color;
};

typedef struct BALL Ball;

struct TARGET{
    int health;
    int x;
    int y;
	bool col_on;
};

typedef struct TARGET Target;

struct COORD{
	int x;
	int y;
};

typedef struct COORD Coord;

bool check_ball_collision(Ball* ball, Target* target);

void check_ball_collisions(node_t* ball_node, node_t* target_head);

#endif