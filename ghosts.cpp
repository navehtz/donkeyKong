#include "ghosts.h"

// Initialize all ghosts
void Ghosts::setStartingGhosts(int size)
{
	num_of_ghosts = size;
	ghosts_vec.clear();
	ghosts_vec.resize(num_of_ghosts);// CHANGE !!! PUSH BACK BY THE TYPE OF THE GHOST

	for (int i = 0; i < size; i++)
	{
		// להכניס לוקטור את סוג הרוח ואז לעשות תנאים איזה סוג רוח אנחנו מאתחלים - מיוחדת או רגילה
		char type  = pBoard->getStartPosAndTypeOfGhost(i).type;
		GameConfig::Position pos = pBoard->getStartPosAndTypeOfGhost(i).pos;
		
		if(type == GameConfig::REGULAR_GHOST)
			ghosts_vec[i].setStartingGhost(pBoard, pos);
		else if(type == GameConfig::SPECIAL_GHOST)
			ghosts_vec[i].setStartingGhost(pBoard, pos);
	}
}

// Draw all the activated ghosts
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

// Erase all the activated ghosts
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

// Move all the activated ghosts
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

// Remove a ghost by its index
void Ghosts::removeGhostByIndex(int index)
{
	if (index < ghosts_vec.size()) {
		ghosts_vec.erase(ghosts_vec.begin() + index);
	}
	else {
		std::cout << "Error: Invalid index!" << std::endl;
	}
}

// Update the character parameters for all activated ghosts
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
