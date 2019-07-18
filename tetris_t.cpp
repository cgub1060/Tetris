#include "stdafx.h"
#include <curses.h>
#include <io.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "tetris.h"

void Startdraw() {
	
	color_set(MOZI1,NULL);
	/*文字Tを表示*/
	mvaddstr(5, 4, "Tetris");
	mvaddstr(5, 10, "Tetris");
	mvaddstr(5, 16, "Tet");
	mvaddstr(6, 11, "t");
	mvaddstr(7, 11, "r");
	mvaddstr(8, 11, "i");
	mvaddstr(9, 11, "s");
	mvaddstr(10, 11, "T");
	mvaddstr(11, 11, "e");

	/*文字Eの表示*/
	mvaddstr(5, 23, "Tetris");
	mvaddstr(5, 29, "Tetris");
	mvaddstr(6, 23, "e");
	mvaddstr(7, 23, "t");
	mvaddstr(8, 23, "r");
	mvaddstr(9, 23, "i");
	mvaddstr(10, 23, "s");
	mvaddstr(11, 23, "T");
	mvaddstr(8, 24, "isTetrisTet");
	mvaddstr(11, 24, "etrisTetri");

	/*文字Tを表示*/
	mvaddstr(5, 38, "Tetris");
	mvaddstr(5, 44, "Tetris");
	mvaddstr(5, 50, "Tet");
	mvaddstr(6, 45, "t");
	mvaddstr(7, 45, "r");
	mvaddstr(8, 45, "i");
	mvaddstr(9, 45, "s");
	mvaddstr(10, 45, "T");
	mvaddstr(11, 45, "e");
	/*文字Rの表示*/
	mvaddstr(5, 57, "Tetris");
	mvaddstr(5, 63, "Tetris");
	mvaddstr(6, 70, "T");
	mvaddstr(7, 70, "e");
	mvaddstr(8, 57, "risTet");
	mvaddstr(8, 63, "risTet");
	mvaddstr(6, 57, "e");
	mvaddstr(7, 57, "t");
	mvaddstr(9, 57, "i");
	mvaddstr(10, 57, "s");
	mvaddstr(11, 57, "T");
	mvaddstr(9, 66, "i");
	mvaddstr(10, 67, "s");
	mvaddstr(11, 68, "T");
	/*文字Iの表示*/
	mvaddstr(5, 75, "Tetris");
	mvaddstr(5, 81, "Tetrist");
	mvaddstr(6, 81, "e");
	mvaddstr(7, 81, "t");
	mvaddstr(8, 81, "r");
	mvaddstr(9, 81, "i");
	mvaddstr(10, 81, "s");
	mvaddstr(11, 81, "T");
	mvaddstr(11, 75, "Tetris");
	mvaddstr(11, 82, "etrist");
	/*文字Sの表示*/
	mvaddstr(5, 92, "TetrisTetrisTet");
	mvaddstr(6, 92, "e");
	mvaddstr(7, 92, "t");
	mvaddstr(8, 92, "isTetrisTetris");
	mvaddstr(9, 106, "T");
	mvaddstr(10, 106, "e");
	mvaddstr(11, 92, "TetrisTetrisTe");
	color_set(MOZI2,NULL);
	/*グループメンバー*/
	mvaddstr(25, 4, "・メンバー・");
	mvaddstr(26, 2, "1116171015 池田仁");
	mvaddstr(27, 2, "1116171059 須原圭祐");
	mvaddstr(28, 2, "1116171060 高橋皓大");

	/*ゲームスタート説明*/
	mvaddstr(20, 85, "PLAYER1(1人プレイ）→PUSH　A");
	mvaddstr(22, 85, "PLAYER2(2人プレイ）→PUSH　B");
	// 終了
	while (1) {
		int c = getch();
		if (c == 'a') {
			break;
		}
	}

}
void Finishdraw() {
	init_pair(1, COLOR_WHITE, COLOR_BLACK);	// 色1 は青地に赤文字
	init_pair(2, COLOR_GREEN, COLOR_BLACK);	// 色2 は青地に緑文字
	init_pair(3, COLOR_YELLOW, COLOR_BLUE);	// 色3 は青地に黄文字
	init_pair(10, COLOR_WHITE, COLOR_BLUE);	// 色10 は青地に白文字
	bkgd(COLOR_PAIR(2));			// 背景は色10

									// 表示
	attrset(COLOR_PAIR(2));			// 色1 を使う


									/*文字Gの表示*/
	mvaddstr(5, 4, " etrisTet  ");
	mvaddstr(6, 4, "e          ");
	mvaddstr(7, 4, "t          ");
	mvaddstr(8, 4, "r          ");
	mvaddstr(9, 4, "i     trisT");
	mvaddstr(10, 4, "s       i e");
	mvaddstr(11, 4, " etrisTet t");
	/*文字Aの表示*/
	mvaddstr(5, 19, "      T      ");
	mvaddstr(6, 19, "     e e     ");
	mvaddstr(7, 19, "    t   t    ");
	mvaddstr(8, 19, "   r     r   ");
	mvaddstr(9, 19, "  isTetrisi  ");
	mvaddstr(10, 19, " s         s ");
	mvaddstr(11, 19, "T           T");
	/*文字Mの表示*/
	mvaddstr(5, 35, "T         T");
	mvaddstr(6, 35, "e e     e e");
	mvaddstr(7, 35, "t  t   t  t");
	mvaddstr(8, 35, "r   r r   r");
	mvaddstr(9, 35, "i    i    i");
	mvaddstr(10, 35, "s         s");
	mvaddstr(11, 35, "T         T");
	/*文字Eの表示*/
	mvaddstr(5, 49, "TetrisTetri");
	mvaddstr(6, 49, "e          ");
	mvaddstr(7, 49, "t          ");
	mvaddstr(8, 49, "rirTetrisTe");
	mvaddstr(9, 49, "i          ");
	mvaddstr(10, 49, "s          ");
	mvaddstr(11, 49, "TetrisTetri");
	/*文字Oの表示*/
	mvaddstr(14, 49, " etrisTetr");
	mvaddstr(15, 49, "e         s");
	mvaddstr(16, 49, "t         T");
	mvaddstr(17, 49, "r         e");
	mvaddstr(18, 49, "i         t");
	mvaddstr(19, 49, "s         r");
	mvaddstr(20, 49, " etrisTet");
	/*文字Vの表示*/
	mvaddstr(14, 63, "T         T");
	mvaddstr(15, 63, "e         e");
	mvaddstr(16, 63, " t       t");
	mvaddstr(17, 63, "  r     r ");
	mvaddstr(18, 63, "   i   i  ");
	mvaddstr(19, 63, "    s s   ");
	mvaddstr(20, 63, "     T    ");
	/*文字Eの表示*/
	mvaddstr(14, 77, "TetrisTetri");
	mvaddstr(15, 77, "e          ");
	mvaddstr(16, 77, "t          ");
	mvaddstr(17, 77, "rirTetrisTe");
	mvaddstr(18, 77, "i          ");
	mvaddstr(19, 77, "s          ");
	mvaddstr(20, 77, "TetrisTetri");
	/*文字Rの表示*/
	mvaddstr(14, 91, "TetrisTetr");
	mvaddstr(15, 91, "e         s");
	mvaddstr(16, 91, "t         T");
	mvaddstr(17, 91, "rirTetrisT ");
	mvaddstr(18, 91, "i       r  ");
	mvaddstr(19, 91, "s        i ");
	mvaddstr(20, 91, "T          s");

	timeout(-1);

	// 終了
	getch();


}