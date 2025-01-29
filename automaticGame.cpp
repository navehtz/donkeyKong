#include "automaticGame.h"

#include "gameConfig.h"
#include <Windows.h>

// Start the overall flow of the game
void AutomaticGame::run()
{
	system("mode con cols=80 lines=25");						// Set the console size to be 80X25
	GameConfig::ShowConsoleCursor(false);						// Hides the console cursor to improve visual appearance during the game

	board.getAllBoardFileNames(files_names_vec);

	startGame(0);

	GameConfig::clrscr();
}

// Sets up the game before it starts
void AutomaticGame::setStartingGame()
{
	if(!is_silent)
		GameConfig::clrscr();

	board.reset();											// Update current board
	mario.setpBoard(board);									// Links Mario to the game board, so he can interact with it
	mario.setStartingMario();								// Initializes Mario to his starting position and state
	mario.setpBarrels(barrels);								// Links Mario to the barrels, allowing interactions between them
	mario.setpGhosts(ghosts);

	barrels.setpBoard(board);								// Links the barrels to the game board, enabling their interaction with it
	barrels.setStartingBarrels();							// Initializes the barrels to their starting positions and states

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
	playing_mario = true;								    // Indicates that the Mario gameplay loop is active
	last_screen = false;									// Indicates that it isn't the last screen

	mario.setLives(GameConfig::FULL_LIVES);
	board.resetScore();

	unmatching_result_found = false;

	stagesLoop(screen_index);
	
}

// Handles the looping through game stages
void AutomaticGame::stagesLoop(int screen_index)
{
	bool valid_file;

	for (int i = screen_index; (i < files_names_vec.size()) && playing_mario; i++)
	{
		valid_file = board.load(files_names_vec[i]);
		if (!valid_file) {								// If the file isn't valid: continue to the next file
			continue;
		}

		if (i == files_names_vec.size() - 1) { last_screen = true; }

		setFilesNames(i);

		if (!loadAutoGame())							// Loading steps and results files. have to be before set starting game to set the random seed
			continue;

		setStartingGame();								// Initializes the game state and entities's starting position and attributes
		playing_mario = true;							// Indicates that the Mario gameplay loop is active

		iteration = 0;									// We need iteration to be outside the loop
		gameLoop(); 									// Main game loop: continues as long as Mario is playing and has lives

		handleResultsErrorAfterLoop();

		printSuccessfulRunIfSilent();					// For tests when silenced
	}
}

// Runs the main game loop
void AutomaticGame::gameLoop()
{
	for (; playing_mario; iteration++)
	{
		size_t diedNextIteration = 0;
		if (results.isFinishedBy(iteration)) {			// When Results file reached finish while game hadn't
			reportResultError("Results file reached finish while game hadn't!", screenFileName, iteration);
			unmatching_result_found = true;
			break;
		}
		else {
			diedNextIteration = results.getDiedNextIteration(); // To know if Mario is going to die according to results file
		}

		if (wonTheLevel())
		{
			board.addScore(GameConfig::END_LEVEL);
			break;
		}

		barrels.bringBackExplodedBarrels();				// Reset the state of barrels that have exploded
		draw();											// Draws the current state of the game (Mario, barrels, ghosts etc.)
		updateIfDiedByBarrelOrGhost();					// Checks if Mario collided with a barrel or ghost and updates his state if he had died

		updateActionByKeys();

		barrels.updateBarrelsCharParameters();
		erase();										// Erases the current state of the game (Mario, barrels, ghosts etc.)
		move();											// Manage movement for all entities (Mario, barrels, ghosts etc.)
		playing_mario = isAlive(mario.getLives());		// Determine if Mario is still alive based on his remaining lives (if lives > 0, the game continues)

		if (!handleResultsError(diedNextIteration))
			break;

		mario_died_this_iteration = false;				// Reset for the next iteration
	}
}

// Reports an error related to game results
void AutomaticGame::reportResultError(const std::string& message, const std::string& filename, size_t _iteration)
{	
	system("cls");
	std::cout << "Screen " << filename << " - " << message << '\n';
	std::cout << "Iteration: " << _iteration << '\n';
	std::cout << "Press any key to continue to next screens (if any)" << std::endl;
	_getch(); // To continue
}

// Reports an error related to file handling
void AutomaticGame::reportFileError(const std::string& message, const std::string& filename)
{
	system("cls");
	std::cout << filename << " - " << message << '\n';
	std::cout << "Press any key to continue to next screens (if any)" << std::endl;
	_getch(); // To continue
}

// Loads the automatic game mode
bool AutomaticGame::loadAutoGame()
{
	// Define file paths for the steps and results files
	std::filesystem::path stepsFilePath = std::filesystem::path(".") / stepsFilename;
	std::filesystem::path resultsFilePath = std::filesystem::path(".") / resultsFilename;

	// Check if the steps file exists, otherwise report an error and return false
	if (!std::filesystem::exists(stepsFilePath)) {
		reportFileError("File doesn't exist", stepsFilename);
		return false;
	}

	// Check if the results file exists, otherwise report an error and return false
	if (!std::filesystem::exists(resultsFilePath)) {
		reportFileError("File doesn't exist", resultsFilename);
		return false;
	}

	steps = Steps::loadSteps(stepsFilename);

	srand(GameConfig::getRandomSeed());

	results = Results::loadResults(resultsFilename);

	return true;
}

// Handles errors in results checking
bool AutomaticGame::handleResultsError(size_t diedNextIteration)
{
	bool res = true;

	if (mario_died_this_iteration) {
		if (mario.getLives() > 0) {
			// Validate that the results file correctly records Mario's death
			if (results.popResult() != Results::ResultEntry{ iteration, Results::ResultValue::died }) {
				reportResultError("Results file doesn't match the died Mario!", screenFileName, iteration);
				unmatching_result_found = true;
				res = false;
			}
		}
		else {
			// Validate that the results file correctly records the game ending
			if (results.myFront() != Results::ResultEntry{ iteration, Results::ResultValue::finished_dead }) {
				reportResultError("Results file doesn't match the died Mario!", screenFileName, iteration);
				unmatching_result_found = true;
				res = false;
			}
			iteration--; // Adjust iteration if Mario lost all lives
		}
	}
	else if (iteration == diedNextIteration && iteration > 0) {
		// Error: Results file indicates Mario died, but he didn't
		reportResultError("Results file has a dead Mario event that didn't happen!", screenFileName, iteration);
		unmatching_result_found = true;
		res = false;
	}

	return res;
}

// Handles result errors after the main loop ends
void AutomaticGame::handleResultsErrorAfterLoop()
{
	if (!unmatching_result_found)	// == If matching result
	{
		// Check if the last result correctly indicates the game finished
		auto last_result = results.popResult();
		if (mario.getLives() > 0 && last_result != Results::ResultEntry{ iteration, Results::ResultValue::finished }) {
			reportResultError("Results file doesn't match finished event!", screenFileName, iteration);
			unmatching_result_found = true;
		}

		else if (mario.getLives() <= 0 && last_result != Results::ResultEntry{ iteration, Results::ResultValue::finished_dead }) {
			reportResultError("Results file doesn't match finished event!", screenFileName, iteration);
			unmatching_result_found = true;
		}
		
		 // Ensure no additional events exist after the finished event
		if (results.popResult().result != Results::ResultValue::noResult) {
			reportResultError("Results file has additional events after finish event!", screenFileName, iteration);
			unmatching_result_found = true;
		}
	}
}

// Prints success message if running in silent mode
void AutomaticGame::printSuccessfulRunIfSilent() const
{
	if (is_silent && !unmatching_result_found)
	{
		system("cls");
		std::cout << "Screen " << screenFileName << " : SUCCESSFULL RUN - test passed :)" << '\n';
		Sleep(GameConfig::SCREEN_WIN);
	}
}



// Updates Mario's actions based on key presses from the user
void AutomaticGame::updateActionByKeys()
{
	if (steps.isNextStepOnIteration(iteration)) {
		while (!steps.isStepEmpty() && iteration >= steps.frontIteration()) {
			char key = steps.popStep();

			// If Mario has a hammer and presses the hammer key
			if (key == GameConfig::HAMMER && mario.getIfGotHammer()) {
				if (mario.validHit()) {
					GameConfig::Position hammer_pos = mario.getHammerPos();			// Get hammer's current position
					char ch = board.getCharFromBoard(hammer_pos.x, hammer_pos.y);	// Get character at hammer's position

					mario.setPosHitHammer(hammer_pos);								// Update hammer's position in Mario's state
					if (!is_silent)
						mario.printHammerOnBoard();									// Display hammer on board if not in silent mode

					// If the hammer does not hit an enemy, store the character behind it
					if (ch != GameConfig::BARREL && ch != GameConfig::REGULAR_GHOST && ch != GameConfig::SPECIAL_GHOST)
						mario.setCharBehindHammer(ch);

					mario.setIfHammerActive(true);									// Activate hammer mode
					updateIfMarioHitBarrelOrGhost();								// Check for collisions with enemies
				}
			}
			else {
				mario.keyPressed(key); // Handle all other key presses
			}
		}
	}

	if (!is_silent)
		Sleep(GameConfig::SCREEN_AUTO_TIME); // Control game speed in non-silent mode
}



