#pragma once

#include "point.h"

class Barrels
{
	char ch = 'O';

	static constexpr int MAX_BARRELS = 2;
	int NUM_BARRELS = 0;

	Point barrels[MAX_BARRELS];

	Board* pBoard = nullptr;

public:
	Barrels() : barrels{ {0,0, ch},{0,0, ch} } {}

	void draw();
	void erase();
	void move();

	void setBoard(Board& _board) { pBoard = &_board; }
	void killBarrel();
};

