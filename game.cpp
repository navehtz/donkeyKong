#include "game.h"
#include "general.h"
#include <Windows.h>

// Manages the overall flow of the game
void Game::run()
{
	system("mode con cols=80 lines=25");			// Set the console size to be 80X25
	ShowConsoleCursor(false);						// Hides the console cursor to improve visual appearance during the game

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
		switch (key) {
		case(START_NEW_GAME):						// User pressed the key to start a new game
			startGame();
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

// Starts the game loop and handles gameplay logic
void Game::startGame()
{
	setStartingGame();								// Initializes the game state and Mario's starting position and attributes
	playing_mario = true;							// Indicates that the Mario gameplay loop is active
	exit_game = false;								// Indicates that the Mario gameplay loop is active


	while (playing_mario && !exit_game)				// Main game loop: continues as long as Mario is playing and has lives
	{
		if (wonTheLevel())
			break;

		barrels.bringBackExplodedBarrels();			// Reset the state of barrels that have exploded
		draw();										// Draws the current state of the game (Mario, barrels)
		updateIfDiedByBarrel();						// Checks if Mario collided with a barrel and updates his state if he has died

		if (_kbhit())
		{
			updateActionByKeys();
		}
		Sleep(SCREEN_TIME);
		barrels.updateBarrelsCharParameters();
		erase();
		move();
		updateIfDiedByBarrel();						// Checks if Mario collided with a barrel and updates his state if he has died
		playing_mario = isAlive(mario.getLives());	// Determine if Mario is still alive based on his remaining lives (if lives > 0, the game continues)
	}
	clrscr();
	board.printScreen(board.getStartBoard());
}

// Initializes the game to its starting state
void Game::setStartingGame()
{
	clrscr();
	board.reset();
	mario.setStartingMario();							// Initializes Mario to his starting position and state
	mario.setBoard(board);								// Links Mario to the game board, so he can interact with it
	mario.setpBarrels(barrels);							// Links Mario to the barrels, allowing interactions between them
	mario.setLives(FULL_LIVES);

	barrels.setStartingBarrels();						// Initializes the barrels to their starting positions and states
	barrels.setpBoard(board);							// Links the barrels to the game board, enabling their interaction with it

	board.printScreen(board.getCurrentBoard());
	
	char ch_lives = (char)mario.getLives() + '0';		// Converts Mario's life count to a character for display
	gotoxy(board.getLifePosX(), board.getLifePosY());	// Moves the cursor to the position where Mario's lives are displayed
	cout << ch_lives;									 
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
}

// Erases Mario's and barrels previous position from the screen
void Game::erase()
{
	mario.erase();
	barrels.erase();
}

// Moves Mario and barrels to a new position based on user input or game logic
void Game::move()
{
	mario.move();
	barrels.move();
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
void Game::updateIfDiedByBarrel()
{
	// Variables to store the positions of the barrels and Mario
	int barrelPosX, barrelPosY;
	int marioPosX, marioPosY;
	int barrelDirX;

	for (int i = 0; i < barrels.getMaxBarrels(); i++)
	{
		// Get the current barrel's position
		barrelPosX = barrels.getPosX(i);
		barrelPosY = barrels.getPosY(i);

		// Get Mario's current position
		marioPosX = mario.getPointX();
		marioPosY = mario.getPointY();

		barrelDirX = barrels.getBarrelDirX(i);

		hitByBarrel(barrelPosX, barrelPosY, marioPosX, marioPosY, barrelDirX);		// Check if Mario is hit directly by the barrel
		diedFromExplodedBarrel(barrelPosX, barrelPosY, marioPosX, marioPosY, i);	// Check if Mario died due to an exploding barrel
	}
	
	if (mario.getLives() == DEAD_MARIO)												// If Mario's lives reach zero, stop the game
		playing_mario = false;
}


// Handles the logic when Mario is hit by a barrel
void Game::hitByBarrel(int barrelPosX, int barrelPosY, int marioPosX, int marioPosY, int barrelDirX)
{
	if (marioPosX == barrelPosX && marioPosY == barrelPosY)											// When mario and the barrel at the same place
		mario.life();
	else if(marioPosX - 1 == barrelPosX && marioPosX == barrelPosX + 1 && marioPosY == barrelPosY)	// When Mario and the barrel move toward each other, we need to check their previous positions
		mario.life();
	else if(marioPosX + 1 == barrelPosX && marioPosX == barrelPosX - 1 && marioPosY == barrelPosY)	// When Mario and the barrel move toward each other, we need to check their previous positions
		mario.life();
}


// Handles the logic when Mario dies due to an exploded barrel
void Game::diedFromExplodedBarrel(int barrelPosX, int barrelPosY, int marioPosX, int marioPosY, int i)
{	
	bool is_exploded = barrels.getIfBarrelExploded(i);			// Check if the specified i barrel has exploded
	if (is_exploded)
		if (abs(barrelPosX - marioPosX + 1) <= EXPLOSION_RADIUS && abs(barrelPosY - marioPosY + 1) <= EXPLOSION_RADIUS)  // +1 because its movement updated before draw
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
