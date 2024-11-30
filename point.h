#pragma once

#include <iostream>
using namespace std;

#include "general.h"
#include "board.h"

class Point {
public:
	int x, y;
	char ch, previous_char;
	Board* pBoard = nullptr;

	Point() {}
	Point(int _x, int _y, char _ch, char _previous_char, Board* _pBoard): x(_x), y(_y), ch(_ch),
														previous_char(_previous_char), pBoard(_pBoard) {}
	void draw(char ch) const {
		gotoxy(x, y);
		cout << ch;
		pBoard->updateBoard(x, y, ch);
	}
	void erase(char previous_char) {   //changeeeeeeeeeeeeeee
		gotoxy(x, y);
		cout << previous_char;
		pBoard->updateBoard(x, y, ch);
	}
	void setBoard(Board& board) {
		pBoard = &board;
	}
	char getCharPosition(int _x, int _y) { return pBoard->getCharPosition(_x, _y); }
};

