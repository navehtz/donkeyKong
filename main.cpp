#include "manualGame.h"
#include "automaticGame.h"
#include "baseGame.h"

void manageOneInput(const std::string& first, bool& is_load, bool& is_save, bool& is_silent);
void manageTwoInputs(const std::string& first, const std::string& second, bool& is_load, bool& is_save, bool& is_silent);
void runGame(bool& is_load, bool& is_save, bool& is_silent);

int main(int argc, char** argv) 
{
	bool is_load = false, is_save = false, is_silent = false;

	if (argc == 3) {		// Two inputs
		try { manageTwoInputs(std::string(argv[1]), std::string(argv[2]), is_load, is_save, is_silent); }
		catch (const char* msg) { std::cout << msg << std::endl; return ERROR; }
	}
	else if (argc == 2) {	// One input
		try { manageOneInput(std::string(argv[1]), is_load, is_save, is_silent); }
		catch (const char* msg) { std::cout << msg << std::endl; return ERROR; }
	}
	else if (argc != 1) {	// Different then no Inputs
		std::cout << "Invalid command arguments inputs" << std::endl;
		return ERROR;
	}

	runGame(is_load, is_save, is_silent);
}


void runGame(bool& is_load, bool& is_save, bool& is_silent)
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

void manageOneInput(const std::string& first, bool& is_load, bool& is_save, bool& is_silent)
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

void manageTwoInputs(const std::string& first, const std::string& second, bool& is_load, bool& is_save, bool& is_silent)
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







