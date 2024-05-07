#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"
#include "Scenes.h"
#include "Player.h"
// Blocks
#include "Wall.h"
#include "InvisTop.h"
#include "Invis3D.h"
#include "Trap.h"
#include "Trap3D.h"

class Game
{
public:
	Game();

	void processEvents(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);

private:

	void processMouseMove(sf::Event t_event);
	void processKeys(sf::Event t_event);
	
	void setupFontAndText();
	void setupSprites();
	void setupObjects();


	// Player
	sf::Vector2f mousePos;
	Player player;

	// Map
	void drawMap();
	int mapX = 8;
	int mapY = 8;
	int blockSize = 64;

	int map[64] = // 1 = wall, 2 = invis (2D), 3 = invis (3D), 4 = trap (2D), 5 = trap (3D), 9 = playerSpawn
	{
		1,1,1,1,1,1,1,1,
		1,1,1,0,0,0,0,1,
		1,1,3,0,0,0,0,1,
		1,0,5,4,0,1,0,1,
		1,0,0,0,0,0,0,1,
		1,0,3,2,0,9,0,1,
		1,0,0,0,0,3,0,1,
		1,1,1,1,1,1,1,1
	};

	// Blocks
	Wall walls[64];
	InvisTop invisTops[64];
	Invis3D invis3Ds[64];
	Trap traps[64];
	Trap3D traps3D[64];

	// Rays
	void drawRays3D();
	float dist(float ax, float ay, float bx, float by, float t_angle) { return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay))); }
	sf::VertexArray ray;


	// 3D
	bool firstPersonMode = true;
	sf::VertexArray wallSegment;
	sf::RectangleShape floor;

	sf::Vector2f spawnPos;
};


