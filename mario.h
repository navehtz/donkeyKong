#pragma once

#include "point.h"
#include "barrels.h"
#include "ghosts.h"
#include "entity.h"
#include "gameConfig.h"

#include <Windows.h>    // For Sleep
#include <stdbool.h>
#include <cstdlib>

class Mario : public Entity
{
	// Characters surrounding Mario
	char two_chars_below = GameConfig::SPACE, ch_above = GameConfig::SPACE;
	char ch_left_down = GameConfig::SPACE, ch_right_down = GameConfig::SPACE, ch_behind_hammer = GameConfig::SPACE;
	char ch_wall_on_two_left = GameConfig::SPACE, ch_wall_on_two_right = GameConfig::SPACE, ch_three_chars_below = GameConfig::SPACE; // Used by the hammer

	// Flags indicating Mario's interaction with his surroundings
	bool res_is_on_ladder = false, res_is_below_roof = false, res_is_two_chars_below_floor = false;
	bool res_is_left_down = false, res_is_right_down = false;
	bool res_ch_wall_on_two_left = false, res_ch_wall_on_two_right = false, res_is_three_chars_below_floor = false; // Used by the hammer


	bool won_level = false;
	bool just_died = false;
	bool got_hammer = false;
	int fall_count = 0;
	int lives = GameConfig::FULL_LIVES;

	// Constants
	static constexpr int FALL_FROM_TOO_HIGH = 5;
	static constexpr int DEAD_MARIO = 0;
	static constexpr int HAMMER_DISTANCE = 2;
	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);

	// Mario's possible states
	enum class MarioState {
		Climbing,
		Jumping,
		Falling,
		Walking_or_Staying
	};
	MarioState state = MarioState::Walking_or_Staying;

	struct Hammer {
		char ch = GameConfig::HAMMER;
		GameConfig::Position pos = { 0, 0 };
		bool active = false;
	};
	Hammer hammer;
	GameConfig::Position pos_hit_hammer = { 0, 0 };

	Barrels* pBarrels = nullptr;
	Ghosts* pGhosts = nullptr;

public:
	Mario() : Entity(GameConfig::MARIO) {}                                        // Constructor initializing Mario's starting position

	void setStartingMario();                                                      // Initialize Mario
	void keyPressed(char key);                                                    // Handle key press input

	void erase() override {                                                       // Erase Mario's current position from the screen and update the board
		point.erase();
		pBoard->updateBoard(point.getPosition(), point.getPreviousChar());
		if (hammer.active) { eraseHammer(); hammer.active = false; } // Erase hammer if active
	}

	void setpBarrels(Barrels& _barrels) { pBarrels = &_barrels; }                 // Set the barrels object pointer
	void setpGhosts(Ghosts& _ghosts) { pGhosts = &_ghosts; }                      // Set the ghosts object pointer

	void updateCharParameters() override;                                         // Update all the character data members around Mario
	void move() override;                                                         // Handle Mario's movement
	void amendNextMove();                                                         // Neutralize illegal movements (jumping under the ceiling, going through a wall, etc.)
	bool isOnLadder() const;                                                      // Check if Mario is on a ladder

	bool isJumping();                                                             // Check if Mario is jumping
	void jump();                                                                  // Handle Mario's jumping movement
	bool isFalling() const;                                                       // Check if Mario is falling
	void fall() override;                                                         // Handle Mario's falling movement
	bool isClimbing();                                                            // Check if Mario is climbing
	void climb();                                                                 // Handle Mario's climbing movement
	void walkOrStay();                                                            // Handle Mario's walking or standing movement

	void checkWhatState() override;                                               // Check the state of Mario
	void updateState() override;                                                  // Update Mario's state
	void updateNextMove() override;                                               // Update Mario's next move

	char getCharFromBoard(int _x, int _y) { return pBoard->getCharFromBoard(_x, _y); } // Get the char in the (x,y) position on board
	char getHammerChar() const { return hammer.ch; }                              // Get the hammer character

	int getLives() const { return lives; }                                        // Get Mario's lives
	void setLives(int _lives) { lives = _lives; }                                 // Set Mario's lives
	bool getIfWon() const { return won_level; }                                   // Check if Mario finished the level (reached Pauline)
	bool getjust_died() const { return just_died; }                               // Check if Mario just died
	void setJust_died() { just_died = false; }                                    // Reset the just died flag
	void life();                                                                  // Handle Mario's lives (when hit or fall)
	void startOver();                                                             // Reset the game after Mario dies but still has lives
	void flashingMario();                                                         // Flash Mario's character after he dies

	bool const getIfGotHammer() const { return got_hammer; }                      // Check if Mario has the hammer
	void handleHammer();                                                          // Handle hammer usage
	void updateHammerPos();                                                       // Update hammer's position
	GameConfig::Position getHammerPos() const { return hammer.pos; }              // Get hammer position
	void printHammerOnBoard() const;                                              // Print the hammer on the board

	void eraseHammer() {
		GameConfig::gotoxy(pos_hit_hammer.x, pos_hit_hammer.y);
		std::cout << ch_behind_hammer;
		pBoard->updateBoard(pos_hit_hammer, ch_behind_hammer);
	}
	void setIfHammerActive(bool b) { hammer.active = b; }                         // Set hammer active status
	void setCharBehindHammer(char _ch) { ch_behind_hammer = _ch; }                // Set character behind hammer
	void setPosHitHammer(GameConfig::Position _pos) { pos_hit_hammer = _pos; }    // Set hammer hit position
	bool validHit() {                                                             // Validate hammer hit
		return (!(point.getDir().y == GameConfig::DOWN || point.getDir().y == GameConfig::UP
			|| res_is_on_ladder || res_is_wall_on_left || res_is_wall_on_right || res_ch_wall_on_two_left || res_ch_wall_on_two_right));
	}
};
