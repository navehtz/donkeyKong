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
	clrscr();
	board.reset();
	mario.setStartingMario();
	mario.setBoard(board);
	mario.setpBarrels(barrels);					//to be able to reset the barrels when marrio died (mario.cpp - 233)
	barrels.setStartingBarrels();

	barrels.setpBoard(board);
	board.printScreen(board.getCurrentBoard());

	mario.setLives(FULL_LIVES);
	bool playing_mario = true;
	bool isMarioAlive = true;
	char ch_lives = (char)mario.getLives() + '0';

	//cout << board.getCharFromBoard(board.getLifePosX(), board.getLifePosY());
	gotoxy(board.getLifePosX(), board.getLifePosY());
	cout << ch_lives;											//printing 


	while (playing_mario)
	{
		mario.draw();
		barrels.timing();
		barrels.draw();


		if (_kbhit())
		{
			int key = _getch();
			if (key == EXIT_GAME)
			{

				playing_mario = false;
				break;
			}
			else if (key == PAUSE)
			{
				pauseGame(key);
			}
			else { mario.keyPressed((char)key); }
		}
		Sleep(150);
		mario.erase();
		barrels.erase();

		mario.move();
		barrels.move();


		playing_mario = isAlive(mario.getLives());	//If mario has more than 0 lives, the game will continue
	}
	clrscr();
	board.printScreen(board.getStartBoard());
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