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


//**********************************’Ç‰Á*************************************
void drawNextBlockField() {
	int h, w;

	mvprintw(nextBlockPositionY - 1, nextBlockPositionX, "nextBlock");
	for (h = 0; h < nextBlockFieldSize; h++) {
		for (w = 0; w < nextBlockFieldSize; w++) {
			if (nextBlockField[h][w] == WALL) {
				color_set(BOUNDARY, NULL);
				mvprintw(nextBlockPositionY + h, nextBlockPositionX + w, "|");
			}
			if (nextBlockField[h][w] == FLOOR) {
				color_set(BOUNDARY, NULL);
				mvprintw(nextBlockPositionY + h, nextBlockPositionX + w, "-");
			}
			if (nextBlockField[h][w] == CONTROL) {

				color_set(BLOCK_COLOR1, NULL);
				mvprintw(nextBlockPositionY + h, nextBlockPositionX + w, "@");

			}
			if (nextBlockField[h][w] == FIXED) {
				color_set(BLOCK_COLOR3, NULL);
				mvprintw(nextBlockPositionY + h, nextBlockPositionX + w, "@");


			}
			if (nextBlockField[h][w] == FREE) {
				color_set(BOUNDARY, NULL);

				mvprintw(nextBlockPositionY + h, nextBlockPositionX + w, " ");
			}
		}
	}
}
//***************************************************************************


void setBlock(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				playField[baseY + h][baseX + w] = setBuf[h][w];
			}
		}
	}
}


//**********************************’Ç‰Á*************************************
void setNextBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				nextBlockField[h + 1][w + 1] = setBuf[h][w];	//˜g•ª‚ð‘«‚µ‚Ä‚¢‚é
			}
		}
	}
}
//***************************************************************************



void unsetBlock(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				playField[baseY + h][baseX + w] = FREE;
			}
		}
	}
}

//**********************************’Ç‰Á*************************************
void unsetNextBlock(int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			nextBlockField[h + 1][w + 1] = FREE;	//˜g•ª‚ð‘«‚µ‚Ä‚¢‚é
		}
	}
}
//***************************************************************************

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
	case 'q':
		currentAppState = EXIT_WAIT;
		break;
	}
}

void setNewControlBlock(int kind) {
	assert(0 <= kind && kind < BLOCK_KINDS);
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			inControlBlock[h][w] = blocks[kind][h][w];
		}
	}
}

//**********************************’Ç‰Á*************************************
void setNextControlBlock(int kind) {
	assert(0 <= kind && kind < BLOCK_KINDS);

	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			nextControlBlock[h][w] = blocks[kind][h][w];
		}
	}
}
//***************************************************************************

void generateBlock(int x, int y) {
	currentBlockPositionX = x;
	currentBlockPositionY = y;

	//	setNewControlBlock(rand() % BLOCK_KINDS);
//**********************************’Ç‰Á*************************************
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
	setBlock(currentBlockPositionX, currentBlockPositionY, inControlBlock);

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
	mvprintw(23, 0, "e: ŽžŒv‰ñ‚è");
	mvprintw(23, 14, "w: ”½ŽžŒv‰ñ‚è");
	mvprintw(24, 0, "©: ¶‚ÉˆÚ“®");
	mvprintw(24, 14, "¨: ‰E‚ÉˆÚ“®");
	mvprintw(24, 28, "«: ‰º‚ÉˆÚ“®");
	mvprintw(25, 0, "q: ƒQ[ƒ€I—¹");
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
			setBlock(currentBlockPositionX, currentBlockPositionY, inControlBlock);

			drawField();


//**********************************’Ç‰Á*************************************
			drawNextBlockField();
//***************************************************************************

			ch = getch();

			unsetBlock(currentBlockPositionX, currentBlockPositionY, inControlBlock);

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

//**********************************’Ç‰Á*************************************
			unsetNextBlock(nextControlBlock);
			setNextBlock(nextControlBlock);
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


