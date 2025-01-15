#pragma once

#include "barrel.h"

class Barrels
{
	static constexpr int TIME_TO_ROLL = 14;		// Every 7 iterations to activate a barrel

	Barrel barrels[MAX_BARRELS];

	Board* pBoard = nullptr;


public:
	Barrels() {}													// ctor of Barrels. initialize all the barrels in the array

	int getPosX(int i) { int posX = barrels[i].getPoint().getPosition().x; return posX; }		// Get the X position of the i barrel in the array
	int getPosY(int i) { int posY = barrels[i].getPoint().getPosition().y; return posY; }		// Get the Y position of the i barrel in the array
	Position getPos(int i) { Position pos = barrels[i].getPoint().getPosition(); return pos; }
	
	const Barrel* getBarrels() { return barrels; }					// Get the member 'barrels'
	int getMaxBarrels() { return MAX_BARRELS; }						// Get the member 'MAX_BARRELS'
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

