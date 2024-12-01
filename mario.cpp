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
	static bool first_move = true;

	char current_char = getCharPosition(p.x, p.y);
	char two_chars_below = getCharPosition(p.x, p.y + 2);
	
	bool res_is_on_floor, res_is_on_ladder;
	res_is_on_floor = isOnFloor();
	res_is_on_ladder = isOnLadder();

	if (previous_char == '=' || previous_char == '>' || previous_char == '<')
		dir = { STAY, STAY };

	if (res_is_on_floor && res_is_on_ladder)
	{
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


	int newX = p.x + dir.x;
	int newY = p.y + dir.y;

	if (newX < 0 || newX > 79)
		newX = p.x;
	if (newY < 0 || newY > 24)
		newY = p.y;

	p.x = newX;
	p.y = newY;

	if (first_move)	{ first_move = false; }
	//else {	setPreviousChar(getCharPosition(p.x, p.y));	}
	else {	previous_char = getCharPosition(p.x, p.y);	}
}

bool Mario::isOnFloor()
{
	char ch_below = getCharPosition(p.x, p.y + 1);
	if (ch_below == '=' || ch_below == '>' || ch_below == '<')
		return true;
	else
		return false;
}


bool Mario::isOnLadder()
{
	char ch_covered = getCharPosition(p.x, p.y);  //MAYBE CHANGE TO CH_PREVIOUS!!!!!!!!!
	char ch_below = getCharPosition(p.x, p.y + 1);
	char two_chars_below = getCharPosition(p.x, p.y + 2);

	if (ch_covered == 'H' || ch_below == 'H' || two_chars_below == 'H')
		return true;
	else
		return false;
}
