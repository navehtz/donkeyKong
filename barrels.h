#pragma once

#include "barrel.h"
#include "gameConfig.h"


class Barrels
{
	static constexpr int TIME_TO_ROLL = 14;		// Every x iterations to activate a barrel

	Barrel barrels[GameConfig::MAX_BARRELS];

	Board* pBoard = nullptr;
	
	int iterations = 0;
	bool first_run = true;

public:
	Barrels() {}													// ctor of Barrels. initialize all the barrels in the array

	GameConfig::Position getPos(int i) { GameConfig::Position pos = barrels[i].getPoint().getPosition(); return pos; }
	
	const Barrel* getBarrels() { return barrels; }					// Get the member 'barrels'
	int getMaxBarrels() { return GameConfig::MAX_BARRELS; }						// Get the member 'MAX_BARRELS'
	void setpBoard(Board& _board) { pBoard = &_board; }				// Set pBoard to the board


	void timing();													// Handle the entry of the barrels into the board
	void setStartingBarrels();										// Inititialize all barrels
	void setStartingBarrel(int i) { barrels[i].setStartingBarrel(pBoard); }										// Inititialize 
	void setPreviousCharOfBarrel(int i, char _ch) { barrels[i].point.setPreviousChar(_ch); }										
	void activateBarrels();											// Activating the first barrel that isn't activated
	void draw();													// Draw all the activated barrels
	void erase();													// Erase all the activated barrels
	void eraseASpecificBarrel(int i) { barrels[i].erase(); }
	void move();													// Move all the activated barrels

	bool getIfBarrelExploded(int i) {								// Check if a barrel has exploded
		bool is_barrel_exploded = barrels[i].getIsExploded();
		return is_barrel_exploded;
	}
	void bringBackExplodedBarrels();								// Initialize all the exploded barrels

	void updateBarrelsCharParameters();
	int getBarrelDirX(int i) { return barrels[i].getDirX(); }

	void deactivate_barrel(int i) { barrels[i].deactivate(); }
};

