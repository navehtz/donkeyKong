#pragma once

#include <Windows.h>	//for Sleep and colors
#include "gameConfig.h"

#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <ios>
#include <vector>
#include <string>


class Board {
	static constexpr size_t MAX_X = 80;			// Board width
	static constexpr size_t MAX_Y = 25;			// Board Height

	static constexpr int LIFE_POS_X = 11  ;		// Position in the board that hold the number lives of mario
	static constexpr int LIFE_POS_Y = 1;

	std::vector<std::string> files_names_vec;	// Vector to store file names
	std::string directory = ".";				// Directory path for file operations (default is current directory)


	char originalBoard[MAX_Y][MAX_X + 1];		// The board that we will load from the file
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

	// Starting position for Mario, gorilla, princess and hammer
	GameConfig::Position start_pos_mario{ 0,0 };
	GameConfig::Position start_pos_gorilla{ 0,0 };
	GameConfig::Position start_pos_princess{ 0,0 };
	GameConfig::Position start_pos_hammer{ 0,0 };

	// Vector to store the starting positions of ghosts
	std::vector<GameConfig::Position> start_pos_ghosts_vec; 

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

	bool readen_mario = false;
	bool readen_princess = false;
	bool readen_gorilla = false;
	bool readen_hammer = false;
	int readen_legend = 0;

public:
	void reset();																				// This function resets the board to its original state
	void printScreen(const char screen[][MAX_X + 1]) const;										// This function prints the input board to the screen
	char getCharFromBoard(const GameConfig::Position& _pos) const { return currentBoard[_pos.y][_pos.x]; }	// This function retrieves a specific character from the board at position (x, y)
	char getCharFromBoard(int x, int y) const { return currentBoard[y][x]; }					// This function retrieves a specific character from the board at position (x, y)
	void updateBoard(const GameConfig::Position& pos, char newChar) { currentBoard[pos.y][pos.x] = newChar; }	// This function updates the board by replacing the character at position (x, y) with a new character
	void updateBoardOriginal(const GameConfig::Position& pos, char newChar) { originalBoard[pos.y][pos.x] = newChar; }	// This function updates the board by replacing the character at position (x, y) with a new character

	const char(&getCurrentBoard() const)[MAX_Y][MAX_X + 1]{ return currentBoard; }				// Returns a const reference to the current board's array
	const char(&getStartBoard() const)[MAX_Y][MAX_X + 1]{ return start_screen; }				// Returns a const reference to the initial state of the board (start screen)
	const char(&getInstructionBoard() const)[MAX_Y][MAX_X + 1]{ return instruction_screen; }	// Returns a const reference to the board with instructions (instruction screen)
	const char(&getLosingBoard() const)[MAX_Y][MAX_X + 1]{ return losing_screen; }				// Returns a const reference to the board shown when the player loses (losing screen)
	const char(&getWinningBoard() const)[MAX_Y][MAX_X + 1]{ return winning_screen; }			// Returns a const reference to the board shown when the player wins (winning screen)
	const char(&getGoodByeBoard() const)[MAX_Y][MAX_X + 1]{ return goodBye_screen; }			// Returns a const reference to the board shown when the player wins (goodBye screen)

	const int get_board_width() const { return MAX_X; }			// Returns the width of the board
	const int get_board_height() const { return MAX_Y; }		// Returns the height of the board

	const int getLifePosX() const { return LIFE_POS_X; }		// Returns the X position in the board that hold the number lives of mario
	const int getLifePosY() const { return LIFE_POS_Y; }		// Returns the Y position in the board that hold the number lives of mario

	void printScreenOptions(const std::vector<std::string>& vec_to_fill) const;		// Print the available screen options from the provided vector
	void getAllBoardFileNames(std::vector<std::string>& vec_to_fill) const;			// Retrieve all board file names and store them in the provided vector
	bool load(const std::string& filename);											// Load the specified board file
	bool handleReadFileErrors(const std::ifstream& _file);							// Handle errors encountered while reading a file
	bool handleUnvalidFile(const std::string& filename) const;						// Handle cases where the given file is invalid
	void manageChar(char& ch, bool& already_readen, GameConfig::Position& pos, int curr_col, int curr_row);	// Process a specific character from the board file, updating its state and position
	const GameConfig::Position& getStartPosMario() const { return start_pos_mario; }						// Get the starting position of Mario
	const GameConfig::Position& getStartPosGorilla() const { return start_pos_gorilla; }					// Get the starting position of Gorilla
	const GameConfig::Position& getStartPosOfGhost(int i) const { return start_pos_ghosts_vec[i]; }			// Get the starting position of the ghost at index 'i'
	
	void setPositionsInLegend();		// Set the positions for the elements in the legend
	void printLegend() const;			// Print the entire legend on the board
	void printLifeLegend() const { GameConfig::gotoxy(legend.pos_life_in_legend.x + (int)(legend.str_life.length()), legend.pos_life_in_legend.y); std::cout << legend.life; }			 // Print the life count in the legend
	void printScoreLegend() const { GameConfig::gotoxy(legend.pos_score_in_legend.x + (int)(legend.str_score.length()), legend.pos_score_in_legend.y); std::cout << legend.score; }		 // Print the life count in the legend
	void printHammerLegend() const { GameConfig::gotoxy(legend.pos_hammer_in_legend.x + (int)(legend.str_hammer.length()), legend.pos_hammer_in_legend.y); std::cout << legend.hammer; } // Print the hammer status in the legend 
	void setScoreLegend(int score) { legend.score = score; }				// Set the score in the legend
	void setLifeLegend(int life) { legend.life = life; }					// Set the life count in the legend
	void setHammerLegend(char hammer) { legend.hammer = hammer; }			// Set the hammer status in the legend
	void setLegend(int score, int life, char hammer);						// Set all legend values at once
	int getGhostVectorSize() { return (int)start_pos_ghosts_vec.size(); }	// Get the size of the ghost positions vector
	
	void setScore() { legend.score = 0; }									// Reset the player's score to zero
	int getScore() const { return legend.score; }							// Get the current player's score
	void addScore(int _score) { legend.score += _score; }					// Add the given value to the player's score


};
