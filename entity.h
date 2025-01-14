#pragma once

#include "point.h"


class Entity
{
	char ch;

	Point point;

	Board* pBoard = nullptr;

	char ch_covered = SPACE, ch_below = SPACE;
	char ch_left = SPACE, ch_right = SPACE;


};

