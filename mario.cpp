#include "mario.h"
#include "point.h"

// Initialize mario
void Mario::setStartingMario()
{
	won_level = false;
	got_hammer = false;
	fall_count = 0;
	point.setPosition(pBoard->getStartPosMario());				// Set stating position for x-axis

	point.setDir({ STAY, STAY });								// Set stating direction for Mario

	point.setPreviousChar(' ');									// Reset the previous char prameter

	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));// Flush the input from the user
}

// Processes a key press to determine Mario's movement direction.
void Mario::keyPressed(char key) {
	Direction new_dir;

	key = (char)std::tolower(key);
	for (int i = 0; i < numKeys; i++) {
		new_dir = point.getDirFromDirectionsArray(i);
		if (key == keys[i]) {
			point.setDir(new_dir);								// Update Mario's direction using the index of the matched key in the direction array.
			
			if (new_dir.x != STAY)
				point.setDirBeforeStay(new_dir);
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

	if (just_died) { return; }

	if (ch_covered == HAMMER) { 
		handleHammer();
	}

	//update prameters
	updateNextMove();			// activate next move
	updatePreviousChar();
	updatePreviousDir();
	if (got_hammer) { updateHammerPos(); }
}

// Update all the char data members around mario
void Mario::updateCharParameters()
{
	int _x = point.getPosition().x, _y = point.getPosition().y;

	ch_covered = getCharFromBoard(_x, _y);
	ch_below = getCharFromBoard(_x, _y + DOWN);
	two_chars_below = getCharFromBoard(_x, _y + 2);
	ch_above = getCharFromBoard(_x, _y + UP);
	ch_left = getCharFromBoard(_x + LEFT, _y);
	ch_right = getCharFromBoard(_x + RIGHT, _y);
	ch_left_down = getCharFromBoard(_x + LEFT, _y + DOWN);
	ch_right_down = getCharFromBoard(_x + RIGHT, _y + DOWN);
	ch_three_chars_below = getCharFromBoard(_x, _y + 3);
	ch_wall_on_two_left = getCharFromBoard(_x - 2, _y);
	ch_wall_on_two_right = getCharFromBoard(_x + 2, _y);

	res_is_on_ladder = isOnLadder();
	res_is_on_floor = isBlock(ch_below);
	res_is_below_roof = isBlock(ch_above);
	res_is_wall_on_left = isBlock(ch_left);
	res_is_wall_on_right = isBlock(ch_right);
	res_is_two_chars_below_floor = isBlock(two_chars_below);
	res_is_left_down = isBlock(ch_left_down);
	res_is_right_down = isBlock(ch_right_down);
	res_is_three_chars_below_floor = isBlock(ch_three_chars_below);
	res_ch_wall_on_two_left = isBlock(ch_wall_on_two_left);
	res_ch_wall_on_two_right = isBlock(ch_wall_on_two_right);
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
	if (res_is_on_ladder && point.getDir().y == UP && ch_covered != SPACE)												// Mario covers the latter 'H' 
		return true;

	// Check if climbing down
	else if (res_is_on_floor && two_chars_below == LADDER && point.getDir().y == DOWN && point.getPreviousDir().y != DOWN)		// Mario stands on the floor above a ladder
		return true;
	else if (res_is_on_ladder && point.getDir().y == DOWN)																// On the ladder and wants to go down
		return true;
	else
		return false;
}

// Handle the Mario's climb
void Mario::climb()
{
	int previous_dir_x = point.getPreviousDir().x;

	if (!res_is_on_floor && (previous_dir_x == LEFT || previous_dir_x == RIGHT))		// When Mario jumps or fall and lands on a ledder
	{
		point.setDirX(STAY);																			// We want that Mario will HOLD the ledder
		if (point.getDir().y == UP) { return; }															// When mario JUMPS UP and land on a ladder - we want him to continue his move up                
		else if (point.getDir().y == DOWN)	{ point.setDirY(STAY);	}	                                    // When mario FALLS DOWN and land on a ladder - we want him to hold the ledder
	}
}

// Check if the Mario is jump
bool Mario::isJumping() 
{
	static int count_jump = 0;

	if (res_is_on_floor && point.getDir().y == UP) {									// When Mario is on the floor and and the user pressed 'w'
		if (two_chars_below == LADDER && point.getPreviousDir().y == UP)					// When Mario finished to climb the ledder and stands on the floorr
		{
			point.setDirY(STAY);
			return false;
		}
		else																		// When Mario stands on the floor and try to jump
		{
			count_jump += 1;
			fall_count = 0;
			return true;
		}
	}
	else if (ch_below != LADDER && point.getDir().y == UP && count_jump == 1) {			// When Mario did 1/2 parts of the jump 
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
	point.setDirX(point.getPreviousDir().x);					// Keep Mario's previous direction by x-axis while jumping
	point.setDirY(UP);
}


// Check if the Mario is falling
bool Mario::isFalling() const
{
	return (ch_below == SPACE || ch_below == HAMMER || ch_below == PRINCESS) ? true : false;
}

// Handle the Mario's falling
void Mario::fall()
{
	int previous_dir_y = point.getPreviousDir().y;

	if (previous_dir_y == UP || previous_dir_y == DOWN)		// If mario finish a jump, we want to save the previous x vector
		if(!res_is_left_down && !res_is_right_down)
			point.setDirX(point.getPreviousDir().x);
	else
		point.setDirX(STAY);

	point.setDirY(DOWN);
	fall_count += 1;

}

// Handle the Mario's walking and standing
void Mario::walkOrStay()					
{
	if (!just_died)
	{
		if (fall_count >= FALL_FROM_TOO_HIGH)								// If fall from high places, mario lose life
			life();

		if (ch_left == GORRILA || ch_right == GORRILA)
			life();
	}

	fall_count = 0;														// Reset count_jump counter
	point.setDirY(STAY);
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
		if (point.getDir().y == UP) { point.setDirY(STAY); }			
	}

	if (res_is_wall_on_left) {										// Linked to a wall - mario can't pass
		if (point.getDir().x == LEFT) { point.setDirX(STAY); }
	}

	if (res_is_wall_on_right) {
		if (point.getDir().x == RIGHT) { point.setDirX(STAY); }				// Linked to a wall - mario can't pass
	}

	if (res_is_on_floor && two_chars_below != LADDER) {				// Above floor - mario can't go down
		if (point.getDir().y == DOWN) { point.setDirY(STAY); }
	}
	if (res_is_left_down || res_is_right_down)
		if (point.getDir().y == DOWN) { point.setDirX(STAY); }
}

// Updating the movement of the barrel for the next loop according to the position and the direction
void Mario::updateNextMove()
{
	int newX = point.getPosition().x + point.getDir().x;
	int newY = point.getPosition().y + point.getDir().y;

	if (newX < 0 || newX >= pBoard->get_board_width())						// Update the next move by the board size	
		newX = point.getPosition().x;
	if (newY < 0 || newY >= pBoard->get_board_height())						// Update the next move by the board size
		newY = point.getPosition().y;

	if (pBoard->getCharFromBoard(newX, newY) == PRINCESS || ch_below == PRINCESS)		// Check if mario reached pauline	
	{
		won_level = true;
		return;
	}

	point.setPosition(newX, newY);
}

void Mario::handleHammer()
{
	got_hammer = true;
	pBoard->setHammerLegend(HAMMER);
	pBoard->printHammerLegend();
	pBoard->updateBoard(getPosition(), SPACE);
	point.setPreviousChar(SPACE);
	erase();
	updateHammerPos();
}

void Mario::updateHammerPos()
{
	Position pos = point.getPosition();
	Direction dir = point.getDir();
	Direction dir_before = point.getDirBeforeStay();
	bool jumping_or_falling = false;

	switch (dir.y)
	{
	case(UP):
		hammer.pos.y = pos.y - HAMMER_DISTANCE;
		jumping_or_falling = true;
		break;
	case(DOWN):
		hammer.pos.y = pos.y + HAMMER_DISTANCE;
		jumping_or_falling = true;
		break;
	case(STAY):
		hammer.pos.y = pos.y;
		break;
	}

	switch (dir.x)
	{
	case(LEFT):
		hammer.pos.x = pos.x - HAMMER_DISTANCE;
		break;
	case(RIGHT):
		hammer.pos.x = pos.x + HAMMER_DISTANCE;
		break;
	case(STAY):
		if (jumping_or_falling)
		{
			hammer.pos.x = pos.x;
		}
		else
		{
			if (dir_before.x == LEFT)
				hammer.pos.x = pos.x - HAMMER_DISTANCE;
			else if (dir_before.x == RIGHT)
				hammer.pos.x = pos.x + HAMMER_DISTANCE;
			else
				hammer.pos.x = pos.x;
		}
		break;
	}



}

void Mario::printHammerOnBoard() const
{
	if (hammer.pos.x < 0 || hammer.pos.x >= pBoard->get_board_width() ||
		hammer.pos.y < 0 || hammer.pos.y >= pBoard->get_board_height())
			return; // To handle if the hammer's hit is beyond the board
	gotoxy(hammer.pos.x, hammer.pos.y);
	std::cout << hammer.ch;
	//pBoard->updateBoard(hammer.pos, hammer.ch);
}

// Handle Mario's lives (when hit or fall)
void Mario::life()
{
	lives -= 1;

	pBoard->setLifeLegend(lives);
	pBoard->printLifeLegend();

	if (lives > DEAD_MARIO) {															// Check if lives > 0
		startOver();																	// Function that reset the game after mario died but still has more than 0 lives
	}
	else if (lives == DEAD_MARIO) {														
		flashingMario();
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
	pGhosts->setStartingGhosts(pGhosts->getNumOfGhosts());
	pBoard->printScreen(pBoard->getCurrentBoard());			//printing new board screen
	pBoard->setHammerLegend(SPACE);
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
