#include "stdafx.h"
#include <curses.h>
#include <io.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "tetris.h"

void getCurrentDirectory(char *currentDirectory) {
	GetCurrentDirectory(CHARBUFF, currentDirectory);
}
void getData() {
	char currentDirectory[CHARBUFF];
	getCurrentDirectory(currentDirectory);
	char settingFile[CHARBUFF];
	sprintf_s(settingFile, "%s\\setting.ini", currentDirectory);

	char section[CHARBUFF];
	sprintf_s(section, "define1");
	char keyWord[CHARBUFF];
	sprintf_s(keyWord, "currentBlockPositionX");
	currentBlockPositionX = GetPrivateProfileInt(section, keyWord, -1, settingFile);
	sprintf_s(keyWord, "currentBlockPositionY");
	currentBlockPositionY = GetPrivateProfileInt(section, keyWord, -1, settingFile);
	sprintf_s(keyWord, "gameScore");
	tetris.SCORE = GetPrivateProfileInt(section, keyWord, -1, settingFile);
	sprintf_s(keyWord, "gameLevel");
	tetris.LEVEL = GetPrivateProfileInt(section, keyWord, -1, settingFile);

}
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
			if (playField[h][w] == FIX) {
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
void setBlock(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				playField[baseY + h][baseX + w] = setBuf[h][w];
			}
		}
	}
}

void unsetBlock(int baseX, int baseY, int setBuf[BLOCK_HEIGHT][BLOCK_WIDTH]) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			if (setBuf[h][w] == CONTROL) {
				playField[baseY + h][baseX + w] = FREE;
			}
		}
	}
}

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
				buf[h][w] = inControlBlock[pw][ph];
			}
		}
	}
	else {
		for (int h = 0; h < BLOCK_HEIGHT; h++) {
			for (int w = 0; w < BLOCK_WIDTH; w++) {
				int pw = w;
				int ph = (BLOCK_WIDTH - 1) - h;
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

void play(int ch) {
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
	case 's':
		stockBlock();
		break;
	case 'p':
		currentAppState = EXIT_WAIT;
		break;
	}
}

void setNewControlBlock(int kind) {
	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			inControlBlock[h][w] = blocks[kind][h][w];
		}
	}
}

void generateBlock(int x, int y) {
	currentBlockPositionX = x;
	currentBlockPositionY = y;
	static int generateBlockNum = 10;
	if (generateBlockNum == 10) {
		generateBlockNum = rand() % BLOCK_KINDS;
		//generateBlockNum = 0;
	}
	setNewControlBlock(generateBlockNum);
	generateBlockNum = rand() % BLOCK_KINDS;
	//generateBlockNum = 0;
	setNextControlBlock(generateBlockNum);

}

void fixBlock() {
	setBlock(currentBlockPositionX, currentBlockPositionY, inControlBlock);

	for (int h = 0; h < BLOCK_HEIGHT; h++) {
		for (int w = 0; w < BLOCK_WIDTH; w++) {
			int ph = currentBlockPositionY + h;
			int pw = currentBlockPositionX + w;

			if ((0 < ph && ph < FIELD_HEIGHT - 1) &&
				(0 < pw && pw < FIELD_WIDTH - 1)) {
				if (playField[currentBlockPositionY + h][currentBlockPositionX + w] == CONTROL) {
					playField[currentBlockPositionY + h][currentBlockPositionX + w] = FIX;
				}
			}
		}
	}
}

int isCompleteLine(int line) {
	for (int w = 0; w < FIELD_WIDTH; w++) {
		if (playField[line][w] != FIX && playField[line][w] != WALL) {
			return 0;
		}
	}
	return 1;
}

void eraseLine(int line) {
	for (int w = 0; w < FIELD_WIDTH; w++) {
		if (playField[line][w] == FIX) {
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

			tetris.SCORE += 5;
			tetris.LEVEL += 1;

		}
	}
}
void showGuide() {
	mvprintw(23, 0, "e: 時計回り");
	mvprintw(23, 14, "w: 反時計回り");
	mvprintw(23, 28, "s: ストック");
	mvprintw(24, 0, "←: 左に移動");
	mvprintw(24, 14, "→: 右に移動");
	mvprintw(24, 28, "↓: 下に移動");
	mvprintw(25, 0, "p: ゲーム終了");
}

void showRecord() {
	mvprintw(1, FIELD_WIDTH + 1, "SCORE: %d", tetris.SCORE);
	mvprintw(2, FIELD_WIDTH + 1, "LEVEL: %d", tetris.LEVEL);
}

void initializeColor() {
	init_pair(BOUNDARY, COLOR_WHITE, COLOR_WHITE);
	init_pair(BLOCK_COLOR1, COLOR_CYAN, COLOR_CYAN);
	init_pair(BLOCK_COLOR2, COLOR_GREEN, COLOR_GREEN);
	init_pair(BLOCK_COLOR3, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(BLOCK_COLOR4, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(BLOCK_COLOR5, COLOR_RED, COLOR_RED);
	init_pair(MOZI1, COLOR_YELLOW, COLOR_BLACK);
	init_pair(MOZI2, COLOR_CYAN, COLOR_BLACK);
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
			
			drawNextBlockField();

			drawStockBlockField();
			ch = getch();

			unsetBlock(currentBlockPositionX, currentBlockPositionY, inControlBlock);

			play(ch);

			clock_t currentTime = time(NULL);
			double diff = difftime(currentTime, baseTime);
			if (tetris.LEVEL < 10) {
				if (diff >= FALL_TIME - (tetris.LEVEL * 0.1)) {
					break;
				}
			}
			else if (tetris.LEVEL >= 10) {
				if (diff >= FALL_TIME - 0.9) {
					break;
				}
			}
		}

		int is_fallen = moveBlock(currentBlockPositionX, currentBlockPositionY + 1);

		if (!is_fallen) {
			fixBlock();
			eraseCompleteLine();
			generateBlock(FALL_BASE_X, FALL_BASE_Y);
			unsetNextField(nextControlBlock);
			setNextField(nextControlBlock);

			if (isCollision(FALL_BASE_X, FALL_BASE_Y, inControlBlock)) {
				currentAppState = GAME_OVER;
			}
		}
		showRecord();
		showGuide();
	}

	if (currentAppState == GAME_OVER) {
		clear();
		Finishdraw();
		errno_t error;
		error = fopen_s(&fp, "kadai.txt", "w");
		if (error != 0) {
			fprintf_s(stderr, "failed to open");
		}
		else {
			fprintf(fp, "%s%s\n", "自分のスコア ","到達レベル");
			fprintf(fp, "%d%s%d\n",tetris.SCORE,"　　　　　　",tetris.LEVEL);
			fclose(fp);
		}
	}
}


