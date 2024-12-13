#include "game.h"
#include "general.h"
#include <Windows.h>

void Game::run()
{
	ShowConsoleCursor(false);

	board.printScreen(board.getStartBoard());
	bool in_game = true;

	while (in_game)	
		in_game = menu();    //Menu loop
}

bool Game::menu()
{
	if (_kbhit())
	{
		int key = _getch();
		switch (key) {
		case(START_NEW_GAME):			//Playing mario
			startGame();
			break;
		case(INSTRUCTIONS_AND_KEYS):	//Showing instructions and keys
			showInstructions();
			break;
		case(EXIT_GAME):				//Exit game
			return false;
		}
	}
	return true;
}


void Game::startGame()
{
	setStartingGame();
	playing_mario = true;
	bool isMarioAlive = true;
	char ch_lives = (char)mario.getLives() + '0';

	while (playing_mario)
	{
		playing_mario = isAlive(mario.getLives());	//If mario has more than 0 lives, the game will continue
		draw();
		mario.updateIfHitByBarrel();

		if (_kbhit())
		{
			updateActionByKeys();
		}
		Sleep(150);
		
		erase();
		move();

		mario.updateIfHitByBarrel();
	}
	clrscr();
	board.printScreen(board.getStartBoard());
}

void Game::setStartingGame()
{
	clrscr();
	board.reset();
	mario.setStartingMario();
	mario.setBoard(board);
	mario.setpBarrels(barrels);
	barrels.setStartingBarrels();

	barrels.setpBoard(board);
	board.printScreen(board.getCurrentBoard());

	mario.setLives(FULL_LIVES);
	
	char ch_lives = (char)mario.getLives() + '0';
	gotoxy(board.getLifePosX(), board.getLifePosY());
	cout << ch_lives;											//printing 
}

void Game::updateActionByKeys()
{
	int key = _getch();
	if (key == EXIT_GAME)
	{
		playing_mario = false;
		return;
	}
	else if (key == PAUSE)
	{
		pauseGame(key);
	}
	else { mario.keyPressed((char)key); }
}

void Game::draw()
{
	mario.draw();
	barrels.timing();
	barrels.draw();
}

void Game::erase()
{
	mario.erase();
	barrels.erase();
}

void Game::move()
{
	mario.move();
	barrels.move();
}

void Game::pauseGame(int _key)
{
	bool pause_on = true;

	while (pause_on == true)
	{
		if (_kbhit())
		{
			_key = _getch();
			if (_key == PAUSE)
				pause_on = false;
		}
	}
	Sleep(50);
}


void Game::showInstructions()
{
	clrscr();
	board.printScreen(board.getInstructionBoard());
	bool in_instruction_screen = true;

	while (in_instruction_screen)
	{
		if (_kbhit())
		{
			int key = _getch();
			key = std::tolower(key);
			if (key == RETURN_BACK)
				in_instruction_screen = false;
		}
	}
	clrscr();
	board.printScreen(board.getStartBoard());
}	

void Game::updateIfHitByBarrel()
{
	int barrelPosX, barrelPosY;
	int marioPosX, marioPosY;
	for (int i = 0; i < barrels.getMaxBarrels(); i++)
	{
		barrelPosX = barrels.getPosX(i);
		barrelPosY = barrels.getPosY(i);

		marioPosX = mario.getPointX();
		marioPosY = mario.getPointY();
		if (marioPosX == barrelPosX && marioPosY == barrelPosY)
			mario.life();

		if(barrels.getIfBarrelExplode(i))
			if(abs(barrelPosX - marioPosX) <= EXPLOSION_RADIUS && abs(barrelPosY - marioPosY) <= EXPLOSION_RADIUS)
				mario.life();
	}
}