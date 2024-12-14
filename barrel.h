#pragma once

#include "point.h"
#include <Windows.h>	//for Sleep and colors
#include <random>


class Barrel
{
	static constexpr int STARTING_POS_LEFT_X = 36;
	static constexpr int STARTING_POS_RIGHT_X = 38;
	char ch = 'O';

	int fall_count = 0;
	Point point;

	Board* pBoard = nullptr;

	char ch_covered = ' ', ch_below = ' ', two_chars_below = ' ';
	char ch_above = ' ', ch_left = ' ', ch_right = ' ';

	bool res_is_on_ladder = false, res_is_on_floor = false, res_is_below_roof = false;
	bool res_is_wall_on_left = false, res_is_wall_on_right = false, res_is_two_chars_below_floor = false;

	bool is_activated = false;
	bool is_exploded = false;
	static constexpr int STARTING_POS_Y = 3;

	static constexpr int DOWN = 1;
	static constexpr int RIGHT = 1;
	static constexpr int LEFT = -1;
	static constexpr int STAY = 0;

	static constexpr int FALL_FROM_TOO_HIGH = 8;
	static constexpr int EXPLODED_BARREL = 0;

	enum class BarrelState {
		Falling,
		Rolling
	};
	BarrelState state = BarrelState::Rolling;

	struct Direction {
		int x, y;
	};

public:
	Barrel() : point(ch) {}
	//Barrel() : point(STARTING_POS_LEFT_X, STARTING_POS_Y, ch) {}

	Point getPoint() { return point; } //maybe const

	void draw() {
		point.draw(ch);
		pBoard->updateBoard(point.getX(), point.getY(), ch);
	}
	void erase() {
		point.erase();
		pBoard->updateBoard(point.getX(), point.getY(), point.getPreviousChar());
	}

	void setpBoard(Board& _board) { pBoard = &_board; }	

	void setStartingBarrel();

	void checkWhatState();
	void updateState();

	char getCharFromBoard(int _x, int _y) { return pBoard->getCharFromBoard(_x, _y); }

	void move();
	bool isFalling();
	void fall();
	void roll();
	void explode();
	bool getIsExploded() { return is_exploded; }
	void setIsExploded(bool _is_exploded) { is_exploded = _is_exploded; }
	bool isBlock(char _ch);

	void updatePreviousDir() { point.setPreviousDir(point.getDir()); } //previous_dir = dir; }                     //change the name without underscore
	void updatePreviousChar() { point.setPreviousChar(getCharFromBoard(point.getX(), point.getY())); }

	void updateNextMove();

	bool IsActivated() { return is_activated; };
	void activate() { is_activated = true; }
	
	int myRandom();
	void drawExplosion();
};

