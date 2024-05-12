#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"   // include Globals header file
#include "Trap.h"   // include Globals header file
#include "Wall.h"   // include Globals header file

class MovingTrap : public Trap
{
public:

	void setup(int t_moveType); // 0 = side to side, 1 = up and down

	void move(int t_map[], int t_index, int t_type);

private:

	int direction = 0; // 0 = side to side, 1 = up and down

	int timer = 0;
	const int TIME_BETWEEN_MOVES = 1.5 * 60;

	// Borders of play area
	const int BORDER = SCREEN_HEIGHT - 96;

};

