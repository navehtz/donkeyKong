#include "barrels.h"


void Barrels::draw() {
	int i;

	for (i = 0; i < MAX_BARRELS; i++)
	{
		barrels[i].draw(ch);
		pBoard->updateBoard(barrels[i].getX(), barrels[i].getY(), ch);
	}
}

void Barrels::erase() {
	int i;

	for (i = 0; i < MAX_BARRELS; i++)
	{
		barrels[i].erase();
		pBoard->updateBoard(barrels[i].getX(), barrels[i].getY(), barrels[i].getPreviousChar());
	}
}