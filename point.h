#pragma once

#include <iostream>
using namespace std;

#include "general.h"
#include "board.h"

class Point {
	int x, y;
	char ch, previous_char;
	Board* pBoard = nullptr;

public:
	Point() {}
	Point(int _x, int _y, char _ch, char _previous_char, Board* _pBoard):
		x(_x), y(_y), ch(_ch), previous_char(_previous_char), pBoard(_pBoard) {}

	int getX() const { return x; }
	int getY() const { return y; }
	void setX(int _x) { x = _x; }
	void setY(int _y) { y = _y; }

	char getPreviousChar() const { return previous_char; }
	void setPreviousChar(char _ch) { previous_char = _ch; }

	Board* get_pBoard() { return pBoard; }
	void set_pBoard(Board* _pBoard) { pBoard = _pBoard; }

	void draw(char ch) const {
		gotoxy(x, y);
		cout << ch;
		pBoard->updateBoard(x, y, ch);
	}
	void erase(char _previous_char) {   
		gotoxy(x, y);
		cout << previous_char;
		pBoard->updateBoard(x, y, previous_char);
	}
	void setBoard(Board& board) {
		pBoard = &board;
	}
	char getCharPosition(int _x, int _y) { return pBoard->getCharPosition(_x, _y); }
};

