#pragma once

#include "barrel.h"

class Barrels
{
	static constexpr int MAX_BARRELS = 10;
	//int num_barrels = 0;
	static constexpr int TIME_TO_ROLL = 7;		//every X iterations to activate a barrel

	Barrel barrels[MAX_BARRELS];

	Board* pBoard = nullptr;


public:
	Barrels() {
		for (int i = 0; i < MAX_BARRELS; i++) {
			//barrels[i] = Barrel();
			barrels[i].setStartingBarrel();
		}
	}

	void activateBarrels();
	//void deActivateBarrel();
	void setpBoard(Board& _board) { pBoard = &_board; }

	const Barrel* getBarrels() { return barrels; }

	void timing();
	void draw();
	void erase();
	void move();
	void setStartingBarrels();
	int getMaxBarrels() { return MAX_BARRELS; }

	int getPosX(int i) { int posX = barrels[i].getPoint().getX(); return posX; }
	int getPosY(int i) { int posY = barrels[i].getPoint().getY(); return posY; }

	bool getIfBarrelExploded(int i) { bool is_barrel_exploded = barrels[i].getIsExploded(); return is_barrel_exploded; }
	void bringBackExplodedBarrels();

};

