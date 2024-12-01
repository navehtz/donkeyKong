#include "mario.h"
#include "point.h"

void Mario::keyPressed(char key) {
	key = std::tolower(key);
	for (size_t i = 0; i < numKeys; i++) {
		if (key == keys[i]) {
			dir = directions[i];
			return;
		}
	}
}

void Mario::move()
{
	int _x = p.getX(), _y = p.getY();
	static bool first_move = true;
	char current_char = getCharPosition(_x, _y);
	char two_chars_below = getCharPosition(_x, _y + 2);
	
	bool res_is_on_floor, res_is_on_ladder;
	res_is_on_floor = isOnFloor();
	res_is_on_ladder = isOnLadder();

	//static int count_falling = 0;
	bool in_jump = false;


	if (isJumping() && !res_is_on_ladder && current_char != 'H')
	{
		/*if (res_is_on_floor)
			in_jump = true;
		else*/
		jump();
	}
	else if (res_is_on_floor && res_is_on_ladder)
	{
		previous_dir = dir;
		if (dir.y == UP && current_char != 'H')	//The user try to go up and mario is on top of the ladder
			dir.y = STAY;
		else if (dir.y == DOWN && current_char == 'H')	//The user try to go up and mario is on top of the ladder
			dir.y = STAY;
	}
	else if (res_is_on_floor)
	{
		if (dir.y == DOWN)
			dir.y = STAY;
	}
	else if (res_is_on_ladder)
	{
		if (current_char == ' ' && dir.y == UP)
		{
			dir.y = STAY;
		}
	}
	else
	{
		dir.x = STAY;
		dir.y = DOWN;
	}


	int newX = p.getX() + dir.x;
	int newY = p.getY() + dir.y;

	if (newX < 0 || newX > 79)
		newX = _x;
	if (newY < 0 || newY > 24)
		newY = _y;

	p.setX(newX);
	p.setY(newY);

	if (first_move)	{ first_move = false; }
	else {	p.setPreviousChar(getCharPosition(p.getX(), p.getY())); }
	//else {	previous_char = getCharPosition(_x, _y);	}

}

bool Mario::isOnFloor()
{
	int _x = p.getX(), _y = p.getY();
	char ch_below = getCharPosition(_x, _y + 1);
	if (ch_below == '=' || ch_below == '>' || ch_below == '<')
		return true;
	else
		return false;

}


bool Mario::isOnLadder()
{
	int _x = p.getX(), _y = p.getY();
	char ch_covered = getCharPosition(_x, _y);  
	char ch_below = getCharPosition(_x, _y + 1);
	char two_chars_below = getCharPosition(_x, _y + 2);

	if (ch_covered == 'H' || ch_below == 'H' || two_chars_below == 'H')
		return true;
	else
		return false;
}

bool Mario::isJumping()
{
	return (dir.x == STAY && dir.y == UP);
}

void Mario::jump()	//relevent only for the first half of the jump
{
	static int pace = 0;
	
	switch (pace)
	{
	case(0):
		pace += 1;
		dir.y = UP;
		dir.x = previous_dir.x;
		break;
	case(1):
		pace += 1;
		dir.y = UP;
		dir.x = previous_dir.x;
		break;
	case(2):
		dir.y = DOWN;
		dir.x = previous_dir.x;
		pace = 0;
		break;
	}
}