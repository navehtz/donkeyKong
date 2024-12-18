#include "barrels.h"

// Handle the entry of the barrels into the board
void Barrels::timing()
{
	static int iterations = 0;
	static bool first_run = true;

	if (iterations == TIME_TO_ROLL || first_run == true)	// If it's time to roll a barrel
	{
		activateBarrels();
		iterations = 0;
		first_run = false;
		return;
	}
	iterations++;
}

// Inititialize all barrels
void Barrels::setStartingBarrels()
{
	for (int i = 0; i < MAX_BARRELS; i++)
	{
		barrels[i].setStartingBarrel();
	}
}

// Activating the first barrel that isn't activated
void Barrels::activateBarrels()		
{
	for (int i = 0; i < MAX_BARRELS; i++)
	{
		if (!barrels[i].IsActivated())
		{
			barrels[i].setpBoard(*pBoard);
			barrels[i].activate();
			return;											// For activating only the first barrel that isn't activated
		}
	}
}

// Draw all the activated barrels
void Barrels::draw()
{
	for (int i = 0; i < MAX_BARRELS; i++)
	{
		if (barrels[i].IsActivated())
		{
			barrels[i].draw();
		}
	}
}

// Erase all the activated barrels
void Barrels::erase()
{
	for (int i = 0; i < MAX_BARRELS; i++)
	{
		if (barrels[i].IsActivated())
		{
			barrels[i].erase();
		}
	}
}

// Move all the activated barrels
void Barrels::move()
{
	for (int i = 0; i < MAX_BARRELS; i++)
	{
		if (barrels[i].IsActivated())
		{
			barrels[i].move();
		}
	}
}

// Initialize all the exploded barrels
void Barrels::bringBackExplodedBarrels()
{
	for (int i = 0; i < MAX_BARRELS; i++)
	{
		if (barrels[i].getIsExploded())
		{
			barrels[i].setStartingBarrel();
		}
	}
}

void Barrels::updateBarrelsCharParameters()
{
	for (int i = 0; i < MAX_BARRELS; i++)
	{
		if (barrels[i].IsActivated())
		{
			barrels[i].updateCharParameters();
		}
	}
}

