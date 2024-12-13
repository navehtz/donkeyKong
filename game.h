#pragma once

#include <iostream>		//for cout
#include <conio.h>		//for _kbhit(), _getch()
#include <Windows.h>	//for Sleep and colors

#include "general.h"
#include "point.h"
#include "mario.h"
#include "board.h"
#include "barrels.h"

using namespace std;

class Game {
	static constexpr int START_NEW_GAME = 49;			// The key - 1
	static constexpr int INSTRUCTIONS_AND_KEYS = 56;	//The key - 8
	static constexpr int EXIT_GAME = 57;				//The key - 9
	static constexpr int PAUSE = 27;					//ESC key
	static constexpr int RETURN_BACK = 114;				//The key - r

	static constexpr int DEAD_MARIO = 0;
	static constexpr int FULL_LIVES = 3;

	bool playing_mario = true;
	static constexpr int EXPLOSION_RADIUS = 2;

	Mario mario;
	Board board;
	Barrels barrels;

public:

	void showInstructions();
	void run();							//Function that manage the game

	void setStartingGame();
	void updateActionByKeys();
	bool isAlive(int lives) { return lives != DEAD_MARIO; } //Returning True if mario has lives and False if lives == 0
	void startGame();
	bool menu();
	void pauseGame(int key);

	void draw();
	void erase();
	void move();
	void updateIfHitByBarrel();

};




