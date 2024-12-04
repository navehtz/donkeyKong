#include "mario.h"
#include "point.h"

void Mario::keyPressed(char key) {
	key = (char)std::tolower(key);
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
	static bool is_climbing = false;

	ch_covered = getCharFromBoard(_x, _y);
	ch_below = getCharFromBoard(_x, _y + DOWN);
	two_chars_below = getCharFromBoard(_x, _y + 2);
	ch_above = getCharFromBoard(_x, _y + UP);
	ch_left = getCharFromBoard(_x + LEFT, _y);
	ch_right = getCharFromBoard(_x + RIGHT, _y);

	bool res_is_on_ladder = isOnLadder();
	bool res_is_on_floor = isBlock(ch_below);
	bool res_is_below_roof = isBlock(ch_above);
	bool res_is_wall_on_left = isBlock(ch_left);
	bool res_is_wall_on_right = isBlock(ch_right);
	bool res_is_two_chars_below_floor = isBlock(two_chars_below);

	amend_next_move(res_is_below_roof, res_is_on_ladder, res_is_wall_on_left, res_is_wall_on_right);


	if (res_is_on_floor && res_is_on_ladder)  //use stract?
	{
		if (dir.y == UP && ch_covered != 'H')	//The user try to go up and mario is on top of the ladder
		{
			if (is_climbing == true)			//when mario reached the top of the ladder while climbing
			{
				dir.y = STAY;
				is_climbing = false;
			}
			else								//when mario try to jump on the floor (not while climbing)
			{
				jump();
				jump_height += 1;
			}
		}
		else if (dir.y == DOWN && ch_covered == 'H')	//The user try to go down and mario is on the floor
			dir.y = STAY;


		else if (dir.y == DOWN && ch_covered != ' ')	//The user try to go down and mario is on the floor
		{
			dir.y = DOWN;
			is_climbing = false;
		}			
	}
	else if (res_is_on_floor)
	{
		is_climbing = false;		//when only on the floor, mario isn't climbing
		if (dir.y == DOWN)
			dir.y = STAY;
		else if (dir.y == UP)
		{
			jump();
			jump_height += 1;
		}

		if (jump_height <= -5) //insert into help_function - and to use in the condition above
		{
			jump_height = 0;
			life();
			//life go down, and the game start from beginning maybe
		}
		else if (jump_height < 0 && dir.y != DOWN)
			jump_height = 0;
	}
	else if (res_is_on_ladder)
	{
		is_climbing = true;						//when only on a ladder, mario is climbing

		if (ch_covered == ' ' && dir.y == UP)	//stop climbing on half ladder (without jumping)
		{
			dir.y = STAY;
		}

		else if (ch_covered == 'H')
		{
			dir.x = STAY;
			if (isJumping()) 
				jump_height = 0; 
			else 
				jump_height -= 1;
		}
	}
	else if(!isJumping())  //falling
	{
		if (jump_height > 0)
			fall(previous_dir.x);
		else
		{
			fall(STAY);
		}
		jump_height -= 1;

	}
	else if (ch_covered != 'H')  //jumping
	{
		jump();
		jump_height += 1;
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
	else {	p.setPreviousChar(getCharFromBoard(p.getX(), p.getY())); }
	//else {	previous_char = getCharPosition(_x, _y);	}

	previous_dir.x = dir.x;
}

bool Mario::isBlock(char _ch)
{
	if (_ch == '=' || _ch == '>' || _ch == '<')
		return true;
	else
		return false;

}

bool Mario::isOnLadder() const
{
	if (ch_covered == 'H' || ch_below == 'H' || two_chars_below == 'H')
		return true;
	else
		return false;
}

bool Mario::isJumping() const
{
	if (jump_height < 2 && dir.y == UP)
		return true;
	else
		return false;
}

void Mario::jump()
{
	dir.x = previous_dir.x;
	dir.y = UP;
}

void Mario::fall(int _dir_x)
{
	//dir.x = previous_dir.x;
	dir.x = _dir_x;
	dir.y = DOWN;
}

void Mario::life()
{
	lives -= 1;
	char ch_lives = (char)lives + '0';

	gotoxy(life_pos_x, life_pos_y);
	cout << ch_lives;
	pBoard->updateBoard(life_pos_x, life_pos_y, ch_lives);
}

void Mario::amend_next_move(bool below_roof, bool on_ladder, bool wall_on_left, bool wall_on_right)
{
	if (below_roof && !on_ladder) {
		if (dir.y == UP) { dir.y = DOWN; }
	}

	if (wall_on_left) {
		if (dir.x == LEFT) { dir.x = STAY; }
	}

	if (wall_on_right) {
		if (dir.x == RIGHT) { dir.x = STAY; }
	}
}
