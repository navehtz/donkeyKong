#include "mario.h"
#include "point.h"

void Mario::setStartingMario()
{
	won_level = false;

	p.setX(STARTING_POS_X);
	p.setY(STARTING_POS_Y);

	p.setDir({ STAY, STAY });

	p.setPreviousChar(' ');
}

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

	static bool first_move = true;	//deleteeeeeeeeeeeeeeeeeeeeee
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

	//fixing the input from the user by the rules of the game
	amendNextMove();

	//if (ch_left == '$' || ch_right == '$')
	//{
	//	won_level = true;
	//	return;
	//}

	checkWhatState();			//check what is mario state (climbing/ jumping/ falling/ walking or staying)
	updateState();				//update the moves that mario should commit by the state

	//updateIfHitByBarrel();

	//update prameters
	updateNextMove();			
	updatePreviousChar();
	updatePreviousDir();
}

void Mario::checkWhatState()
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

void Mario::updateState()
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
		walkOrStay();
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

bool Mario::isFalling() const
{
	return ch_below == ' ' ? true : false;
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


void Mario::walkOrStay()					//if fall from high place, mario lose life
{
	if (fall_count >= FALL_FROM_TOO_HIGH) {
		life();
	}		

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


void Mario::amendNextMove()
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

	if (ch_below == '$')
		won_level = true;
}

void Mario::updateNextMove()
{
	int newX = p.getX() + p.getDir().x;
	int newY = p.getY() + p.getDir().y;

	if (newX < 0 || newX >= pBoard->get_board_width())	//80	
		newX = p.getX();
	if (newY < 0 || newY >= pBoard->get_board_height())	//25
		newY = p.getY();

	if (pBoard->getCharFromBoard(newX, newY) == '$')
	{
		won_level = true;
		return;
	}

	p.setX(newX);
	p.setY(newY);
}


void Mario::life()
{
	lives -= 1;
	char ch_lives = (char)lives + '0';

	printLives();
	pBoard->updateBoard(pBoard->getLifePosX(), pBoard->getLifePosY(), ch_lives);		//update mario's life on current board

	if (lives > DEAD_MARIO) {									//check if lives > 0
		startOver();
	}
	else if (lives == DEAD_MARIO) {
		pBoard->printScreen(pBoard->getLosingBoard());			//printing LOSING screen
		Sleep(2000);
	}
}


void Mario::printLives()
{
	char ch_lives = (char)lives + '0';

	gotoxy(pBoard->getLifePosX(), pBoard->getLifePosY());
	cout << ch_lives;
}


//when mario died but still has more than 0 lives - we want to rest the the board, mario and the barrels to the start position
void Mario::startOver()
{									
	flashingMario();

	pBoard->reset();
	setStartingMario();
	pBarrels->setStartingBarrels();							//reset barrels
	pBoard->printScreen(pBoard->getCurrentBoard());			//printing new board screen
	printLives();											//printing mario's lives
}

void Mario::flashingMario()
{
	pBarrels->draw();

	draw();
	Sleep(200);
	erase();
	Sleep(200);
	draw();
	Sleep(200);
	erase();
	Sleep(200);
	draw();
	Sleep(200);
}
