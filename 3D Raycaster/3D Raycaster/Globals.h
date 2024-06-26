#pragma once

#include <SFML/Graphics.hpp>

const int SCREEN_WIDTH = 1024 / 2;
const int SCREEN_HEIGHT = 512;

const double PI = 3.14159265358;
const double P2 = 1.57079632679; // P2 = PI / 2
const double P3 = 4.71238898038; // P3 = 4.71
const double DEGREE_R = 0.0174533;
const int LIGHT_REACH = 100;

const int LEVELS_AMOUNT = 10;

/// ------- Colors ------- ///

// Walls
const sf::Color WALL_COLOR = { 0, 0, 0, 255 };
const sf::Color INVIS_COLOR = { 200, 200, 200, 255 };
const sf::Color TRAP_COLOR = { 255, 0, 0, 255 };
const sf::Color DOOR_COLOR = { 0, 0, 255, 255 };
const sf::Color EXIT_COLOR = { 0, 255, 0, 255 };

const sf::Color SIDE_COLOR_CHANGE = { 75, 75, 75, 255};

// Light
const sf::Color LIGHT_COLOR = { 255, 255, 100, 5 };


/// ------ Levels ------ ///
// Blocks
// Wall			   // 1
// InvisableWall   // 2
// InvisableWall   // 3  // 3D
// Trap 		   // 4
// Trap 		   // 5  // 3D
// Door 		   // 6
// Door 		   // 7  // 3D
// MovingTrapH     // 8
// MovingTrapV     // 9 
// MovingTrapH     // 10 // 3D
// MovingTrapV     // 11 // 3D
const int LEVEL_1[64]
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,-1,0,0,0,0,1,
	1,0,0,0,3,0,0,1,
	1,0,0,0,3,0,0,1,
	1,0,0,0,3,-2,0,1,
	1,0,0,0,3,0,0,1,
	1,1,1,1,1,1,1,1
};
const int LEVEL_2[64]
{
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,3,-2,0,0,1,
	1,0,0,3,3,3,0,1,
	1,0,0,0,0,2,0,1,
	1,-1,0,0,0,2,0,1,
	1,1,1,1,1,1,1,1
};
const int LEVEL_3[64]
{
	1,1,1,1,1,1,1,1,
	1,0,0,-2,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,7,1,6,6,1,7,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,-1,0,0,1,
	1,1,1,1,1,1,1,1
};
const int LEVEL_4[64]
{
	1,1,1,1,1,1,1,1,
	1,-1,0,0,0,3,3,1,
	1,0,0,0,0,3,3,1,
	1,3,3,3,6,0,0,1,
	1,2,0,0,0,0,0,1,
	1,0,7,0,0,0,0,1,
	1,-2,0,2,0,0,0,1,
	1,1,1,1,1,1,1,1
};
const int LEVEL_5[64]
{
	1,1,1,1,1,1,1,1,
	1,-1,0,4,1,1,1,1,
	1,0,0,4,0,1,1,1,
	1,0,0,0,0,0,1,1,
	1,1,0,0,5,0,0,1,
	1,1,1,5,0,0,0,1,
	1,1,1,1,0,0,-2,1,
	1,1,1,1,1,1,1,1
};
const int LEVEL_6[64]
{
	1,1,1,1,1,1,1,1,
	1,0,0,-1,0,0,0,1,
	1,8,0,0,0,0,0,1,
	1,0,0,0,10,0,0,1,
	1,0,0,0,10,0,0,1,
	1,8,0,0,0,0,0,1,
	1,0,0,-2,0,0,0,1,
	1,1,1,1,1,1,1,1
};
const int LEVEL_7[64]
{
	1,1,1,1,1,1,1,1,
	1,-1,0,11,11,1,1,1,
	1,0,0,0,0,1,1,1,
	1,1,1,0,0,1,1,1,
	1,1,1,9,9,1,1,1,
	1,5,6,0,0,0,0,1,
	1,5,6,0,0,0,-2,1,
	1,1,1,1,1,1,1,1
};
const int LEVEL_8[64]
{
	1,1,1,1,1,1,1,1,
	1,-1,0,11,9,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,1,1,1,1,1,1,1,
	1,0,0,0,0,0,0,1,
	1,0,0,0,0,0,-2,1,
	1,1,1,1,1,1,1,1
};
const int LEVEL_9[64]
{
	1,1,1,1,1,1,1,1,
	1,-1,0,0,0,0,0,1,
	1,0,0,0,0,0,0,1,
	1,0,0,5,3,3,7,1,
	1,0,5,3,-2,6,0,1,
	1,5,3,4,0,3,0,1,
	1,3,4,4,0,0,0,1,
	1,1,1,1,1,1,1,1
};
const int LEVEL_10[64]
{
	1,1,1,1,1,1,1,1,
	1,-1,0,11,0,4,4,1,
	1,0,0,4,0,0,4,1,
	1,5,4,4,4,0,0,1,
	1,0,0,4,0,4,0,1,
	1,10,4,4,4,4,4,1,
	1,0,0,4,4,4,-2,1,
	1,1,1,1,1,1,1,1
};
