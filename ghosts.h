#pragma once

#include "ghost.h"
#include "board.h"


class Ghosts
{
	std::vector <Ghost> ghosts_vec;
	Board* pBoard = nullptr;
	int num_of_ghosts = 0;

public:
	Ghosts() {}													// ctor of Barrels. initialize all the barrels in the array

	int getPosX(int i) { int posX = ghosts_vec[i].getPoint().getPosition().x; return posX; }		// Get the X position of the i barrel in the array
	int getPosY(int i) { int posY = ghosts_vec[i].getPoint().getPosition().y; return posY; }		// Get the Y position of the i barrel in the array

	const std::vector <Ghost> getGhostsVec() { return ghosts_vec; }					// Get the member 'ghosts'
	int getGhostsVecSize() { return pBoard->getGhostVectorSize(); }						// Get the number of ghosts
	void setpBoard(Board& _board) { pBoard = &_board; }				// Set pBoard to the board


	void setStartingGhosts(int size);										// Inititialize all barrels
	void draw();													// Draw all the activated barrels
	void erase();													// Erase all the activated barrels
	void move();													// Move all the activated barrels

	bool getIfGhostExploded(int i) {								// Check if a barrel has exploded
		bool is_barrel_exploded = ghosts_vec[i].IsActivated();
		return is_barrel_exploded;
	}
	void removeGhostByIndex(int index);

	//void bringBackExplodedBarrels();								// Initialize all the exploded barrels

	void updateGhostsCharParameters();

	int getGhostDirX(int i) { return ghosts_vec[i].getDirX(); }
	int getNumOfGhosts() { return num_of_ghosts; }
	Position getGhostPosition(int i) { return ghosts_vec[i].point.getPosition(); }
};








/*
public:
	Ghosts() {}													// ctor of Barrels. initialize all the barrels in the array

	int getPosX(int i) { int posX = ghosts[i].getPoint().getPosition().x; return posX; }		// Get the X position of the i barrel in the array
	int getPosY(int i) { int posY = ghosts[i].getPoint().getPosition().y; return posY; }		// Get the Y position of the i barrel in the array

	const std::vector <Ghost> getGhostsVec() { return ghosts; }					// Get the member 'ghosts'
	int getGhostsVecSize() { return pBoard->getGhostVectorSize(); }						// Get the number of ghosts
	void setpBoard(Board& _board) { pBoard = &_board; }				// Set pBoard to the board


	void setStartingGhosts(int size);										// Inititialize all barrels
	void draw();													// Draw all the activated barrels
	void erase();													// Erase all the activated barrels
	void move();													// Move all the activated barrels

	//bool getIfGhostExploded(int i) {								// Check if a barrel has exploded
	//	bool is_barrel_exploded = ghosts[i].getIsActivated();
	//	return is_barrel_exploded;
	//}

	//void bringBackExplodedBarrels();								// Initialize all the exploded barrels

	void updateGhostsCharParameters();

	int getGhostDirX(int i) { return ghosts[i].getDirX(); }
	int getNumOfGhosts() { return num_of_ghosts; }
	Position getGhostPosition(int i) { return ghosts[i].point.getPosition(); }
};

*/