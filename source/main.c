#include "draw.h"
#include "move.h"
#include "game.h"

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
			Target target = {2, x, y, true};	//Has a set health of 2
			targets[i][j] = target;
		}
	}

	//2. Init each ball
	for(int i = 0; i < 1; i++){
		balls[i] = (Ball){-1, 1, 5, 350, 300, 1, COLOR_BLUE};
	}
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
	Paddle paddle = {25, 5, cursor_x, SCRN_Y - 25, 2};
	
    while(1) {
		WPAD_ScanPads();
		PAD_ScanPads();

		// Check GameCube controller input
		u32 gcButtonsDown = PAD_ButtonsDown(0);

		if(!GAME_OVER){
			clear_screen(COLOR_GREEN);

			if(gcButtonsDown & PAD_BUTTON_START){	//Ends game loop
				GAME_OVER = true;
			}

			if (PAD_StickX(0) > 18) {
				cursor_x += paddle.speed;
			}
			if (PAD_StickX(0) < -18) {
				cursor_x -= paddle.speed;
			}

			paddle.x = cursor_x;

			check_ball_collisions(balls, targets);

			//For now if the ball hits the bottom, the game just ends
			if (!move_balls(balls, &paddle))
				GAME_OVER = true;

			//Your paddle
			draw_solid_box(paddle.x, paddle.y, paddle.x + paddle.l, paddle.y + paddle.h, COLOR_WHITE);

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