#ifndef GAME_H
#define GAME_H

#define SCRN_X 640
#define SCRN_Y 480

typedef struct{
	int l;	//Length
	int h;	//Height
	int x;
	int y;
	int speed;
}Paddle;

typedef struct{
	int x_pos;
	int y_pos;
	int size;
	int x;
	int y;
	int speed;
}Ball;

#endif