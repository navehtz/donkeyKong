
#include "mainHelper.h"


int main(int argc, char** argv) 
{
	bool is_load = false, is_save = false, is_silent = false;

	// Check for command-line arguments and process accordingly 
	if (argc == 3) {												// Case: Two inputs provided
		try { MainHelper::manageTwoInputs(std::string(argv[1]), std::string(argv[2]), is_load, is_save, is_silent); }
		catch (const char* msg) { std::cout << msg << std::endl; return ERROR; }
	}
	else if (argc == 2) {											// Case: One input provided 
		try { MainHelper::manageOneInput(std::string(argv[1]), is_load, is_save, is_silent); }
		catch (const char* msg) { std::cout << msg << std::endl; return ERROR; }
	}
	else if (argc != 1) {											// Case: Invalid number of inputs (other than zero, one, or two)
		std::cout << "Invalid command arguments inputs" << std::endl;
		return ERROR;
	}


	MainHelper::runGame(is_load, is_save, is_silent);				// Run the game with the parsed options
}









