#include "manualGame.h"
#include "gameConfig.h"
#include <Windows.h>

// Manages the overall flow of the game
void ManualGame::run()
{
	system("mode con cols=80 lines=25");			// Set the console size to be 80X25
	GameConfig::ShowConsoleCursor(false);			// Hides the console cursor to improve visual appearance during the game

	board.getAllBoardFileNames(files_names_vec);
	board.printScreen(board.getStartBoard());		// Displays the starting board on the screen
	bool in_game = true;

	while (in_game)									// Main game loop: keeps running while the game is active
		in_game = menu();

	GameConfig::clrscr();
}

// Displays the game menu and handles user input to start or quit the game
bool ManualGame::menu()
{
	if (_kbhit())									// Checks if a key has been pressed
	{
		int key = _getch();							// Reads the key that was pressed
		int screen_index;
		switch (key) {
		case(START_NEW_GAME):						// User pressed the key to start a new game
			if (!is_save) {							
				board.printScreenOptions(files_names_vec);
				screen_index = chooseGameScreen();
				if (screen_index == GameConfig::EXIT_GAME_FLAG)
					break;
				startGame(screen_index);			// If in save mode we start from stage 1
			}
			else
				startGame(GameConfig::FIRST_SCREEN_INDEX);
			break;
		case(INSTRUCTIONS_AND_KEYS):				// User pressed the key to view instructions
			showInstructions();
			break;
		case(EXIT_GAME):							// User pressed the key to exit the game
			board.printScreen(board.getGoodByeBoard());
			Sleep(GameConfig::SCREEN_EXIT);
			return false;							// Exit the menu loop and terminate the game
		}
	}
	return true;
}

// Displays the game instructions screen to the player
int ManualGame::chooseGameScreen()
{
	while (true)																		// Checks if a key has been pressed
	{
		if (_kbhit())
		{
			int key = _getch() - '0';													// Reads the key that was pressed
			if (!files_names_vec.empty() && key > 0 && key <= files_names_vec.size())	// Valid key
			{
				key--;																	// The array start from zero
				return key;
			}
			else if (key == EXIT_GAME) {
				return GameConfig::EXIT_GAME_FLAG;
			}
		}
	}
	return GameConfig::EXIT_GAME_FLAG;													// Prevent warnings
}

// Handles the looping through game stages
void ManualGame::stagesLoop(int screen_index)
{
	bool valid_file;

	for (int i = screen_index; (i < files_names_vec.size() && playing_mario && !exit_game); i++)
	{
		results.clearResultList();
		steps.clearStepsList();

		valid_file = board.load(files_names_vec[i]);
		if (!valid_file) {								// If the file isnt valid: continue to the next file
			continue;
		}

		if (i == files_names_vec.size() - 1) { last_screen = true; }

		if (is_save) {
			GameConfig::setRandomSeed(static_cast<long>(std::chrono::system_clock::now().time_since_epoch().count()));
			srand(GameConfig::getRandomSeed());
			setFilesNames(i);
		}

		setStartingGame();								// Initializes the game state and Mario's starting position and attributes
		playing_mario = true;							// Indicates that the Mario gameplay loop is active
		exit_game = false;								// Indicates that the Mario gameplay loop is active
		iteration = 0;									// We need iteration to be outside the loop
		score_before_level = board.getScore();			// For the result file
		gameLoop();										// Main game loop: continues as long as Mario is playing and has lives

		if (!exit_game && is_save)						// If in save mode, save the game
			saveManualGame();
	}
}

// Starts the game loop and handles gameplay logic
void ManualGame::startGame(int screen_index)
{
	playing_mario = true;							    // Indicates that the Mario gameplay loop is active
	last_screen = false;								// Indicates that it isn't the last screen

	mario.setLives(GameConfig::FULL_LIVES);
	board.resetScore();

	exit_game = false;								    // Indicates that the Mario gameplay loop is active


	stagesLoop(screen_index);							// Handles the looping through game stages
	
	GameConfig::clrscr();
	board.printScreen(board.getStartBoard());
}

void ManualGame::gameLoop()
{
	results.clearResultList();
	steps.clearStepsList();

	for (; playing_mario && !exit_game; iteration++)
	{
		if (wonTheLevel())
		{
			board.addScore(GameConfig::END_LEVEL);
			if (is_save)
				results.addResult(iteration, results.finished);	// If in save mode, adding to results vector
			break;
		}

		barrels.bringBackExplodedBarrels();			// Reset the state of barrels that have exploded
		draw();										// Draws the current state of the game (Mario, barrels, ghosts etc.)
		updateIfDiedByBarrelOrGhost();				// Checks if Mario collided with a barrel and updates his state if he has died

		manageInput();								// Manage the input
		if (exit_game) {
			results.clearResultList();
			steps.clearStepsList();
			break;
		}

		barrels.updateBarrelsCharParameters();
		erase();									// Erases the current state of the game (Mario, barrels, ghosts etc.)
		move();										// Manage movement for all entities (Mario, barrels, ghosts etc.)
		playing_mario = isAlive(mario.getLives());	// Determine if Mario is still alive based on his remaining lives (if lives > 0, the game continues)

		if (is_save)								// If in save mode, adding to results vector
			setResult();
	}
}

// Handles user input during gameplay
void ManualGame::manageInput()
{
	for (int j = 0; j < GameConfig::POSSIBLE_INPUT; j++)	// Able to get some input from the user at the same game loop
	{
		if (_kbhit())
		{
			updateActionByKeys();
		}
		Sleep(GameConfig::SCREEN_TIME);
	}
}

// Updates Mario's actions based on key presses from the user
void ManualGame::updateActionByKeys()
{
	int key = _getch();
	if (key == EXIT_GAME)					// If the key corresponds to the "Exit Game" action
	{
		exit_game = true;
	}
	else if (key == PAUSE)					// If the key corresponds to "Pause Game"
	{
		pauseGame();
	}
	// If Mario has a hammer and presses the hammer key
	else if (key == GameConfig::HAMMER && mario.getIfGotHammer())
	{
		if (mario.validHit())
		{
			GameConfig::Position hammer_pos = mario.getHammerPos();			// Get the current hammer position from Mario
			char ch = board.getCharFromBoard(hammer_pos.x, hammer_pos.y);	// Retrieve the character at the hammer's position on the board
			mario.setPosHitHammer(hammer_pos);								// Update Mario's internal state with the hammer's position
			mario.printHammerOnBoard();										// Print the hammer on the game board
			
			// If the hammer does not hit an enemy, store the character behind it
			if (ch != GameConfig::BARREL && ch != GameConfig::REGULAR_GHOST && ch != GameConfig::SPECIAL_GHOST)	
				mario.setCharBehindHammer(ch);
			mario.setIfHammerActive(true);									// Activate the hammer
			updateIfMarioHitBarrelOrGhost();								// Check for collisions with enemies
			if(is_save)
				steps.addStep(iteration, (char)key);						// If in save mode, adding to steps vector
		}	
	}
	else {																	// For all other key presses
		mario.keyPressed((char)key);
		if (is_save)
			steps.addStep(iteration, (char)key);							// If in save mode, adding to steps vector
	}
}

// Pauses the game when a specific key is pressed (PAUSE)
void ManualGame::pauseGame()
{
	bool pause_on = true;
	int key;

	while (pause_on == true)
	{
		if (_kbhit())
		{
			key = _getch();
			if (key == PAUSE)
				pause_on = false;
		}
	}
	Sleep(GameConfig::SCREEN_PAUSE_GAME);
}

// Displays the game instructions screen to the player
void ManualGame::showInstructions()
{
	GameConfig::clrscr();
	board.printScreen(board.getInstructionBoard());
	bool in_instruction_screen = true;								 // Flag to keep the instruction screen active until the user decides to exit

	while (in_instruction_screen)									 // Loop to wait for user input while on the instruction scree
	{
		if (_kbhit())
		{
			int key = _getch();
			key = tolower(key);
			if (key == RETURN_BACK)
				in_instruction_screen = false;
		}
	}
	GameConfig::clrscr();
	board.printScreen(board.getStartBoard());
}


// Saves the game state in manual mode
void ManualGame::saveManualGame()
{
	steps.saveSteps(stepsFilename);
	results.saveResults(resultsFilename, (board.getScore() - score_before_level));
}


// Adding the game result to the results vector
void ManualGame::setResult()
{
	if (mario_died_this_iteration) {
		if (mario.getLives() > 0)
			results.addResult(iteration, results.died);
		else {
			results.addResult(iteration, results.finished_dead);
		}
	}
	mario_died_this_iteration = false;
}



