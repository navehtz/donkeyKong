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

// Generate a random number (0 or 1)
//int Entity::myRandom()
//{
//	static std::random_device rd;
//	static std::mt19937 gen(rd());
//	std::uniform_int_distribution<> dist(0, 1);
//	return dist(gen);
//}

//int Entity::myRandom() {
//	static bool seeded = false;
//	if (!seeded) {
//		srand(time(0));
//		seeded = true;
//	}
//	return rand() % 2;
//}