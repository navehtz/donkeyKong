#include "regularGhost.h"

//// Initialize a ghost based on starting position
//void RegularGhost::setStartingGhost(Board* _pBoard, GameConfig::Position pos)
//{
//	pBoard = _pBoard;
//	point.setPosition(pos);         // Set the initial position of the ghost
//
//	//srand(GameConfig::getRandomSeed());
//	if (rand() % 2 == 0)            // Randomly decide initial direction (left or right)
//	{
//		point.setDirX(GameConfig::LEFT);
//	}
//	else
//	{
//		point.setDirX(GameConfig::RIGHT);
//	}
//
//	point.setPreviousChar(GameConfig::SPACE);
//
//	is_activated = true;
//
//	point.setPreviousChar(GameConfig::SPACE);
//}

// Update the chars representing the tiles around the ghost
void RegularGhost::updateCharParameters()
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
void RegularGhost::checkWhatState()
{
	if (isFalling())
		state = GhostState::Falling;
	else
		state = GhostState::Wander;
}

// Update the ghost's state
void RegularGhost::updateState()
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

//// Handle the ghost's wandering behavior
//void RegularGhost::wander()
//{
//	manageDirection();
//	blockedByWall();
//	point.setDirY(GameConfig::STAY);
//}

//// Handle the ghost's falling behavior
//void RegularGhost::fall()
//{
//	point.setDirX(GameConfig::STAY);
//	point.setDirY(GameConfig::DOWN);
//}

//// Manage the ghost's direction while wandering on the floor
//void RegularGhost::manageWanderDirection()
//{
//	int dirX = point.getDir().x;
//
//	if (dirX == GameConfig::STAY) {  // If just finished falling, set initial direction
//		dirX = GameConfig::LEFT;
//		point.setDirX(dirX);
//	}
//
//	//srand(GameConfig::getRandomSeed());
//	if ((rand() % 100) < (CHANGE_DIR_PROB * 100)) {  // Randomly change direction
//		point.setDirX(dirX * -1);
//		dirX *= -1;
//	}
//
//	if ((dirX == GameConfig::LEFT && ch_left_down == GameConfig::SPACE) || (dirX == GameConfig::RIGHT && ch_right_down == GameConfig::SPACE))
//		point.setDirX(dirX * -1);
//}

//// Stop the ghost's movement if it encounters a wall
//void RegularGhost::blockedByWall()
//{
//	int dirX = point.getDir().x;
//	if (res_is_wall_on_left && dirX == GameConfig::LEFT) {
//		point.setDirX(GameConfig::RIGHT);
//	}
//	if (res_is_wall_on_right && dirX == GameConfig::RIGHT) {
//		point.setDirX(GameConfig::LEFT);
//	}
//}

//// Update the ghost's movement for the next game loop
//void RegularGhost::updateNextMove()
//{
//	int newX = point.getPosition().x + point.getDir().x;
//	int newY = point.getPosition().y + point.getDir().y;
//
//	if (newX < 0 || newX >= GameConfig::BOARD_WIDTH) {  // Ensure position is within board bounds
//		newX = point.getPosition().x;
//	}
//	if (newY < 0 || newY >= GameConfig::BOARD_HEIGHT) {
//		newY = point.getPosition().y;
//	}
//
//	point.setPositionX(newX);
//	point.setPositionY(newY);
//}
