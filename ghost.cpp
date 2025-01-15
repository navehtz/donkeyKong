#include "ghost.h"

// Initialize ghost
void Ghost::setStartingGhost(Board* _pBoard, Position pos)
{
	pBoard = _pBoard;
	point.setPosition(pos);         // Same y-axis starting position for both cases

	if (myRandom() == 0)										// Start moving left
	{
		point.setDirX(LEFT);
	}
	else														// Start moving right
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
	point.setDirY(STAY);
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

// Manage the direction of the ghost while on the floor
void Ghost::manageDirection()
{
	int dirX = point.getDir().x;
	if ((rand() % 100) < (CHANGE_DIR_PROB * 100)) {
		point.setDirX(dirX * -1);
		dirX *= -1;
	}
	
	if ((dirX == LEFT && ch_left_down == SPACE) || (dirX = RIGHT && ch_right_down == SPACE))
		point.setDirX(dirX * -1);


}

// Handle the cases which the barrel explodes in (falling 8 chars or at wall)
void Ghost::blockedByWall()
{
	int dirX = point.getDir().x;
	if (res_is_wall_on_left) {										//linked to a wall - barrel can't pass
		if (dirX == LEFT) { point.setDirX(RIGHT); }
	}

	if (res_is_wall_on_right) {
		if (dirX == RIGHT) { point.setDirX(LEFT); }		//linked to a wall - barrel can't pass
	}
}


// The function returns true if the parameter is a floor/ceiling/wall and false otherwise
bool Ghost::isBlock(char _ch) const
{
	if (_ch == FLOOR || _ch == FLOOR_RIGHT || _ch == FLOOR_LEFT || _ch == WALL || _ch == ch)
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
