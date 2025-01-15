#pragma once

#include <Windows.h>	//for Sleep and colors
#include <random>
#include "point.h"
#include "entity.h"


class Barrel : public Entity
{
	// Constants
	static constexpr int FALL_FROM_TOO_HIGH = 8;
	static constexpr int EXPLODED_BARREL = 0;

	// Members
	//char ch = BARREL;

	int fall_count = 0;
	//Point point;

	//Board* pBoard = nullptr;

	char two_chars_below = SPACE;
	//char ch_covered = SPACE, ch_below = SPACE;
	//char ch_left = SPACE, ch_right = SPACE;

	//bool res_is_on_floor = false, res_is_wall_on_left = false, res_is_wall_on_right = false;

	bool is_activated = false;
	bool is_exploded = false;

	// States of barrel
	enum class BarrelState {
		Falling,
		Rolling
	};
	BarrelState state = BarrelState::Rolling;

	friend class Barrels;

public:
	Barrel() : Entity(BARREL) {} 												// Ctor of barrel with point

	void setStartingBarrel(Board* _pBoard);												// Initialize barrel
	//void setpBoard(Board& _board) { pBoard = &_board; }						// Set pBoard to the board
	bool getIsExploded() { return is_exploded; }							// Get the member 'is_exploded'
	void setIsExploded(bool _is_exploded) { is_exploded = _is_exploded; }	// Set the member 'is_exploded'
	Point getPoint() const { return point; }								// Get the member 'point'
	int getDirX() const { return point.getDir().x; }													// Get Mario's lives

	//void draw() {															// Draw the barrel on the screen
	//	point.draw(ch);														// Erase the barrel from the screen
	//	pBoard->updateBoard(point.getPosition(), ch);				// Update the board with the current barrel
	//}
	//void erase() override {
	//	point.erase();
	//	pBoard->updateBoard(point.getPosition(), point.getPreviousChar());						// Update the board without the current barrel
	//}

	void checkWhatState() override;										// Check in which state the barrel is
	void updateState() override;											// Update the barrel's state
	void updateNextMove() override;										// Updating the movement of the barrel for the next loop according to the position and the direction

	//char getCharFromBoard(Position _pos) const { return pBoard->getCharFromBoard(_pos); }			// Get the char in the (x,y) position on board
	//char getCharFromBoard(int _x, int _y) const { return pBoard->getCharFromBoard(_x, _y); }			// Get the char in the (x,y) position on board

	void updateCharParameters() override;						// Update all the char data members around mario
	//void move();												// Handle the barrel's movement
	bool isFalling() const;										// Check if the barrel is falling 
	void fall() override;												// Handle the barrel's falling
	void roll();												// Handle the barrel's rolling
	void manageDirection();										// Manage the direction of the barrel while on the floor
	bool explosionCases();										// Handle the cases which the barrel explodes in (falling 8 chars or at wall)
	void explode();												// Function to update the barrel's 'is_activated' and 'is_exploded' members
	void blockedByWall();										// Function to stop the barrels's movement if it reaches a wall
	//bool isBlock(char _ch) const;								// The function returns true if the parameter is a floor/ceiling/wall and false otherwise

	//void updatePreviousDir() { point.setPreviousDir(point.getDir()); }									// Function to update the barrel's previous direction like the current (similar to previous_dir = dir)              
	//void updatePreviousChar() { point.setPreviousChar(getCharFromBoard(point.getPosition())); }	// Function for keeping the char the barrel is on so it can be printes in the next loop

	bool const IsActivated() const { return is_activated; };				// The function returns true if the barrel is activated(rolling/falling etc.)and false otherwise
	void activate() { is_activated = true; }					// Function to activate the barrel
	void deactivate() { is_activated = false; }
	int myRandom();												// Function to raffle a number ( 1 or 0 )


};


