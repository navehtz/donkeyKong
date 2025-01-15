#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>
#include "gameConfig.h"


// Moves the console cursor to a specific position (x, y) on the screen.       (From the lab)
void GameConfig::gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;											// Handle to access the console output buffer
	COORD dwCursorPosition;											// Structure to hold the cursor's X and Y coordinates
	std::cout.flush();													// Ensures that the output buffer is flushed before moving the cursor
	dwCursorPosition.X = (short)x;									// Convert x to a short type
	dwCursorPosition.Y = (short)y;									// Convert y to a short type
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);				// Get the console output handle
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);		// Move the console cursor to the specified coordinates
}

// Display the cursor														   (From the lab)
void GameConfig::ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);					// Get console handle
	CONSOLE_CURSOR_INFO     cursorInfo;								// Cursor info structure
	GetConsoleCursorInfo(out, &cursorInfo);							// Retrieve current cursor info
	cursorInfo.bVisible = showFlag;									// Set visibility based on showFlag
	SetConsoleCursorInfo(out, &cursorInfo);							// Apply the updated cursor info
}

// Clear the screen 
void GameConfig::clrscr()
{
	system("cls");
}