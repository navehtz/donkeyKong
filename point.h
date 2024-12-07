#pragma once

#include <iostream>
using namespace std;

#include "general.h"
#include "board.h"


class Point {
	int x, y;
	char ch = ' ', previous_char = ' ';

	struct Direction {
		int x, y;
	};
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y
	Direction previous_dir{ 0,0 };

public:
	Point(int _x, int _y, char _ch):
		x(_x), y(_y), ch(_ch) {}

	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }

	char getPreviousChar() const { return previous_char; }
	void setPreviousChar(char _ch) { previous_char = _ch; }

	void draw(char _ch) const{
		gotoxy(x, y);
		cout << _ch;
	}
	void erase() {   
		gotoxy(x, y);
		cout << previous_char;
	}

	Direction getDir() { return dir; }
	void setDir(Direction _dir) { dir = _dir; }
	void setDirX(int _x) { dir.x = _x; }
	void setDirY(int _y) { dir.y = _y; }

	Direction getPreviousDir() { return previous_dir; }
	void setPreviousDir(Direction _previous_dir) { previous_dir = _previous_dir; }

	Direction getDirFromDirectionsArray(int i) { return directions[i]; }
};

