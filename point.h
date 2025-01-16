#pragma once

#include <iostream>
#include <locale>
#include <codecvt>
#include <string>

#include "gameConfig.h"
#include "board.h"


class Point {

	char ch = ' ';
	char  previous_char = ' ';

	GameConfig::Position pos{ 0,0 };

	GameConfig::Direction previous_dir{ GameConfig::STAY, GameConfig::STAY };															// Last direction before the current movement
	GameConfig::Direction dir_before_stay{ GameConfig::STAY, GameConfig::STAY };														// To remember the direction before mario stopped
	GameConfig::Direction dir_before_falling{ GameConfig::LEFT,GameConfig::STAY };														// Direction prior to a fall

	static constexpr GameConfig::Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };			// Movement options: UP, LEFT, DOWN, RIGHT, STAY
	GameConfig::Direction dir{ 0, 0 };


public:
	Point(char _ch) : ch(_ch) {}													// For barrels (character only)
	 
	char getChar() const { return ch; }
	GameConfig::Position getPosition() const { return pos; }									// Get the member 'pos'
	void setPosition(GameConfig::Position _pos) { pos = _pos; }													// Set the data member 'x'
	void setPosition(int _x, int _y) { pos.x = _x; pos.y = _y; }							// Set the (x,y) position
	void setPositionX(int _x) { pos.x = _x; }							// Set the (x,y) position
	void setPositionY(int _y) { pos.y = _y; }							// Set the (x,y) position

	char getPreviousChar() const { return previous_char; }							// Get the previous char data memeber
	void setPreviousChar(char _ch) { previous_char = _ch; }							// Set the previous char data memeber

	void draw() const {														// Draw the current character on the board
		GameConfig::gotoxy(pos.x, pos.y);
		std::cout << ch;
	}
	void erase() const {															// Erase the character by redrawing the previous character
		GameConfig::gotoxy(pos.x, pos.y);
		std::cout << previous_char;
	}

	GameConfig::Direction getDir() const { return dir; }										// Get the current movement direction (x,y)
	void setDir(GameConfig::Direction _dir) { dir = _dir; }										// Set the current movement direction (x,y)
	void setDirX(int _x) { dir.x = _x; }											// Set the current movement direction (only x-axis)
	void setDirY(int _y) { dir.y = _y; }                                            // Set the current movement direction (only y-axis)

	GameConfig::Direction getPreviousDir() const { return previous_dir; }						// Get the previous movement direction (x,y)
	GameConfig::Direction getDirBeforeFalling() const { return dir_before_falling; }			// Get the previous movement direction before falling (function for barrels
	void setPreviousDir(GameConfig::Direction _previous_dir) { previous_dir = _previous_dir; }						  // Set the previous direction
	void setDirBeforeFalling(GameConfig::Direction _dir_before_falling) { dir_before_falling = _dir_before_falling; } // Set the direction before falling

	GameConfig::Direction getDirFromDirectionsArray(int i) { return directions[i]; }			// Get the current the direction 
	
	GameConfig::Direction getDirBeforeStay() { return dir_before_stay; }						//
	void setDirBeforeStay(GameConfig::Direction _dir_before_stay) { dir_before_stay = _dir_before_stay; } // Set the direction before falling

};

