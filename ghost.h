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

	char ch_covered = SPACE, ch_below = SPACE;
	char ch_left = SPACE, ch_right = SPACE;
	char ch_left_down = SPACE, ch_right_down = SPACE;

	bool res_is_on_floor = false, res_is_wall_on_left = false, res_is_wall_on_right = false;

	// States of ghost
	enum class GhostState {
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

