#pragma once

#include <iostream>		//for cout
#include <conio.h>		//for _kbhit(), _getch()
#include <Windows.h>	//for Sleep and colors

#include "general.h"
#include "point.h"
#include "mario.h"
#include "board.h"

using namespace std;

class Game {
	static constexpr int START_NEW_GAME = 49;			// The key - 1
	static constexpr int INSTRUCTIONS_AND_KEYS = 56;	//The key - 8
	static constexpr int EXIT_GAME = 57;				//The key - 9
	static constexpr int PAUSE = 27;					//ESC key
	static constexpr int RETURN_BACK = 114;				//The key - r

	Mario mario;
	Board board;

public:

	void showInstructions();
	void run();							//function that manage the game

	void startGame();
	bool menu();
	void pauseGame(int key);
};



