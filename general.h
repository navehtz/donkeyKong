#pragma once


void gotoxy(int x, int y);							// Move the cursor to the (x,y) position
void ShowConsoleCursor(bool showFlag);				// Display the cursor
void clrscr();										// Clear the screen

static constexpr int DEAD_MARIO = 0;
static constexpr int FULL_LIVES = 3;
static constexpr int EXPLOSION_RADIUS = 2;
static constexpr int MAX_BARRELS = 5;

static constexpr int SCREEN_APPEARANCE = 5;
static constexpr int SCREEN_TIME = 150;
static constexpr int SCREEN_PAUSE_GAME = 50;
static constexpr int SCREEN_WIN = 2000;
static constexpr int SCREEN_EXIT = 2000;
static constexpr int SCREEN_FLASH_MARIO = 200;

static constexpr char WALL = 'Q';
static constexpr char FLOOR = '=';
static constexpr char FLOOR_LEFT = '<';
static constexpr char FLOOR_RIGHT = '>';
static constexpr char LADDER = 'H';
static constexpr char PRINCESS = '$';
static constexpr char GORRILA = '&';
static constexpr char SPACE = ' ';

struct Position {
	int x, y;
};