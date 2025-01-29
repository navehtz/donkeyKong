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

	GameConfig::Position getPos(int i) { return barrels[i].getPoint().getPosition(); } // Retrieve the position of the barrel at index 'i'
	
	const Barrel* getBarrels() { return barrels; }					// Get the member 'barrels'
	int getMaxBarrels() { return GameConfig::MAX_BARRELS; }			// Get the member 'MAX_BARRELS'
	void setpBoard(Board& _board) { pBoard = &_board; }				// Set pBoard to the board

	void timing();													// Handle the entry of the barrels into the board
	void setStartingBarrels();										// Inititialize all barrels
	void setStartingBarrel(int i) { barrels[i].setStartingBarrel(pBoard); }	// Inititialize a specific barrel
	void setPreviousCharOfBarrel(int i, char _ch) { barrels[i].point.setPreviousChar(_ch); } // Set the previous character of the barrel at index 'i'									
	void activateBarrels();											// Activating the first barrel that isn't activated
	void draw();													// Draw all the activated barrels
	void erase();													// Erase all the activated barrels
	void eraseASpecificBarrel(int i) { barrels[i].erase(); }		// Erase the barrel at index 'i' from the board
	void move();													// Move all the activated barrels

	bool getIfBarrelExploded(int i) { return barrels[i].getIsExploded(); }	// Check if a barrel has exploded

	void bringBackExplodedBarrels();								// Initialize all the exploded barrels

	void updateBarrelsCharParameters();								// Update the character-related parameters of all barrels
	int getBarrelDirX(int i) { return barrels[i].getDirX(); }		// Get the x-direction of the barrel at index 'i'

	bool isactivateBarrel(int i) { barrels[i].activate(); }		// Deactivate the barrel at index 'i'
	void deactivateBarrel(int i) { barrels[i].deactivate(); }		// Deactivate the barrel at index 'i'
};

