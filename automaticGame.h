#pragma once

#include "baseGame.h"

class AutomaticGame : public BaseGame {
	bool unmatching_result_found = false;						// Indicates if a mismatch in results has been found
	bool is_silent;												// Determines whether the game runs in silent mode

public:
	AutomaticGame(bool silent_flag) : is_silent(silent_flag) { board.setIsSilent(is_silent); } // Constructor initializing silent mode or not

	void run() override;										// Start the overall flow of the game
	void setStartingGame() override;							// Sets up the game before it starts
	void startGame(int screen_index) override;					// Starts the game loop and handles gameplay logic
	void stagesLoop(int screen_index) override;					// Handles the looping through game stages
	void gameLoop() override;									// Runs the main game loop
	void updateActionByKeys() override;							// Updates Mario's actions based on key presses from the user

	void reportResultError(const std::string& message, const std::string& filename, size_t _iteration); // Reports an error related to game results

	void reportFileError(const std::string& message, const std::string& filename); // Reports an error related to file handling

	bool loadAutoGame();										// Loads the automatic game mode
	bool handleResultsError(size_t diedNextIteration);			// Handles errors in results checking
	void handleResultsErrorAfterLoop();							// Handles result errors after the main loop ends
	void printSuccessfulRunIfSilent() const;					// Prints success message if running in silent mode
};
