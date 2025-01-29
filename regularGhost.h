#pragma once
//#include "point.h"
#include "baseGhost.h"
#include "gameConfig.h"


class RegularGhost : public BaseGhost
{
	//static constexpr double CHANGE_DIR_PROB = 0.05;                             // Probability of changing direction while wandering

	//char ch_left_down = GameConfig::SPACE;                                      // Character below the left side of the ghost
	//char ch_right_down = GameConfig::SPACE;                                     // Character below the right side of the ghost

	//bool res_is_left_down = false;                                              // True if the tile below the left side is passable
	//bool res_is_right_down = false;                                             // True if the tile below the right side is passable

	//bool is_wander_left = true;                                                 // True if the ghost is currently wandering to the left

	enum class GhostState {	//!!!
		Wander,                                                                 // The ghost is wandering on the floor
		Falling                                                                 // The ghost is falling
	};
	GhostState state = GhostState::Wander;                                      // Current state of the ghost

	//friend class Ghosts;                                                        // Allow the Ghosts class to access private members of Ghost

public:
	RegularGhost() : BaseGhost(GameConfig::REGULAR_GHOST) {}                                      // Default constructor initializing the ghost with the default char
	RegularGhost(int x, int y) : BaseGhost(x, y, GameConfig::REGULAR_GHOST) {}                    // Constructor initializing the ghost at a specific position with its char

	//void setStartingGhost(Board* _pBoard, GameConfig::Position pos);            // Initialize a ghost based on starting position
	//int getDirX() const { return point.getDir().x; }                            // Get the ghost's current horizontal direction

	void checkWhatState() override;                                             // Check the ghost's current state
	void updateState() override;                                                // Update the ghost's state
	//void updateNextMove() override;                                             // Update the ghost's movement for the next game loop
	void updateCharParameters() override;                                       // Update the chars representing the tiles around the ghost

	//void wander();                                                              // Handle the ghost's wandering behavior
	//void manageWanderDirection();                                                     // Manage the ghost's direction while wandering on the floor
	//void fall() override;                                                       // Handle the ghost's falling behavior
	//void disappear() { is_activated = false; }                                  // Deactivate the ghost, making it disappear
	//void blockedByWall();                                              // Stop the ghost's movement if it encounters a wall

};
