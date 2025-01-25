#pragma once

#include <iostream>
#include <locale>
#include <codecvt>
#include <string>

#include "gameConfig.h"
#include "board.h"

class Point {

	char ch = ' ';													// Character represented by this point
	char previous_char = ' ';										// Character previously at this point

	GameConfig::Position pos{ 0, 0 };								// Current position of the point

	GameConfig::Direction previous_dir{ GameConfig::STAY, GameConfig::STAY };               // Last direction before the current movement
	GameConfig::Direction dir_before_stay{ GameConfig::STAY, GameConfig::STAY };            // Direction before staying
	GameConfig::Direction dir_before_falling{ GameConfig::LEFT, GameConfig::STAY };         // Direction before a fall

	static constexpr GameConfig::Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} }; // Movement options: UP, LEFT, DOWN, RIGHT, STAY
	GameConfig::Direction dir{ 0, 0 };								// Current movement direction

public:
	Point(char _ch) : ch(_ch) {}									// Constructor initializing the point with a character

	char getChar() const { return ch; }								// Get the character represented by the point
	GameConfig::Position getPosition() const { return pos; }		// Get the current position of the point
	void setPosition(GameConfig::Position _pos) { pos = _pos; }		// Set the position of the point using Position
	void setPosition(int _x, int _y) { pos.x = _x; pos.y = _y; }	// Set the position of the point using x and y coordinates
	void setPositionX(int _x) { pos.x = _x; }						// Set the x-coordinate of the position
	void setPositionY(int _y) { pos.y = _y; }						// Set the y-coordinate of the position

	char getPreviousChar() const { return previous_char; }			// Get the previous character at this point
	void setPreviousChar(char _ch) { previous_char = _ch; }			// Set the previous character at this point

	void draw() const { GameConfig::gotoxy(pos.x, pos.y); std::cout << ch; }               // Draw the current character at the point's position
	void erase() const { GameConfig::gotoxy(pos.x, pos.y); std::cout << previous_char; }   // Erase the current character by drawing the previous character

	GameConfig::Direction getDir() const { return dir; }			// Get the current movement direction
	void setDir(GameConfig::Direction _dir) { dir = _dir; }			// Set the current movement direction
	void setDirX(int _x) { dir.x = _x; }							// Set the x component of the current direction
	void setDirY(int _y) { dir.y = _y; }							// Set the y component of the current direction

	GameConfig::Direction getPreviousDir() const { return previous_dir; }                   // Get the previous movement direction
	GameConfig::Direction getDirBeforeFalling() const { return dir_before_falling; }        // Get the direction before falling
	void setPreviousDir(GameConfig::Direction _previous_dir) { previous_dir = _previous_dir; } // Set the previous direction
	void setDirBeforeFalling(GameConfig::Direction _dir_before_falling) { dir_before_falling = _dir_before_falling; } // Set the direction before falling

	GameConfig::Direction getDirFromDirectionsArray(int i) { return directions[i]; }        // Get a direction from the directions array
	GameConfig::Direction getDirBeforeStay() { return dir_before_stay; }                    // Get the direction before staying
	void setDirBeforeStay(GameConfig::Direction _dir_before_stay) { dir_before_stay = _dir_before_stay; } // Set the direction before staying

};
