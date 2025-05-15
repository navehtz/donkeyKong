#pragma once

#include <iostream>      // For cout
#include <conio.h>       // For _kbhit(), _getch()
#include <Windows.h>     // For Sleep and colors
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
	static constexpr int START_NEW_GAME = 49;      // Key - '1'
	static constexpr int INSTRUCTIONS_AND_KEYS = 56; // Key - '8'
	static constexpr int EXIT_GAME = 57;           // Key - '9'
	static constexpr int PAUSE = 27;               // ESC key
	static constexpr int RETURN_BACK = 114;        // Key - 'r'
	static constexpr int LEFT = -1;                // Represents left movement
	static constexpr int RIGHT = 1;                // Represents right movement

	bool playing_mario = true;                     // True = game continues while Mario has lives left
	bool last_screen = false;                      // False = game has more screens remaining
	size_t iteration = 0;                          // Tracks the current iteration in the game loop
	bool mario_died_this_iteration = false;        // True if Mario died during this iteration

	std::string screenFileName, filename_prefix, stepsFilename, resultsFilename; // File management variables

	Mario mario;
	Board board;
	Barrels barrels;
	Ghosts ghosts;

	std::vector<std::string> files_names_vec;      // Stores names of game level files

	Steps steps;
	Results results;

public:
	virtual void run() = 0;                        // Manages the overall flow of the game
	virtual void stagesLoop(int screen_index) = 0; // Handles looping through game stages
	virtual void setStartingGame();                // Initializes the game to its starting state
	void setFilesNames(int i);                     // Sets the filenames for steps and results based on level index
	virtual void updateActionByKeys() = 0;         // Updates Mario's actions based on key presses from the user
	bool isAlive(int lives) { return lives > GameConfig::DEAD_MARIO; } // Returns true if Mario has more lives than DEAD_MARIO
	virtual void startGame(int screen_index) = 0;  // Starts the game loop and handles gameplay logic
	virtual void gameLoop() = 0;                   // Runs the main game loop
	void draw();                                   // Draws the current state of the game (Mario, barrels, ghosts etc.)
	void erase();                                  // Erases the current state of the game (Mario, barrels, ghosts etc.)
	void move();                                   // Manage movement for all entities (Mario, barrels, ghosts etc.)
	void updateIfMarioHitBarrelOrGhost();          // Checks if Mario hits a barrel or ghost
	bool hitTheEnemy(GameConfig::Position enemy_pos, GameConfig::Position mario_pos); // Checks if Mario hits an enemy
	void updateIfDiedByBarrelOrGhost();            // Checks if Mario died from a barrel or ghost
	bool hitByEnemy(GameConfig::Position enemy_pos, GameConfig::Position mario_pos); // Handles Mario getting hit by an enemy
	void diedFromExplodedBarrel(GameConfig::Position barrel_pos, GameConfig::Position mario_pos, int index); // Handles Mario dying from an exploded barrel
	bool wonTheLevel();                            // Checks if Mario successfully completed the level
};
