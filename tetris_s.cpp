#include "stdafx.h"
#include <curses.h>
#include <io.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "tetris.h"

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
			if (nextBlockField[h][w] == FIX) {
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
			if (stockBlockField[h][w] == FIX) {
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



void setNextField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				nextBlockField[h + 1][w + 1] = setBuf[h][w];	//枠分を足している
			}
		}
	}
}

void setStockField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				stockBlockField[h + 1][w + 1] = setBuf[h][w];	//枠分を足している
			}
		}
	}
}

void unsetControlBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			inControlBlock[h][w] = FREE;
		}
	}
}

void unsetNextField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			nextBlockField[h + 1][w + 1] = FREE;	//枠分を足している
		}
	}
}

void unsetStockField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			stockBlockField[h + 1][w + 1] = FREE;
		}
	}
}

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
				if (currentBlockPositionX >= FIELD_WIDTH - 3) {
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

void setControlBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			inControlBlock[h][w] = setBuf[h][w];
		}
	}
}

void setNextControlBlock(int kind) {

	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			nextControlBlock[h][w] = blocks[kind][h][w];
		}
	}
}

void setStockControlBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			stockControlBlock[h][w] = setBuf[h][w];
		}
	}
}