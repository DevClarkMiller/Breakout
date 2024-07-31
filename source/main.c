#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <jpeg/jpgogc.h>

#include "globals.h"
#include "game.h"
#include "draw.h"

extern char picdata[];
extern int piclength;

bool GAME_OVER = false;

static Target targets[NUM_TARGET_ROWS][NUM_TARGETS];
static Ball balls[1];

u32 *xfb;          // Define the variable
GXRModeObj *rmode; // Define the variable

//Sets up the initial targets and such
void init_game(){
	//1. Init each element in the array of targets with a target
	for(int i = 0; i < NUM_TARGET_ROWS; i++){
		for(int j = 0; j < NUM_TARGETS; j++){
			int x = (j * TARGET_L);
			int y = (i * TARGET_H);	
			Target target = {1, x, y};	//Has a set health of 1
			targets[i][j] = target;
		}
	}


	//2. Init each ball
	balls[0] = (Ball){-1, 1, 5, 200, 300, 1};
}

void Initialise() {
	VIDEO_Init();
	PAD_Init();
 
	rmode = VIDEO_GetPreferredMode(NULL);

	xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
	console_init(xfb,20,20,rmode->fbWidth,rmode->xfbHeight,rmode->fbWidth*VI_DISPLAY_PIX_SZ);
 
	VIDEO_Configure(rmode);
	VIDEO_SetNextFramebuffer(xfb);
	VIDEO_SetBlack(FALSE);
	VIDEO_Flush();
	VIDEO_WaitVSync();
	if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
	init_game();
}

int main() {
    Initialise();
	int cursor_x = 300;

	//Spawn it at the bottom of screen with a bit of offset
	Paddle paddle = {15, 5, cursor_x, SCRN_Y - 25, 15};
	
    while(1) {
		WPAD_ScanPads();
		PAD_ScanPads();

		// Check GameCube controller input
		u32 gcButtonsDown = PAD_ButtonsDown(0);

		if(!GAME_OVER){
			clear_screen(COLOR_GREEN);

			if(gcButtonsDown & PAD_BUTTON_START){	//Ends game loop
				GAME_OVER = true;
				break;
			}

			if (PAD_StickX(0) > 18) {
				cursor_x++;
			}
			if (PAD_StickX(0) < -18) {
				cursor_x--;
			}

			paddle.x = cursor_x;

			//Your paddle
			DrawBox(paddle.x, paddle.y, paddle.x + paddle.l, paddle.y + paddle.h, COLOR_WHITE);

			//The breakable boxes
			draw_targets(targets);

			draw_balls(balls);
			
			VIDEO_WaitVSync();
		}else{
			clear_screen(COLOR_RED);
			printf("GAME OVER!\n");
		}
    }
 
    return 0;
}