#pragma once
#include "point.h"
#include "entity.h"
#include "gameConfig.h"

class SpecialGhost : public Entity
{
	static constexpr double CHANGE_DIR_PROB = 0.05;                             // Probability of changing direction while wandering

	// Characters surrounding special ghosts
	char ch_left_down = GameConfig::SPACE;                                      // Character below the left side of the ghost
	char ch_right_down = GameConfig::SPACE;                                     // Character below the right side of the ghost
	char two_chars_below = GameConfig::SPACE;

	bool res_is_left_down = false;                                              // True if the tile below the left side is passable
	bool res_is_right_down = false;                                             // True if the tile below the right side is passable
	bool res_is_on_ladder = false;
	bool res_is_two_chars_below_floor = false;

	bool is_wander_left = true;                                                 // True if the ghost is currently wandering to the left

	enum class GhostState { ///!!!
		Wander,                                                                 // The ghost is wandering on the floor
		Climbing,
		Falling                                                                 // The ghost is falling
	};
	GhostState state = GhostState::Wander;                                      // Current state of the ghost

	friend class Ghosts;



public:
	SpecialGhost() : Entity(GameConfig::SPECIAL_GHOST) {}                                      // Default constructor initializing the ghost with the default char
	SpecialGhost(int x, int y) : Entity(x, y, GameConfig::GHOST) {}                    // Constructor initializing the ghost at a specific position with its char

	void setStartingGhost(Board* _pBoard, GameConfig::Position pos);            // Initialize a ghost based on starting position
	int getDirX() const { return point.getDir().x; }                            // Get the ghost's current horizontal direction

	void checkWhatState() override;                                             // Check the ghost's current state
	void updateState() override;                                                // Update the ghost's state
	void updateNextMove() override;                                             // Update the ghost's movement for the next game loop
	void updateCharParameters() override;                                       // Update the chars representing the tiles around the ghost

	void wander();                                                              // Handle the ghost's wandering behavior
	void fall() override;                                                       // Handle the ghost's falling behavior
	bool isClimbing();                                                          // Check if Mario is climbing
	void climb();                                                               // Handle Mario's climbing movement
	void manageDirection();                                                     // Manage the ghost's direction while wandering on the floor
	void disappear() { is_activated = false; }                                  // Deactivate the ghost, making it disappear
	void blockedByWall();                                              // Stop the ghost's movement if it encounters a wall

};
