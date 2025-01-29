#pragma once

#include "baseGame.h"

class AutomaticGame : public BaseGame {
	bool unmatching_result_found = false;
	bool is_silent;

public:
	AutomaticGame(bool silent_flag) : is_silent(silent_flag) { board.setIsSilent(is_silent); }
	void run() override;//!!!!													// Manages the overall flow of the game
	void setStartingGame() override;
	void stagesLoop(int screen_index) override;
	void updateActionByKeys() override;									// Updates Mario's actions based on key presses from the user
	void startGame(int screen_index) override;							// Starts the game loop and handles gameplay logic
	void gameLoop() override;

	void reportResultError(const std::string& message, const std::string& filename, size_t _iteration);

	void reportFileError(const std::string& message, const std::string& filename);

	bool loadAutoGame();
	bool handleResultsError(size_t diedNextIteration);
	void handleResultsErrorAfterLoop();
	void printSuccessfulRunIfSilent() const;
};
