#pragma once
#include <random>
#include "point.h"
#include "entity.h"

class Ghost : public Entity
{
	// Constants
	static constexpr double CHANGE_DIR_PROB = 0.05;

	char ch_left_down = GameConfig::SPACE, ch_right_down = GameConfig::SPACE;

	bool res_is_left_down = false, res_is_right_down = false;

	bool is_activated = true;
	bool is_wander_left = true;

	// States of ghost
	enum class GhostState {
		Wander,
		Falling
	};
	GhostState state = GhostState::Wander;


	friend class Ghosts;

public:
	Ghost() : Entity(GameConfig::GHOST) {}												// Ctor of barrel with point
	Ghost(int x, int y) : Entity(x, y, GameConfig::GHOST) {}

	void setStartingGhost(Board* _pBoard, GameConfig::Position pos);					// Initialize barrel
	int getDirX() const { return point.getDir().x; }									// Get Mario's lives

	void checkWhatState() override;								// Check in which state the barrel is
	void updateState() override;								// Update the barrel's state
	void updateNextMove() override;								// Updating the movement of the barrel for the next loop according to the position and the direction
	void updateCharParameters() override;						// Update all the char data members around mario

	void wander();												// Handle the barrel's rolling
	void fall() override;												// Handle the barrel's falling
	void manageDirection();										// Manage the direction of the barrel while on the floor
	void disappear() { is_activated = false; }												// Function to update the barrel's 'is_activated' and 'is_exploded' members
	void blockedByWall();										// Function to stop the barrels's movement if it reaches a wall

	int myRandom();												// Function to raffle a number ( 1 or 0 )

	bool const IsActivated() const { return is_activated; };	// The function returns true if the ghost is activated(rolling/falling etc.) and false otherwise
	void activate() { is_activated = true; }					// Function to activate the barrel
	void deactivate() { is_activated = false; }					// Function to deactivate the barrel
};

