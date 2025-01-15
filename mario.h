#pragma once

#include "point.h"
#include "barrels.h"
#include "ghosts.h"
#include "entity.h"

#include <Windows.h>	//for Sleep and colors
#include <stdbool.h>
#include <cstdlib>


class Mario : public Entity
{
	//char ch = MARIO;

	// Characters surrounding Mario
	char two_chars_below = GameConfig::SPACE, ch_above = GameConfig::SPACE;
	char ch_left_down = GameConfig::SPACE, ch_right_down = GameConfig::SPACE, ch_behind_hammer = GameConfig::SPACE;
	char ch_wall_on_two_left = GameConfig::SPACE, ch_wall_on_two_right = GameConfig::SPACE, ch_three_chars_below = GameConfig::SPACE;	// Used by the hammer


	// Flags indicating Mario's interaction with his surroundings
	bool res_is_on_ladder = false, res_is_below_roof = false, res_is_two_chars_below_floor = false;
	bool res_is_left_down = false, res_is_right_down = false;
	bool res_ch_wall_on_two_left = false, res_ch_wall_on_two_right = false, res_is_three_chars_below_floor = false;		// Used by the hammer

	bool won_level = false;
	bool just_died = false;
	bool got_hammer = false;
	int fall_count = 0;
	int lives = GameConfig::FULL_LIVES;

	static constexpr int FALL_FROM_TOO_HIGH = 5;
	static constexpr int DEAD_MARIO = 0;
	static constexpr int HAMMER_DISTANCE = 2;


	static constexpr char keys[] = { 'w', 'a', 'x', 'd', 's' };
	static constexpr size_t numKeys = sizeof(keys) / sizeof(keys[0]);

	// Enumeration for Mario's possible states
	enum class MarioState {
		Climbing,
		Jumping,
		Falling,
		Walking_or_Staying
	};
	MarioState state = MarioState::Walking_or_Staying;

	struct Hammer {
		char ch = GameConfig::HAMMER;
		GameConfig::Position pos = { 0,0 };
		bool active = false;
	};
	Hammer hammer;
	GameConfig::Position pos_hit_hammer = {0,0};

	Barrels* pBarrels = nullptr;
	Ghosts* pGhosts = nullptr;

public:
	Mario() : Entity(GameConfig::MARIO) {}													// Constructor initializing Mario's starting position

	void setStartingMario();												// Set Mario to his starting position
	void keyPressed(char key);												// Handle key press input

	void erase() override {															// Erase Mario's current position from the screen and update the board
		point.erase();
		pBoard->updateBoard(point.getPosition(), point.getPreviousChar());
		if (hammer.active) { eraseHammer(); hammer.active = false; }
	}

	void setpBarrels(Barrels& _barrels) { pBarrels = &_barrels; }			// Set the barrels object pointer
	void setpGhosts(Ghosts& _ghosts) { pGhosts = &_ghosts; }			// Set the barrels object pointer

	void updateCharParameters() override;									// Update all the char data members around mario
	void move() override;															// Handle the Marrio's movement
	void amendNextMove();													// Neutralizing illegal movements (jumping under the ceiling, going through a wall, etc.)
	bool isOnLadder() const;												// Check if Mario is on a ladder

	bool isJumping();														// Check if the Mario is jump
	void jump();															// Handle the Mario's jumping
	bool isFalling() const;													// Check if the Mario is falling
	void fall() override;															// Handle the Mario's falling
	bool isClimbing();														// Check if the Mario is climbing
	void climb();															// Handle the Mario's climb
	void walkOrStay();														// Check if the Mario is walking or standing on the floor

	void checkWhatState() override;																		// Check the state of Mario
	void updateState() override;																			// Update Mario's state
	void updateNextMove() override;																		// Update Mario's next move

	char getCharFromBoard(int _x, int _y) { return pBoard->getCharFromBoard(_x, _y); }			// Get the char in the (x,y) position on board
	char getHammerChar() const { return hammer.ch; }			 

	int getLives() const { return lives; }														// Get Mario's lives
	void setLives(int _lives) { lives = _lives; }												// Set Mario's lives
	bool getIfWon() const { return won_level; }													// Check if Mario finish the level (reached Pauline)
	bool getjust_died() const { return just_died; }
	void setJust_died() { just_died = false; }
	void life();																				// Handle Mario's lives (when hit or fall)
	void startOver();																			// Reset the game after mario died but still has more than 0 lives
	void flashingMario();																		// Printing Mario after he died (by flashing the char)

	bool const getIfGotHammer() const { return got_hammer; }
	void handleHammer();
	void updateHammerPos();
	GameConfig::Position getHammerPos() const { return hammer.pos; }														// Get Mario's lives
	void printHammerOnBoard() const;

	void eraseHammer() {
		GameConfig::gotoxy(pos_hit_hammer.x, pos_hit_hammer.y);
		std::cout << ch_behind_hammer;      
		pBoard->updateBoard(pos_hit_hammer, ch_behind_hammer);
	}
	void setIfHammerActive(bool b) { hammer.active = b; }
	void setCharBehindHammer(char _ch) { ch_behind_hammer = _ch; }
	void setPosHitHammer(GameConfig::Position _pos) { pos_hit_hammer = _pos; }
	bool validHit() {
		return (!(point.getDir().y == GameConfig::DOWN || point.getDir().y == GameConfig::UP
			|| res_is_on_ladder || res_is_wall_on_left || res_is_wall_on_right || res_ch_wall_on_two_left || res_ch_wall_on_two_right));
	}

};




