#pragma once

#include <Windows.h>	//for Sleep and colors
#include "general.h"

#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ios>
#include <vector>
#include <string>


class Board {
	static constexpr size_t MAX_X = 80;		// Board width
	static constexpr size_t MAX_Y = 25;		// Board Height

	static constexpr int LIFE_POS_X = 11  ;	// Position in the board that hold the number lives of mario
	static constexpr int LIFE_POS_Y = 1;

	std::vector<std::string> files_names_vec;
	std::string directory = ".";


	char originalBoard[MAX_Y][MAX_X + 1];
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
	char choose_boardscreens_picks[MAX_Y][MAX_X + 1] = {
		//01234567890123456789012345678901234567890123456789012345678901234567890123456789
		 "********************************************************************************", //0
		 "*                                                                              *", //1
		 "*                                                                              *", //2
		 "*                                                                              *", //3
		 "*                                                                              *", //4
		 "*                                                                              *", //5 
		 "*                                                                              *", //6
		 "*                                                                              *", //7
		 "*                                                                              *", //8
		 "*                                                                              *", //9
		 "*                                                                              *", //10
		 "*                                                                              *", //11
		 "*                                                                              *", //12
		 "*                                                                              *", //13
		 "*                                                                              *", //14
		 "*                                                                              *", //15
		 "*                                                                              *", //16
		 "*                                                                              *", //17
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
		 "* - S/s: Stay in place                 - P/p: Throw a hammer                   *",//18 
		 "* - (9): Back to the menu              - ESC: Pause, press again to resume     *",//19 
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
		 "*                                                                              *",//7
		 "*                                                                              *",//8
		 "*                __   __             _              _      _                   *",//9
		 "*                \\ \\ / /__  _   _   | |    ___  ___| |_   | |                  *",//10
		 "*                 \\ V / _ \\| | | |  | |   / _ \\/ __| __|  | |                  *",//11
		 "*                  | | (_) | |_| |  | |__| (_) \\__ \\ |_   |_|                  *",//12
		 "*                  |_|\\___/ \\__,_|  |_____\\___/|___/\\__|  (_)                  *",//13
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
	char winning_screen[MAX_Y][MAX_X + 1] = {
		//01234567890123456789012345678901234567890123456789012345678901234567890123456789
		 "********************************************************************************",//0
		 "*                                                                              *",//1
		 "*                                                                              *",//2
		 "*                                                                              *",//3
		 "*                                                                              *",//4
		 "*                                                                              *",//5
		 "*                                                                              *",//6
		 "*           _____                                              _____           *",//7
		 "*           (___)                                              (___)           *",//8
		 "*           |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   |           *",//9
		 "*           |   | __   __           __        __            _  |   |           *",//10
		 "*           |   | \\ \\ / /__  _   _  \\ \\      / /__  _ __   | | |   |           *",//11
		 "*           |   |  \\ V / _ \\| | | |  \\ \\ /\\ / / _ \\| '_ \\  | | |   |           *",//12
		 "*           |   |   | | (_) | |_| |   \\ V  V / (_) | | | | |_| |   |           *",//13
		 "*           |   |   |_|\\___/ \\__,_|    \\_/\\_/ \\___/|_| |_| (_) |   |           *",//14
		 "*           |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___|           *",//15
		 "*          (_____)                                            (_____)          *",//16
		 "*                                                                              *",//17
		 "*                                                                              *",//18
		 "*                                                                              *",//19 
		 "*                                                                              *",//20 
		 "*                                                                              *",//21
		 "*                                                                              *",//22 
		 "*                                                                              *",//23 
		 "********************************************************************************" //24

	};
	char goodBye_screen[MAX_Y][MAX_X + 1] = {
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
		 "*             **************************************************               *",//9
		 "*             *  ____                 _   ____               _ *               *",//10
		 "*             * / ___| ___   ___   __| | | __ ) _   _  ___  | |*               *",//11
		 "*             *| |  _ / _ \\ / _ \\ / _` | |  _ \\| | | |/ _ \\ | |*               *",//12
		 "*             *| |_| | (_) | (_) | (_| | | |_) | |_| |  __/ |_|*               *",//13
		 "*             * \\____|\\___/ \\___/ \\__,_| |____/ \\__, |\\___| (_)*               *",//14
		 "*             *                                 |___/          *               *",//15
		 "*             **************************************************               *",//16         
		 "*                                                                              *",//17
		 "*                                                                              *",//18 
		 "*                                                                              *",//19 
		 "*                                                                              *",//20 
		 "*                                                                              *",//21 
		 "*                                                                              *",//22 
		 "*                                                                              *",//23 
		 "********************************************************************************" //24
	};
	char chooseBoard_screen[MAX_Y][MAX_X + 1] = {
		//01234567890123456789012345678901234567890123456789012345678901234567890123456789
		 "********************************************************************************",//0
		 "*                                                                              *",//1
		 "*    ____                               ___        _   _                       *",//2
		 "*   / ___|  ___ _ __ ___  ___ _ __     / _ \\ _ __ | |_(_) ___  _ __  ___   _   *",//3
		 "*   \\___ \\ / __| '__/ _ \\/ _ \\ '_ \\   | | | | '_ \\| __| |/ _ \\| '_ \\/ __| (_)  *",//4
		 "*    ___) | (__| | |  __/  __/ | | |  | |_| | |_) | |_| | (_) | | | \\__ \\  _   *",//5
		 "*   |____/ \\___|_|  \\___|\\___|_| |_|   \\___/| .__/ \\__|_|\\___/|_| |_|___/ (_)  *",//6
		 "*                                           |_|                                *",//7
		 "*                                                                              *",//8
		 "*                                                                              *",//9
		 "*                                                                              *",//10
		 "*                                                                              *",//11
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

	Position start_pos_mario{ 0,0 };
	Position start_pos_gorilla{ 0,0 };
	Position start_pos_princess{ 0,0 };
	Position start_pos_hammer{ 0,0 };
	std::vector<Position> start_pos_ghosts_vec;

	struct Legend {
		int score = 0;
		int life = FULL_LIVES;
		char hammer = ' ';
		Position pos_L{ 0,0 };
		Position pos_score_in_legend{ 0,0 };
		Position pos_life_in_legend{ 0,0 };
		Position pos_hammer_in_legend{ 0,0 };

		std::string str_score = "Score: ";
		std::string str_life = "Life: ";
		std::string str_hammer = "Hammer: ";
	};
	Legend legend;

	bool readen_mario = false;
	bool readen_princess = false;
	bool readen_gorilla = false;
	int readen_legend = 0;

public:
	void reset();																				// This function resets the board to its original state
	void printScreen(const char screen[][MAX_X + 1]) const;										// This function prints the input board to the screen
	char getCharFromBoard(Position _pos) const { return currentBoard[_pos.y][_pos.x]; }					// This function retrieves a specific character from the board at position (x, y)
	char getCharFromBoard(int x, int y) const { return currentBoard[y][x]; }					// This function retrieves a specific character from the board at position (x, y)
	void updateBoard(Position pos, char newChar) { currentBoard[pos.y][pos.x] = newChar; }				// This function updates the board by replacing the character at position (x, y) with a new character

	const char(&getCurrentBoard() const)[MAX_Y][MAX_X + 1]{ return currentBoard; }				// Returns a const reference to the current board's array
	const char(&getStartBoard() const)[MAX_Y][MAX_X + 1]{ return start_screen; }				// Returns a const reference to the initial state of the board (start screen)
	const char(&getInstructionBoard() const)[MAX_Y][MAX_X + 1]{ return instruction_screen; }	// Returns a const reference to the board with instructions (instruction screen)
	const char(&getLosingBoard() const)[MAX_Y][MAX_X + 1]{ return losing_screen; }				// Returns a const reference to the board shown when the player loses (losing screen)
	const char(&getWinningBoard() const)[MAX_Y][MAX_X + 1]{ return winning_screen; }			// Returns a const reference to the board shown when the player wins (winning screen)
	const char(&getGoodByeBoard() const)[MAX_Y][MAX_X + 1]{ return goodBye_screen; }			// Returns a const reference to the board shown when the player wins (goodBye screen)

	int get_board_width() { return MAX_X; }			// Returns the width of the board
	int get_board_height() { return MAX_Y; }		// Returns the height of the board

	int getLifePosX() { return LIFE_POS_X; }		// Returns the X position in the board that hold the number lives of mario
	int getLifePosY() { return LIFE_POS_Y; }		// Returns the Y position in the board that hold the number lives of mario

	void printScreenOptions(std::vector<std::string>& vec_to_fill) const;
	void getAllBoardFileNames(std::vector<std::string>& vec_to_fill) const;
	bool load(const std::string& filename);
	bool handleReadFileErrors(const std::ifstream& _file);
	bool handleUnvalidFile() const;
	void manageChar(char& ch, bool& already_readen, Position& pos, int curr_col, int curr_row);
	Position getStartPosMario() const { return start_pos_mario; }
	Position getStartPosGorilla() const { return start_pos_gorilla; }
	Position getStartPosPauline() const { return start_pos_princess; }
	Position getStartPosHammer() const { return start_pos_hammer; }
	Position getStartPosL() const { return legend.pos_L; }
	Position getStartPosOfGhost(int i) const { return start_pos_ghosts_vec[i]; }

	void setPositionsInLegend();
	void printLegend() const;
	void printLifeLegend() const { gotoxy(legend.pos_life_in_legend.x + (int)(legend.str_life.length()), legend.pos_life_in_legend.y); std::cout << legend.life; }
	void printScoreLegend() const { gotoxy(legend.pos_score_in_legend.x + (int)(legend.str_score.length()), legend.pos_life_in_legend.y); std::cout << legend.score; }
	void printHammerLegend() const { gotoxy(legend.pos_hammer_in_legend.x + (int)(legend.str_hammer.length()), legend.pos_hammer_in_legend.y); std::cout << legend.hammer; }
	void setScoreLegend(int score) { legend.score = score; }
	void setLifeLegend(int life) { legend.life = life; }
	void setHammerLegend(char hammer) { legend.hammer = hammer; }
	void setLegend(int score, int life, char hammer);
	int getGhostVectorSize() { return (int)start_pos_ghosts_vec.size(); }
	Position getGhostPos(int i) { return start_pos_ghosts_vec[i]; }
	
};
