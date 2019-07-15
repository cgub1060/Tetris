#include "stdafx.h"
#include <curses.h>
#include <io.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "tetris.h"

void drawField() {
	int h, w;
	for (h = 0; h < FIELD_HEIGHT; h++) {
		for (w = 0; w < FIELD_WIDTH; w++) {
			if (playField[h][w] == WALL) {
				color_set(BOUNDARY, NULL);
				mvprintw(h, w, "|");
			}
			if (playField[h][w] == FLOOR) {
				color_set(BOUNDARY, NULL);
				mvprintw(h, w, "-");
			}
			if (playField[h][w] == CONTROL) {
				
					color_set(BLOCK_COLOR1, NULL);
					mvprintw(h, w, "@");
				
			}
			if (playField[h][w] == FIXED) {
				color_set(BLOCK_COLOR3, NULL);
					mvprintw(h, w, "@");
			
				
			}
			if (playField[h][w] == FREE) {
				color_set(BOUNDARY, NULL);
				
				mvprintw(h, w, " ");
			}
		}
	}
}


//**********************************追加*************************************
void drawNextBlockField() {
	int h, w;

	mvprintw(NEXT_BLOCK_POSITION_Y - 1, NEXT_BLOCK_POSITION_X, "nextBlock");
	for (h = 0; h < SUB_FIELD_HEIGHT; h++) {
		for (w = 0; w < SUB_FIELD_WIDTH; w++) {
			if (nextBlockField[h][w] == WALL) {
				color_set(BOUNDARY, NULL);
				mvprintw(NEXT_BLOCK_POSITION_Y + h, NEXT_BLOCK_POSITION_X + w, "|");
			}
			if (nextBlockField[h][w] == FLOOR) {
				color_set(BOUNDARY, NULL);
				mvprintw(NEXT_BLOCK_POSITION_Y + h, NEXT_BLOCK_POSITION_X + w, "-");
			}
			if (nextBlockField[h][w] == CONTROL) {

				color_set(BLOCK_COLOR1, NULL);
				mvprintw(NEXT_BLOCK_POSITION_Y + h, NEXT_BLOCK_POSITION_X + w, "@");

			}
			if (nextBlockField[h][w] == FIXED) {
				color_set(BLOCK_COLOR3, NULL);
				mvprintw(NEXT_BLOCK_POSITION_Y + h, NEXT_BLOCK_POSITION_X + w, "@");


			}
			if (nextBlockField[h][w] == FREE) {
				color_set(BOUNDARY, NULL);

				mvprintw(NEXT_BLOCK_POSITION_Y + h, NEXT_BLOCK_POSITION_X + w, " ");
			}
		}
	}
}
//***************************************************************************


//++++++++++++++++++++++++++++++++++追加+++++++++++++++++++++++++++++++++++++
void drawStockBlockField() {
	int h, w;

	mvprintw(STOCK_BLOCK_POSITION_Y - 1, STOCK_BLOCK_POSITION_X, "stockBlock");
	for (h = 0; h < SUB_FIELD_HEIGHT; h++) {
		for (w = 0; w < SUB_FIELD_WIDTH; w++) {
			if (stockBlockField[h][w] == WALL) {
				color_set(BOUNDARY, NULL);
				mvprintw(STOCK_BLOCK_POSITION_Y + h, STOCK_BLOCK_POSITION_X + w, "|");
			}
			if (stockBlockField[h][w] == FLOOR) {
				color_set(BOUNDARY, NULL);
				mvprintw(STOCK_BLOCK_POSITION_Y + h, STOCK_BLOCK_POSITION_X + w, "-");
			}
			if (stockBlockField[h][w] == CONTROL) {

				color_set(BLOCK_COLOR1, NULL);
				mvprintw(STOCK_BLOCK_POSITION_Y + h, STOCK_BLOCK_POSITION_X + w, "@");

			}
			if (stockBlockField[h][w] == FIXED) {
				color_set(BLOCK_COLOR3, NULL);
				mvprintw(STOCK_BLOCK_POSITION_Y + h, STOCK_BLOCK_POSITION_X + w, "@");


			}
			if (stockBlockField[h][w] == FREE) {
				color_set(BOUNDARY, NULL);

				mvprintw(STOCK_BLOCK_POSITION_Y + h, STOCK_BLOCK_POSITION_X + w, " ");
			}
		}
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//++++++++++++++++++++++++++++++++名称変更+++++++++++++++++++++++++++++++++++
void setField(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				playField[baseY + h][baseX + w] = setBuf[h][w];
			}
		}
	}
}

//**********************************追加*************************************
void setNextField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				nextBlockField[h + 1][w + 1] = setBuf[h][w];	//枠分を足している
			}
		}
	}
}
//***************************************************************************


//++++++++++++++++++++++++++++++++++追加+++++++++++++++++++++++++++++++++++++
void setStockField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				stockBlockField[h + 1][w + 1] = setBuf[h][w];	//枠分を足している
			}
		}
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//**********************************追加*************************************
void unsetControlBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			inControlBlock[h][w] = FREE;
		}
	}
}
//***************************************************************************


void unsetField(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				playField[baseY + h][baseX + w] = FREE;
			}
		}
	}
}

//**********************************追加*************************************
void unsetNextField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			nextBlockField[h + 1][w + 1] = FREE;	//枠分を足している
		}
	}
}
//***************************************************************************

//++++++++++++++++++++++++++++++++++追加+++++++++++++++++++++++++++++++++++++
void unsetStockField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			stockBlockField[h + 1][w + 1] = FREE;
		}
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


int isCollision(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				if (playField[baseY + h][baseX + w] != FREE) {
					return 1;
				}
			}
		}
	}
	return 0;
}

int moveBlock(int baseX, int baseY) {
	if (isCollision(baseX, baseY, inControlBlock) == 0) {
		currentBlockPositionX = baseX;
		currentBlockPositionY = baseY;
		return 1;
	}
	return 0;
}

void rotateBlock(int isClockwise) {
	int buf[BLOCK_HEIGHT][BLOCK_WIDTH] = {};

	if (isClockwise == 1) {
		for (int h = 0; h < BLOCK_HEIGHT; h++) {
			for (int w = 0; w < BLOCK_WIDTH; w++) {
				int pw = (BLOCK_HEIGHT - 1) - w;
				int ph = h;
				assert(0 <= pw && pw < BLOCK_WIDTH);
				assert(0 <= ph && ph < BLOCK_HEIGHT);
				buf[h][w] = inControlBlock[pw][ph];
			}
		}
	}
	else {
		for (int h = 0; h < BLOCK_HEIGHT; h++) {
			for (int w = 0; w < BLOCK_WIDTH; w++) {
				int pw = w;
				int ph = (BLOCK_WIDTH - 1) - h;
				assert(0 <= pw && pw < BLOCK_WIDTH);
				assert(0 <= ph && ph < BLOCK_HEIGHT);
				buf[h][w] = inControlBlock[pw][ph];
			}
		}
	}
	int baseX = currentBlockPositionX;
	int baseY = currentBlockPositionY;
	if (isCollision(baseX, baseY, buf) == 0) {
		for (int h = 0; h < BLOCK_HEIGHT; h++) {
			for (int w = 0; w < BLOCK_WIDTH; w++) {
				inControlBlock[h][w] = buf[h][w];
			}
		}
	}
}

//++++++++++++++++++++++++++++++++++追加+++++++++++++++++++++++++++++++++++++
void stockBlock() {
	bool firstStock = TRUE;
	int tmpBlock[BLOCK_HEIGHT][BLOCK_WIDTH] = {
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 },
		{ 0,0,0,0 }
	};

	//ストックが空かどうかの判別
	//現在のストックブロックを保持
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (w >= 2 && stockControlBlock[h][w] == CONTROL) {
				if (currentBlockPositionX >= FIELD_WIDTH-3) {
					mvprintw(20, 20, "枠外にブロックがでるためストック不可");
					return;
				}
			}
			if (stockControlBlock[h][w] == CONTROL) {
				tmpBlock[h][w] = stockControlBlock[h][w];
				firstStock = FALSE;
			}
		}
	}

	//現在操作中のブロックをストック
	setStockControlBlock(inControlBlock);

	/*if ストックが空(初めてストックを行う)
	* 現在操作中のブロックをストック
	* 現在操作中のブロックを削除
	* 次のブロックを削除
	* ブロックを新たに生成
	* 次のブロックを表示
	*/

	/*else ストックが空ではない(ストックを既に行っている)
	* ストックを非表示に
	* 現在操作中のブロックを
	* stockControlBlockのkindからinControlBlockを生成
	*/
	if (firstStock) {
		setStockField(inControlBlock);
		unsetControlBlock(inControlBlock);
		unsetNextField(nextControlBlock);
		generateBlock(FALL_BASE_X, FALL_BASE_Y);
		setNextField(nextControlBlock);
	}
	else {
		unsetStockField(stockControlBlock);		
		setStockField(inControlBlock);
		unsetControlBlock(inControlBlock);
		setControlBlock(tmpBlock);
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void playerOperate(int ch) {
	switch (ch) {
	case KEY_RIGHT:
		moveBlock(currentBlockPositionX + 1, currentBlockPositionY);
		break;
	case KEY_LEFT:
		moveBlock(currentBlockPositionX - 1, currentBlockPositionY);
		break;
	case KEY_DOWN:
		moveBlock(currentBlockPositionX, currentBlockPositionY + 1);
		break;
	case 'w':
		rotateBlock(1);
		break;
	case 'e':
		rotateBlock(0);
		break;

//++++++++++++++++++++++++++++++++++追加+++++++++++++++++++++++++++++++++++++
	case 's':
		stockBlock();
		break;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	case 'q':
		currentAppState = EXIT_WAIT;
		break;
	}
}

//++++++++++++++++++++++++++++++++++追加+++++++++++++++++++++++++++++++++++++
void setControlBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			inControlBlock[h][w] = setBuf[h][w];
		}
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void setNewControlBlock(int kind) {
	assert(0 <= kind && kind < BLOCK_KINDS);
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			inControlBlock[h][w] = blocks[kind][h][w];
		}
	}
}

//**********************************追加*************************************
void setNextControlBlock(int kind) {
	assert(0 <= kind && kind < BLOCK_KINDS);

	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			nextControlBlock[h][w] = blocks[kind][h][w];
		}
	}
}
//***************************************************************************

//++++++++++++++++++++++++++++++++++追加+++++++++++++++++++++++++++++++++++++
void setStockControlBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			stockControlBlock[h][w] = setBuf[h][w];
		}
	}
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



void generateBlock(int x, int y) {
	currentBlockPositionX = x;
	currentBlockPositionY = y;

	//	setNewControlBlock(rand() % BLOCK_KINDS);
//**********************************追加*************************************
	static int generateBlockNum = 10;
	if (generateBlockNum == 10) {
		generateBlockNum = rand() % BLOCK_KINDS;
	}
	setNewControlBlock(generateBlockNum);
	generateBlockNum = rand() % BLOCK_KINDS;
	setNextControlBlock(generateBlockNum);

//***************************************************************************

}

void fixBlock() {
	setField(currentBlockPositionX, currentBlockPositionY, inControlBlock);

	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			int ph = currentBlockPositionY + h;
			int pw = currentBlockPositionX + w;

			if ((0 < ph && ph < FIELD_HEIGHT - 1) &&
				(0 < pw && pw < FIELD_WIDTH - 1)) {
				assert(ph < FIELD_HEIGHT - 1);
				assert(0 < pw && pw < FIELD_WIDTH - 1);
				if (playField[currentBlockPositionY + h][currentBlockPositionX + w] == CONTROL) {
					playField[currentBlockPositionY + h][currentBlockPositionX + w] = FIXED;
				}
			}
		}
	}
}

int isCompleteLine(int line) {
	for (int w = 0; w < FIELD_WIDTH; w++) {
		if (playField[line][w] != FIXED && playField[line][w] != WALL) {
			return 0;
		}
	}
	return 1;
}

void eraseLine(int line) {
	for (int w = 0; w < FIELD_WIDTH; w++) {
		if (playField[line][w] == FIXED) {
			playField[line][w] = FREE;
		}
	}
}

void compaction(int line) {
	for (int h = line; h > 0; h--) {
		for (int w = 0; w < FIELD_WIDTH; w++) {
			playField[h][w] = playField[h - 1][w];
		}
	}
	eraseLine(0);
}

void eraseCompleteLine() {
	for (int h = 0; h < FIELD_HEIGHT; h++) {
		if (isCompleteLine(h)) {
			eraseLine(h);
			compaction(h);

			gameScore += 5;
		}
	}
}
void showGuide() {
	mvprintw(23, 0, "e: 時計回り");
	mvprintw(23, 14, "w: 反時計回り");

//++++++++++++++++++++++++++++++++++追加+++++++++++++++++++++++++++++++++++++
	mvprintw(23, 28, "s: ストック");
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	mvprintw(24, 0, "←: 左に移動");
	mvprintw(24, 14, "→: 右に移動");
	mvprintw(24, 28, "↓: 下に移動");
	mvprintw(25, 0, "q: ゲーム終了");
}

void showScore() {
	mvprintw(1, FIELD_WIDTH + 1, "SCORE: %d", gameScore);
}

void initializeColor() {
	start_color();
	init_pair(BOUNDARY, COLOR_WHITE, COLOR_WHITE);
	init_pair(BLOCK_COLOR1, COLOR_CYAN, COLOR_CYAN);
	init_pair(BLOCK_COLOR2, COLOR_GREEN, COLOR_GREEN);
	init_pair(BLOCK_COLOR3, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(BLOCK_COLOR4, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(BLOCK_COLOR5, COLOR_RED, COLOR_RED);
}


void showGameOverScreen() {
	mvprintw(0, FIELD_WIDTH + 1, "GAME OVER");
	timeout(-1);
	getch();
}

void gameLoop() {
	int ch = 0;
	
	while (currentAppState == RUNNING) {
		clock_t baseTime = time(NULL);

		while (1) {
			setField(currentBlockPositionX, currentBlockPositionY, inControlBlock);

			drawField();


//**********************************追加*************************************
			drawNextBlockField();
//***************************************************************************

//++++++++++++++++++++++++++++++++++追加+++++++++++++++++++++++++++++++++++++
			drawStockBlockField();
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

			ch = getch();

			unsetField(currentBlockPositionX, currentBlockPositionY, inControlBlock);

			playerOperate(ch);

			clock_t currentTime = time(NULL);
			double diff = difftime(currentTime, baseTime);
			if (diff >= FALL_TIME) {
				break;
			}
		}

		int is_fallen = moveBlock(currentBlockPositionX, currentBlockPositionY + 1);

		if (!is_fallen) {
			fixBlock();
			eraseCompleteLine();
			generateBlock(FALL_BASE_X, FALL_BASE_Y);
//**********************************追加*************************************
			unsetNextField(nextControlBlock);
			setNextField(nextControlBlock);
//***************************************************************************
			if (isCollision(FALL_BASE_X, FALL_BASE_Y, inControlBlock)) {
				currentAppState = GAME_OVER;
			}
		}
		showScore();
		showGuide();
	}

	if (currentAppState == GAME_OVER) {
		showGameOverScreen();
	}
}


