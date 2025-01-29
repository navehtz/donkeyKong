#include "mainHelper.h"

// Starts the game based on the selected mode
// If `is_load` is true, an automatic game is started (possibly in silent mode)  
// Otherwise, a manual game is started (possibly in save mode) 
void MainHelper::runGame(bool& is_load, bool& is_save, bool& is_silent)
{
	if (is_load) {
		AutomaticGame auto_game(is_silent);
		auto_game.run();
	}
	else {
		ManualGame manual_game(is_save);
		manual_game.run();
	}
}

// Parses a single command-line argument and determines the game mode  
void MainHelper::manageOneInput(const std::string& first, bool& is_load, bool& is_save, bool& is_silent)
{
	is_silent = false;			// One input - can't be silent
	if (first == "-load") {
		is_load = true;
		is_save = false;
	}
	else if (first == "-save") {
		is_load = false;
		is_save = true;
	}
	else
		throw "Invalid input";
}

// Parses two command-line arguments and determines the game mode
void MainHelper::manageTwoInputs(const std::string& first, const std::string& second, bool& is_load, bool& is_save, bool& is_silent)
{
	if (first == "-load" || second == "-load") {		// If one of the input is load : "load mode"
		is_load = true;
		is_save = false;
		if (first == "-silent" || second == "-silent")
			is_silent = true;
		else
			is_silent = false;
	}
	else if (first == "-save" || second == "-save") {	// If one of the input is save and there is no load in input : "save mode"
		is_load = false;
		is_save = true;
		is_silent = false;
	}
	else {												// No input : play manual without saving
		throw "Invalid input";
	}
}