#include "mario.h"
#include "point.h"

// Initialize Mario
void Mario::setStartingMario()
{
	won_level = false;
	got_hammer = false;
	fall_count = 0;
	point.setPosition(pBoard->getStartPosMario());              // Set starting position for Mario
	point.setDir({ GameConfig::STAY, GameConfig::STAY });       // Set starting direction for Mario
	point.setPreviousChar(' ');                                // Reset the previous char parameter
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));   // Flush the input from the user
}

// Handle key press input
void Mario::keyPressed(char key)
{
	GameConfig::Direction new_dir;
	key = (char)std::tolower(key);
	for (int i = 0; i < numKeys; i++) {
		new_dir = point.getDirFromDirectionsArray(i);
		if (key == keys[i]) {
			point.setDir(new_dir);                                // Update Mario's direction
			if (new_dir.x != GameConfig::STAY)
				point.setDirBeforeStay(new_dir);
			return;
		}
	}
}

// Handle Mario's movement
void Mario::move()
{
	updateCharParameters();     // Update all the character data members around Mario
	amendNextMove();            // Neutralize illegal movements
	checkWhatState();           // Check the state of Mario
	updateState();              // Update Mario's state

	if (just_died) { return; }

	if (ch_covered == GameConfig::HAMMER) {
		handleHammer();
	}

	updateNextMove();
	updatePreviousChar();
	updatePreviousDir();
	if (got_hammer) { updateHammerPos(); }
}

// Update all the character data members around Mario
void Mario::updateCharParameters()
{
	int _x = point.getPosition().x, _y = point.getPosition().y;

	ch_covered = getCharFromBoard(_x, _y);
	ch_below = getCharFromBoard(_x, _y + GameConfig::DOWN);
	two_chars_below = getCharFromBoard(_x, _y + 2);
	ch_above = getCharFromBoard(_x, _y + GameConfig::UP);
	ch_left = getCharFromBoard(_x + GameConfig::LEFT, _y);
	ch_right = getCharFromBoard(_x + GameConfig::RIGHT, _y);
	ch_left_down = getCharFromBoard(_x + GameConfig::LEFT, _y + GameConfig::DOWN);
	ch_right_down = getCharFromBoard(_x + GameConfig::RIGHT, _y + GameConfig::DOWN);
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

// Check the state of Mario
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

// Update Mario's state
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

// Check if Mario is climbing
bool Mario::isClimbing()
{
	if (res_is_on_ladder && point.getDir().y == GameConfig::UP && ch_covered != GameConfig::SPACE)
		return true; // Climbing up

	if (res_is_on_floor && two_chars_below == GameConfig::LADDER && point.getDir().y == GameConfig::DOWN && point.getPreviousDir().y != GameConfig::DOWN)
		return true; // Climbing down from above a ladder

	if (res_is_on_ladder && point.getDir().y == GameConfig::DOWN)
		return true; // Climbing down while on a ladder

	return false;
}

// Handle Mario's climbing movement
void Mario::climb()
{
	int previous_dir_x = point.getPreviousDir().x;

	if (!res_is_on_floor && (previous_dir_x == GameConfig::LEFT || previous_dir_x == GameConfig::RIGHT)) {
		point.setDirX(GameConfig::STAY); // Hold ladder when jumping or falling
		if (point.getDir().y == GameConfig::UP) return;
		else if (point.getDir().y == GameConfig::DOWN) point.setDirY(GameConfig::STAY);
	}
}

// Check if Mario is jumping
bool Mario::isJumping()
{
	static int count_jump = 0;

	if (res_is_on_floor && point.getDir().y == GameConfig::UP) {
		if (two_chars_below == GameConfig::LADDER && point.getPreviousDir().y == GameConfig::UP) {
			point.setDirY(GameConfig::STAY);
			return false;
		}
		count_jump += 1;
		fall_count = 0;
		return true;
	}
	else if (ch_below != GameConfig::LADDER && point.getDir().y == GameConfig::UP && count_jump == 1) {
		count_jump += 1;
		return true;
	}
	else {
		count_jump = 0;
		return false;
	}
}

// Handle Mario's jumping movement
void Mario::jump()
{
	point.setDirX(point.getPreviousDir().x);
	point.setDirY(GameConfig::UP);
}

// Check if Mario is falling
bool Mario::isFalling() const
{
	return (ch_below == GameConfig::SPACE || ch_below == GameConfig::HAMMER || ch_below == GameConfig::PRINCESS);
}

// Handle Mario's falling movement
void Mario::fall()
{
	if (!res_is_left_down && !res_is_right_down)
		point.setDirX(point.getPreviousDir().x);
	else
		point.setDirX(GameConfig::STAY);

	point.setDirY(GameConfig::DOWN);
	fall_count += 1;
}

// Handle Mario's walking or standing movement
void Mario::walkOrStay()
{
	if (!just_died)
	{
		if (fall_count >= FALL_FROM_TOO_HIGH)
			life(); // Mario loses life if falling from a high place

		if (ch_left == GameConfig::GORRILA || ch_right == GameConfig::GORRILA)
			life(); // Mario loses life if touching a gorilla
	}

	fall_count = 0;
	point.setDirY(GameConfig::STAY);
}

// Check if Mario is on a ladder
bool Mario::isOnLadder() const
{
	return (ch_covered == GameConfig::LADDER || ch_below == GameConfig::LADDER);
}

// Neutralize illegal movements (jumping under the ceiling, going through a wall, etc.)
void Mario::amendNextMove()
{
	if (res_is_below_roof && !res_is_on_ladder && point.getDir().y == GameConfig::UP)
		point.setDirY(GameConfig::STAY);

	if (res_is_wall_on_left && point.getDir().x == GameConfig::LEFT)
		point.setDirX(GameConfig::STAY);

	if (res_is_wall_on_right && point.getDir().x == GameConfig::RIGHT)
		point.setDirX(GameConfig::STAY);

	if (res_is_on_floor && two_chars_below != GameConfig::LADDER && point.getDir().y == GameConfig::DOWN)
		point.setDirY(GameConfig::STAY);

	if ((res_is_left_down || res_is_right_down) && point.getDir().y == GameConfig::DOWN)
		point.setDirX(GameConfig::STAY);
}

// Update Mario's next move
void Mario::updateNextMove()
{
	int newX = point.getPosition().x + point.getDir().x;
	int newY = point.getPosition().y + point.getDir().y;

	if (newX < 0 || newX >= pBoard->get_board_width())
		newX = point.getPosition().x;

	if (newY < 0 || newY >= pBoard->get_board_height())
		newY = point.getPosition().y;

	if (pBoard->getCharFromBoard(newX, newY) == GameConfig::PRINCESS || ch_below == GameConfig::PRINCESS) {
		won_level = true;
		return;
	}

	point.setPosition(newX, newY);
}

// Handle hammer usage
void Mario::handleHammer()
{
	got_hammer = true;
	pBoard->setHammerLegend(GameConfig::HAMMER);
	pBoard->printHammerLegend();
	pBoard->updateBoard(getPosition(), GameConfig::SPACE);
	point.setPreviousChar(GameConfig::SPACE);
	erase();
	updateHammerPos();
}

// Update hammer's position
void Mario::updateHammerPos()
{
	GameConfig::Position pos = point.getPosition();
	GameConfig::Direction dir = point.getDir();
	GameConfig::Direction dir_before = point.getDirBeforeStay();
	bool jumping_or_falling = false;

	switch (dir.y)
	{
	case(GameConfig::UP):
		//hammer.pos.y = pos.y - HAMMER_DISTANCE;
		hammer.pos.y = pos.y;
		jumping_or_falling = true;
		break;
	case(GameConfig::DOWN):
		//hammer.pos.y = pos.y + HAMMER_DISTANCE;
		hammer.pos.y = pos.y;
		jumping_or_falling = true;
		break;
	case(GameConfig::STAY):
		hammer.pos.y = pos.y;
		break;
	}

	switch (dir.x)
	{
	case(GameConfig::LEFT):
		hammer.pos.x = pos.x - HAMMER_DISTANCE;
		break;
	case(GameConfig::RIGHT):
		hammer.pos.x = pos.x + HAMMER_DISTANCE;
		break;
	case(GameConfig::STAY):
		if (jumping_or_falling) {
			hammer.pos.x = pos.x;
		}
		else {
			if (dir_before.x == GameConfig::LEFT)
				hammer.pos.x = pos.x - HAMMER_DISTANCE;
			else if (dir_before.x == GameConfig::RIGHT)
				hammer.pos.x = pos.x + HAMMER_DISTANCE;
			else
				hammer.pos.x = pos.x;
		}
		break;
	}
}

// Print the hammer on the board
void Mario::printHammerOnBoard() const
{
	if (hammer.pos.x < 0 || hammer.pos.x >= pBoard->get_board_width() ||
		hammer.pos.y < 0 || hammer.pos.y >= pBoard->get_board_height())
		return; // Handle if the hammer's hit is beyond the board
	GameConfig::gotoxy(hammer.pos.x, hammer.pos.y);
	std::cout << hammer.ch;
}

bool Mario::validHit()
{
	char ch_covered_by_hammer = pBoard->getCharFromBoard(hammer.pos);
	int dirX_before_stay = point.getDirBeforeStay().x;

	if (point.getDir().y == GameConfig::DOWN || point.getDir().y == GameConfig::UP)	// If the mario is jumping / climbing or falling he can't use the hammer
		return false;
	else if (ch_covered_by_hammer == GameConfig::FLOOR || ch_covered_by_hammer == GameConfig::FLOOR_LEFT || ch_covered_by_hammer == GameConfig::FLOOR_RIGHT) // If the possion of the hammer is on a wall we dont want that the hammer will hit
		return false;
	else if (dirX_before_stay == GameConfig::LEFT && (res_is_wall_on_left || res_ch_wall_on_two_left))	// Mario can't hit through the wall
		return false;
	else if (dirX_before_stay == GameConfig::RIGHT && (res_is_wall_on_right || res_ch_wall_on_two_right))		// Mario can't hit through the wall
		return false;
	else
		return true;
}

// Handle Mario's lives (when hit or falling)
void Mario::life()
{
	lives -= 1;
	if (pBoard->getScore() >= -GameConfig::DIE_SCORE) { // Decrease points when die
		pBoard->addScore(GameConfig::DIE_SCORE);
	}
	else
		pBoard->resetScore(); // For not get to negative score

	pBoard->setLifeLegend(lives);
	pBoard->printLifeLegend();

	if (lives > DEAD_MARIO) {
		startOver();
	}
	else if (lives == DEAD_MARIO) {
		flashingMario();
		pBoard->printScreen(pBoard->getLosingBoard());
		Sleep(GameConfig::SCREEN_EXIT);
	}
}

// Reset the game after Mario dies but still has lives
void Mario::startOver()
{
	just_died = true;
	flashingMario();

	pBoard->reset();
	setStartingMario();
	pBarrels->setStartingBarrels();
	pGhosts->setStartingGhosts(pGhosts->getNumOfGhosts());
	pBoard->printScreen(pBoard->getCurrentBoard());
	pBoard->setHammerLegend(GameConfig::SPACE);
	pBoard->printLegend();
}

// Flash Mario's character after he dies
void Mario::flashingMario()
{
	pBarrels->draw();

	for (int i = 0; i < 3; i++) {
		draw();
		Sleep(GameConfig::SCREEN_FLASH_MARIO);
		erase();
		Sleep(GameConfig::SCREEN_FLASH_MARIO);
	}
}
