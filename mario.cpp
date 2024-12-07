#include "mario.h"
#include "point.h"

void Mario::keyPressed(char key) {
	key = (char)std::tolower(key);
	for (size_t i = 0; i < numKeys; i++) {
		if (key == keys[i]) {
			p.setDir(p.getDirFromDirectionsArray(i));
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
	amend_next_move();


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
	if (res_is_on_ladder && p.getDir().y == UP && ch_covered != ' ')			//mario covers the latter 'H' 
		return true;

	//check if climbing down
	else if (res_is_on_floor && two_chars_below == 'H' && p.getDir().y == DOWN && p.getPreviousDir().y != DOWN)		//mario stands on the floor above a ladder
		return true;
	else if (res_is_on_ladder && p.getDir().y == DOWN)		//on the ladder and wants to go down
		return true;
	else
		return false;
}

void Mario::climb()
{
	if (!res_is_on_floor && (p.getPreviousDir().x == LEFT || p.getPreviousDir().x == RIGHT))
	{
		p.setDirX(STAY);
		if (p.getDir().y == UP) { return; }			//when mario JUMPS UP and land on a ladder                  
		else if (p.getDir().y == DOWN)	{ p.setDirY(STAY);	}	//when mario FALLS DOWN and land on a ladder
	}
}


bool Mario::isJumping() 
{
	static int count_jump = 0;

	if (res_is_on_floor && p.getDir().y == UP) {		//on floor and press 'w'
		if (two_chars_below == 'H' && p.getPreviousDir().y == UP)
		{
			p.setDirY(STAY);
			return false;
		}
		else
		{
			count_jump += 1;
			return true;
		}
	}
	else if (ch_below != 'H' && p.getDir().y == UP && count_jump == 1) {
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
	p.setDirX(p.getPreviousDir().x);
	p.setDirY(UP);
}

bool Mario::isFalling()
{
	if (ch_below == ' ')
	{
		return true;
	}
	else
		return false;
}

void Mario::fall()
{
	if (p.getPreviousDir().y == UP || p.getPreviousDir().y == DOWN)		//if mario finish a jump, we want to save the previous x vector
		p.setDirX(p.getPreviousDir().x);
	else
		p.setDirX(STAY);

	p.setDirY(DOWN);
	fall_count += 1;
}


void Mario::walk_or_stay()					//if fall from high place, mario lose life
{
	if (fall_count >= FALL_FROM_TO_HIGH) 	{ life(); }		

	fall_count = 0;
	p.setDirY(STAY);
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


void Mario::amend_next_move()
{
	if (res_is_below_roof && !res_is_on_ladder) {					//under roof - mario can't jump
		if (p.getDir().y == UP) { p.setDirY(STAY); } //change to downnnn 5/12 14:20
	}

	if (res_is_wall_on_left) {								//linked to a wall - mario can't pass
		if (p.getDir().x == LEFT) { p.setDirX(STAY); }
	}

	if (res_is_wall_on_right) {
		if (p.getDir().x == RIGHT) { p.setDirX(STAY); }		//linked to a wall - mario can't pass
	}

	if (res_is_on_floor && two_chars_below != 'H') {	//above floor - mario can't go down
		if (p.getDir().y == DOWN) { p.setDirY(STAY); }
	}
}

void Mario::update_next_move()
{
	int newX = p.getX() + p.getDir().x;
	int newY = p.getY() + p.getDir().y;

	if (newX < 0 || newX >= pBoard->get_board_width())	//80	
		newX = p.getX();
	if (newY < 0 || newY >= pBoard->get_board_height())	//25
		newY = p.getY();

	p.setX(newX);
	p.setY(newY);
}


void Mario::life()
{
	lives -= 1;
	char ch_lives = (char)lives + '0';

	gotoxy(pBoard->getLifePosX(), pBoard->getLifePosY());
	cout << ch_lives;											//printing 

	pBoard->updateBoard(pBoard->getLifePosX(), pBoard->getLifePosY(), ch_lives);		//update mario's life on current board
	Sleep(500);

	if(lives > DEAD_MARIO) {									//check if lives > 0
		pBoard->printScreen(pBoard->getLostLifeBoard());		//printing lost life screen
		Sleep(2000);
		pBoard->reset();
		setStartingMario();
		pBoard->printScreen(pBoard->getCurrentBoard());			//printing new board screen
		cout << pBoard->getCharFromBoard(pBoard->getLifePosX(), pBoard->getLifePosY());
	}
	else {
		pBoard->printScreen(pBoard->getLosingBoard());			//printing LOSING screen
		Sleep(2000);
	}
}

void Mario::setStartingMario()
{
	p.setX(STARTING_POS_X);
	p.setY(STARTING_POS_Y);

	p.setDir({ STAY, STAY });
}
