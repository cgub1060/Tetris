// kadai.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <curses.h>
#include <io.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "tetris.h"


int playField[FIELD_HEIGHT][FIELD_WIDTH] = {
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 2,2,2,2,2,2,2,2,2,2,2,2 }
};

int nextBlockField[SUB_FIELD_HEIGHT][SUB_FIELD_WIDTH] = {
	{ 0,2,2,2,2,0 },
	{ 1,0,0,0,0,1 },
	{ 1,0,0,0,0,1 },
	{ 1,0,0,0,0,1 },
	{ 1,0,0,0,0,1 },
	{ 0,2,2,2,2,0 }
};

int stockBlockField[SUB_FIELD_HEIGHT][SUB_FIELD_WIDTH] = {
	{ 0,2,2,2,2,0 },
	{ 1,0,0,0,0,1 },
	{ 1,0,0,0,0,1 },
	{ 1,0,0,0,0,1 },
	{ 1,0,0,0,0,1 },
	{ 0,2,2,2,2,0 }
};

int blocks[BLOCK_KINDS][BLOCK_HEIGHT][BLOCK_WIDTH] = {
	{
		{ 4,0,0,0 },
		{ 4,0,0,0 },
		{ 4,0,0,0 },
		{ 4,0,0,0 }
	},
	{
		{ 0,4,0,0 },
		{ 4,4,4,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }
	},
	{
		{ 4,4,0,0 },
		{ 0,4,4,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }
	},
	{
		{ 0,4,4,0 },
		{ 4,4,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }
	},
	{
		{ 4,4,0,0 },
		{ 4,4,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }
	},
	{
		{ 4,4,0,0 },
		{ 4,0,0,0 },
		{ 4,0,0,0 },
		{ 0,0,0,0 }
	},
	{
		{ 4,4,0,0 },
		{ 0,4,0,0 },
		{ 0,4,0,0 },
		{ 0,0,0,0 }
	}
};

int inControlBlock[BLOCK_HEIGHT][BLOCK_WIDTH];
int nextControlBlock[BLOCK_HEIGHT][BLOCK_WIDTH];
int stockControlBlock[BLOCK_HEIGHT][BLOCK_WIDTH];

int currentBlockPositionX;
int currentBlockPositionY;

record tetris;

int currentAppState = RUNNING;

FILE *fp;

int main()
{
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	timeout(KEYINPUT_TIMEOUT_TIME);
	srand((unsigned)time(NULL));
	start_color();
	initializeColor();
	Startdraw();
	clear();
	generateBlock(FALL_BASE_X, FALL_BASE_Y);
	gameLoop();

	endwin();


    return 0;
}

