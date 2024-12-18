#pragma once

#include <windows.h> // for gotoxy
#include <process.h> // for system
#include <iostream>

using namespace std;

static constexpr int SCREEN_APPEARANCE = 5;
static constexpr int SCREEN_TIME = 150;
static constexpr int SCREEN_PAUSE_GAME = 50;				
static constexpr int SCREEN_WIN = 2000;
static constexpr int SCREEN_EXIT = 2000;

static constexpr WORD BLUE = FOREGROUND_BLUE;
static constexpr WORD RED = FOREGROUND_RED;
static constexpr WORD GREEN = FOREGROUND_GREEN;
static constexpr WORD DEFULT = RED | GREEN | BLUE;
static constexpr WORD PINK = RED | BLUE | FOREGROUND_INTENSITY;

static constexpr char FLOOR = '=';
static constexpr char FLOOR_LEFT = '<';
static constexpr char FLOOR_RIGHT = '>';
static constexpr char LADDER = 'H';
static constexpr char PRINCESS = '$';
static constexpr char DONKEY = '&';


void gotoxy(int x, int y);							// Move the cursor to the (x,y) position
void ShowConsoleCursor(bool showFlag);				// Display the cursor
void clrscr();										// Clear the screen
void setConsoleColor(WORD color);

extern bool colors_on;
