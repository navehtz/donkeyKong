#include <iostream>		//for cout
#include <conio.h>		//for _kbhit(), _getch()
#include <Windows.h>	//for Sleep and colors
using namespace std;
#include "general.h"
#include "point.h"
#include "mario.h"
#include "board.h"

#include <Windows.h>	//for Sleep and colors

// Better put this is a proper class
constexpr int ESC = 27;

int main() {
	ShowConsoleCursor(false);
	Board board;
	board.reset();
	board.print();
	Mario mario;

	mario.setBoard(board);
	while (true)
	{
		mario.draw();

		if (_kbhit())
		{
			char key = _getch();
			if (key == ESC) 
				break;
			mario.keyPressed(key);
		}
		Sleep(150);
		mario.erase();
		mario.move();
		
	}
}








