
#include "manualGame.h"
#include "automaticGame.h"
#include "baseGame.h"

int main(int argc, char** argv) 
{
	//Game donkeyKong;
	//donkeyKong.run();

	//TODOOOO:  manage all possible inputs
	bool is_load = argc > 1 && std::string(argv[1]) == "-load";
	bool is_save = argc > 1 && std::string(argv[1]) == "-save";
	bool is_silent = is_load && argc > 2 && std::string(argv[2]) == "-silent";

	if (is_load) {
		AutomaticGame auto_game(is_silent);
		auto_game.run();
	}
	else{
		ManualGame manual_game(is_save);
		manual_game.run();
	}
}








