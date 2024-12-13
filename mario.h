#pragma once

#include "point.h"
#include "barrels.h"

#include <Windows.h>	//for Sleep and colors
#include <stdbool.h>
#include <cstdlib>


class Mario
{
	char ch = '@';

	char ch_covered = ' ', ch_below = ' ', two_chars_below = ' ';  
	char ch_above = ' ', ch_left = ' ', ch_right = ' ';

	bool res_is_on_ladder = false, res_is_on_floor = false, res_is_below_roof = false;
	bool res_is_wall_on_left = false, res_is_wall_on_right = false, res_is_two_chars_below_floor = false;

	int fall_count = 0;
	int lives = 3;

	static constexpr int STARTING_POS_X = 2;
	static constexpr int STARTING_POS_Y = 23;
	//static constexpr int LIFE_POS_X = 11;
	//static constexpr int LIFE_POS_Y = 1;

	static constexpr int FALL_FROM_TOO_HIGH = 5;
	static constexpr int DEAD_MARIO = 0;

	static constexpr int UP = -1;
	static constexpr int LEFT = -1;
	static constexpr int DOWN = 1;
	static constexpr int RIGHT = 1;
	static constexpr int STAY = 0;
	static constexpr int MAX_BARRELS = 10;


	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);
	
	enum class MarioState {
		Climbing,
		Jumping,
		Falling,
		Walking_or_Staying
	};
	MarioState state = MarioState::Walking_or_Staying;

	struct Direction {
		int x, y;
	};

	Point p;
	Board* pBoard = nullptr;
	Barrels* pBarrels = nullptr;

public:
	Mario(): p(STARTING_POS_X, STARTING_POS_Y, ch) {}

	void setStartingMario();
	void keyPressed(char key);

	void draw() {
		p.draw(ch);
		pBoard->updateBoard(p.getX(), p.getY(), ch);
	}
	void erase() {
		p.erase();
		pBoard->updateBoard(p.getX(), p.getY(), p.getPreviousChar());
	}

	Point getPointP() const { return p; }
	int getPointX() const { return p.getX(); }
	int getPointY() const { return p.getY(); }

	void setBoard(Board& _board) {pBoard = &_board; }
	void setpBarrels(Barrels& _barrels) { pBarrels = &_barrels; }

	void move();
	void amendNextMove();
	bool isOnLadder() const;
	bool isBlock(char _ch);
	 
	bool isJumping();
	void jump();
	bool isFalling() const;
	void fall();
	bool isClimbing() ;
	void climb();
	void walkOrStay();

	void checkWhatState();
	void updateState();
	void updateNextMove();
	void updatePreviousDir() { p.setPreviousDir(p.getDir()); } //previous_dir = dir; }
	void updatePreviousChar() { p.setPreviousChar(getCharFromBoard(p.getX(), p.getY())); }
	void drawPreviousLetter(char _ch) { p.draw(_ch); }
	char getCharFromBoard(int _x, int _y) { return pBoard->getCharFromBoard(_x, _y); }

	int getLives() const { return lives; }
	void setLives(int _lives) { lives = _lives; }
	void printLives();
	void life();
	void startOver();
};

