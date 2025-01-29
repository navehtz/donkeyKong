#pragma once

#include "baseGhost.h"
#include "gameConfig.h"


class RegularGhost : public BaseGhost
{
	enum class GhostState {	
		Wander,                                              // The ghost is wandering on the floor
		Falling                                              // The ghost is falling
	};
	GhostState state = GhostState::Wander;                  // Current state of the ghost

public:
	RegularGhost() : BaseGhost(GameConfig::REGULAR_GHOST) {}                    // Default constructor initializing the ghost with the default char
	RegularGhost(int x, int y) : BaseGhost(x, y, GameConfig::REGULAR_GHOST) {}  // Constructor initializing the ghost at a specific position with its char

	void checkWhatState() override;                                             // Check the ghost's current state
	void updateState() override;                                                // Update the ghost's state
	void updateCharParameters() override;                                       // Update the chars representing the tiles around the ghost
};
