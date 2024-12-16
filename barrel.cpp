#include "barrel.h"

// Initialize barrel
void Barrel::setStartingBarrel()
{
	point.setY(STARTING_POS_Y);									// Same y-axis starting position for both cases

	if (myRandom() == 0)										// Start from the left side
	{
		point.setX(STARTING_POS_LEFT_X);
		point.setDirBeforeFalling({ LEFT, STAY });
	}
	else														// Start from the right side
	{
		point.setX(STARTING_POS_RIGHT_X);
		point.setDirBeforeFalling({ RIGHT, STAY });
	}
	fall_count = 0;
	is_exploded = false;
}

// Function to raffle a number ( 1 or 0 )
int Barrel::myRandom()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 1);
	return dist(gen);
}

// Handle the barrel's movement
void Barrel::move()
{
	int _x = point.getX(), _y = point.getY();

	// Chars around the barrel
	ch_covered = getCharFromBoard(_x, _y);
	ch_below = getCharFromBoard(_x, _y + DOWN);
	two_chars_below = getCharFromBoard(_x, _y + 2);
	ch_left = getCharFromBoard(_x + LEFT, _y);
	ch_right = getCharFromBoard(_x + RIGHT, _y);

	res_is_on_floor = isBlock(ch_below);
	res_is_wall_on_left = isBlock(ch_left);
	res_is_wall_on_right = isBlock(ch_right);


	checkWhatState();										// Check what is the barrel's state (falling/ walking or staying)
	updateState();											// Update the moves that the barrel should do by the state

	//update prameters
	updateNextMove();
	updatePreviousChar();
	updatePreviousDir();
}

// Check in which state the barrel is
void Barrel::checkWhatState()
{
	if (isFalling())
		state = BarrelState::Falling;
	else
		state = BarrelState::Rolling;
}

// Update the barrel's state
void Barrel::updateState()
{
	switch (state)
	{
	case BarrelState::Falling:
		fall();
		break;
	case BarrelState::Rolling:
		roll();
		break;
	}
}

// Handle the barrel's rolling
void Barrel::roll()
{
	manageDirection();
	
	if (explosionCases())
		return;

	blockedByWall();

	fall_count = 0;
	point.setDirY(STAY);
}

// Manage the direction of the barrel while on the floor
void Barrel::manageDirection()
{
	switch (ch_below)
	{
	case('<'):
		point.setDir({ LEFT, STAY });					// Update direction to left
		point.setDirBeforeFalling(point.getDir());		// Update direction before (maybe) falling
		break;
	case('>'):
		point.setDir({ RIGHT, STAY });					// Update direction to right
		point.setDirBeforeFalling(point.getDir());		// Update direction before (maybe) falling
		break;
	case('='):
		point.setDir({ point.getDirBeforeFalling() });	// Keep moving the direction as before
	}
}

// Handle the cases which the barrel explodes in (falling 8 chars or at wall)
bool Barrel::explosionCases()
{
	if (fall_count >= FALL_FROM_TOO_HIGH) {
		explode();
		return true;
	}

	if (point.getX() < 1 || point.getX() >= pBoard->get_board_width() - 1) { // 1 less than the board width from both sides	
		explode();
		return true;
	}
	else
		return false;
}

// Handle the cases which the barrel explodes in (falling 8 chars or at wall)
void Barrel::blockedByWall()
{
	if (res_is_wall_on_left) {										//linked to a wall - barrel can't pass
		if (point.getDir().x == LEFT) { point.setDirX(STAY); }
	}

	if (res_is_wall_on_right) {
		if (point.getDir().x == RIGHT) { point.setDirX(STAY); }		//linked to a wall - barrel can't pass
	}
}

// Check if the barrel is falling 
bool Barrel::isFalling() const
{
	return ch_below == ' ' ? true : false;
}

// Handle the barrel's falling
void Barrel::fall()
{
	point.setDirX(STAY);
	point.setDirY(DOWN);
	fall_count += 1;
}

// Function to update the barrel's 'is_activated' and 'is_exploded' members
void Barrel::explode()
{
	is_activated = false;
	is_exploded = true;
}

// The function returns true if the parameter is a floor/ceiling/wall and false otherwise
bool Barrel::isBlock(char _ch) const
{
	if (_ch == '=' || _ch == '>' || _ch == '<' || _ch == 'O')
		return true;
	else
		return false;
}

// Updating the movement of the barrel for the next loop according to the position and the direction
void Barrel::updateNextMove()
{
	int newX = point.getX() + point.getDir().x;
	int newY = point.getY() + point.getDir().y;

	if (newX < 0 || newX >= pBoard->get_board_width())				// Update the next move by the board size	
		newX = point.getX();
	if (newY < 0 || newY >= pBoard->get_board_height())				// Update the next move by the board size	
		newY = point.getY();

	point.setX(newX);
	point.setY(newY);
}

/*void Barrel::drawExplosion()
{
	int x, y;

	for (int i = 0; i < 5; i++) //change magic number
	{
		for (int j = 0; j < 5; j++)
		{
			x = point.getX() -2 + j;
			y = point.getY() - 2 + i;

			gotoxy(point.getX() - 2 + j, point.getY() - 2 + i);

			if (x > 0 && x < pBoard->get_board_width())			//80	
				if (y > 0 && y < pBoard->get_board_height())	//25
					std::cout << 'X';
		}
	}
	//pBoard->printScreen(pBoard->getCurrentBoard());
}*/