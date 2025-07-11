#include "ghosts.h"

// Initialize all ghosts
void Ghosts::setStartingGhosts(int size)
{
	num_of_ghosts = size;
	ghosts_vec.clear();

	for (int i = 0; i < size; i++)
	{
		char type  = pBoard->getStartPosAndTypeOfGhost(i).type;
		GameConfig::Position pos = pBoard->getStartPosAndTypeOfGhost(i).pos;
		
		if (type == GameConfig::REGULAR_GHOST) {
			addGhost(new RegularGhost(pos.x, pos.y));
			ghosts_vec[i]->setStartingGhost(pBoard, pos);
		}
		else if (type == GameConfig::SPECIAL_GHOST) {
			addGhost(new SpecialGhost(pos.x, pos.y));
			ghosts_vec[i]->setStartingGhost(pBoard, pos);
		}
	}
}

// Draw all the activated ghosts
void Ghosts::draw()
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts_vec[i]->IsActivated())
		{
			ghosts_vec[i]->draw();
		}
	}
}

// Erase all the activated ghosts
void Ghosts::erase()
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts_vec[i]->IsActivated())
		{
			ghosts_vec[i]->erase();
		}
	}
}

// Move all the activated ghosts
void Ghosts::move()
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts_vec[i]->IsActivated())
		{
			ghosts_vec[i]->move();
		}
	}
}

// Update the character parameters for all activated ghosts
void Ghosts::updateGhostsCharParameters()
{
	for (int i = 0; i < num_of_ghosts; i++)
	{
		if (ghosts_vec[i]->IsActivated())
		{
			ghosts_vec[i]->updateCharParameters();
		}
	}
}
