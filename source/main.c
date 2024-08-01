#include "draw.h"
#include "move.h"
#include "game.h"

extern char picdata[];
extern int piclength;

bool GAME_OVER = false;

//Heads for the linked lists
static node_t* targets_head;	//NOTE: This is a 2d linked list
static node_t* balls_head; 

static unsigned target_size;
static unsigned ball_size;

u32 *xfb;          // Define the variable
GXRModeObj *rmode; // Define the variable

//Sets up the initial targets and such
void init_game(){
	//1. Setup the heads for each of the linked lists
	targets_head = NULL;
	balls_head = NULL;

	targets_head->next = NULL;
	targets_head->data = NULL;

	balls_head->next = NULL;
	balls_head->data = NULL;

	//2. Init the sizes for the structs that are used in the linked lists
	target_size = sizeof(Target);
	ball_size = sizeof(Ball);

	//3. Init each element in the linked list of targets with a target
	for(int i = 0; i < NUM_TARGET_ROWS; i++){
		//Create a new node for each row
		node_t* new_row_head
        	= (node_t*)malloc(sizeof(node_t));

		//Then this new list to the target list
		new_row_head->data = NULL;
		new_row_head->next = NULL;
		push_back_node(&targets_head, new_row_head);	

		for(int j = 0; j < NUM_TARGETS; j++){
			int x = (j * TARGET_L);
			int y = (i * TARGET_H);	
			Target* target = (Target*)malloc(target_size);
			*target = (Target){2, x, y, true};	//Has a set health of 2

			push_back(&new_row_head, target, target_size);	//Adds target to the 2d linked list
		}
	}

	//4. Init first ball
	Ball* ball = (Ball*)malloc(sizeof(Ball));
    *ball = (Ball){-1, 1, 5, 350, 300, 1, COLOR_BLUE};

	push_back(&balls_head, ball, ball_size);
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

			// check_ball_collisions(balls_head, targets_head);

			// //For now if the ball hits the bottom, the game just ends
			// if (!move_balls(balls_head, &paddle))
			// 	GAME_OVER = true;

			// //Your paddle
			draw_solid_box(paddle.x, paddle.y, paddle.x + paddle.l, paddle.y + paddle.h, COLOR_WHITE);

			// //The breakable boxes
			// draw_targets(targets_head);

			//draw_balls(balls_head);
			Ball* ball = (Ball*)balls_head->data; 
			printf("X: %d, Y: %d", ball->x, ball->y);
			
			VIDEO_WaitVSync();
		}else{
			clear_screen(COLOR_RED);
			printf("GAME OVER!\n");
		}
    }

	//Frees up the memory for the lists
	free_list(&balls_head);
	free_2d_list(&targets_head);
 
    return 0;
}