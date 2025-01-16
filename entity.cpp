#include "entity.h"

// Handle the ghost's movement
void Entity::move()
{
	updateCharParameters();									// Update all the char data members around mario
	checkWhatState();										// Check what is the ghost's state 
	updateState();											// Update the moves that the ghost should do by the state

	//update prameters
	updateNextMove();
	updatePreviousChar();
	updatePreviousDir();
}

// The function returns true if the parameter is a floor/ceiling/wall and false otherwise
bool Entity::isBlock(char _ch) const
{
	if (_ch == GameConfig::FLOOR || _ch == GameConfig::FLOOR_RIGHT || _ch == GameConfig::FLOOR_LEFT || _ch == GameConfig::WALL || _ch == point.getChar())
		return true;
	else
		return false;
}

// The function returns true if the entity is falling 
bool Entity::isFalling() const
{
	return ch_below == GameConfig::SPACE ? true : false;
}
