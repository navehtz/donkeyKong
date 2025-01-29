#pragma once
#include "baseGhost.h"
#include "gameConfig.h"

class SpecialGhost : public BaseGhost
{
	char two_chars_below = GameConfig::SPACE;

	bool res_is_on_ladder = false;
	bool res_is_two_chars_below_floor = false;

	enum class GhostState { 
		Wander,                                                                 // The ghost is wandering on the floor
		Climbing,																// The ghost is climbing on a ladder
		Falling                                                                 // The ghost is falling
	};
	GhostState state = GhostState::Wander;                                      // Current state of the ghost

public:
	SpecialGhost() : BaseGhost(GameConfig::SPECIAL_GHOST) {}                    // Default constructor initializing the ghost with the default char
	SpecialGhost(int x, int y) : BaseGhost(x, y, GameConfig::SPECIAL_GHOST) {}
	
	int getDirY() const { return point.getDir().y; }                            // Get the ghost's current vertical direction

	void checkWhatState() override;                                             // Check the ghost's current state
	void amendNextMove();
	void updateState() override;                                                // Update the ghost's state
	void updateCharParameters() override;                                       // Update the chars representing the tiles around the ghost

	bool isClimbing();															// Check if Mario is climbing
	void climb();																// Handle Mario's climbing movement
	void decideIfNeedToClimb();                                                 // Manage the ghost's direction while wandering on the floor
	bool isOnLadder() const;                                                    // Check if Mario is on a ladder
};
