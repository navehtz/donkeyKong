#include "ghost.h"

// Initialize a ghost based on starting position
void Ghost::setStartingGhost(Board* _pBoard, GameConfig::Position pos)
{
	pBoard = _pBoard;
	point.setPosition(pos);         // Set the initial position of the ghost

	if (myRandom() == 0)            // Randomly decide initial direction (left or right)
	{
		point.setDirX(GameConfig::LEFT);
	}
	else
	{
		point.setDirX(GameConfig::RIGHT);
	}

	point.setPreviousChar(GameConfig::SPACE);

	is_activated = true;

	point.setPreviousChar(GameConfig::SPACE);
}

// Generate a random number (0 or 1)
int Ghost::myRandom()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 1);
	return dist(gen);
}

// Update the chars representing the tiles around the ghost
void Ghost::updateCharParameters()
{
	int _x = point.getPosition().x, _y = point.getPosition().y;

	ch_covered = getCharFromBoard(_x, _y);
	ch_below = getCharFromBoard(_x, _y + GameConfig::DOWN);
	ch_left = getCharFromBoard(_x + GameConfig::LEFT, _y);
	ch_right = getCharFromBoard(_x + GameConfig::RIGHT, _y);
	ch_left_down = getCharFromBoard(_x + GameConfig::LEFT, _y + GameConfig::DOWN);
	ch_right_down = getCharFromBoard(_x + GameConfig::RIGHT, _y + GameConfig::DOWN);

	res_is_on_floor = isBlock(ch_below);
	res_is_wall_on_left = isBlock(ch_left);
	res_is_wall_on_right = isBlock(ch_right);
	res_is_left_down = isBlock(ch_left_down);
	res_is_right_down = isBlock(ch_right_down);
}

// Check the ghost's current state
void Ghost::checkWhatState()
{
	if (isFalling())
		state = GhostState::Falling;
	else
		state = GhostState::Wander;
}

// Update the ghost's state
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

// Handle the ghost's wandering behavior
void Ghost::wander()
{
	manageDirection();
	blockedByWall();
	point.setDirY(GameConfig::STAY);
}

// Handle the ghost's falling behavior
void Ghost::fall()
{
	point.setDirX(GameConfig::STAY);
	point.setDirY(GameConfig::DOWN);
}

// Manage the ghost's direction while wandering on the floor
void Ghost::manageDirection()
{
	int dirX = point.getDir().x;

	if (dirX == GameConfig::STAY) {  // If just finished falling, set initial direction
		dirX = GameConfig::LEFT;
		point.setDirX(dirX);
	}
	if ((rand() % 100) < (CHANGE_DIR_PROB * 100)) {  // Randomly change direction
		point.setDirX(dirX * -1);
		dirX *= -1;
	}

	if ((dirX == GameConfig::LEFT && ch_left_down == GameConfig::SPACE) || (dirX == GameConfig::RIGHT && ch_right_down == GameConfig::SPACE))
		point.setDirX(dirX * -1);
}

// Stop the ghost's movement if it encounters a wall
void Ghost::blockedByWall()
{
	int dirX = point.getDir().x;
	if (res_is_wall_on_left && dirX == GameConfig::LEFT) {
		point.setDirX(GameConfig::RIGHT);
	}
	if (res_is_wall_on_right && dirX == GameConfig::RIGHT) {
		point.setDirX(GameConfig::LEFT);
	}
}

// Update the ghost's movement for the next game loop
void Ghost::updateNextMove()
{
	int newX = point.getPosition().x + point.getDir().x;
	int newY = point.getPosition().y + point.getDir().y;

	if (newX < 0 || newX >= pBoard->get_board_width()) {  // Ensure position is within board bounds
		newX = point.getPosition().x;
	}
	if (newY < 0 || newY >= pBoard->get_board_height()) {
		newY = point.getPosition().y;
	}

	point.setPositionX(newX);
	point.setPositionY(newY);
}
