#pragma once

#include <Windows.h>	//for Sleep and colors
#include "gameConfig.h"
//#include "baseGhost.h"
//#include "regularGhost.h"
//#include "specialGhost.h"

#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ios>
#include <vector>
#include <string>


class Board {
	static constexpr int LIFE_POS_X = 11  ;		// Position in the board that hold the number lives of mario
	static constexpr int LIFE_POS_Y = 1;

	std::vector<std::string> files_names_vec;	// Vector to store file names
	std::string directory = ".";				// Directory path for file operations (default is current directory)


	char originalBoard[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1];		// The board that we will load from the file
	char start_screen[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1] = {
		 //01234567890123456789012345678901234567890123456789012345678901234567890123456789
		R"(********************************************************************************)", //0
		R"(*                                                                              *)", //1
		R"(*                                                                              *)", //2
		R"(*                                                                              *)", //3
		R"(*      *****************************************************************       *)", //4
		R"(*      * ____              _                     _  __                 *       *)", //5
		R"(*      *|  _ \  ___  _ __ | | _____ _   _       | |/ /___  _ __   __ _ *       *)", //6
		R"(*      *| | | |/ _ \| '_ \| |/ / _ \ | | |      | ' // _ \| '_ \ / _` |*       *)", //7
		R"(*      *| |_| | (_) | | | |   <  __/ |_| |      | . \ (_) | | | | (_| |*       *)", //8
		R"(*      *|____/ \___/|_| |_|_|\_\___|\__, |      |_|\_\___/|_| |_|\__, |*       *)", //9
		R"(*      *                            |___/                        |___/ *       *)", //10
		R"(*      *****************************************************************       *)", //11
		R"(*                                                                              *)", //12
		R"(*                                                                              *)", //13
		R"(*                                                                              *)", //14
		R"(*          (1) Start new game                                                  *)", //15
		R"(*          (8) Show instructions and keys                                      *)", //16
		R"(*          (9) Exit                                                            *)", //17
		R"(*                                                                              *)", //18
		R"(*                                                                              *)", //19
		R"(*                                                                              *)", //20
		R"(*                                                                              *)", //21
		R"(*                                                                              *)", //22
		R"(*                                                                              *)", //23
		R"(********************************************************************************)"  //24
	};
	
	char instruction_screen[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1] = {
		//01234567890123456789012345678901234567890123456789012345678901234567890123456789
		 "********************************************************************************",//0
		 "*                                                                              *",//1
		 "*                          GAME INSTRUCTIONS AND KEYS                          *",//2
		 "*                                                                              *",//3
		 "* Instructions:                                                                *",//4
		 "* - The goal is to help Mario (@) rescue Pauline ($) while avoiding barrels.   *",//5
		 "* - Donkey Kong (&) throws barrels that move across floors (<, >, =).          *",//6
		 "* - Use ladders (H), jumps, and a hammer (p) to avoid barrels and ghosts (x).  *",//7
		 "* - Mario loses a life if hit by a barrel, ghost, or falls from a height.      *",//8
		 "* - Mario has 3 lives; losing all ends the game.                               *",//9
		 "* - Barrels explode if they fall 8 lines, damaging nearby areas.               *",//10
		 "* - Ghosts move randomly and harm Mario on contact.                            *",//11
		 "* - The stage restarts after losing a life.                                    *",//12
		 "* - Reach Pauline to win the stage.                                            *",//13
		 "*                                                                              *",//14
		 "* Keys:                                                                        *",//15
		 "* - A/a: Move left                     - D/d: Move right                       *",//16
		 "* - W/w: Jump or climb up a ladder     - X/x: Climb down a ladder              *",//17
		 "* - S/s: Stay in place                 - P/p: Use hammer                       *",//18
		 "* - (9): Back to the menu              - ESC: Pause, press again to resume     *",//19
		 "*                                                                              *",//20
		 "*                                                                              *",//21
		 "*                                            < Press 'R' to return to menu >   *",//22
		 "*                                                                              *",//23
		 "********************************************************************************" //24
	};

	char losing_screen[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1] = {
		 //01234567890123456789012345678901234567890123456789012345678901234567890123456789
		R"(********************************************************************************)",//0
		R"(*                                                                              *)",//1
		R"(*                                                                              *)",//2
		R"(*                                                                              *)",//3
		R"(*                                                                              *)",//4
		R"(*                                                                              *)",//5
		R"(*                                                                              *)",//6
		R"(*                                                                              *)",//7
		R"(*                                                                              *)",//8
		R"(*             ____                         ___                 _               *)",//9
		R"(*            / ___| __ _ _ __ ___   ___   / _ \__   _____ _ __| |              *)",//10
		R"(*           | |  _ / _` | '_ ` _ \ / _ \ | | | \ \ / / _ \ '__| |              *)",//11
		R"(*           | |_| | (_| | | | | | |  __/ | |_| |\ V /  __/ |  |_|              *)",//12
		R"(*            \____|\__,_|_| |_| |_|\___|  \___/  \_/ \___|_|  (_)              *)",//13
		R"(*                                                                              *)",//14
		R"(*                                                                              *)",//15
		R"(*                                                                              *)",//16
		R"(*                                                                              *)",//17
		R"(*                                                                              *)",//18
		R"(*                                                                              *)",//19
		R"(*                                                                              *)",//20
		R"(*                                                                              *)",//21
		R"(*                                                                              *)",//22
		R"(*                                                                              *)",//23
		R"(********************************************************************************)" //24
	};

	char winning_screen[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1] = {
		 //01234567890123456789012345678901234567890123456789012345678901234567890123456789
		R"(********************************************************************************)",//0
		R"(*                                                                              *)",//1
		R"(*                                                                              *)",//2
		R"(*                                                                              *)",//3
		R"(*                                                                              *)",//4
		R"(*                                                                              *)",//5
		R"(*                                                                              *)",//6
		R"(*           _____                                              _____           *)",//7
		R"(*           (___)                                              (___)           *)",//8
		R"(*           |   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|   |           *)",//9
		R"(*           |   | __   __           __        __            _  |   |           *)",//10
		R"(*           |   | \ \ / /__  _   _  \ \      / /__  _ __   | | |   |           *)",//11
		R"(*           |   |  \ V / _ \| | | |  \ \ /\ / / _ \| '_ \  | | |   |           *)",//12
		R"(*           |   |   | | (_) | |_| |   \ V  V / (_) | | | | |_| |   |           *)",//13
		R"(*           |   |   |_|\___/ \__,_|    \_/\_/ \___/|_| |_| (_) |   |           *)",//14
		R"(*           |___|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|___|           *)",//15
		R"(*          (_____)                                            (_____)          *)",//16
		R"(*                                                                              *)",//17
		R"(*                                                                              *)",//18
		R"(*                                                                              *)",//19
		R"(*                                                                              *)",//20
		R"(*                                                                              *)",//21
		R"(*                                                                              *)",//22
		R"(*                                                                              *)",//23
		R"(********************************************************************************)" //24
	};

	char next_stage_screen[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1] = {
		 //01234567890123456789012345678901234567890123456789012345678901234567890123456789
		R"(********************************************************************************)",//0
		R"(*                                                                              *)",//1
		R"(*                                                                              *)",//2
		R"(*                                                                              *)",//3
		R"(*                                                                              *)",//4
		R"(*                                                                              *)",//5
		R"(*                                                                              *)",//6
		R"(*                   _                        _             _                   *)",//7
		R"(*                  / \   _ __ ___   __ _ ___(_)_ __   __ _| |                  *)",//8
		R"(*                 / _ \ | '_ ` _ \ / _` |_  / | '_ \ / _` | |                  *)",//9
		R"(*                / ___ \| | | | | | (_| |/ /| | | | | (_| |_|                  *)",//10
		R"(*               /_/   \_\_| |_| |_|\__,_/___|_|_| |_|\__, (_)                  *)",//11
		R"(*                                                    |___/                     *)",//12
		R"(*                                                                              *)",//13
		R"(*                                                                              *)",//14
		R"(*                        -Moving to the next stage-                            *)",//15
		R"(*                                                                              *)",//16
		R"(*                                                                              *)",//17
		R"(*                                                                              *)",//18
		R"(*                                                                              *)",//19
		R"(*                                                                              *)",//20
		R"(*                                                                              *)",//21
		R"(*                                                                              *)",//22
		R"(*                                                                              *)",//23
		R"(********************************************************************************)" //24
	};                    

	char goodBye_screen[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1] = {
		 //01234567890123456789012345678901234567890123456789012345678901234567890123456789
		R"(********************************************************************************)",//0
		R"(*                                                                              *)",//1
		R"(*                                                                              *)",//2
		R"(*                                                                              *)",//3
		R"(*                                                                              *)",//4
		R"(*                                                                              *)",//5
		R"(*                                                                              *)",//6
		R"(*                                                                              *)",//7
		R"(*                                                                              *)",//8
		R"(*             **************************************************               *)",//9
		R"(*             *  ____                 _   ____               _ *               *)",//10
		R"(*             * / ___| ___   ___   __| | | __ ) _   _  ___  | |*               *)",//11
		R"(*             *| |  _ / _ \ / _ \ / _` | |  _ \| | | |/ _ \ | |*               *)",//12
		R"(*             *| |_| | (_) | (_) | (_| | | |_) | |_| |  __/ |_|*               *)",//13
		R"(*             * \____|\___/ \___/ \__,_| |____/ \__, |\___| (_)*               *)",//14
		R"(*             *                                 |___/          *               *)",//15
		R"(*             **************************************************               *)",//16
		R"(*                                                                              *)",//17
		R"(*                                                                              *)",//18
		R"(*                                                                              *)",//19
		R"(*                                                                              *)",//20
		R"(*                                                                              *)",//21
		R"(*                                                                              *)",//22
		R"(*                                                                              *)",//23
		R"(********************************************************************************)" //24
	};

	char chooseBoard_screen[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1] = {
		 //01234567890123456789012345678901234567890123456789012345678901234567890123456789
		R"(********************************************************************************)",//0
		R"(*                                                                              *)",//1
		R"(*    ____                               ___        _   _                       *)",//2
		R"(*   / ___|  ___ _ __ ___  ___ _ __     / _ \ _ __ | |_(_) ___  _ __  ___   _   *)",//3
		R"(*   \___ \ / __| '__/ _ \/ _ \ '_ \   | | | | '_ \| __| |/ _ \| '_ \/ __| (_)  *)",//4
		R"(*    ___) | (__| | |  __/  __/ | | |  | |_| | |_) | |_| | (_) | | | \__ \  _   *)",//5
		R"(*   |____/ \___|_|  \___|\___|_| |_|   \___/| .__/ \__|_|\___/|_| |_|___/ (_)  *)",//6
		R"(*                                           |_|                                *)",//7
		R"(*                                                                              *)",//8
		R"(*                                                                              *)",//9
		R"(*                                                                              *)",//10
		R"(*                                                                              *)",//11
		R"(*                                                                              *)",//12
		R"(*                                                                              *)",//13
		R"(*                                                                              *)",//14
		R"(*                                                                              *)",//15
		R"(*                                                                              *)",//16
		R"(*                                                                              *)",//17
		R"(*                                                                              *)",//18
		R"(*                                                                              *)",//19
		R"(*                                                                              *)",//20
		R"(*                                                                              *)",//21
		R"(*                                                                              *)",//22
		R"(*                                                                              *)",//23
		R"(********************************************************************************)" //24
	};
	char currentBoard[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1]; // +1 for null terminator

	// Starting position for Mario, gorilla, princess and hammer
	GameConfig::Position start_pos_mario{ 0,0 };
	GameConfig::Position start_pos_gorilla{ 0,0 };
	GameConfig::Position start_pos_princess{ 0,0 };
	GameConfig::Position start_pos_hammer{ 0,0 };

	struct GhostTypeAndPosition {
		char type;
		GameConfig::Position pos;
	};
	// Vector to store the starting positions of ghosts
	std::vector<GhostTypeAndPosition> start_pos_and_type_ghosts_vec;



	// Structure to represent the game legend displayed on the board
	struct Legend {
		int score = 0;
		int life = GameConfig::FULL_LIVES;
		char hammer = ' ';
		GameConfig::Position pos_L{ 0,0 };
		GameConfig::Position pos_score_in_legend{ 0,0 };
		GameConfig::Position pos_life_in_legend{ 0,0 };
		GameConfig::Position pos_hammer_in_legend{ 0,0 };

		std::string str_score = "Score: ";
		std::string str_life = "Life: ";
		std::string str_hammer = "Hammer: ";
	};
	Legend legend;

	GameConfig::Position mario_pos{ 0,0 };


	bool is_silent = false;
	bool readen_mario = false;
	bool readen_princess = false;
	bool readen_gorilla = false;
	bool readen_hammer = false;
	int readen_legend = 0;

public:
	void reset();																				// This function resets the board to its original state
	void printScreen(const char screen[][GameConfig::BOARD_WIDTH + 1]) const;										// This function prints the input board to the screen
	char getCharFromBoard(const GameConfig::Position& _pos) const { return currentBoard[_pos.y][_pos.x]; }	// This function retrieves a specific character from the board at position (x, y)
	char getCharFromBoard(int x, int y) const { return currentBoard[y][x]; }					// This function retrieves a specific character from the board at position (x, y)
	void updateBoard(const GameConfig::Position& pos, char newChar) { currentBoard[pos.y][pos.x] = newChar; }	// This function updates the board by replacing the character at position (x, y) with a new character
	void updateBoardOriginal(const GameConfig::Position& pos, char newChar) { originalBoard[pos.y][pos.x] = newChar; }	// This function updates the board by replacing the character at position (x, y) with a new character

	const char(&getCurrentBoard() const)[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1]{ return currentBoard; }				// Returns a const reference to the current board's array
	const char(&getStartBoard() const)[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1]{ return start_screen; }				// Returns a const reference to the initial state of the board (start screen)
	const char(&getInstructionBoard() const)[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1]{ return instruction_screen; }	// Returns a const reference to the board with instructions (instruction screen)
	const char(&getLosingBoard() const)[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1]{ return losing_screen; }				// Returns a const reference to the board shown when the player loses (losing screen)
	const char(&getWinningBoard() const)[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1]{ return winning_screen; }			// Returns a const reference to the board shown when the player wins (winning screen)
	const char(&getNextStageBoard() const)[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1]{ return next_stage_screen; }			// Returns a const reference to the board shown when the player wins (winning screen)
	const char(&getGoodByeBoard() const)[GameConfig::BOARD_HEIGHT][GameConfig::BOARD_WIDTH + 1]{ return goodBye_screen; }			// Returns a const reference to the board shown when the player wins (goodBye screen)

	const int getLifePosX() const { return LIFE_POS_X; }		// Returns the X position in the board that hold the number lives of mario
	const int getLifePosY() const { return LIFE_POS_Y; }		// Returns the Y position in the board that hold the number lives of mario

	void printScreenOptions(const std::vector<std::string>& vec_to_fill) const;		// Print the available screen options from the provided vector
	void getAllBoardFileNames(std::vector<std::string>& vec_to_fill) const;			// Retrieve all board file names and store them in the provided vector
	bool load(const std::string& filename);											// Load the specified board file
	bool handleReadFileErrors(const std::ifstream& _file);							// Handle errors encountered while reading a file
	bool handleUnvalidFile(const std::string& filename, int rows_number) const;						// Handle cases where the given file is invalid
	void manageChar(char& ch, bool& already_readen, GameConfig::Position& pos, int curr_col, int curr_row);	// Process a specific character from the board file, updating its state and position
	const GameConfig::Position& getStartPosMario() const { return start_pos_mario; }						// Get the starting position of Mario
	const GameConfig::Position& getStartPosGorilla() const { return start_pos_gorilla; }					// Get the starting position of Gorilla
	const GhostTypeAndPosition& getStartPosAndTypeOfGhost(int i) const { return start_pos_and_type_ghosts_vec[i]; }			// Get the starting position of the ghost at index 'i'
	
	void setPositionsInLegend();		// Set the positions for the elements in the legend
	void printLegend() const;			// Print the entire legend on the board
	void printLifeLegend() const { GameConfig::gotoxy(legend.pos_life_in_legend.x + (int)(legend.str_life.length()), legend.pos_life_in_legend.y); std::cout << legend.life; }			 // Print the life count in the legend
	void printScoreLegend() const { GameConfig::gotoxy(legend.pos_score_in_legend.x + (int)(legend.str_score.length()), legend.pos_score_in_legend.y); std::cout << legend.score; }		 // Print the life count in the legend
	void printHammerLegend() const { GameConfig::gotoxy(legend.pos_hammer_in_legend.x + (int)(legend.str_hammer.length()), legend.pos_hammer_in_legend.y); std::cout << legend.hammer; } // Print the hammer status in the legend 
	void printEndLevelScore() const;												// Print the current score when finish level					
	void setScoreLegend(int score) { legend.score = score; }				// Set the score in the legend
	void setLifeLegend(int life) { legend.life = life; }					// Set the life count in the legend
	void setHammerLegend(char hammer) { legend.hammer = hammer; }			// Set the hammer status in the legend
	void setLegend(int score, int life, char hammer);						// Set all legend values at once
	int getGhostVectorSize() { return (int)start_pos_and_type_ghosts_vec.size(); }	// Get the size of the ghost positions vector
	
	void resetScore() { legend.score = 0; }									// Reset the player's score to zero
	int getScore() const { return legend.score; }							// Get the current player's score
	void addScore(int _score) { legend.score += _score; }					// Add the given value to the player's score

	void setIsSilent(bool silent_flag) { is_silent = silent_flag; }
	bool getIsSilent() { return is_silent; }

	GameConfig::Position getMarioPosition() const { return mario_pos; }
	void setMarioPosition(GameConfig::Position _mario_pos) { mario_pos = _mario_pos; }
};
