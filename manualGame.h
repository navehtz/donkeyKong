#pragma once

#include "baseGame.h"

class ManualGame : public BaseGame
{
	bool exit_game = false;									// False = game continues until EXIT_GAME is pressed
	bool is_save;											// Determines whether game progress should be in save mode
	int score_before_level = 0;								// Stores the player's score before starting a new level

public:
	ManualGame(bool save_mode_flag) : is_save(save_mode_flag) {} // Constructor initializing save mode or not

	void run() override;									// Manages the overall flow of the game
	bool menu();											// Displays the game menu and handles user input to start or quit the game
	void showInstructions();								// Displays the game instructions screen to the player
	int chooseGameScreen();									// Allows the user to choose a game screen and returns the selected screen index
	void stagesLoop(int screen_index) override;				// Handles the looping through game stages
	void gameLoop() override;								// Runs the game loop
	void startGame(int screen_index) override;				// Starts the game loop and handles gameplay logic
	void pauseGame();										// Pauses the game when a specific key is pressed (PAUSE)
	void manageInput();										// Handles user input during gameplay
	void updateActionByKeys() override;						// Updates Mario's actions based on key presses from the user
	void saveManualGame();									// Saves the game state in manual mode
	void setResult();										// Adding the game result to the results vector

};
