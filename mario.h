#pragma once

#include "point.h"
#include <Windows.h>	//for Sleep and colors
#include <stdbool.h>


class Mario
{
	char ch = '@';

	char ch_covered = ' ', ch_below = ' ', two_chars_below = ' ';  
	char ch_above = ' ', ch_left = ' ', ch_right = ' ';

	bool res_is_on_ladder = false, res_is_on_floor = false, res_is_below_roof = false;
	bool res_is_wall_on_left = false, res_is_wall_on_right = false, res_is_two_chars_below_floor = false;

	int fall_count = 0;
	int lives = 3;

	static constexpr int starting_pos_x = 25;
	static constexpr int starting_pos_y = 23;
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

	enum class MarioState {
		Climbing,
		Jumping,
		Falling,
		Walking_or_Staying
	};
	MarioState state;

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
	bool isOnLadder() const;
	bool isBlock(char _ch);
	void drawPreviousLetter(char _ch) { p.draw(_ch); }
	 
	void amend_next_move(bool below_roof, bool on_ladder, bool wall_on_left, bool wall_on_right, bool above_floor);
	void life();

	bool isJumping();
	void jump();

	bool isFalling();
	void fall();

	bool isClimbing() ;
	void climb();

	void walk_or_stay();

	void check_what_state();
	void update_state();
	void update_next_move();
	void update_previous_dir() { previous_dir = dir; }
	void update_previous_char() { p.setPreviousChar(getCharFromBoard(p.getX(), p.getY())); }
};

