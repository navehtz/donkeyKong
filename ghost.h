#pragma once


#include <random>
#include "point.h"

class Ghost
{
	// Constants
	static constexpr int DOWN = 1;
	static constexpr int RIGHT = 1;
	static constexpr int LEFT = -1;
	static constexpr int STAY = 0;
	static constexpr double CHANGE_DIR_PROB = 0.05;


	// Members
	char ch = 'x';

	Point point;

	Board* pBoard = nullptr;

	char ch_covered = SPACE, ch_below = SPACE;
	char ch_left = SPACE, ch_right = SPACE;
	char ch_left_down = SPACE, ch_right_down = SPACE;

	bool res_is_on_floor = false, res_is_wall_on_left = false, res_is_wall_on_right = false;
	bool res_is_left_down = false, res_is_right_down = false;

	bool is_activated = true;

	bool is_wander_left = true;
	// States of ghost
	enum class GhostState {
		Wander,
		Falling
	};
	GhostState state = GhostState::Wander;

	// Defining struct for barrel's direction
	struct Direction {
		int x, y;
	};

	friend class Ghosts;

public:
	Ghost() : point(ch) {}													// Ctor of barrel with point
	Ghost(int x, int y) : point(ch) { point.setPositionX(x); point.setPositionY(y); }

	void setStartingGhost(Board* _pBoard, Position pos);					// Initialize barrel
	void setpBoard(Board& _board) { pBoard = &_board; }						// Set pBoard to the board
	Point getPoint() const { return point; }								// Get the member 'point'
	int getDirX() const { return point.getDir().x; }													// Get Mario's lives

	void draw() {															// Draw the barrel on the screen
		point.draw(ch);														// Erase the barrel from the screen
		pBoard->updateBoard(point.getPosition(), ch);				// Update the board with the current barrel
	}
	void erase() {
		point.erase();
		pBoard->updateBoard(point.getPosition(), point.getPreviousChar());						// Update the board without the current barrel
	}

	void checkWhatState();										// Check in which state the barrel is
	void updateState();											// Update the barrel's state

	char getCharFromBoard(Position _pos) const { return pBoard->getCharFromBoard(_pos); }			// Get the char in the (x,y) position on board
	char getCharFromBoard(int _x, int _y) const { return pBoard->getCharFromBoard(_x, _y); }			// Get the char in the (x,y) position on board

	void updateCharParameters();								// Update all the char data members around mario
	void move();												// Handle the barrel's movement
	void wander();												// Handle the barrel's rolling
	bool isFalling() const;										// Check if the barrel is falling 
	void fall();												// Handle the barrel's falling
	void manageDirection();										// Manage the direction of the barrel while on the floor
	void disappear() { is_activated = false; }												// Function to update the barrel's 'is_activated' and 'is_exploded' members
	void blockedByWall();										// Function to stop the barrels's movement if it reaches a wall
	bool isBlock(char _ch) const;								// The function returns true if the parameter is a floor/ceiling/wall and false otherwise

	void updatePreviousDir() { point.setPreviousDir(point.getDir()); }									// Function to update the barrel's previous direction like the current (similar to previous_dir = dir)              
	void updatePreviousChar() { point.setPreviousChar(getCharFromBoard(point.getPosition())); }	// Function for keeping the char the barrel is on so it can be printes in the next loop
	void updateNextMove();										// Updating the movement of the barrel for the next loop according to the position and the direction

	bool IsActivated() { return is_activated; };				// The function returns true if the barrel is activated(rolling/falling etc.)and false otherwise
	void activate() { is_activated = true; }					// Function to activate the barrel

	int myRandom();												// Function to raffle a number ( 1 or 0 )
};

