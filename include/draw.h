#ifndef DRAW_H
#define DRAW_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ogcsys.h>
#include <gccore.h>
#include <wiiuse/wpad.h>
#include <jpeg/jpgogc.h>

#include "game.h"

void DrawHLine (int x1, int x2, int y, int color);

void DrawVLine (int x, int y1, int y2, int color);

void DrawBox (int x1, int y1, int x2, int y2, int color);

void draw_solid_box(int x1, int y1, int x2, int y2, int color);

void draw_target(Target* target);

void draw_targets (Target targets[NUM_TARGET_ROWS][NUM_TARGETS]);

void draw_balls (Ball balls[1]);

void clear_screen(u32 color);

#endif