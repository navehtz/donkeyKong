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

class ManualGame {
	static constexpr int START_NEW_GAME = 49;			// The key - 1
	static constexpr int INSTRUCTIONS_AND_KEYS = 56;	//The key - 8
	static constexpr int EXIT_GAME = 57;				//The key - 9
	static constexpr int PAUSE = 27;					//ESC key
	static constexpr int RETURN_BACK = 114;				//The key - r
	static constexpr int LEFT = -1;
	static constexpr int RIGHT = 1;

	bool playing_mario = true;							// True = while mario has more than 0 lives
	bool exit_game = false;//!!!!						// False = while EXIT_GAME hasn't been pressed
	bool last_screen = false;							// False = while it isn't the last screen
	size_t iteration = 0;
	bool mario_died_this_iteration = false;

	Mario mario;
	Board board;
	Barrels barrels;
	Ghosts ghosts;

	std::vector<std::string> files_names_vec;

	Steps steps;
	Results results;
public:

	void showInstructions();//!!!!								// Displays the game instructions screen to the player
	void run();//!!!													// Manages the overall flow of the game

	void setStartingGame();										// Initializes the game to its starting state
	void updateActionByKeys();									// Updates Mario's actions based on key presses from the user
	bool isAlive(int lives) { return lives > GameConfig::DEAD_MARIO; }		// Returns true if Mario is alive (has more lives than DEAD_MARIO), otherwise false
	void startGame(int screen_index);							// Starts the game loop and handles gameplay logic
	bool menu();												// Displays the game menu and handles user input to start or quit the game
	void pauseGame();											// Pauses the game when a specific key is pressed (PAUSE)

	void draw();												// Draws Mario and barrels on the screen
	void erase();												// Erases Mario's and barrels previous position from the screen
	void move();												// Moves Mario and barrels to a new position based on user input or game logic

	void updateIfMarioHitBarrelOrGhost();
	bool hitTheEnemy(GameConfig::Position enemy_pos, GameConfig::Position mario_pos);
	void updateIfDiedByBarrelOrGhost();																			// Checks if Mario died from a barrel (hit or explosion)
	bool hitByEnemy(GameConfig::Position enemy_pos, GameConfig::Position mario_pos);							// Handles the logic when Mario is hit by a barrel
	void diedFromExplodedBarrel(GameConfig::Position barrel_pos, GameConfig::Position mario_pos, int index);	// Handles the logic when Mario dies due to an exploded barrel
	bool wonTheLevel();																							// Checks if Mario successfully completed the level
	int chooseGameScreen();																						// Allow the user to choose a game screen and return the selected screen index

	void manageInput();
	void saveManualGame(const std::string& stepsFilename, const std::string& resultsFilename);
	void setResult() { 
		if(mario_died_this_iteration) {	
			if(mario.getLives() > 0)
				results.addResult(iteration, results.died);
			else {
				results.addResult(iteration, results.finished);
			}
		}
		mario_died_this_iteration = false;
	}
};

