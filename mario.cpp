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

	res_is_on_ladder = isOnLadder();
	res_is_on_floor = isBlock(ch_below);
	res_is_below_roof = isBlock(ch_above);
	res_is_wall_on_left = isBlock(ch_left);
	res_is_wall_on_right = isBlock(ch_right);
	res_is_two_chars_below_floor = isBlock(two_chars_below);

	//fixing the input from the user by the roles of the game
	amend_next_move(res_is_below_roof, res_is_on_ladder, res_is_wall_on_left, res_is_wall_on_right, res_is_on_floor);


	check_what_state();			//check what is mario state (climbing/ jumping/ falling/ walking or staying)
	update_state();				//update the moves that mario should commit by the state


	//update prameters
	update_next_move();			
	update_previous_char();
	update_previous_dir();
}

void Mario::check_what_state()
{
	if (isClimbing())
		state = MarioState::Climbing;
	else if (isJumping())
		state = MarioState::Jumping;
	else if (isFalling())
		state = MarioState::Falling;
	else
		state = MarioState::Walking_or_Staying;
}

void Mario::update_state()
{
	switch (state)
	{
	case MarioState::Climbing:
		climb();
		break;
	case MarioState::Jumping:
		jump();
		break;
	case MarioState::Falling:
		fall();
		break;
	case MarioState::Walking_or_Staying:
		walk_or_stay();
		break;
	}
}


bool Mario::isClimbing()
{
	//check if climbing up
	if (res_is_on_ladder && dir.y == UP && ch_covered != ' ')			//mario covers the latter 'H' 
		return true;

	//check if climbing down
	else if (res_is_on_floor && two_chars_below == 'H' && dir.y == DOWN && previous_dir.y != DOWN)		//mario stands on the floor above a ladder
		return true;
	else if (res_is_on_ladder && dir.y == DOWN)		//on the ladder and wants to go down
		return true;
	else
		return false;
}

void Mario::climb()
{
	if (!res_is_on_floor && (previous_dir.x == LEFT || previous_dir.x == RIGHT))	
	{
		dir.x = STAY;
		if (dir.y == UP) { dir.y = UP; }			//when mario JUMPS UP and land on a ladder
		else if (dir.y == DOWN)	{ dir.y = STAY;	}	//when mario FALLS DOWN and land on a ladder
	}
}


bool Mario::isJumping() 
{
	static int count_jump = 0;

	if (res_is_on_floor && dir.y == UP) {		//on floor and press 'w'
		if (two_chars_below == 'H' && previous_dir.y == UP)				
		{
			dir.y = 0;
			return false;
		}
		else
		{
			count_jump += 1;
			return true;
		}
	}
	else if (ch_below != 'H' && dir.y == UP && count_jump == 1) {
		count_jump += 1;
		return true;
	}
	else {
		count_jump = 0;
		return false;
	}
}

void Mario::jump()
{
	dir.x = previous_dir.x;
	dir.y = UP;
}

bool Mario::isFalling()
{
	if (ch_below == ' ')
	{
		fall_count -= 1;	//לבדוק כשאני מגיע לרצפה אם המונה הגיע ל5, וגם לאפס את המשתנה כשאני מגיע לרצפה ובשאר הפונקציות
		return true;
	}
	else
		return false;
}

void Mario::fall()
{
	if (previous_dir.y == UP || previous_dir.y == DOWN)		//if mario finish a jump, we want to save the previous x vector
		dir.x = previous_dir.x;
	else
		dir.x = STAY;			//if mario fall of a cliff - x vector should be 0

	dir.y = DOWN;
	fall_count += 1;
}


void Mario::walk_or_stay()
{
	fall_count = 0;
	dir.y = STAY;
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
	if (ch_covered == 'H' || ch_below == 'H')	//returns true only if mario is on the letter 'H' or above it
		return true;
	else
		return false;
}

void Mario::amend_next_move(bool below_roof, bool on_ladder, bool wall_on_left, bool wall_on_right, bool above_floor)
{
	if (below_roof && !on_ladder) {					//under roof - mario can't jump
		if (dir.y == UP) { dir.y = STAY; } //change to downnnn 5/12 14:20
	}

	if (wall_on_left) {								//linked to a wall - mario can't pass
		if (dir.x == LEFT) { dir.x = STAY; }
	}

	if (wall_on_right) {
		if (dir.x == RIGHT) { dir.x = STAY; }		//linked to a wall - mario can't pass
	}

	if (above_floor && two_chars_below != 'H') {	//above floor - mario can't go down
		if (dir.y == DOWN) { dir.y = STAY; }
	}
}

void Mario::update_next_move()
{
	int newX = p.getX() + dir.x;
	int newY = p.getY() + dir.y;

	if (newX < 0 || newX > 79)
		newX = p.getX();
	if (newY < 0 || newY > 24)
		newY = p.getY();

	p.setX(newX);
	p.setY(newY);
}


void Mario::life()
{
	lives -= 1;
	char ch_lives = (char)lives + '0';

	gotoxy(life_pos_x, life_pos_y);
	cout << ch_lives;
	pBoard->updateBoard(life_pos_x, life_pos_y, ch_lives);
}