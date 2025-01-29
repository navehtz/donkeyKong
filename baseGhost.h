#pragma once

#include "entity.h"

class BaseGhost : public Entity
{
protected:
	static constexpr double CHANGE_DIR_PROB = 0.05;   // Probability of changing direction while wandering

	// Characters surrounding special ghosts
	char ch_left_down = GameConfig::SPACE;            // Character below the left side of the ghost
	char ch_right_down = GameConfig::SPACE;

	bool res_is_left_down = false;                    // True if the tile below the left side is passable
	bool res_is_right_down = false;

	bool is_wander_left = true;                       // True if the ghost is currently wandering to the left

	friend class Ghosts;

public:
	BaseGhost(char ghost_type) : Entity(ghost_type) {}
	BaseGhost(int x, int y, char ghost_type) : Entity(x, y, ghost_type) {}
	virtual ~BaseGhost() = default;

	void setStartingGhost(Board* _pBoard, GameConfig::Position pos);    // Initialize a ghost based on starting position
	int getDirX() const { return point.getDir().x; }                    // Get the ghost's current horizontal direction

	void disappear() { is_activated = false; }                          // Deactivate the ghost, making it disappear
	void blockedByWall();                                               // Stop the ghost's movement if it encounters a wall
	
	virtual void checkWhatState() = 0;
	virtual void updateState() = 0;                                     // Update the ghost's state
	void updateNextMove() override;                                     // Update the ghost's movement for the next game loop
	virtual void updateCharParameters() = 0;                            // Update the chars representing the tiles around the ghost

	void wander();														// Manage the ghost's wandering behavior
	void manageWanderDirection();                                       // Manage the ghost's direction while wandering on the floor
	void fall() override;                                               // Handle the ghost's falling behavior
};

