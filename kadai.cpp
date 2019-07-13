// kadai.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
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

//**********************************�ǉ�*************************************
int nextBlockField[nextBlockFieldSize][nextBlockFieldSize] = {
	{ 0,2,2,2,2,0 },
	{ 1,0,0,0,0,1 },
	{ 1,0,0,0,0,1 },
	{ 1,0,0,0,0,1 },
	{ 1,0,0,0,0,1 },
	{ 0,2,2,2,2,0 }
};
//***************************************************************************


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

//**********************************�ǉ�*************************************
int nextControlBlock[BLOCK_HEIGHT][BLOCK_WIDTH];
//***************************************************************************

int currentBlockPositionX = 0;
int currentBlockPositionY = 0;

int gameScore = 0;
int currentAppState = RUNNING;


int main()
{
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	timeout(KEYINPUT_TIMEOUT_TIME);
	initializeColor();
	srand((unsigned)time(NULL));
	generateBlock(FALL_BASE_X, FALL_BASE_Y);
	setNextBlock(nextControlBlock);
	gameLoop();
	endwin();


    return 0;
}
