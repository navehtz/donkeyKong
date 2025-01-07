#include "mario.h"
#include "point.h"

// Initialize mario
void Mario::setStartingMario()
{
	won_level = false;

	p.setPosition(pBoard->getStartPosMario());				// Set stating position for x-axis

	p.setDir({ STAY, STAY });								// Set stating direction for Mario

	p.setPreviousChar(' ');									// Reset the previous char prameter

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));// Flush the input from the user
}

// Processes a key press to determine Mario's movement direction.
void Mario::keyPressed(char key) {
	key = (char)std::tolower(key);
	for (int i = 0; i < numKeys; i++) {
		if (key == keys[i]) {
			p.setDir(p.getDirFromDirectionsArray(i));		// Update Mario's direction using the index of the matched key in the direction array.
			return;
		}
	}
}

// Handle the barrel's movement
void Mario::move()
{
	static bool is_climbing = false;

	updateCharParameters();		// Update all the char data members around mario
	amendNextMove();			// Neutralizing illegal movements (jumping under the ceiling, going through a wall, etc.)

	checkWhatState();			// Check what is mario state (climbing/ jumping/ falling/ walking or staying)
	updateState();				// Update the moves that mario should commit by the state

	if (just_died) { just_died = false; return; }

	//update prameters
	updateNextMove();			// activate next move
	updatePreviousChar();
	updatePreviousDir();
}

// Update all the char data members around mario
void Mario::updateCharParameters()
{
	int _x = p.getPosition().x, _y = p.getPosition().y;

	ch_covered = getCharFromBoard(_x, _y);
	ch_below = getCharFromBoard(_x, _y + DOWN);
	two_chars_below = getCharFromBoard(_x, _y + 2);
	ch_above = getCharFromBoard(_x, _y + UP);
	ch_left = getCharFromBoard(_x + LEFT, _y);
	ch_right = getCharFromBoard(_x + RIGHT, _y);
	ch_left_down = getCharFromBoard(_x + LEFT, _y + DOWN);
	ch_right_down = getCharFromBoard(_x + RIGHT, _y + DOWN);

	res_is_on_ladder = isOnLadder();
	res_is_on_floor = isBlock(ch_below);
	res_is_below_roof = isBlock(ch_above);
	res_is_wall_on_left = isBlock(ch_left);
	res_is_wall_on_right = isBlock(ch_right);
	res_is_two_chars_below_floor = isBlock(two_chars_below);
	res_is_left_down = isBlock(ch_left_down);
	res_is_right_down = isBlock(ch_right_down);
}

// Check in which state the Marrio is
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

// Update the Marrio's state
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

// Check if the Mario is climbing
bool Mario::isClimbing()
{
	// Check if climbing up
	if (res_is_on_ladder && p.getDir().y == UP && ch_covered != SPACE)												// Mario covers the latter 'H' 
		return true;

	// Check if climbing down
	else if (res_is_on_floor && two_chars_below == LADDER && p.getDir().y == DOWN && p.getPreviousDir().y != DOWN)		// Mario stands on the floor above a ladder
		return true;
	else if (res_is_on_ladder && p.getDir().y == DOWN)																// On the ladder and wants to go down
		return true;
	else
		return false;
}

// Handle the Mario's climb
void Mario::climb()
{
	if (!res_is_on_floor && (p.getPreviousDir().x == LEFT || p.getPreviousDir().x == RIGHT))		// When Mario jumps or fall and lands on a ledder
	{
		p.setDirX(STAY);																			// We want that Mario will HOLD the ledder
		if (p.getDir().y == UP) { return; }															// When mario JUMPS UP and land on a ladder - we want him to continue his move up                
		else if (p.getDir().y == DOWN)	{ p.setDirY(STAY);	}	                                    // When mario FALLS DOWN and land on a ladder - we want him to hold the ledder
	}
}

// Check if the Mario is jump
bool Mario::isJumping() 
{
	static int count_jump = 0;

	if (res_is_on_floor && p.getDir().y == UP) {									// When Mario is on the floor and and the user pressed 'w'
		if (two_chars_below == LADDER && p.getPreviousDir().y == UP)					// When Mario finished to climb the ledder and stands on the floorr
		{
			p.setDirY(STAY);
			return false;
		}
		else																		// When Mario stands on the floor and try to jump
		{
			count_jump += 1;
			fall_count = 0;
			return true;
		}
	}
	else if (ch_below != LADDER && p.getDir().y == UP && count_jump == 1) {			// When Mario did 1/2 parts of the jump 
		count_jump += 1;
		return true;
	}
	else {
		count_jump = 0;																// Reset count_jump counter
		return false;
	}
}

// Handle the Mario's jumping
void Mario::jump()
{
	p.setDirX(p.getPreviousDir().x);					// Keep Mario's previous direction by x-axis while jumping
	p.setDirY(UP);
}


// Check if the Mario is falling
bool Mario::isFalling() const
{
	return ch_below == SPACE ? true : false;
}

// Handle the Mario's falling
void Mario::fall()
{
	if (p.getPreviousDir().y == UP || p.getPreviousDir().y == DOWN)		// If mario finish a jump, we want to save the previous x vector
		if(!res_is_left_down && !res_is_right_down)
			p.setDirX(p.getPreviousDir().x);
	else
		p.setDirX(STAY);

	p.setDirY(DOWN);
	fall_count += 1;

}

// Handle the Mario's walking and standing
void Mario::walkOrStay()					
{
	if (fall_count >= FALL_FROM_TOO_HIGH)								// If fall from high places, mario lose life
		life();

	if (ch_left == GORRILA || ch_right == GORRILA)
		life();

	fall_count = 0;														// Reset count_jump counter
	p.setDirY(STAY);
}

// The function returns true if the parameter is a floor/ceiling/wall and false otherwise
bool Mario::isBlock(char _ch)
{
	if (_ch == FLOOR || _ch == FLOOR_RIGHT || _ch == FLOOR_LEFT || _ch == WALL)
		return true;
	else
		return false;
}

// Check if Mario is on a ladder
bool Mario::isOnLadder() const
{
	if (ch_covered == LADDER || ch_below == LADDER)	// Returns true only if mario is on the letter 'H' or above it
		return true;
	else
		return false;
}

// Neutralizing illegal movements (jumping under the ceiling, going through a wall, etc.)
void Mario::amendNextMove()
{
	if (res_is_below_roof && !res_is_on_ladder) {					// Under roof - mario can't jump
		if (p.getDir().y == UP) { p.setDirY(STAY); }			
	}

	if (res_is_wall_on_left) {										// Linked to a wall - mario can't pass
		if (p.getDir().x == LEFT) { p.setDirX(STAY); }
	}

	if (res_is_wall_on_right) {
		if (p.getDir().x == RIGHT) { p.setDirX(STAY); }				// Linked to a wall - mario can't pass
	}

	if (res_is_on_floor && two_chars_below != LADDER) {				// Above floor - mario can't go down
		if (p.getDir().y == DOWN) { p.setDirY(STAY); }
	}
	if (res_is_left_down || res_is_right_down)
		if (p.getDir().y == DOWN) { p.setDirX(STAY); }
}

// Updating the movement of the barrel for the next loop according to the position and the direction
void Mario::updateNextMove()
{
	int newX = p.getPosition().x + p.getDir().x;
	int newY = p.getPosition().y + p.getDir().y;

	if (newX < 0 || newX >= pBoard->get_board_width())						// Update the next move by the board size	
		newX = p.getPosition().x;
	if (newY < 0 || newY >= pBoard->get_board_height())						// Update the next move by the board size
		newY = p.getPosition().y;

	if (pBoard->getCharFromBoard(newX, newY) == PRINCESS || ch_below == PRINCESS)		// Check if mario reached pauline	
	{
		won_level = true;
		return;
	}

	p.setPosition(newX, newY);
}

// Handle Mario's lives (when hit or fall)
void Mario::life()
{
	lives -= 1;

	//char ch_lives = (char)lives + '0';
	//printLives();																		// Print Mario's lives on screen
	//pBoard->updateBoard(pBoard->getLifePosX(), pBoard->getLifePosY(), ch_lives);		// Update mario's life on current board


	pBoard->setLifeLegend(lives);
	pBoard->printLifeLegend();

	if (lives > DEAD_MARIO) {															// Check if lives > 0
		startOver();																	// Function that reset the game after mario died but still has more than 0 lives
	}
	else if (lives == DEAD_MARIO) {														
		pBoard->printScreen(pBoard->getLosingBoard());									// Printing LOSING screen
		Sleep(SCREEN_EXIT);
	}
}


// Reset the game after mario died but still has more than 0 lives
void Mario::startOver()
{		
	just_died = true;
	flashingMario();

	pBoard->reset();
	setStartingMario();
	pBarrels->setStartingBarrels();							//reset barrels
	pBoard->printScreen(pBoard->getCurrentBoard());			//printing new board screen
	pBoard->printLegend();
}

// Printing Mario after he died (by flashing the char)
void Mario::flashingMario()
{
	pBarrels->draw();

	for (int i = 0; i < 3; i++) {
		draw();
		Sleep(SCREEN_FLASH_MARIO);
		erase();
		Sleep(SCREEN_FLASH_MARIO);
	}

}
