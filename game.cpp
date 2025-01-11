#include "game.h"
#include "general.h"
#include <Windows.h>

// Manages the overall flow of the game
void Game::run()
{
	system("mode con cols=80 lines=25");			// Set the console size to be 80X25
	ShowConsoleCursor(false);						// Hides the console cursor to improve visual appearance during the game

	board.getAllBoardFileNames(files_names_vec);
	board.printScreen(board.getStartBoard());		// Displays the starting board on the screen
	bool in_game = true;

	while (in_game)									// Main game loop: keeps running while the game is active
		in_game = menu();

	clrscr();
}

// Displays the game menu and handles user input to start or quit the game
bool Game::menu()
{
	if (_kbhit())									// Checks if a key has been pressed
	{
		int key = _getch();							// Reads the key that was pressed
		int screen_index;
		switch (key) {
		case(START_NEW_GAME):						// User pressed the key to start a new game
			board.printScreenOptions(files_names_vec);
			screen_index = chooseGameScreen();
			if (screen_index == -1)
				break;
			startGame(screen_index);
			break;
		case(INSTRUCTIONS_AND_KEYS):				// User pressed the key to view instructions
			showInstructions();
			break;
		case(EXIT_GAME):							// User pressed the key to exit the game
			board.printScreen(board.getGoodByeBoard());
			Sleep(SCREEN_EXIT);
			return false;							// Exit the menu loop and terminate the game
		}
	}
	return true;
}

int Game::chooseGameScreen()
{
	while (true)										// Checks if a key has been pressed
	{
		if (_kbhit())
		{
			int key = _getch() - '0';									// Reads the key that was pressed
			if (!files_names_vec.empty() && key > 0 && key <= files_names_vec.size())
			{
				key--;											// The array start from zero
				return key;
			}
			else if (key == EXIT_GAME) {
				return -1;
			}

			break;
		}
	}
	return -1;													// Prevent warnings
}


// Starts the game loop and handles gameplay logic
void Game::startGame(int screen_index)
{
	bool valid_file;
	playing_mario = true;							    // Indicates that the Mario gameplay loop is active
	exit_game = false;								    // Indicates that the Mario gameplay loop is active

	for (int i = screen_index; (i < files_names_vec.size()) && (playing_mario && !exit_game); i++)
	{
		valid_file = board.load(files_names_vec[i]);
		if (!valid_file)
			menu();

		setStartingGame();								// Initializes the game state and Mario's starting position and attributes
		playing_mario = true;							// Indicates that the Mario gameplay loop is active
		exit_game = false;								// Indicates that the Mario gameplay loop is active

		while (playing_mario && !exit_game)				// Main game loop: continues as long as Mario is playing and has lives
		{
			if (wonTheLevel())
			{
				break;
			}

			barrels.bringBackExplodedBarrels();			// Reset the state of barrels that have exploded
			draw();										// Draws the current state of the game (Mario, barrels)
			updateIfDiedByBarrelOrGhost();						// Checks if Mario collided with a barrel and updates his state if he has died

			if (_kbhit())
			{
				updateActionByKeys();
			}
			Sleep(SCREEN_TIME);
			barrels.updateBarrelsCharParameters(); //CHECK IF WE CAN WITHOUT THIS LINE OR ONLY WITH THAT LINE (THE OTHER IS IN MOVE FUNC)
			erase();
			move();
			updateIfDiedByBarrelOrGhost();						// Checks if Mario collided with a barrel and updates his state if he has died
			playing_mario = isAlive(mario.getLives());	// Determine if Mario is still alive based on his remaining lives (if lives > 0, the game continues)
		}
	}
	clrscr();
	board.printScreen(board.getStartBoard());
}

// Initializes the game to its starting state
void Game::setStartingGame()
{
	clrscr();

	board.reset();										// Update current board
	mario.setBoard(board);								// Links Mario to the game board, so he can interact with it
	mario.setStartingMario();							// Initializes Mario to his starting position and state
	mario.setLives(FULL_LIVES);
	mario.setpBarrels(barrels);							// Links Mario to the barrels, allowing interactions between them
	mario.setpGhosts(ghosts);

	barrels.setpBoard(board);							// Links the barrels to the game board, enabling their interaction with it
	barrels.setStartingBarrels();						// Initializes the barrels to their starting positions and states

	ghosts.setpBoard(board);
	ghosts.setStartingGhosts(board.getGhostVectorSize());

	board.setLegend(0, FULL_LIVES, ' ');
	board.printScreen(board.getCurrentBoard());
	board.printLegend();
}


// Updates Mario's actions based on key presses from the user
void Game::updateActionByKeys()
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
	else { mario.keyPressed((char)key); }	// For all other keys, pass the key to Mario's keyPressed handler
}

// Draws Mario and barrels on the screen
void Game::draw()
{
	mario.draw();
	barrels.timing();						// Updates the barrels' timing to manage their movement and state
	barrels.draw();
	ghosts.draw();
}

// Erases Mario's and barrels previous position from the screen
void Game::erase()
{
	mario.erase();
	barrels.erase();
	ghosts.erase();
}

// Moves Mario and barrels to a new position based on user input or game logic
void Game::move()
{
	mario.move();
	if (mario.getjust_died())
	{
		mario.setJust_died();
		return; 
	}
	barrels.move();
	ghosts.move();
}

// Pauses the game when a specific key is pressed (PAUSE)
void Game::pauseGame()
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
	Sleep(SCREEN_PAUSE_GAME);
}

// Displays the game instructions screen to the player
void Game::showInstructions()
{
	clrscr();
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
	clrscr();
	board.printScreen(board.getStartBoard());
}

// Checks if Mario died from a barrel (hit or explosion)
void Game::updateIfDiedByBarrelOrGhost()
{
	// Variables to store the positions of the barrels and Mario
	Position mario_pos, barrel_pos, ghost_pos;
	//int barrelPosX, barrelPosY;
	int marioPosX, marioPosY;
	int max_barrels = barrels.getMaxBarrels();
	int num_of_ghosts = ghosts.getNumOfGhosts();

	// Get Mario's current position
	mario_pos = mario.getPosition();
	marioPosX = mario.getPosition().x;
	marioPosY = mario.getPosition().y;


	for (int i = 0; i < max_barrels; i++)
	{
		// Get the current barrel's position
		barrel_pos = barrels.getPos(i);
		//barrelPosX = barrels.getPosX(i);
		//barrelPosY = barrels.getPosY(i);

		hitByBarrel(barrel_pos, mario_pos);		// Check if Mario is hit directly by the barrel
		diedFromExplodedBarrel(barrel_pos, mario_pos, i);	// Check if Mario died due to an exploding barrel
	}

	for (int i = 0; i < num_of_ghosts; i++)
	{
		ghost_pos = ghosts.getGhostPosition(i);
		hitByGhost(ghost_pos, mario_pos);		// Check if Mario is hit directly by the barrel
	}
	
	if (mario.getLives() == DEAD_MARIO)												// If Mario's lives reach zero, stop the game
		playing_mario = false;
}


// Handles the logic when Mario is hit by a barrel
void Game::hitByBarrel(Position barrel_pos, Position mario_pos)
{
	if (mario_pos.x == barrel_pos.x && mario_pos.y == barrel_pos.y)											// When mario and the barrel at the same place
		mario.life();
	else if(mario_pos.x - 1 == barrel_pos.x && mario_pos.x == barrel_pos.x + 1 && mario_pos.y == barrel_pos.y)	// When Mario and the barrel move toward each other, we need to check their previous positions
		mario.life();
	else if(mario_pos.x + 1 == barrel_pos.x && mario_pos.x == barrel_pos.x - 1 && mario_pos.y == barrel_pos.y)	// When Mario and the barrel move toward each other, we need to check their previous positions
		mario.life();
}

void Game::hitByGhost(Position ghost_pos, Position mario_pos)
{
	if (mario_pos.x == ghost_pos.x && mario_pos.y == ghost_pos.y)											// When mario and the barrel at the same place
		mario.life();
	else if (mario_pos.x - 1 == ghost_pos.x && mario_pos.x == ghost_pos.x + 1 && mario_pos.y == ghost_pos.y)	// When Mario and the barrel move toward each other, we need to check their previous positions
		mario.life();
	else if (mario_pos.x + 1 == ghost_pos.x && mario_pos.x == ghost_pos.x - 1 && mario_pos.y == ghost_pos.y)	// When Mario and the barrel move toward each other, we need to check their previous positions
		mario.life();
}


// Handles the logic when Mario dies due to an exploded barrel
void Game::diedFromExplodedBarrel(Position barrel_pos, Position mario_pos, int i)
{	
	bool is_exploded = barrels.getIfBarrelExploded(i);			// Check if the specified i barrel has exploded
	if (is_exploded)
		if (abs(barrel_pos.x - mario_pos.x + 1) <= EXPLOSION_RADIUS && abs(barrel_pos.y - mario_pos.y + 1) <= EXPLOSION_RADIUS)  // +1 because its movement updated before draw
			mario.life();	
}

// Checks if Mario successfully completed the level
bool Game::wonTheLevel()
{
	if (mario.getIfWon())
	{
		board.printScreen(board.getWinningBoard());	
		Sleep(SCREEN_WIN);
		return true;
	}
	else
		return false;
}
