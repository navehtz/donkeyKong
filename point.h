#pragma once

#include <iostream>
#include <locale>
#include <codecvt>
#include <string>

#include "general.h"
#include "board.h"


class Point {

	char ch = ' ';
	char  previous_char = ' ';

	static constexpr int DOWN = 1;
	static constexpr int RIGHT = 1;
	static constexpr int LEFT = -1;
	static constexpr int STAY = 0;

	//struct Direction {																				// Direction structure for handling movement	
	//	int x, y;
	//};
	//int x=0, y=0;

	Position pos{ 0,0 };

	Direction previous_dir{ STAY, STAY };															// Last direction before the current movement
	Direction dir_before_stay{ STAY, STAY };														// To remember the direction before mario stopped
	Direction dir_before_falling{ LEFT,STAY };														// Direction prior to a fall

	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };			// Movement options: UP, LEFT, DOWN, RIGHT, STAY
	Direction dir{ 0, 0 }; 


public:
	//Point(int _x, int _y, char _ch) : x(_x), y(_y), ch(_ch) {}						// For Mario (initial position and character)
	Point(char _ch) : ch(_ch) {}													// For barrels (character only)
	

	Position getPosition() const { return pos; }									// Get the member 'pos'
	void setPosition(Position _pos) { pos = _pos; }													// Set the data member 'x'
	void setPosition(int _x, int _y) { pos.x = _x; pos.y = _y; }							// Set the (x,y) position
	void setPositionX(int _x) { pos.x = _x; }							// Set the (x,y) position
	void setPositionY(int _y) { pos.y = _y; }							// Set the (x,y) position


	//int getX() const { return x; }													// Get the data member 'x'
	//int getY() const { return y; }													// Get the data member 'y'
	//void setX(int _x) { x = _x; }													// Set the data member 'x'
	//void setY(int _y) { y = _y; }													// Set the data member 'y'

	char getPreviousChar() const { return previous_char; }							// Get the previous char data memeber
	void setPreviousChar(char _ch) { previous_char = _ch; }							// Set the previous char data memeber

	void draw(char _ch) const {														// Draw the current character on the board
		gotoxy(pos.x, pos.y);
		std::cout << _ch;
	}
	void erase() const {															// Erase the character by redrawing the previous character
		gotoxy(pos.x, pos.y);
		std::cout << previous_char;
	}

	Direction getDir() const { return dir; }										// Get the current movement direction (x,y)
	void setDir(Direction _dir) { dir = _dir; }										// Set the current movement direction (x,y)
	void setDirX(int _x) { dir.x = _x; }											// Set the current movement direction (only x-axis)
	void setDirY(int _y) { dir.y = _y; }                                            // Set the current movement direction (only y-axis)

	Direction getPreviousDir() const { return previous_dir; }						// Get the previous movement direction (x,y)
	Direction getDirBeforeFalling() const { return dir_before_falling; }			// Get the previous movement direction before falling (function for barrels
	void setPreviousDir(Direction _previous_dir) { previous_dir = _previous_dir; }						  // Set the previous direction
	void setDirBeforeFalling(Direction _dir_before_falling) { dir_before_falling = _dir_before_falling; } // Set the direction before falling

	Direction getDirFromDirectionsArray(int i) { return directions[i]; }			// Get the current the direction 
	
	Direction getDirBeforeStay() { return dir_before_stay; }						//
	void setDirBeforeStay(Direction _dir_before_stay) { dir_before_stay = _dir_before_stay; } // Set the direction before falling

};

