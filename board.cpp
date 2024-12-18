#include <cstring> //for memcpy
#include <iostream>

#include "Board.h"

// This function resets the board to its original state
void Board::reset() {
	for (int i = 0; i < MAX_Y; i++) {
		memcpy(currentBoard[i], originalBoard[i], MAX_X + 1);
	}
}

 //This function prints the input board to the screen
void Board::printScreen(const char screen[][MAX_X + 1]) const 
{
	clrscr();														// Clears the console screen before printing the new board

	for (int i = 0; i < MAX_Y - 1; i++) {
		std::cout << screen[i] << '\n';
		Sleep(SCREEN_APPEARANCE);
	}
	std::cout << screen[MAX_Y - 1];									// Print the last row without a newline to avoid an extra blank line
}

//This function prints the input board to the screen
void Board::printScreen(const char screen[][MAX_X + 1], bool _colors) const
{
	clrscr();														// Clears the console screen before printing the new board

	if (_colors) {
		for (int i = 0; i < MAX_Y; i++) {
			for (int j = 0; j < MAX_X; j++) {
				char ch = screen[i][j];

				switch (ch) {
				case LADDER:						                                  
					setConsoleColor(BLUE);  
					break;
				case FLOOR:
					setConsoleColor(RED);
					break;
				case FLOOR_LEFT:
					setConsoleColor(RED);
					break;
				case FLOOR_RIGHT:
					setConsoleColor(RED);
					break;
				case PRINCESS:
					setConsoleColor(PINK);
					break;
				case DONKEY:
					setConsoleColor(GREEN);
					break;
				default:
					setConsoleColor(DEFULT);       
					break;
				}
				cout << ch;
			}
			Sleep(SCREEN_APPEARANCE);
			if(i != MAX_Y - 1)
				cout << '\n';
		}
		setConsoleColor(DEFULT);                   // Return consol's color to defult
	}
	else	{
		for (int i = 0; i < MAX_Y - 1; i++) {
			std::cout << screen[i] << '\n';
			Sleep(SCREEN_APPEARANCE);
		}
		cout << screen[MAX_Y - 1];								// Print the last row without a newline to avoid an extra blank line
	}
								
}

void Board::printScreenWithColors(const char screen[][MAX_X + 1], WORD color) const
{
	setConsoleColor(color);
	printScreen(screen);
	setConsoleColor(DEFULT);
}
