#pragma once

#include <iostream>
using namespace std;

#include "general.h"
#include "board.h"

class Point {
	int x, y;
	char ch, previous_char = ' ';

public:
	Point(int _x, int _y, char _ch):
		x(_x), y(_y), ch(_ch) {}

	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }

	char getPreviousChar() const { return previous_char; }
	void setPreviousChar(char _ch) { previous_char = _ch; }

	void draw(char ch) const {
		gotoxy(x, y);
		cout << ch;
	}
	void erase() {   
		gotoxy(x, y);
		cout << previous_char;
	}
};

