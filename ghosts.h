#pragma once

#include "baseGhost.h"
#include "regularGhost.h"
#include "specialGhost.h"
#include "board.h"
#include "gameConfig.h"


class Ghosts
{
	std::vector<BaseGhost*> ghosts_vec;								   // Vector containing all types of ghosts
	Board* pBoard = nullptr;                                           // Pointer to the game board
	int num_of_ghosts = 0;                                             // Number of ghosts in the game

public:
	Ghosts() {}                                                        // Constructor for the Ghosts class
	~Ghosts() {	clearGhosts(); }									   // Destructor for the Ghosts class
	void setpBoard(Board& _board) { pBoard = &_board; }                // Set the board pointer
	void setStartingGhosts(int size);                                  // Initialize all ghosts
	void draw();                                                       // Draw all activated ghosts
	void erase();                                                      // Erase all activated ghosts
	void move();                                                       // Move all activated ghosts

	void updateGhostsCharParameters();                                 // Update the character parameters for all activated ghosts
	int getGhostDirX(int i) { return ghosts_vec[i]->getDirX(); }       // Get the horizontal direction of a specific ghost
	int getNumOfGhosts() const { return num_of_ghosts; }               // Get the total number of ghosts
	void setNumOfGhosts(int new_num) { num_of_ghosts = new_num; }      // Set the total number of ghosts
	GameConfig::Position getGhostPosition(int i) const { return ghosts_vec[i]->point.getPosition(); } // Get the position of a specific ghost
		
	void deactivate_ghost(int i) { ghosts_vec[i]->deactivate(); }								// Deactivate the ghost at index 'i'
	void setPreviousCharOfGhost(int i, char _ch) { ghosts_vec[i]->point.setPreviousChar(_ch); }  // Set the previous character of the ghost at index 'i'									
	void eraseASpecificGhost(int i) { ghosts_vec[i]->erase(); }									// Erase the ghost at index 'i' FROM THE BOARD

	void kickGhostFromBoard(int i) { ghosts_vec[i]->setPositionOfEntity(GameConfig::NOT_RELEVET_POS); } // Moves the ghost at index 'i' to a non-relevant position, effectively removing it from the board
	void addGhost(BaseGhost* ghost) {																	// Adds a new ghost to the list of active ghosts  
		ghosts_vec.push_back(ghost);
	}
	void clearGhosts() {																				// Deletes all ghosts from memory and clears the vector
		for (BaseGhost* ghost : ghosts_vec) {
			delete ghost; 
		}
		ghosts_vec.clear();
	}
};
