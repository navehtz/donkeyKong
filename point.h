#pragma once

#include <iostream>
using namespace std;

#include "general.h"
#include "board.h"


class Point {

	char ch = ' ';
	char  previous_char = ' ';

	static constexpr int DOWN = 1;
	static constexpr int RIGHT = 1;
	static constexpr int LEFT = -1;
	static constexpr int STAY = 0;

	struct Direction {
		int x, y;
	};
	int x=0, y=0;

	Direction previous_dir{ STAY,STAY };
	Direction dir_before_falling{ LEFT,STAY };

	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y

public:
	Point(int _x, int _y, char _ch) : x(_x), y(_y), ch(_ch) {}															//constructor for mario
	Point(char _ch) : ch(_ch) {}																						//constructor for barrel
	//Point(int _x, int _y, char _ch, Direction _previous_dir) : x(_x), y(_y), ch(_ch), previous_dir(_previous_dir) {}		//constructor for barrel

	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }

	char getPreviousChar() const { return previous_char; }
	void setPreviousChar(char _ch) { previous_char = _ch; }

	void draw(char _ch) const {
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
	Direction getDirBeforeFalling() { return dir_before_falling; }
	void setPreviousDir(Direction _previous_dir) { previous_dir = _previous_dir; }
	void setDirBeforeFalling(Direction _dir_before_falling) { dir_before_falling = _dir_before_falling; }

	Direction getDirFromDirectionsArray(int i) { return directions[i]; }
};

