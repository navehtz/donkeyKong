#include "ghosts.h"

void Ghosts::setStartingGhosts(int size)
{
	num_of_ghosts = size;
	ghosts.clear();
	ghosts.resize(num_of_ghosts);

	for (int i = 0; i < size; i++)
	{
		Position pos = pBoard->getStartPosOfGhost(i);
		ghosts[i].setStartingGhost(pBoard, pos);
	}
}

// Draw all the activated barrels
void Ghosts::draw()
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts[i].IsActivated())
		{
			ghosts[i].draw();
		}
	}
}

// Erase all the activated barrels
void Ghosts::erase()
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts[i].IsActivated())
		{
			ghosts[i].erase();
		}
	}
}

// Move all the activated barrels
void Ghosts::move()
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts[i].IsActivated())
		{
			ghosts[i].move();
		}
	}
}

void Ghosts::updateGhostsCharParameters()
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts[i].IsActivated())
		{
			ghosts[i].updateCharParameters();
		}
	}

}
