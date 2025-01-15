#pragma once

#include "point.h"
#include "gameConfig.h"

class Entity
{
protected:
	Point point;

	Board* pBoard = nullptr;

	char ch_covered = GameConfig::SPACE, ch_below = GameConfig::SPACE;
	char ch_left = GameConfig::SPACE, ch_right = GameConfig::SPACE;

	bool res_is_on_floor = false, res_is_wall_on_left = false, res_is_wall_on_right = false;

public:
	Entity(char _ch) : point(_ch) {}
	Entity(int x, int y, char _ch) : point(_ch) { point.setPositionX(x); point.setPositionY(y); }

	void setpBoard(Board& _board) { pBoard = &_board; }						// Set pBoard to the board
	const Point& getPoint() const { return point; }								// Get the member 'point'
	GameConfig::Position getPosition() const { return point.getPosition(); }								// Get Mario position by x-axis
	GameConfig::Direction getDir() const { return point.getDir(); }		//Use it!!!!    // Get Mario's lives
	void draw() {															// Draw Mario on the screen and update the board
		point.draw();
		pBoard->updateBoard(point.getPosition(), point.getChar());
	}
	virtual void erase() {
		point.erase();
		pBoard->updateBoard(point.getPosition(), point.getPreviousChar());						// Update the board without the current barrel
	}
	virtual void checkWhatState() = 0;
	virtual void updateState() = 0;																			// Update Mario's state
	virtual void updateNextMove() = 0;
	virtual void updateCharParameters() = 0;						// Update all the char data members around mario

	virtual void move();
	virtual void fall() = 0;												// Handle the barrel's falling
	bool isFalling() const;										// Check if the barrel is falling 
	bool isBlock(char _ch) const;								// The function returns true if the parameter is a floor/ceiling/wall and false otherwise

	char getCharFromBoard(GameConfig::Position _pos) const { return pBoard->getCharFromBoard(_pos); }			// Get the char in the (x,y) position on board
	char getCharFromBoard(int _x, int _y) const { return pBoard->getCharFromBoard(_x, _y); }			// Get the char in the (x,y) position on board

	void updatePreviousDir() { point.setPreviousDir(point.getDir()); }									// Function to update the Mario's previous direction to become the current (similar to previous_dir = dir)
	void updatePreviousChar() { point.setPreviousChar(getCharFromBoard(point.getPosition().x, point.getPosition().y)); }		// Function for keeping the char the barrel is on so it can be printes in the next loop

};

