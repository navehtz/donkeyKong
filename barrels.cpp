#include "barrels.h"

void Barrels::timing()
{
	static int iterations = 0;
	static bool first_run = true;

	if (iterations == TIME_TO_ROLL || first_run == true)	// if it's time to roll a barrel
	{
		activateBarrels();
		iterations = 0;
		first_run = false;
		return;
	}
	iterations++;
}

void Barrels::setStartingBarrels()
{
	for (int i = 0; i < MAX_BARRELS; i++)
	{
		barrels[i].setStartingBarrel();
	}
}

void Barrels::activateBarrels()		
{
	for (int i = 0; i < MAX_BARRELS; i++)
	{
		if (/*num_barrels != MAX_BARRELS &&*/ !barrels[i].IsActivated())
		{
			barrels[i].setpBoard(*pBoard);
			barrels[i].activate();
			//num_barrels++;
			return;
		}
	}
}

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

