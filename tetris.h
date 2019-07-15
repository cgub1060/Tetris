#pragma once

#define FIELD_HEIGHT 21
#define FIELD_WIDTH  12
#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 4


//++++++++++++++++++++++++++++++++++•ÏX+++++++++++++++++++++++++++++++++++++
//**********************************’Ç‰Á*************************************
#define SUB_FIELD_HEIGHT 6
#define SUB_FIELD_WIDTH 6
//***************************************************************************

#define BLOCK_KINDS 7
#define FALL_BASE_X 1
#define FALL_BASE_Y 0
#define KEYINPUT_TIMEOUT_TIME 20
#define FALL_TIME 1.0
//**********************************’Ç‰Á*************************************
//FIELD_WIDTH + 1
#define NEXT_BLOCK_POSITION_X 13
#define NEXT_BLOCK_POSITION_Y 5
//***************************************************************************

//++++++++++++++++++++++++++++++++++’Ç‰Á+++++++++++++++++++++++++++++++++++++
#define STOCK_BLOCK_POSITION_X 13
#define STOCK_BLOCK_POSITION_Y 13
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


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

//++++++++++++++++++++++++++++++++++•ÏX+++++++++++++++++++++++++++++++++++++
//**********************************’Ç‰Á*************************************
extern int nextBlockField[SUB_FIELD_HEIGHT][SUB_FIELD_WIDTH];
//***************************************************************************

//++++++++++++++++++++++++++++++++++’Ç‰Á+++++++++++++++++++++++++++++++++++++
extern int stockBlockField[SUB_FIELD_HEIGHT][SUB_FIELD_WIDTH];
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

extern int blocks[BLOCK_KINDS][BLOCK_HEIGHT][BLOCK_WIDTH];
extern int inControlBlock[BLOCK_HEIGHT][BLOCK_WIDTH];

//**********************************’Ç‰Á*************************************
extern int nextControlBlock[BLOCK_HEIGHT][BLOCK_WIDTH];
//***************************************************************************

//++++++++++++++++++++++++++++++++++’Ç‰Á+++++++++++++++++++++++++++++++++++++
extern int stockControlBlock[BLOCK_HEIGHT][BLOCK_WIDTH];
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
void setField(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);

//++++++++++++++++++++++++++++++++++’Ç‰Á+++++++++++++++++++++++++++++++++++++
void setControlBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//**********************************’Ç‰Á*************************************
void setNextField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
//***************************************************************************

void unsetField(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);

//**********************************’Ç‰Á*************************************
void unsetNextField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
//***************************************************************************

//++++++++++++++++++++++++++++++++++’Ç‰Á+++++++++++++++++++++++++++++++++++++
void setStockControlBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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