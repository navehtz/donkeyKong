#include "specialGhost.h"

// Update the chars representing the tiles around the ghost
void SpecialGhost::updateCharParameters()
{
	int _x = point.getPosition().x, _y = point.getPosition().y;

	ch_covered = getCharFromBoard(_x, _y);
	ch_below = getCharFromBoard(_x, _y + GameConfig::DOWN);
	ch_left = getCharFromBoard(_x + GameConfig::LEFT, _y);
	ch_right = getCharFromBoard(_x + GameConfig::RIGHT, _y);
	ch_left_down = getCharFromBoard(_x + GameConfig::LEFT, _y + GameConfig::DOWN);
	ch_right_down = getCharFromBoard(_x + GameConfig::RIGHT, _y + GameConfig::DOWN);
	two_chars_below = getCharFromBoard(_x, _y + 2);

	res_is_on_ladder = isOnLadder();
	res_is_on_floor = isBlock(ch_below);
	res_is_wall_on_left = isBlock(ch_left);
	res_is_wall_on_right = isBlock(ch_right);
	res_is_left_down = isBlock(ch_left_down);
	res_is_right_down = isBlock(ch_right_down);
	res_is_two_chars_below_floor = isBlock(two_chars_below);
}

// Check the ghost's current state
void SpecialGhost::checkWhatState()
{
	if (isFalling())
		state = GhostState::Falling;
	else 
	{				
		decideIfNeedToClimb();				// THE order of function in lines 55 and 56 set if the ghost can start climbing on the same ladder just after it finished the climb
		amendNextMove();
		if (isClimbing())
			state = GhostState::Climbing; 
		else
			state = GhostState::Wander;
	}
}

// Update the ghost's state
void SpecialGhost::updateState()
{
	switch (state)
	{
	case GhostState::Wander:
		wander();
		break;
	case GhostState::Climbing:
		climb();
		break;
	case GhostState::Falling:
		fall();
		break;
	}
}

// Neutralize illegal movements (jumping under the ceiling, going through a wall, etc.)
void SpecialGhost::amendNextMove()
{
	if (res_is_on_floor && two_chars_below != GameConfig::LADDER && point.getDir().y == GameConfig::DOWN)
		point.setDirY(GameConfig::STAY);
}

// Check if Mario is climbing
bool SpecialGhost::isClimbing()
{

	if (res_is_on_ladder && point.getDir().y == GameConfig::UP && ch_covered != GameConfig::SPACE)
		return true; // Climbing up

	if (res_is_on_floor && two_chars_below == GameConfig::LADDER && point.getDir().y == GameConfig::DOWN/* && point.getPreviousDir().y != GameConfig::DOWN*/)
		return true; // Climbing down from above a ladder

	if (res_is_on_ladder && point.getDir().y == GameConfig::DOWN)
		return true; // Climbing down while on a ladder

	return false;
}

// Handle Mario's climbing movement
void SpecialGhost::climb()
{
	point.setDirX(GameConfig::STAY); // Hold ladder when jumping or falling
}

// Change Y direction in prob of 50% if Ghost is above ladder or at the bottom of the ladder
void SpecialGhost::decideIfNeedToClimb()
{
	int mario_axis_y = pBoard->getMarioPosition().y;
	int special_ghost_axis_y = point.getPosition().y;

	if (point.getDir().y == GameConfig::STAY) {
		if (ch_covered == GameConfig::LADDER && (mario_axis_y < special_ghost_axis_y))	// Ghost is at the bottom of the ladder
		{
			point.setDirY(GameConfig::UP); // Ghost climbs up
		}
		else if (two_chars_below == GameConfig::LADDER && ch_covered != GameConfig::FLOOR && (mario_axis_y > special_ghost_axis_y))
		{
			point.setDirY(GameConfig::DOWN); // Ghost climbs down
		}
	}

	//if (point.getDir().y == GameConfig::STAY) {
	//	if (ch_covered == GameConfig::LADDER)	// Ghost is at the bottom of the ladder
	//	{
	//		point.setDirY((rand() % 2) * -1); // Ghost climbs up
	//	}
	//	else if (two_chars_below == GameConfig::LADDER && ch_covered != GameConfig::FLOOR)
	//	{
	//		point.setDirY(rand() % 2); // Ghost climbs down
	//	}
	//}
}

bool SpecialGhost::isOnLadder() const
{
	return (ch_covered == GameConfig::LADDER || ch_below == GameConfig::LADDER);
}

//// Manage the ghost's direction while wandering on the floor
//void SpecialGhost::manageWanderDirection()
//{
//	int dirX = point.getDir().x;
//
//	if (dirX == GameConfig::STAY) {  // If just finished falling, set initial direction
//		dirX = GameConfig::LEFT;
//		point.setDirX(dirX);
//	}
//
//	if ((rand() % 100) < (CHANGE_DIR_PROB * 100)) {  // Randomly change direction
//		point.setDirX(dirX * -1);
//		dirX *= -1;
//	}
//
//	if ((dirX == GameConfig::LEFT && ch_left_down == GameConfig::SPACE) || (dirX == GameConfig::RIGHT && ch_right_down == GameConfig::SPACE))
//		point.setDirX(dirX * -1);
//}

//// Stop the ghost's movement if it encounters a wall
//void SpecialGhost::blockedByWall()
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
//void SpecialGhost::updateNextMove()
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
//	point.setPosition(newX, newY);
//}
