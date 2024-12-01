#pragma once

#include "point.h"
#include <stdbool.h>


class Mario
{
	char ch = '@';
	//char previous_char = ' ';
	static constexpr int starting_pos_x = 20;
	static constexpr int starting_pos_y = 23;
	static constexpr int UP = -1;
	static constexpr int LEFT = -1;
	static constexpr int DOWN = 1;
	static constexpr int RIGHT = 1;
	static constexpr int STAY = 0;

	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	
	struct Direction
	{
		int x, y;
	};

	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y
	
public:
	Point p;
	char previous_char = ' ';
	Mario(): p(starting_pos_x, starting_pos_y, ch, previous_char, nullptr) {}
	void draw() { p.draw(ch); }
	void erase() { p.erase(previous_char); }
	void keyPressed(char key);

	char getPreviousChar() { return previous_char; }
	void setPreviousChar(char _ch) { previous_char = _ch; }
	//Point getPointP() { return p; }

	char getCharPosition(int _x, int _y) { return p.getCharPosition(_x, _y); }
	void move();
	bool isOnFloor();
	bool isOnLadder();
	
	void drawPreviousLetter(char _ch) { p.draw(_ch); }
	
	 
};

