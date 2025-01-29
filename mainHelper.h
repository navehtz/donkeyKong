#pragma once
#include "manualGame.h"
#include "automaticGame.h"
#include "baseGame.h"

class MainHelper
{
public:
	// Parses a single input argument and determines game mode flags 
	static void manageOneInput(const std::string& first, bool& is_load, bool& is_save, bool& is_silent);    

	// Parses two input arguments and determines game mode flags
	static void manageTwoInputs(const std::string& first, const std::string& second, bool& is_load, bool& is_save, bool& is_silent); 

	// Runs the game based on the selected mode flags
	static void runGame(bool& is_load, bool& is_save, bool& is_silent);									    
};

