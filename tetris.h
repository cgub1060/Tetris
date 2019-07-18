#pragma once

#define FIELD_HEIGHT 21
#define FIELD_WIDTH  12
#define SUB_FIELD_HEIGHT 6
#define SUB_FIELD_WIDTH 6
#define NEXT_BLOCK_POSITION_X 13
#define NEXT_BLOCK_POSITION_Y 5
#define STOCK_BLOCK_POSITION_X 13
#define STOCK_BLOCK_POSITION_Y 13
#define BLOCK_HEIGHT 4
#define BLOCK_WIDTH 4
#define BLOCK_KINDS 7
#define FALL_BASE_X 1
#define FALL_BASE_Y 0
#define KEYINPUT_TIMEOUT_TIME 20
#define FALL_TIME 1.0
#define CHARBUFF 124

enum color {
	BOUNDARY, 
	BLOCK_COLOR1,
	BLOCK_COLOR2,
	BLOCK_COLOR3,
	BLOCK_COLOR4,
	BLOCK_COLOR5,
	MOZI1,
	MOZI2
};

enum blockType {
	FREE,
	WALL,
	FLOOR,
	FIX,
	CONTROL
};

struct record {
	int SCORE, LEVEL;
};
extern FILE *fp;
extern int playField[FIELD_HEIGHT][FIELD_WIDTH];
extern int blocks[BLOCK_KINDS][BLOCK_HEIGHT][BLOCK_WIDTH];
extern int inControlBlock[BLOCK_HEIGHT][BLOCK_WIDTH];
extern int currentBlockPositionX;
extern int currentBlockPositionY;
extern int nextBlockField[SUB_FIELD_HEIGHT][SUB_FIELD_WIDTH];
extern int stockBlockField[SUB_FIELD_HEIGHT][SUB_FIELD_WIDTH];
extern int nextControlBlock[BLOCK_HEIGHT][BLOCK_WIDTH];
extern int stockControlBlock[BLOCK_HEIGHT][BLOCK_WIDTH];
extern record tetris;
enum appState {
	PRE,
	RUNNING,
	EXIT_WAIT,
	GAME_OVER,
};

extern int currentAppState;

void Startdraw();
void Finishdraw();
void setControlBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
void setNextField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
void unsetNextField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
void setStockControlBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
void stockBlock();
void setNextControlBlock(int kind);
void drawNextBlockField();
void drawStockBlockField();
void showGameOverScreen();
void getCurrentDirectory(char *currentDirectory);
void getData();
void drawField();
void setBlock(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
void unsetBlock(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
int isCollision(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]);
int moveBlock(int baseX, int baseY);
void rotateBlock(int isClockwise);
void play(int ch);
void setNewControlBlock(int kind);
void generateBlock(int x, int y);
void fixBlock();
int isCompleteLine(int line);
void eraseLine(int line);
void compaction(int line);
void eraseCompleteLine();
void showRecord();
void showGuide();
void initializeColor();
void gameLoop();