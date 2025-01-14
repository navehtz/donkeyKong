#include "ghosts.h"

void Ghosts::setStartingGhosts(int size)
{
	num_of_ghosts = size;
	ghosts_vec.clear();
	ghosts_vec.resize(num_of_ghosts);

	for (int i = 0; i < size; i++)
	{
		Position pos = pBoard->getStartPosOfGhost(i);
		ghosts_vec[i].setStartingGhost(pBoard, pos);
	}
}

// Draw all the activated barrels
void Ghosts::draw()
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts_vec[i].IsActivated())
		{
			ghosts_vec[i].draw();
		}
	}
}

// Erase all the activated barrels
void Ghosts::erase()
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts_vec[i].IsActivated())
		{
			ghosts_vec[i].erase();
		}
	}
}

// Move all the activated barrels
void Ghosts::move()
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts_vec[i].IsActivated())
		{
			ghosts_vec[i].move();
		}
	}
}

void Ghosts::removeGhostByIndex(int index)
{
	if (index < ghosts_vec.size()) {
		ghosts_vec.erase(ghosts_vec.begin() + index);
	}
	else {
		std::cout << "Error: Invalid index!" << std::endl;
	}
}

void Ghosts::updateGhostsCharParameters()
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts_vec[i].IsActivated())
		{
			ghosts_vec[i].updateCharParameters();
		}
	}

}
