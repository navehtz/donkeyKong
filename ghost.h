#pragma once

#include "point.h"

class ghost
{
	// Constants
	static constexpr int RIGHT = 1;
	static constexpr int LEFT = -1;
	static constexpr int STAY = 0;

	// Members
	char ch = 'x';

	Point point;

	Board* pBoard = nullptr;

	char ch_covered = SPACE, ch_below = SPACE, two_chars_below = SPACE;
	char ch_left = SPACE, ch_right = SPACE;

	bool res_is_on_ladder = false, res_is_on_floor = false, res_is_below_roof = false;
	bool res_is_wall_on_left = false, res_is_wall_on_right = false, res_is_two_chars_below_floor = false;

	bool is_activated = false;
	bool is_exploded = false;

	// States of barrel
	enum class BarrelState {
		Falling,
		Rolling
	};
	BarrelState state = BarrelState::Rolling;

	// Defining struct for barrel's direction
	struct Direction {
		int x, y;
	};

	friend class Barrels;
};

