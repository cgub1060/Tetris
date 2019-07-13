#pragma once

#define FIELD_HEIGHT 21
#define FIELD_WIDTH  12
#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 4

//**********************************’Ç‰Á*************************************
#define nextBlockFieldSize 6
//***************************************************************************

#define BLOCK_KINDS 7
#define FALL_BASE_X 1
#define FALL_BASE_Y 0
#define KEYINPUT_TIMEOUT_TIME 20
#define FALL_TIME 1.0
//**********************************’Ç‰Á*************************************
//FIELD_WIDTH + 1
#define nextBlockPositionX 13
#define nextBlockPositionY 5
//***************************************************************************

enum color {
	BOUNDARY, 
	BLOCK_COLOR1,
	BLOCK_COLOR2,
	BLOCK_COLOR3,
	BLOCK_COLOR4,
	BLOCK_COLOR5
};

enum blockType {
	FREE,
	WALL,
	FLOOR,
	FIXED,
	CONTROL
};
extern int playField[FIELD_HEIGHT][FIELD_WIDTH];

//**********************************’Ç‰Á*************************************
extern int nextBlockField[BLOCK_HEIGHT+2][BLOCK_WIDTH+2];
//***************************************************************************

extern int blocks[BLOCK_KINDS][BLOCK_HEIGHT][BLOCK_WIDTH];
extern int inControlBlock[BLOCK_HEIGHT][BLOCK_WIDTH];

//**********************************’Ç‰Á*************************************
extern int nextControlBlock[BLOCK_HEIGHT][BLOCK_WIDTH];
//***************************************************************************

extern int currentBlockPositionX;
extern int currentBlockPositionY;
extern int gameScore;

enum appState {
	RUNNING,
	EXIT_WAIT,
	GAME_OVER,
};

extern int currentAppState;

void drawField();
void setBlock(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);

//**********************************’Ç‰Á*************************************
void setNextBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
//***************************************************************************
void unsetBlock(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);

//**********************************’Ç‰Á*************************************
void unsetNextBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
//***************************************************************************
int isCollision(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
int moveBlock(int baseX, int baseY);
void rotateBlock(int isClockwise);
void playerOperate(int ch);
void setNewControlBlock(int kind);
void generateBlock(int x, int y);
void fixBlock();
int isCompleteLine(int line);
void eraseLine(int line);
void compaction(int line);
void eraseCompleteLine();
void showScore();
void showGuide();
void initializeColor();
void gameLoop();