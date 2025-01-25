#pragma once

#include "point.h"
#include "gameConfig.h"

#include <random>

class Entity
{
protected:
	Point point;

	Board* pBoard = nullptr;

	// Characters surrounding Entity
	char ch_covered = GameConfig::SPACE, ch_below = GameConfig::SPACE;
	char ch_left = GameConfig::SPACE, ch_right = GameConfig::SPACE;

	// Flags indicating Entity's interaction with his surroundings
	bool res_is_on_floor = false, res_is_wall_on_left = false, res_is_wall_on_right = false;
	bool is_activated = false;

public:
	Entity(char _ch) : point(_ch) {}															  // Constructor initializing the entity with a character
	Entity(int x, int y, char _ch) : point(_ch) { point.setPositionX(x); point.setPositionY(y); } // Constructor initializing the entity with a position (x, y) and a character

	void setpBoard(Board& _board) { pBoard = &_board; }								// Set pBoard to the board
	const Point& getPoint() const { return point; }									// Get the member 'point'
	GameConfig::Position getPosition() const { return point.getPosition(); }	// Get the current position of the entity as a constant reference
	void draw() {																	// Draw the entity on the screen and update the board
		point.draw();
		pBoard->updateBoard(point.getPosition(), point.getChar());
	}
	virtual void erase() {															// Erase the entity from the screen and update the board
		point.erase();
		pBoard->updateBoard(point.getPosition(), point.getPreviousChar());
	}
	virtual void checkWhatState() = 0;			// Pure virtual function to check the entity's current state
	virtual void updateState() = 0;				// Pure virtual function to update the entity's state											
	virtual void updateNextMove() = 0;			// Pure virtual function to calculate and update the entity's next move
	virtual void updateCharParameters() = 0;	// Pure virtual function to update the entity's character-related parameters					

	virtual void move();						// Virtual function to handle the movement of the entity
	virtual void fall() = 0;					// Pure virtual function to handle the falling behavior of the entity
	bool isFalling() const;						// Check if the entity is falling 
	bool isBlock(char _ch) const;				// The function returns true if the parameter is a floor/ceiling/wall and false otherwise

	char getCharFromBoard(const GameConfig::Position& _pos) const { return pBoard->getCharFromBoard(_pos); } // Get the char by Position position on board
	char getCharFromBoard(int _x, int _y) const { return pBoard->getCharFromBoard(_x, _y); }				 // Get the char by (x,y) position on board

	void updatePreviousDir() { point.setPreviousDir(point.getDir()); }										 // Function to update the entity's previous direction to become the current (similar to previous_dir = dir)
	void updatePreviousChar() { point.setPreviousChar(getCharFromBoard(point.getPosition().x, point.getPosition().y)); } // Update the previous character of the entity based on its current position on the board

	bool const IsActivated() const { return is_activated; };	// The function returns true if the entity is activated(rolling/falling etc.) and false otherwise
	void activate() { is_activated = true; }					// Function to activate the entity
	void deactivate() { is_activated = false; }					// Function to deactivate the entity
	virtual int myRandom();										// Function to raffle a number ( 1 or 0 )

	void setPositionOfEntity(const GameConfig::Position& _pos) { point.setPosition(_pos); }
};





