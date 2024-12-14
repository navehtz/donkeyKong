#include <cstring> //for memcpy
#include <iostream>

#include "Board.h"

void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
	}
}

void Board::printScreen(const char screen[][MAX_X + 1]) const 
{
	clrscr();

	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << screen[i] << '\n';
	}
	std::cout << screen[MAX_Y - 1];
}

