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
	void setpBoard(Board& _board) { pBoard = &_board; }				// Set pBoard to the board

	void setStartingGhosts(int size);										// Inititialize all barrels
	void setStartingSpecificGhost(int index);										// Inititialize all barrels
	void draw();													// Draw all the activated barrels
	void erase();													// Erase all the activated barrels
	void move();													// Move all the activated barrels

	void removeGhostByIndex(int index);

	void updateGhostsCharParameters();
	int getGhostDirX(int i) { return ghosts_vec[i].getDirX(); }
	int getNumOfGhosts() const { return num_of_ghosts; }
	void setNumOfGhosts(int new_num) { num_of_ghosts = new_num; }
	GameConfig::Position getGhostPosition(int i) const { return ghosts_vec[i].point.getPosition(); }

	void deactivate_ghost(int i) { ghosts_vec[i].deactivate(); }								// Deactivate the ghost at index 'i'
	void setPreviousCharOfGhost(int i, char _ch) { ghosts_vec[i].point.setPreviousChar(_ch); }  // Set the previous character of the ghost at index 'i'									
	void eraseASpecificGhost(int i) { ghosts_vec[i].erase(); }									// Erase the ghost at index 'i' FROM THE BOARD
	//void setStartingSpecificGhost(int i) { ghosts_vec[i].setStartingGhost(pBoard, pBoard->getStartPosOfGhost(i)); }			// Inititialize a specific ghost
};
