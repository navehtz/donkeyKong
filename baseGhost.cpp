#include "baseGhost.h"

// Initialize a ghost based on starting position
void BaseGhost::setStartingGhost(Board* _pBoard, GameConfig::Position pos)
{
	pBoard = _pBoard;
	point.setPosition(pos);         // Set the initial position of the ghost

	//srand(GameConfig::getRandomSeed());
	if (rand() % 2 == 0)            // Randomly decide initial direction (left or right)
	{
		point.setDirX(GameConfig::LEFT);
	}
	else
	{
		point.setDirX(GameConfig::RIGHT);
	}

	point.setPreviousChar(GameConfig::SPACE);

	is_activated = true;

	//point.setPreviousChar(GameConfig::SPACE);
}

// Stop the ghost's movement if it encounters a wall
void BaseGhost::blockedByWall()
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
void BaseGhost::updateNextMove()
{
	int newX = point.getPosition().x + point.getDir().x;
	int newY = point.getPosition().y + point.getDir().y;

	if (newX < 0 || newX >= GameConfig::BOARD_WIDTH) {  // Ensure position is within board bounds
		newX = point.getPosition().x;
	}
	if (newY < 0 || newY >= GameConfig::BOARD_HEIGHT) {
		newY = point.getPosition().y;
	}

	point.setPosition(newX, newY);
}

// Handle the ghost's wandering behavior
void BaseGhost::wander()
{
	manageWanderDirection();
	blockedByWall();
	point.setDirY(GameConfig::STAY);
}

// Manage the ghost's direction while wandering on the floor
void BaseGhost::manageWanderDirection()
{
	int dirX = point.getDir().x;

	if (dirX == GameConfig::STAY) {  // If just finished falling, set initial direction
		dirX = GameConfig::LEFT;
		point.setDirX(dirX);
	}

	//srand(GameConfig::getRandomSeed());
	if ((rand() % 100) < (CHANGE_DIR_PROB * 100)) {  // Randomly change direction
		point.setDirX(dirX * -1);
		dirX *= -1;
	}

	if ((dirX == GameConfig::LEFT && ch_left_down == GameConfig::SPACE) || (dirX == GameConfig::RIGHT && ch_right_down == GameConfig::SPACE))
		point.setDirX(dirX * -1);
}

// Handle the ghost's falling behavior
void BaseGhost::fall()
{
	point.setDirX(GameConfig::STAY);
	point.setDirY(GameConfig::DOWN);
}