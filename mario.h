#pragma once

#include "point.h"
#include "barrels.h"
#include "ghosts.h"

#include <Windows.h>	//for Sleep and colors
#include <stdbool.h>
#include <cstdlib>


class Mario
{
	char ch = '@';

	// Characters surrounding Mario
	char ch_covered = SPACE, ch_below = SPACE, two_chars_below = SPACE;
	char ch_above = SPACE, ch_left = SPACE, ch_right = SPACE;
	char ch_left_down = SPACE, ch_right_down = SPACE, ch_behind_hammer = SPACE;
	char ch_wall_on_two_left, ch_wall_on_two_right, ch_three_chars_below;	// Used by the hammer

	// Flags indicating Mario's interaction with his surroundings
	bool res_is_on_ladder = false, res_is_on_floor = false, res_is_below_roof = false, res_is_two_chars_below_floor = false;
	bool res_is_wall_on_left = false, res_is_wall_on_right = false;
	bool res_is_left_down = false, res_is_right_down = false;
	bool res_ch_wall_on_two_left = false, res_ch_wall_on_two_right = false, res_is_three_chars_below_floor = false;		// Used by the hammer

	bool won_level = false;
	bool just_died = false;
	bool got_hammer = false;
	int fall_count = 0;
	int lives = FULL_LIVES;

	static constexpr int FALL_FROM_TOO_HIGH = 5;
	static constexpr int DEAD_MARIO = 0;
	//static constexpr int UP = -1;
	//static constexpr int LEFT = -1;
	//static constexpr int DOWN = 1;
	//static constexpr int RIGHT = 1;
	//static constexpr int STAY = 0;
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

	//struct Direction {
	//	int x, y;
	//};

	struct Hammer {
		char ch = HAMMER;
		Position pos;
		bool active;
	};
	Hammer hammer;
	Position pos_hit_hammer;

	// Member variables for Mario's position and game references
	Point p;
	Board* pBoard = nullptr;
	Barrels* pBarrels = nullptr;
	Ghosts* pGhosts = nullptr;

public:
	Mario() : p(ch) {}														// Constructor initializing Mario's starting position

	void setStartingMario();												// Set Mario to his starting position
	void keyPressed(char key);												// Handle key press input

	void draw() {															// Draw Mario on the screen and update the board
		p.draw(ch);
		pBoard->updateBoard(p.getPosition(), ch);
	}
	void erase() {															// Erase Mario's current position from the screen and update the board
		p.erase();
		pBoard->updateBoard(p.getPosition(), p.getPreviousChar());
		if (hammer.active) { eraseHammer(); hammer.active = false; }
	}

	Point getPointP() const { return p; }									// Get Mario position
	Position getPosition() const { return p.getPosition(); }								// Get Mario position by x-axis
	//int getPointX() const { return p.getX(); }								// Get Mario position by x-axis
	//int getPointY() const { return p.getY(); }								// Get Mario position by y-axis

	void setBoard(Board& _board) { pBoard = &_board; }						// Set the game board pointer
	void setpBarrels(Barrels& _barrels) { pBarrels = &_barrels; }			// Set the barrels object pointer
	void setpGhosts(Ghosts& _ghosts) { pGhosts = &_ghosts; }			// Set the barrels object pointer

	void updateCharParameters();											// Update all the char data members around mario
	void move();															// Handle the Marrio's movement
	void amendNextMove();													// Neutralizing illegal movements (jumping under the ceiling, going through a wall, etc.)
	bool isOnLadder() const;												// Check if Mario is on a ladder
	bool isBlock(char _ch);													// The function returns true if the parameter is a floor/ceiling/wall and false otherwise

	bool isJumping();														// Check if the Mario is jump
	void jump();															// Handle the Mario's jumping
	bool isFalling() const;													// Check if the Mario is falling
	void fall();															// Handle the Mario's falling
	bool isClimbing();														// Check if the Mario is climbing
	void climb();															// Handle the Mario's climb
	void walkOrStay();														// Check if the Mario is walking or standing on the floor

	void checkWhatState();																		// Check the state of Mario
	void updateState();																			// Update Mario's state
	void updateNextMove();																		// Update Mario's next move
	void updatePreviousDir() { p.setPreviousDir(p.getDir()); }									// Function to update the Mario's previous direction to become the current (similar to previous_dir = dir)
	void updatePreviousChar() { p.setPreviousChar(getCharFromBoard(p.getPosition().x, p.getPosition().y)); }		// Function for keeping the char the barrel is on so it can be printes in the next loop

	char getCharFromBoard(int _x, int _y) { return pBoard->getCharFromBoard(_x, _y); }			// Get the char in the (x,y) position on board
	char getHammerChar() { return hammer.ch; }			// 

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
	Position getHammerPos() const { return hammer.pos; }														// Get Mario's lives
	void printHammerOnBoard();

	void eraseHammer() {
		gotoxy(pos_hit_hammer.x, pos_hit_hammer.y);
		std::cout << ch_behind_hammer;      
		pBoard->updateBoard(pos_hit_hammer, ch_behind_hammer);
	}
	void setIfHammerActive(bool b) { hammer.active = b; }
	void setCharBehindHammer(char _ch) { ch_behind_hammer = _ch; }
	void setPosHitHammer(Position _pos) { pos_hit_hammer = _pos; }                    
	bool validHit() {
		return (!((p.getDir().y == DOWN &&
			(res_is_on_floor || res_is_two_chars_below_floor || res_is_three_chars_below_floor))
			|| res_is_on_ladder || res_is_wall_on_left || res_is_wall_on_right || res_ch_wall_on_two_left || res_ch_wall_on_two_right));
	}

};




