#pragma once

#include <Windows.h>	//for Sleep and colors
#include <random>
#include "point.h"


class Barrel
{
	// Constants
	static constexpr int STARTING_POS_LEFT_X = 36;
	static constexpr int STARTING_POS_RIGHT_X = 38;
	static constexpr int STARTING_POS_Y = 3;

	static constexpr int DOWN = 1;
	static constexpr int RIGHT = 1;
	static constexpr int LEFT = -1;
	static constexpr int STAY = 0;

	static constexpr int FALL_FROM_TOO_HIGH = 8;
	static constexpr int EXPLODED_BARREL = 0;

	// Members
	char ch = 'O';

	int fall_count = 0;
	Point point;

	Board* pBoard = nullptr;

	char ch_covered = ' ', ch_below = ' ', two_chars_below = ' ';
	char ch_left = ' ', ch_right = ' ';

	bool res_is_on_ladder = false, res_is_on_floor = false, res_is_below_roof = false;
	bool res_is_wall_on_left = false, res_is_wall_on_right = false, res_is_two_chars_below_floor = false;

	bool is_activated = false;
	bool is_exploded = false;

	// States of barrel
	enum class BarrelState {
		Falling,
		Rolling
	};
	BarrelState state = BarrelState::Rolling;

	// Defining struct for barrel's direction
	struct Direction {
		int x, y;
	};

public:
	Barrel() : point(ch) {}													// Ctor of barrel with point

	void setStartingBarrel();												// Initialize barrel
	bool getIsExploded() { return is_exploded; }							// Get the member 'is_exploded'
	void setIsExploded(bool _is_exploded) { is_exploded = _is_exploded; }	// Set the member 'is_exploded'
	void setpBoard(Board& _board) { pBoard = &_board; }						// Set pBoard to the board
	Point getPoint() const { return point; }								// Get the member 'point'

	void draw() {															// Draw the barrel on the screen
		point.draw(ch);														// Erase the barrel from the screen
		pBoard->updateBoard(point.getX(), point.getY(), ch);				// Update the board with the current barrel
	}
	void erase() {
		point.erase();
		pBoard->updateBoard(point.getX(), point.getY(), point.getPreviousChar());						// Update the board without the current barrel
	}

	void checkWhatState();										// Check in which state the barrel is
	void updateState();											// Update the barrel's state

	char getCharFromBoard(int _x, int _y) const { return pBoard->getCharFromBoard(_x, _y); }			// Get the char in the (x,y) position on board

	void move();												// Handle the barrel's movement
	bool isFalling() const;										// Check if the barrel is falling 
	void fall();												// Handle the barrel's falling
	void roll();												// Handle the barrel's rolling
	void manageDirection();										// Manage the direction of the barrel while on the floor
	bool explosionCases();										// Handle the cases which the barrel explodes in (falling 8 chars or at wall)
	void explode();												// Function to update the barrel's 'is_activated' and 'is_exploded' members
	void blockedByWall();										// Function to stop the barrels's movement if it reaches a wall
	bool isBlock(char _ch) const;								// The function returns true if the parameter is a floor/ceiling/wall and false otherwise

	void updatePreviousDir() { point.setPreviousDir(point.getDir()); }									// Function to update the barrel's previous direction like the current (similar to previous_dir = dir)              
	void updatePreviousChar() { point.setPreviousChar(getCharFromBoard(point.getX(), point.getY())); }	// Function for keeping the char the barrel is on so it can be printes in the next loop
	void updateNextMove();										// Updating the movement of the barrel for the next loop according to the position and the direction

	bool IsActivated() { return is_activated; };				// The function returns true if the barrel is activated(rolling/falling etc.)and false otherwise
	void activate() { is_activated = true; }					// Function to activate the barrel
	
	int myRandom();												// Function to raffle a number ( 1 or 0 )
	//void drawExplosion();
};

