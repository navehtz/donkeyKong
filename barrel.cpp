#include "barrel.h"

void Barrel::setStartingBarrel()
{
	point.setY(STARTING_POS_Y);

	if (myRandom() == 0)
	{
		point.setX(STARTING_POS_LEFT_X);
		point.setDirBeforeFalling({ LEFT, STAY });
	}
	else
	{
		point.setX(STARTING_POS_RIGHT_X);
		point.setDirBeforeFalling({ RIGHT, STAY });
	}
	fall_count = 0;
	//is_exploded = false;
}

int Barrel::myRandom()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(0, 1);
	int random = dist(gen);
	return random;
}

void Barrel::move()
{
	int _x = point.getX(), _y = point.getY();

	ch_covered = getCharFromBoard(_x, _y);
	ch_below = getCharFromBoard(_x, _y + DOWN);
	two_chars_below = getCharFromBoard(_x, _y + 2);
	ch_left = getCharFromBoard(_x + LEFT, _y);
	ch_right = getCharFromBoard(_x + RIGHT, _y);

	res_is_on_floor = isBlock(ch_below);
	res_is_below_roof = isBlock(ch_above);
	res_is_wall_on_left = isBlock(ch_left);
	res_is_wall_on_right = isBlock(ch_right);


	checkWhatState();			//check what is mario state (climbing/ jumping/ falling/ walking or staying)
	updateState();				//update the moves that mario should commit by the state

	//update prameters
	updateNextMove();
	updatePreviousChar();
	updatePreviousDir();
}


void Barrel::checkWhatState()
{
	if (isFalling())
		state = BarrelState::Falling;
	else
		state = BarrelState::Rolling;
}


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


void Barrel::roll()
{
	switch (ch_below)
	{
	case('<'):
		point.setDir({ LEFT, STAY });					//update direction
		point.setDirBeforeFalling(point.getDir());		//update direction before (maybe) falling
		break;
	case('>'):
		point.setDir({ RIGHT, STAY });					//update direction
		point.setDirBeforeFalling(point.getDir());		//update direction before (maybe) falling
		break;
	case('='):
		point.setDir({ point.getDirBeforeFalling() });
	}

	if (fall_count >= FALL_FROM_TOO_HIGH) {
		explode();
		return;
	}

	if (res_is_wall_on_left) {										//linked to a wall - barrel can't pass
		if (point.getDir().x == LEFT) { point.setDirX(STAY); }
	}

	if (res_is_wall_on_right) {
		if (point.getDir().x == RIGHT) { point.setDirX(STAY); }		//linked to a wall - barrel can't pass
	}

	fall_count = 0;
	point.setDirY(STAY);
}

bool Barrel::isFalling()
{
	return ch_below == ' ' ? true : false;
}

void Barrel::fall()
{
	point.setDirX(STAY);
	point.setDirY(DOWN);
	fall_count += 1;
}

void Barrel::explode()
{
	is_activated = false;
	is_exploded = true;
	//drawExplosion();     //TODO!!!

	setStartingBarrel();
}

bool Barrel::isBlock(char _ch)
{
	if (_ch == '=' || _ch == '>' || _ch == '<' || _ch == 'O')
		return true;
	else
		return false;
}

void Barrel::updateNextMove()
{
	int newX = point.getX() + point.getDir().x;
	int newY = point.getY() + point.getDir().y;

	if (newX < 0 || newX >= pBoard->get_board_width())	//80	
		newX = point.getX();
	if (newY < 0 || newY >= pBoard->get_board_height())	//25
		newY = point.getY();

	point.setX(newX);
	point.setY(newY);
}

void Barrel::drawExplosion()
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
}