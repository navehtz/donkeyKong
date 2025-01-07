#include "ghost.h"

// Initialize ghost
void Ghost::setStartingGhost(Board* _pBoard, Position pos)
{
	pBoard = _pBoard;
	point.setPosition(pos);         // Same y-axis starting position for both cases

	if (myRandom() == 0)										// Start from the left side
	{
		point.setDirX(LEFT);
	}
	else														// Start from the right side
	{
		point.setDirX(RIGHT);
	}

	point.setPreviousChar(SPACE);
}

// Function 
int Ghost::myRandom()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 1);
	return dist(gen);
}


// Handle the ghost's movement
void Ghost::move()
{
	updateCharParameters();									// Update all the char data members around mario
	checkWhatState();										// Check what is the ghost's state 
	updateState();											// Update the moves that the ghost should do by the state

	//update prameters
	updateNextMove();
	updatePreviousChar();
	updatePreviousDir();
}

// Update all the char data members around mario
void Ghost::updateCharParameters()
{
	int _x = point.getPosition().x, _y = point.getPosition().y;

	ch_covered = getCharFromBoard(_x, _y);
	ch_below = getCharFromBoard(_x, _y + DOWN);
	ch_left = getCharFromBoard(_x + LEFT, _y);
	ch_right = getCharFromBoard(_x + RIGHT, _y);
	ch_left_down = getCharFromBoard(_x + LEFT, _y + DOWN);
	ch_right_down = getCharFromBoard(_x + RIGHT, _y + DOWN);

	res_is_on_floor = isBlock(ch_below);
	res_is_wall_on_left = isBlock(ch_left);
	res_is_wall_on_right = isBlock(ch_right);
	res_is_left_down = isBlock(ch_left_down);
	res_is_right_down = isBlock(ch_right_down);
}

//// Check in which state the barrel is
void Ghost::checkWhatState()
{
	if (isFalling())
		state = GhostState::Falling;
	else
		state = GhostState::Wander;
}

// Update the barrel's state
void Ghost::updateState()
{
	switch (state)
	{
	case GhostState::Wander:
		wander();
		break;
	case GhostState::Falling:
		fall();
		break;
	}
}

// Handle the barrel's rolling
void Ghost::wander()
{
	manageDirection();

	blockedByWall();
	updateWanderDirection();
	point.setDirY(STAY);
}

void Ghost::updateWanderDirection()
{
	// randommmmmmmmmmmmmm 95 / 5
}
// Check if the barrel is falling 
bool Ghost::isFalling() const
{
	return ch_below == SPACE ? true : false;
}

// Handle the barrel's falling
void Ghost::fall()
{
	point.setDirX(STAY);
	point.setDirY(DOWN);
}

// Manage the direction of the barrel while on the floor
void Ghost::manageDirection()
{
	switch (ch_below)
	{
	case(FLOOR_LEFT):
		point.setDir({ LEFT, STAY });					// Update direction to left
		point.setDirBeforeFalling(point.getDir());		// Update direction before (maybe) falling
		break;
	case(FLOOR_RIGHT):
		point.setDir({ RIGHT, STAY });					// Update direction to right
		point.setDirBeforeFalling(point.getDir());		// Update direction before (maybe) falling
		break;
	case(FLOOR):
		point.setDir({ point.getDirBeforeFalling() });	// Keep moving the direction as before
	}
}

// Handle the cases which the barrel explodes in (falling 8 chars or at wall)
void Ghost::blockedByWall()
{
	if (res_is_wall_on_left) {										//linked to a wall - barrel can't pass
		if (point.getDir().x == LEFT) { point.setDirX(STAY); }
	}

	if (res_is_wall_on_right) {
		if (point.getDir().x == RIGHT) { point.setDirX(STAY); }		//linked to a wall - barrel can't pass
	}
}


// The function returns true if the parameter is a floor/ceiling/wall and false otherwise
bool Ghost::isBlock(char _ch) const
{
	if (_ch == FLOOR || _ch == FLOOR_RIGHT || _ch == FLOOR_LEFT || _ch == WALL)
		return true;
	else
		return false;
}

// Updating the movement of the barrel for the next loop according to the position and the direction
void Ghost::updateNextMove()
{
	int newX = point.getPosition().x + point.getDir().x;
	int newY = point.getPosition().y + point.getDir().y;

	if (newX < 0 || newX >= pBoard->get_board_width())				// Update the next move by the board size	
		newX = point.getPosition().x;
	if (newY < 0 || newY >= pBoard->get_board_height())				// Update the next move by the board size	
		newY = point.getPosition().y;

	point.setPositionX(newX);
	point.setPositionY(newY);
}
