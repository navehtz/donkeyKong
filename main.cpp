
#include "manualGame.h"
#include "automaticGame.h"
#include "baseGame.h"

int main(int argc, char** argv) 
{
	//Game donkeyKong;
	//donkeyKong.run();

	//TODOOOO:  manage all possible inputs
	bool is_load = argc > 1 && std::string(argv[1]) == "-load";
	bool is_silent = is_load && argc > 2 && std::string(argv[2]) == "-silent";
	bool is_save = !is_load;

	if (is_load) {
		AutomaticGame auto_game;
		auto_game.run();
	}
	else {
		ManualGame manual_game;
		manual_game.run();
	}
}








