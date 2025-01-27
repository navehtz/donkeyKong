#include "automaticGame.h"

#include "gameConfig.h"
#include <Windows.h>
// Manages the overall flow of the game
void AutomaticGame::run()
{
	system("mode con cols=80 lines=25");			// Set the console size to be 80X25
	GameConfig::ShowConsoleCursor(false);						// Hides the console cursor to improve visual appearance during the game

	board.getAllBoardFileNames(files_names_vec);
	//board.printScreen(board.getStartBoard());		// Displays the starting board on the screen
	//bool in_game = true;

	startGame(0);
	//TODO: try catch if we start saving from the second screen !!!!!!!!!!!!

	GameConfig::clrscr();
}

void AutomaticGame::setStartingGame()
{
	if(!is_silent)
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
	if (!is_silent) {
		board.printScreen(board.getCurrentBoard());
		board.printLegend();
	}
}



// Starts the game loop and handles gameplay logic
void AutomaticGame::startGame(int screen_index)
{
	playing_mario = true;							    // Indicates that the Mario gameplay loop is active
	last_screen = false;								// Indicates that it isn't the last screen

	mario.setLives(GameConfig::FULL_LIVES);
	board.resetScore();

	unmatching_result_found = false;

	stagesLoop(screen_index);
	
	if (!is_silent) {
		GameConfig::clrscr();
		board.printScreen(board.getStartBoard());
	}
}


void AutomaticGame::stagesLoop(int screen_index)
{
	bool valid_file;

	for (int i = screen_index; (i < files_names_vec.size()) && playing_mario /* && exit_game */; i++)
	{
		//std::string filename_prefix, stepsFilename, resultsFilename;

		valid_file = board.load(files_names_vec[i]);
		if (!valid_file) {	// If the file isnt valid: continue to the next file
			continue;
		}

		if (i == files_names_vec.size() - 1) { last_screen = true; }

		setFilesNames(i);

		if (!loadAutoGame())
			continue;

		setStartingGame();								// Initializes the game state and Mario's starting position and attributes
		playing_mario = true;							// Indicates that the Mario gameplay loop is active

		iteration = 0; // we need iteration to be outside the loop
		gameLoop(); //while (playing_mario)							// Main game loop: continues as long as Mario is playing and has lives

		handleResultsErrorAfterLoop();
	}
}


void AutomaticGame::reportResultError(const std::string& message, const std::string& filename, size_t _iteration)
{	
	system("cls");
	std::cout << "Screen " << filename << " - " << message << '\n';
	std::cout << "Iteration: " << _iteration << '\n';
	std::cout << "Press any key to continue to next screens (if any)" << std::endl;
	int zevel = _getch(); // To continue
	zevel = 0; // For the warning of not referenced
}

void AutomaticGame::reportFileError(const std::string& message, const std::string& filename)
{
	system("cls");
	std::cout << filename << " - " << message << '\n';
	std::cout << "Press any key to continue to next screens (if any)" << std::endl;
	int zevel = _getch(); // To continue
	zevel = 0; // For the warning of not referenced
}

bool AutomaticGame::loadAutoGame()
{
	std::filesystem::path stepsFilePath = std::filesystem::path(".") / stepsFilename;
	std::filesystem::path resultsFilePath = std::filesystem::path(".") / resultsFilename;

	if (!std::filesystem::exists(stepsFilePath)) {
		reportFileError("File doesn't exist", stepsFilename);
		return false;
	}

	if (!std::filesystem::exists(resultsFilePath)) {
		reportFileError("File doesn't exist", resultsFilename);
		return false;
	}

	steps = Steps::loadSteps(stepsFilename); //HAVE TO BE BEFORE STARTING THE BARRELS AND GHOSTS - TO SET THE RANDOM SEED
	srand(GameConfig::getRandomSeed());

	results = Results::loadResults(resultsFilename);
	return true;
}

void AutomaticGame::gameLoop()
{
	for (; playing_mario; iteration++)
	{
		//mario.setIteration(++iteration);

		size_t diedNextIteration = 0;
		if (results.isFinishedBy(iteration)) {
			reportResultError("Results file reached finish while game hadn't!", screenFileName, iteration);
			unmatching_result_found = true;
			break;
		}
		else {
			diedNextIteration = results.getDiedNextIteration();
		}

		if (wonTheLevel())
		{
			board.addScore(GameConfig::END_LEVEL);
			break;
		}

		barrels.bringBackExplodedBarrels();			// Reset the state of barrels that have exploded
		draw();										// Draws the current state of the game (Mario, barrels)
		updateIfDiedByBarrelOrGhost();						// Checks if Mario collided with a barrel and updates his state if he has died

		//manageInput();
		updateActionByKeys();

		barrels.updateBarrelsCharParameters();
		erase();
		move();
		//updateIfDiedByBarrelOrGhost();				// Checks if Mario collided with a barrel and updates his state if he has died
		playing_mario = isAlive(mario.getLives());	// Determine if Mario is still alive based on his remaining lives (if lives > 0, the game continues)


		if (!handleResultsError(diedNextIteration))
			break;

		mario_died_this_iteration = false; // Reset for the next iteration
	}
}

bool AutomaticGame::handleResultsError(size_t diedNextIteration)
{
	bool res = true;
	if (mario_died_this_iteration) {
		if (mario.getLives() > 0) {
			if (results.popResult() != Results::ResultEntry{ iteration, Results::ResultValue::died }) {
				reportResultError("Results file doesn't match the died mario!", screenFileName, iteration);
				unmatching_result_found = true;
				res = false;
			}
		}
		else {
			if (results.myFront() != Results::ResultEntry{ iteration, Results::ResultValue::finished }) {
				reportResultError("Results file doesn't match the died mario!", screenFileName, iteration);
				unmatching_result_found = true;
				res = false;
			}
			iteration--;
		}
	}
	else if (iteration == diedNextIteration && iteration > 0) {
		reportResultError("Results file has a dead Mario event that didn't happen!", screenFileName, iteration);
		unmatching_result_found = true;
		res = false;
	}
	return res;
}

void AutomaticGame::handleResultsErrorAfterLoop()
{
	if (!unmatching_result_found)	// == If matching result
	{
		auto last_result = results.popResult();
		if (last_result != Results::ResultEntry{ iteration, Results::ResultValue::finished }) {
			reportResultError("Results file doesn't match finished event!", screenFileName, iteration);
			unmatching_result_found = true;
		}
		//else if	(last_result != Results::ResultEntry{ iteration - 1, Results::ResultValue::finished_dead }) {
		//	reportResultError("Results file doesn't match finished event!", files_names_vec[i], iteration);
		//	unmatching_result_found = true;
		//}
		if (results.popResult().result != Results::ResultValue::noResult) {
			reportResultError("Results file has additional events after finish event!", screenFileName, iteration);
			unmatching_result_found = true;
		}
	}
}


//// Initializes the game to its starting state
//void AutomaticGame::setStartingGame()
//{
//	GameConfig::clrscr();
//
//	board.reset();										// Update current board
//	mario.setpBoard(board);								// Links Mario to the game board, so he can interact with it
//	mario.setStartingMario();							// Initializes Mario to his starting position and state
//	mario.setpBarrels(barrels);							// Links Mario to the barrels, allowing interactions between them
//	mario.setpGhosts(ghosts);
//
//	barrels.setpBoard(board);							// Links the barrels to the game board, enabling their interaction with it
//	barrels.setStartingBarrels();						// Initializes the barrels to their starting positions and states
//
//	ghosts.setpBoard(board);								// Set the board pointer for the ghosts manager
//	ghosts.setStartingGhosts(board.getGhostVectorSize());	// Initialize the starting positions and count of ghosts
//
//	board.setLegend(board.getScore(), mario.getLives(), GameConfig::SPACE); // Update the legend with the current score, Mario's remaining lives, and hammer status
//	board.printScreen(board.getCurrentBoard());
//	board.printLegend();
//}

//void AutomaticGame::manageInput()
//{
	//for (int j = 0; j < GameConfig::POSSIBLE_INPUT; j++)	// Able to get some input from the user at the same game loop
	//{
	//	if (_kbhit())
	//	{
	//		updateActionByKeys();
	//	}
	//	Sleep(GameConfig::SCREEN_TIME);
	//}

// Updates Mario's actions based on key presses from the user
void AutomaticGame::updateActionByKeys()
{
	if (steps.isNextStepOnIteration(iteration))
	{
		while (!steps.isStepEmpty() && iteration >= steps.frontIteration())
		{
			char key = steps.popStep();
			if (key == GameConfig::HAMMER && mario.getIfGotHammer())
			{
				if (mario.validHit())
				{
					GameConfig::Position hammer_pos = mario.getHammerPos();			// Get the current hammer position from Mario
					char ch = board.getCharFromBoard(hammer_pos.x, hammer_pos.y);	// Retrieve the character at the hammer's position on the board
					mario.setPosHitHammer(hammer_pos);								// Update Mario's internal state with the hammer's position
					mario.printHammerOnBoard();										// Print the hammer on the game board
					if (ch != GameConfig::BARREL && ch != GameConfig::GHOST)		// If the hammer's position does not overlap with a barrel or ghost, update the character behind the hammer
						mario.setCharBehindHammer(ch);
					mario.setIfHammerActive(true);									// Activate the hammer
					updateIfMarioHitBarrelOrGhost();								// Check if Mario hits a barrel or a ghost while the hammer is active
				}
			}
			else {									// For all other keys, pass the key to Mario's keyPressed handler
				mario.keyPressed((char)key);
			}
		}
	}
	Sleep(150); // MAGIC NUMBER !!!!!!!
}

//// Draws Mario and barrels on the screen
//void AutomaticGame::draw()
//{
//	mario.draw();
//	barrels.timing();						// Updates the barrels' timing to manage their movement and state
//	barrels.draw();
//	ghosts.draw();
//}

// Erases Mario's, barrels and ghosts previous position from the screen
//void AutomaticGame::erase()
//{
//	mario.erase();
//	barrels.erase();
//	ghosts.erase();
//}

//// Moves Mario, barrels and ghosts to a new position based on user input or game logic
//void AutomaticGame::move()
//{
//	mario.move();
//	if (mario.getjust_died())
//	{
//		mario_died_this_iteration = true;
//		mario.setJust_died();
//		return;
//	}
//	barrels.move();
//	ghosts.move();
//}

// Pauses the game when a specific key is pressed (PAUSE)
//void AutomaticGame::pauseGame()
//{
//	bool pause_on = true;
//	int key;
//
//	while (pause_on == true)
//	{
//		if (_kbhit())
//		{
//			key = _getch();
//			if (key == PAUSE)
//				pause_on = false;
//		}
//	}
//	Sleep(GameConfig::SCREEN_PAUSE_GAME);
//}

// Displays the game instructions screen to the player
//void AutomaticGame::showInstructions()
//{
//	GameConfig::clrscr();
//	board.printScreen(board.getInstructionBoard());
//	bool in_instruction_screen = true;								 // Flag to keep the instruction screen active until the user decides to exit
//
//	while (in_instruction_screen)									 // Loop to wait for user input while on the instruction scree
//	{
//		if (_kbhit())
//		{
//			int key = _getch();
//			key = tolower(key);
//			if (key == RETURN_BACK)
//				in_instruction_screen = false;
//		}
//	}
//	GameConfig::clrscr();
//	board.printScreen(board.getStartBoard());
//}

//void AutomaticGame::updateIfMarioHitBarrelOrGhost() {
//	// Variables to store the positions of the barrels and Mario
//	GameConfig::Position barrel_pos, ghost_pos, hammer_pos;
//
//	int max_barrels = barrels.getMaxBarrels();
//	int num_of_ghosts = ghosts.getNumOfGhosts();
//
//	// Get Mario's current hammer position
//	hammer_pos = mario.getHammerPos();
//
//
//	// Check if Mario's hammer hits any barrels
//	for (int i = 0; i < max_barrels; i++)
//	{
//		barrel_pos = barrels.getPos(i);								    // Get the current barrel's position
//		if (hitTheEnemy(barrel_pos, hammer_pos))						// Check for collision
//		{
//			barrels.deactivate_barrel(i);								// Deactivate the barrel
//			barrels.setPreviousCharOfBarrel(i, mario.getHammerChar());	// To print the hammer on board
//			//barrels.eraseASpecificBarrel(i);							// Remove the barrel from the board
//			barrels.setStartingBarrel(i);								// Reset the barrel's position
//			board.addScore(GameConfig::KILL_BARREL);					// Add score for destroying a barrel
//			break;
//		}
//	}
//
//	// Check if Mario's hammer hits any ghosts
//	for (int i = 0; i < num_of_ghosts; i++)
//	{
//		ghost_pos = ghosts.getGhostPosition(i);
//		if (hitTheEnemy(ghost_pos, hammer_pos))							// Check for collision									
//		{
//			ghosts.deactivate_ghost(i);									// Deactivate the ghost
//			ghosts.setPreviousCharOfGhost(i, mario.getHammerChar());	// To print the hammer on board
//			//ghosts.eraseASpecificGhost(i);							// Remove the ghost from the board
//			ghosts.kickGhostFromBoard(i);
//			board.addScore(GameConfig::KILL_GHOST);						// Add score for destroying a ghost
//			break;
//		}
//	}
//	board.printScoreLegend();									// Update the score display
//}

//bool AutomaticGame::hitTheEnemy(GameConfig::Position enemy_pos, GameConfig::Position hammer_pos)
//{
//	if (hammer_pos.x == enemy_pos.x && hammer_pos.y == enemy_pos.y)		// When mario and the enemy at the same place
//		return true;
//
//	return false;
//}

//// Checks if Mario died from a barrel or ghost
//void AutomaticGame::updateIfDiedByBarrelOrGhost()
//{
//	// Variables to store the positions of the barrels and Mario
//	GameConfig::Position mario_pos, barrel_pos, ghost_pos;
//	int max_barrels = barrels.getMaxBarrels();
//	int num_of_ghosts = ghosts.getNumOfGhosts();
//	bool already_die = false;
//
//	// Get Mario's current position
//	mario_pos = mario.getPosition();
//	for (int i = 0; i < max_barrels && !already_die; i++)
//	{
//		barrel_pos = barrels.getPos(i);						// Get the current barrel's position
//		already_die = hitByEnemy(barrel_pos, mario_pos);
//
//		diedFromExplodedBarrel(barrel_pos, mario_pos, i);	// Check if Mario died due to an exploding barrel
//	}
//
//	for (int i = 0; i < num_of_ghosts && !already_die; i++)
//	{
//		ghost_pos = ghosts.getGhostPosition(i);				// Get the current ghost's position
//		if (hitByEnemy(ghost_pos, mario_pos))					// Check if Mario is hit directly by the ghost
//			break;
//	}
//
//	if (mario.getLives() == GameConfig::DEAD_MARIO)			// If Mario's lives reach zero, stop the game
//		playing_mario = false;
//}

//// Handles the logic when Mario is hit by an enemy (barrel or ghost)
//bool AutomaticGame::hitByEnemy(GameConfig::Position enemy_pos, GameConfig::Position mario_pos)
//{
//	if (mario_pos.x == enemy_pos.x && mario_pos.y == enemy_pos.y) {												// When mario and the barrel at the same place
//		mario.life();
//		return true;
//	}
//	else if (mario_pos.x - 1 == enemy_pos.x && mario_pos.x == enemy_pos.x + 1 && mario_pos.y == enemy_pos.y) {	// When Mario and the barrel move toward each other, we need to check their previous positions
//		mario.life();
//		return true;
//	}
//	else if (mario_pos.x + 1 == enemy_pos.x && mario_pos.x == enemy_pos.x - 1 && mario_pos.y == enemy_pos.y) {	// When Mario and the barrel move toward each other, we need to check their previous positions
//		mario.life();
//		return true;
//	}
//	else
//		return false;
//}

// Handles the logic when Mario dies due to an exploded barrel
//void AutomaticGame::diedFromExplodedBarrel(GameConfig::Position barrel_pos, GameConfig::Position mario_pos, int i)
//{
//	bool is_exploded = barrels.getIfBarrelExploded(i);			// Check if the specified i barrel has exploded
//	if (is_exploded)
//		// Check if Mario is within the explosion radius of the barrel
//		if (abs(barrel_pos.x - mario_pos.x + 1) <= GameConfig::EXPLOSION_RADIUS && abs(barrel_pos.y - mario_pos.y + 1) <= GameConfig::EXPLOSION_RADIUS)  // +1 because its movement updated before draw
//			mario.life();	// Deduct a life from Mario
//}

// Checks if Mario successfully completed the level
//bool AutomaticGame::wonTheLevel()
//{
//	if (mario.getIfWon())
//	{
//		board.printScreen(last_screen ? board.getWinningBoard() : board.getNextStageBoard()); // Printing next stage screen unless it is the last one and then printing winning screen
//		board.printEndLevelScore();
//		Sleep(GameConfig::SCREEN_WIN);
//		return true;
//	}
//	else
//		return false;
//}


