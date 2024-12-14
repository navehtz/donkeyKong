#include <cstring> //for memcpy
#include <iostream>

#include "Board.h"

// This function resets the board to its original state
void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
	}
}

// This function prints the input board to the screen
void Board::printScreen(const char screen[][MAX_X + 1]) const 
{
	clrscr();														// Clears the console screen before printing the new board

	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << screen[i] << '\n';
	}
	std::cout << screen[MAX_Y - 1];									// Print the last row without a newline to avoid an extra blank line
}

