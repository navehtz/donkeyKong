#include <iostream>		//for cout
#include <conio.h>		//for _kbhit(), _getch()
#include <Windows.h>	//for Sleep and colors
using namespace std;
#include "general.h"
#include "point.h"
#include "mario.h"
#include "board.h"


// Better put this is a proper class
constexpr int ESC = 27;

int main() {
	ShowConsoleCursor(false);
	Board board;
	board.reset();
	board.print();
	Mario mario;
	Point p;
	p.setBoard(board);
	mario.p.pBoard = p.pBoard;
	while (true)
	{
		mario.draw();
		//mario.drawPreviousLetter(mario.previous_char);
		if (_kbhit())
		{
			char key = _getch();
			if (key == ESC) 
				break;
			mario.keyPressed(key);
		}
		Sleep(200);
		mario.erase();
		mario.move();
		
	}
}








