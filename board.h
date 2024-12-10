#pragma once

#include "general.h"

class Board {
	static constexpr size_t MAX_X = 80;  //changed from int to size_t
	static constexpr size_t MAX_Y = 25;

	static constexpr int LIFE_POS_X = 11;
	static constexpr int LIFE_POS_Y = 1;

	const char* originalBoard[MAX_Y] = {
		// 01234567890123456789012345678901234567890123456789012345678901234567890123456789
		  "                                                                                ", // 0
		  "     LIFE:                           $                                          ", // 1
		  "                        ==============================                          ", // 2
		  "                        H            &               H                          ", // 3
		  "                        H      =============         H                          ", // 4
		  "                        H                            H                          ", // 5
		  "                        H                            H                          ", // 6
		  "          <<<<<<<<<<<<<<<<<<<<<<<        >>>>>>>>>>>>>>>>>>>>                   ", // 7
		  "            H                                 H                                 ", // 8
		  "            H                                 H                                 ", // 9
		  "            H                                 H           H                     ", // 10
		  "            H                                 H           H                     ", // 11
		  "         >==================            <<<<<<<<<<<<<<<<<<<<<<<<<<<             ", // 12
		  "                       H                                        H               ", // 13
		  "                       H                                        H               ", // 14
		  "                ============<         >===========================<             ", // 15
		  "                  H                               H            H                ", // 16
		  "                  H                               H            H                ", // 17
		  "                  H                               H            H                ", // 18
	      "         =======>================               ====================            ", // 19
	      "          H                                                H                    ", // 20
		  "          H                                                H                    ", // 21
		  "          H                H              H                H                    ", // 22
		  "          H                H              H                H                    ", // 23
		  "================================================================================"  // 24
	};
	char start_screen[MAX_Y][MAX_X + 1] = {
		//01234567890123456789012345678901234567890123456789012345678901234567890123456789
		 "********************************************************************************", //0
		 "*                                                                              *", //1
		 "*                                                                              *", //2
		 "*                                                                              *", //3
		 "*      *****************************************************************       *", //4
		 "*      * ____              _                     _  __                 *       *", //5 
		 "*      *|  _ \\  ___  _ __ | | _____ _   _       | |/ /___  _ __   __ _ *       *", //6
		 "*      *| | | |/ _ \\| '_ \\| |/ / _ \\ | | |      | ' // _ \\| '_ \\ / _` |*       *", //7
		 "*      *| |_| | (_) | | | |   <  __/ |_| |      | . \\ (_) | | | | (_| |*       *", //8
		 "*      *|____/ \\___/|_| |_|_|\\_\\___|\\__, |      |_|\\_\\___/|_| |_|\\__, |*       *", //9
		 "*      *                            |___/                        |___/ *       *", //10
		 "*      *****************************************************************       *", //11
		 "*                                                                              *", //12
		 "*                                                                              *", //13
		 "*                                                                              *", //14
		 "*          (1) Start new game                                                  *", //15
		 "*          (8) Show instructions and keys                                      *", //16
		 "*          (9) Exit                                                            *", //17
		 "*                                                                              *", //18
		 "*                                                                              *", //19
		 "*                                                                              *", //20
		 "*                                                                              *", //21
		 "*                                                                              *", //22
		 "*                                                                              *", //23
		 "********************************************************************************"  //24
	};
	char instruction_screen[MAX_Y][MAX_X + 1] = {
		//01234567890123456789012345678901234567890123456789012345678901234567890123456789
		 "********************************************************************************",//0
		 "*                                                                              *",//1
		 "*                          GAME INSTRUCTIONS AND KEYS                          *",//2
		 "*                                                                              *",//3
		 "* Instructions:                                                                *",//4
		 "* - The goal is to help Mario (@) rescue Pauline ($) while avoiding barrels.   *",//5
		 "* - Donkey Kong (&) throws barrels that move across floors (<, >, =).          *",//6
		 "* - Use ladders (H) and jumps to avoid barrels and reach Pauline.              *",//7 
		 "* - Mario loses a life if hit by a barrel or falls from a height of 5 lines.   *",//8 
		 "* - Mario has 3 lives; losing all ends the game.                               *",//9 
		 "* - Barrels explode if they fall 8 lines, damaging nearby areas.               *",//10 
		 "* - The stage restarts after losing a life.                                    *",//11 
		 "* - Reach Pauline to win the stage.                                            *",//12
		 "*                                                                              *",//13 
		 "*                                                                              *",//14 
		 "* Keys:                                                                        *",//15 
		 "* - A/a: Move left                     - D/d: Move right                       *",//16 
		 "* - W/w: Jump or climb up a ladder     - X/x: Climb down a ladder              *",//17 
		 "* - S/s: Stay in place                 - ESC: Pause, press again to resume     *",//18 
		 "* - 9: Exit the game                                                           *",//19 
		 "*                                                                              *",//20 
		 "*                                                                              *",//21 
		 "*                                            < Press 'R' to return to menu >   *",//22 
		 "*                                                                              *",//23 
		 "********************************************************************************" //24
	};
	char losing_screen[MAX_Y][MAX_X + 1] = {
		//01234567890123456789012345678901234567890123456789012345678901234567890123456789
		 "********************************************************************************",//0
		 "*                                                                              *",//1
		 "*                                                                              *",//2
		 "*                                                                              *",//3
		 "*                                                                              *",//4
		 "*                                                                              *",//5
		 "*                                                                              *",//6
		 "*                         YOU LOST!!                                           *",//7 
		 "*                                                                              *",//8 
		 "*                                                                              *",//9 
		 "*                                                                              *",//10 
		 "*                        YOU ARE A LOSER!!!!!!!!!!!                            *",//11 
		 "*                                                                              *",//12
		 "*                                                                              *",//13 
		 "*                                                                              *",//14 
		 "*                                                                              *",//15 
		 "*                                                                              *",//16 
		 "*                                                                              *",//17 
		 "*                                                                              *",//18 
		 "*                                                                              *",//19 
		 "*                                                                              *",//20 
		 "*                                                                              *",//21 
		 "*                                                                              *",//22 
		 "*                                                                              *",//23 
		 "********************************************************************************" //24
	};

	char lost_life_screen[MAX_Y][MAX_X + 1] = {
		//01234567890123456789012345678901234567890123456789012345678901234567890123456789
		 "********************************************************************************",//0
		 "*                                                                              *",//1
		 "*                                                                              *",//2
		 "*                                                                              *",//3
		 "*                                                                              *",//4
		 "*                                                                              *",//5
		 "*                                                                              *",//6
		 "*                                                                              *",//7 
		 "*                                                                              *",//8 
		 "*                                                                              *",//9 
		 "*                                                                              *",//10 
		 "*                             YOU LOST LIFE                                    *",//11 
		 "*                                                                              *",//12
		 "*                                                                              *",//13 
		 "*                                                                              *",//14 
		 "*                                                                              *",//15 
		 "*                                                                              *",//16 
		 "*                                                                              *",//17 
		 "*                                                                              *",//18 
		 "*                                                                              *",//19 
		 "*                                                                              *",//20 
		 "*                                                                              *",//21 
		 "*                                                                              *",//22 
		 "*                                                                              *",//23 
		 "********************************************************************************" //24
	};

	char currentBoard[MAX_Y][MAX_X + 1]; // +1 for null terminator
public:
	void reset();
	void printScreen(const char screen[][MAX_X + 1]) const;
	char getCharFromBoard(int x, int y) const { return currentBoard[y][x]; }
	void updateBoard(int x, int y, char newChar) { currentBoard[y][x] = newChar; }

	//char(&getCurrentBoard() const)[MAX_Y][MAX_X + 1]{ return currentBoard; }
	const char(&getCurrentBoard() const)[MAX_Y][MAX_X + 1] { return currentBoard; }
	const char(&getStartBoard() const)[MAX_Y][MAX_X + 1]{	return start_screen; }
	const char(&getInstructionBoard() const)[MAX_Y][MAX_X + 1]{	return instruction_screen; }

	const char(&getLosingBoard() const)[MAX_Y][MAX_X + 1]{	return losing_screen; }
	const char(&getLostLifeBoard() const)[MAX_Y][MAX_X + 1]{	return lost_life_screen; }

	int get_board_width() { return MAX_X; }
	int get_board_height() { return MAX_Y; }

	int getLifePosX() { return LIFE_POS_X; }
	int getLifePosY() { return LIFE_POS_Y; }

	void startOver();
};



