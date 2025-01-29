#include "baseGame.h"

// Initializes the game to its starting state
void BaseGame::setStartingGame()
{
	GameConfig::clrscr();

	board.reset();										// Update current board
	mario.setpBoard(board);								// Links Mario to the game board, so he can interact with it
	mario.setStartingMario();							// Initializes Mario to his starting position and state
	mario.setpBarrels(barrels);							// Links Mario to the barrels, allowing interactions between them
	mario.setpGhosts(ghosts);

	barrels.setpBoard(board);							// Links the barrels to the game board, enabling their interaction with it
	barrels.setStartingBarrels();						// Initializes the barrels to their starting positions and states

	ghosts.setpBoard(board);								// Set the board pointer for the ghosts manager
	ghosts.setStartingGhosts(board.getGhostVectorSize());	// Initialize the starting positions and count of ghosts

	board.setLegend(board.getScore(), mario.getLives(), GameConfig::SPACE); // Update the legend with the current score, Mario's remaining lives, and hammer status
	board.printScreen(board.getCurrentBoard());
	board.printLegend();
}

// Sets the filenames for steps and results based on level index
void BaseGame::setFilesNames(int i)
{
	screenFileName = files_names_vec[i];
	filename_prefix = files_names_vec[i].substr(0, files_names_vec[i].find_last_of('.'));
	stepsFilename = filename_prefix + ".steps";
	resultsFilename = filename_prefix + ".result";
}

// Draws Mario and barrels on the screen
void BaseGame::draw()
{
	mario.draw();
	barrels.timing();						// Updates the barrels' timing to manage their movement and state
	barrels.draw();
	ghosts.draw();
}

// Erases the current state of the game (Mario, barrels, ghosts etc.)
void BaseGame::erase()
{
	mario.erase();
	barrels.erase();
	ghosts.erase();
}

// Manage movement for all entities (Mario, barrels, ghosts etc.)
void BaseGame::move()
{
	mario.move();
	if (mario.getjust_died())
	{
		mario_died_this_iteration = true;
		mario.setJust_died();
		return;
	}
	barrels.move();
	ghosts.move();
}

// Checks if Mario died from a barrel or ghost
void BaseGame::updateIfMarioHitBarrelOrGhost() {
	// Variables to store the positions of the barrels and Mario
	GameConfig::Position barrel_pos, ghost_pos, hammer_pos;

	int max_barrels = barrels.getMaxBarrels();
	int num_of_ghosts = ghosts.getNumOfGhosts();

	// Get Mario's current hammer position
	hammer_pos = mario.getHammerPos();


	// Check if Mario's hammer hits any barrels
	for (int i = 0; i < max_barrels; i++)
	{
		barrel_pos = barrels.getPos(i);								    // Get the current barrel's position
		if (hitTheEnemy(barrel_pos, hammer_pos))						// Check for collision
		{
			barrels.deactivateBarrel(i);								// Deactivate the barrel
			barrels.setPreviousCharOfBarrel(i, mario.getHammerChar());	// To print the hammer on board
			barrels.setStartingBarrel(i);								// Reset the barrel's position
			board.addScore(GameConfig::KILL_BARREL);					// Add score for destroying a barrel
			break;
		}
	}

	// Check if Mario's hammer hits any ghosts
	for (int i = 0; i < num_of_ghosts; i++)
	{
		ghost_pos = ghosts.getGhostPosition(i);
		if (hitTheEnemy(ghost_pos, hammer_pos))							// Check for collision									
		{
			ghosts.deactivate_ghost(i);									// Deactivate the ghost
			ghosts.setPreviousCharOfGhost(i, mario.getHammerChar());	// To print the hammer on board
			ghosts.kickGhostFromBoard(i);
			board.addScore(GameConfig::KILL_GHOST);						// Add score for destroying a ghost
			break;
		}
	}
	if(!board.getIsSilent())
		board.printScoreLegend();										// Update the score display
}

// Checks if Mario hits an enemy
bool BaseGame::hitTheEnemy(GameConfig::Position enemy_pos, GameConfig::Position hammer_pos)
{
	if (hammer_pos.x == enemy_pos.x && hammer_pos.y == enemy_pos.y)		// When mario and the enemy at the same place
		return true;

	return false;
}

// Checks if Mario died from a barrel or ghost
void BaseGame::updateIfDiedByBarrelOrGhost()
{
	// Variables to store the positions of the barrels and Mario
	GameConfig::Position mario_pos, barrel_pos, ghost_pos;
	int max_barrels = barrels.getMaxBarrels();
	int num_of_ghosts = ghosts.getNumOfGhosts();
	bool already_die = false;

	// Get Mario's current position
	mario_pos = mario.getPosition();
	for (int i = 0; i < max_barrels && !already_die; i++)
	{
		barrel_pos = barrels.getPos(i);						// Get the current barrel's position
		already_die = hitByEnemy(barrel_pos, mario_pos);

		diedFromExplodedBarrel(barrel_pos, mario_pos, i);	// Check if Mario died due to an exploding barrel
	}

	for (int i = 0; i < num_of_ghosts && !already_die; i++)
	{
		ghost_pos = ghosts.getGhostPosition(i);				// Get the current ghost's position
		if (hitByEnemy(ghost_pos, mario_pos))				// Check if Mario is hit directly by the ghost
			break;
	}

	if (mario.getLives() == GameConfig::DEAD_MARIO)			// If Mario's lives reach zero, stop the game
		playing_mario = false;
}

// Handles the logic when Mario is hit by an enemy (barrel or ghost)
bool BaseGame::hitByEnemy(GameConfig::Position enemy_pos, GameConfig::Position mario_pos)
{
	if (mario_pos.x == enemy_pos.x && mario_pos.y == enemy_pos.y) {												// When mario and the barrel at the same place
		mario.life();
		mario_died_this_iteration = true;
		return true;
	}
	else if (mario_pos.x - 1 == enemy_pos.x && mario_pos.x == enemy_pos.x + 1 && mario_pos.y == enemy_pos.y) {	// When Mario and the barrel move toward each other, we need to check their previous positions
		mario.life();
		mario_died_this_iteration = true;
		return true;
	}
	else if (mario_pos.x + 1 == enemy_pos.x && mario_pos.x == enemy_pos.x - 1 && mario_pos.y == enemy_pos.y) {	// When Mario and the barrel move toward each other, we need to check their previous positions
		mario.life();
		mario_died_this_iteration = true;
		return true;
	}
	else
		return false;
}

// Handles the logic when Mario dies due to an exploded barrel
void BaseGame::diedFromExplodedBarrel(GameConfig::Position barrel_pos, GameConfig::Position mario_pos, int i)
{
	bool is_exploded = barrels.getIfBarrelExploded(i);			// Check if the specified i barrel has exploded
	if (is_exploded)
		// Check if Mario is within the explosion radius of the barrel
		if (abs(barrel_pos.x - mario_pos.x + 1) <= GameConfig::EXPLOSION_RADIUS && abs(barrel_pos.y - mario_pos.y + 1) <= GameConfig::EXPLOSION_RADIUS)  // +1 because its movement updated before draw
			mario.life();	// Deduct a life from Mario
}

// Checks if Mario successfully completed the level
bool BaseGame::wonTheLevel()
{
	if (mario.getIfWon())
	{
		if (!board.getIsSilent()) {
			board.printScreen(last_screen ? board.getWinningBoard() : board.getNextStageBoard()); // Printing next stage screen unless it is the last one and then printing winning screen
			board.printEndLevelScore();
			Sleep(GameConfig::SCREEN_WIN);
		}
		return true;
	}
	else
		return false;
}