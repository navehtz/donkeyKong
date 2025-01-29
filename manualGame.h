#pragma once

#include "baseGame.h"

class ManualGame : public BaseGame 
{
	bool exit_game = false;//!!!!						// False = while EXIT_GAME hasn't been pressed
	bool is_save;

public:
	ManualGame(bool save_mode_flag) : is_save(save_mode_flag) {}
	void showInstructions();								// Displays the game instructions screen to the player
	void run() override;												// Manages the overall flow of the game
	void stagesLoop(int screen_index) override;
	void updateActionByKeys() override;									// Updates Mario's actions based on key presses from the user
	void startGame(int screen_index) override;							// Starts the game loop and handles gameplay logic
	bool menu();												// Displays the game menu and handles user input to start or quit the game
	void pauseGame();											// Pauses the game when a specific key is pressed (PAUSE)

	int chooseGameScreen();																						// Allow the user to choose a game screen and return the selected screen index

	void manageInput();
	void saveManualGame();
	void setResult();

	void gameLoop() override;
};

