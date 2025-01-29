#pragma once

#include "baseGame.h"

class AutomaticGame : public BaseGame {
	//static constexpr int START_NEW_GAME = 49;			// The key - 1
	//static constexpr int INSTRUCTIONS_AND_KEYS = 56;	//The key - 8
	//static constexpr int EXIT_GAME = 57;				//The key - 9
	//static constexpr int PAUSE = 27;					//ESC key
	//static constexpr int RETURN_BACK = 114;				//The key - r
	//static constexpr int LEFT = -1;
	//static constexpr int RIGHT = 1;

	//bool playing_mario = true;							// True = while mario has more than 0 lives
	//bool exit_game = false;								// False = while EXIT_GAME hasn't been pressed
	//bool last_screen = false;							// False = while it isn't the last screen
	//size_t iteration = 0;
	//bool mario_died_this_iteration = false;
	//Mario mario;
	//Board board;
	//Barrels barrels;
	//Ghosts ghosts;

	//std::vector<std::string> files_names_vec;

	//Steps steps;
	//Results results;
	bool unmatching_result_found = false;
	bool is_silent;

public:
	AutomaticGame(bool silent_flag) : is_silent(silent_flag) { board.setIsSilent(is_silent); }
	//void showInstructions();									// Displays the game instructions screen to the player
	void run() override;//!!!!													// Manages the overall flow of the game
	void setStartingGame() override;
	void stagesLoop(int screen_index) override;
	//void setStartingGame();//SSS										// Initializes the game to its starting state
	void updateActionByKeys() override;									// Updates Mario's actions based on key presses from the user
	//bool isAlive(int lives) { return lives > GameConfig::DEAD_MARIO; }		// Returns true if Mario is alive (has more lives than DEAD_MARIO), otherwise false
	void startGame(int screen_index) override;							// Starts the game loop and handles gameplay logic
	void gameLoop() override;

	//void draw() override;												// Draws Mario and barrels on the screen
	//void erase();												// Erases Mario's and barrels previous position from the screen
	//void move();												// Moves Mario and barrels to a new position based on user input or game logic

	//void updateIfMarioHitBarrelOrGhost();
	//bool hitTheEnemy(GameConfig::Position enemy_pos, GameConfig::Position mario_pos);
	//void updateIfDiedByBarrelOrGhost();																			// Checks if Mario died from a barrel (hit or explosion)
	//bool hitByEnemy(GameConfig::Position enemy_pos, GameConfig::Position mario_pos);							// Handles the logic when Mario is hit by a barrel
	//void diedFromExplodedBarrel(GameConfig::Position barrel_pos, GameConfig::Position mario_pos, int index);	// Handles the logic when Mario dies due to an exploded barrel
	//bool wonTheLevel();																							// Checks if Mario successfully completed the level																						// Allow the user to choose a game screen and return the selected screen index

	//void manageInput();
	void reportResultError(const std::string& message, const std::string& filename, size_t _iteration);

	void reportFileError(const std::string& message, const std::string& filename);
	// TODO:: write this like: 

	bool loadAutoGame();
	bool handleResultsError(size_t diedNextIteration);
	void handleResultsErrorAfterLoop();
	void printSuccessfulRunIfSilent() const;

	//bool checkIfResultFileMatch(const std::string& filename) {
	//	if (mario_died_this_iteration) {

	//	}
	//}
};
