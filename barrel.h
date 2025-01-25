#pragma once

#include <Windows.h>	//for Sleep and colors
#include "point.h"
#include "entity.h"
#include "gameConfig.h"


class Barrel : public Entity
{
	// Constants
	static constexpr int FALL_FROM_TOO_HIGH = 8;
	static constexpr int EXPLODED_BARREL = 0;

	// Members

	int fall_count = 0;

	char two_chars_below = GameConfig::SPACE;

	//bool is_activated = false;
	bool is_exploded = false;

	// States of barrel
	enum class BarrelState {
		Falling,
		Rolling
	};
	BarrelState state = BarrelState::Rolling;

	friend class Barrels;

public:
	Barrel() : Entity(GameConfig::BARREL) {} 								// Ctor of barrel with point

	void setStartingBarrel(Board* _pBoard);									// Initialize barrel
	bool getIsExploded() const { return is_exploded; }						// Get the member 'is_exploded'
	void setIsExploded(bool _is_exploded) { is_exploded = _is_exploded; }	// Set the member 'is_exploded'
	const Point& getPoint() const { return point; }							// Get the member 'point'
	int getDirX() const { return point.getDir().x; }						// Get the x-direction of 'point'

	void checkWhatState() override;											// Check in which state the barrel is
	void updateState() override;											// Update the barrel's state
	void updateNextMove() override;											// Updating the movement of the barrel for the next loop according to the position and the direction

	void updateCharParameters() override;						// Update all the char data members around mario
	bool isFalling() const;										// Check if the barrel is falling 
	void fall() override;										// Handle the barrel's falling
	void roll();												// Handle the barrel's rolling
	void manageDirection();										// Manage the direction of the barrel while on the floor
	bool explosionCases();										// Handle the cases which the barrel explodes in (falling 8 chars or at wall)
	void explode();												// Function to update the barrel's 'is_activated' and 'is_exploded' members
	void blockedByWall();								// Function to stop the barrels's movement if it reaches a wall

};


