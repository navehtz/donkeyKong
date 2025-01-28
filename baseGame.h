#pragma once

#include <iostream>		//for cout
#include <conio.h>		//for _kbhit(), _getch()
#include <Windows.h>	//for Sleep and colors
#include <vector>
#include <string>

#include "gameConfig.h"
#include "point.h"
#include "mario.h"
#include "board.h"
#include "barrels.h"
#include "ghosts.h"
#include "steps.h"
#include "results.h"

class BaseGame
{
protected:
	static constexpr int START_NEW_GAME = 49;			// The key - 1
	static constexpr int INSTRUCTIONS_AND_KEYS = 56;	//The key - 8
	static constexpr int EXIT_GAME = 57;				//The key - 9
	static constexpr int PAUSE = 27;					//ESC key
	static constexpr int RETURN_BACK = 114;				//The key - r
	static constexpr int LEFT = -1;
	static constexpr int RIGHT = 1;

	bool playing_mario = true;							// True = while mario has more than 0 lives

	bool last_screen = false;							// False = while it isn't the last screen
	size_t iteration = 0;
	bool mario_died_this_iteration = false;
	std::string screenFileName, filename_prefix, stepsFilename, resultsFilename;

	Mario mario;
	Board board;
	Barrels barrels;
	Ghosts ghosts;

	std::vector<std::string> files_names_vec;

	Steps steps;
	Results results;

public:
	virtual void run() = 0;
	virtual void stagesLoop(int screen_index) = 0;
	virtual void setStartingGame();//SSS											// Initializes the game to its starting state
	void setFilesNames(int i);
	virtual void updateActionByKeys() = 0;											// Updates Mario's actions based on key presses from the user
	bool isAlive(int lives) { return lives > GameConfig::DEAD_MARIO; }		// Returns true if Mario is alive (has more lives than DEAD_MARIO), otherwise false
	virtual void startGame(int screen_index) = 0;									// Starts the game loop and handles gameplay logic
	virtual void gameLoop() = 0;
	void draw();															// Draws Mario and barrels on the screen
	//virtual void draw();															// Draws Mario and barrels on the screen
	void erase();															// Erases Mario's and barrels previous position from the screen
	void move();												// Moves Mario and barrels to a new position based on user input or game logic
	void updateIfMarioHitBarrelOrGhost();
	bool hitTheEnemy(GameConfig::Position enemy_pos, GameConfig::Position mario_pos);
	void updateIfDiedByBarrelOrGhost();																			// Checks if Mario died from a barrel (hit or explosion)
	bool hitByEnemy(GameConfig::Position enemy_pos, GameConfig::Position mario_pos);							// Handles the logic when Mario is hit by a barrel
	void diedFromExplodedBarrel(GameConfig::Position barrel_pos, GameConfig::Position mario_pos, int index);	// Handles the logic when Mario dies due to an exploded barrel
	bool wonTheLevel();																							// Checks if Mario successfully completed the level
};

