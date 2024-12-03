#pragma once

#include "point.h"
#include <Windows.h>	//for Sleep and colors
#include <stdbool.h>


class Mario
{
	char ch = '@';

	char ch_covered = ' ', ch_below = ' ', two_chars_below = ' ';  
	char ch_above = ' ', ch_left = ' ', ch_right = ' ';

	int jump_height = 0;
	int lives = 3;

	static constexpr int starting_pos_x = 10;
	static constexpr int starting_pos_y = 18;
	static constexpr int life_pos_x = 11;
	static constexpr int life_pos_y = 1;

	static constexpr int UP = -1;
	static constexpr int LEFT = -1;
	static constexpr int DOWN = 1;
	static constexpr int RIGHT = 1;
	static constexpr int STAY = 0;

	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	
	struct Direction {
		int x, y;
	};
	static constexpr Direction directions[] = { {0, -1}, {-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	Direction dir{ 0, 0 }; // current direction: dir.x, dir.y
	Direction previous_dir{ 0,0 };

	Point p;
	Board* pBoard = nullptr;


public:
	Mario(): p(starting_pos_x, starting_pos_y, ch) {}

	void draw() {
		p.draw(ch);
		pBoard->updateBoard(p.getX(), p.getY(), ch);
	}
	void erase() {
		p.erase();
		pBoard->updateBoard(p.getX(), p.getY(), p.getPreviousChar());
	}
	void keyPressed(char key);

	Point getPointP() const { return p; }
	void setBoard(Board& _board) {pBoard = &_board; }

	char getCharFromBoard(int _x, int _y) { return pBoard->getCharFromBoard(_x, _y); }

	void move();
	bool isOnLadder();
	bool isBlock(char ch);
	void drawPreviousLetter(char _ch) { p.draw(_ch); }
	 
	bool isJumping();
	void jump();
	void fall(int _dir_x);
	void life();
};

