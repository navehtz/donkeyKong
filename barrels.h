#pragma once

#include "barrel.h"

class Barrels
{
	static constexpr int MAX_BARRELS = 10;
	static constexpr int TIME_TO_ROLL = 7;		// Every 7 iterations to activate a barrel

	Barrel barrels[MAX_BARRELS];

	Board* pBoard = nullptr;


public:
	Barrels() {														// ctor of Barrels. initialize all the barrels in the array
		for (int i = 0; i < MAX_BARRELS; i++) {
			barrels[i].setStartingBarrel();
		}
	}

	int getPosX(int i) { int posX = barrels[i].getPoint().getX(); return posX; }		// Get the X position of the i barrel in the array
	int getPosY(int i) { int posY = barrels[i].getPoint().getY(); return posY; }		// Get the Y position of the i barrel in the array
	
	const Barrel* getBarrels() { return barrels; }					// Get the member 'barrels'
	int getMaxBarrels() { return MAX_BARRELS; }						// Get the member 'MAX_BARRELS'
	void setpBoard(Board& _board) { pBoard = &_board; }				// Set pBoard to the board


	void timing();													// Handle the entry of the barrels into the board
	void setStartingBarrels();										// Inititialize all barrels
	void activateBarrels();											// Activating the first barrel that isn't activated
	void draw();													// Draw all the activated barrels
	void erase();													// Erase all the activated barrels
	void move();													// Move all the activated barrels

	bool getIfBarrelExploded(int i) {								// Check if a barrel has exploded
		bool is_barrel_exploded = barrels[i].getIsExploded();
		return is_barrel_exploded;
	}
	void bringBackExplodedBarrels();								// Initialize all the exploded barrels
};

