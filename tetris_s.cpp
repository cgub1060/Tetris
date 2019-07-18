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
				nextBlockField[h + 1][w + 1] = setBuf[h][w];	//�g���𑫂��Ă���
			}
		}
	}
}

void setStockField(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				stockBlockField[h + 1][w + 1] = setBuf[h][w];	//�g���𑫂��Ă���
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
			nextBlockField[h + 1][w + 1] = FREE;	//�g���𑫂��Ă���
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

	//�X�g�b�N���󂩂ǂ����̔���
	//���݂̃X�g�b�N�u���b�N��ێ�
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (w >= 2 && stockControlBlock[h][w] == CONTROL) {
				if (currentBlockPositionX >= FIELD_WIDTH - 3) {
					mvprintw(20, 20, "�g�O�Ƀu���b�N���ł邽�߃X�g�b�N�s��");
					return;
				}
			}
			if (stockControlBlock[h][w] == CONTROL) {
				tmpBlock[h][w] = stockControlBlock[h][w];
				firstStock = FALSE;
			}
		}
	}

	//���ݑ��쒆�̃u���b�N���X�g�b�N
	setStockControlBlock(inControlBlock);

	/*if �X�g�b�N����(���߂ăX�g�b�N���s��)
	* ���ݑ��쒆�̃u���b�N���X�g�b�N
	* ���ݑ��쒆�̃u���b�N���폜
	* ���̃u���b�N���폜
	* �u���b�N��V���ɐ���
	* ���̃u���b�N��\��
	*/

	/*else �X�g�b�N����ł͂Ȃ�(�X�g�b�N�����ɍs���Ă���)
	* �X�g�b�N���\����
	* ���ݑ��쒆�̃u���b�N��
	* stockControlBlock��kind����inControlBlock�𐶐�
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