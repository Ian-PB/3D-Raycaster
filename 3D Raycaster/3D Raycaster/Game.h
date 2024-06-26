#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"
#include "Scenes.h"
#include "Player.h"
// Blocks
#include "Wall.h"
#include "InvisableWall.h"
#include "Trap.h"
#include "Door.h"
#include "MovingTrap.h"
#include "Exit.h"

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

	int map[64] = // -1 = playerSpawn
	{
		1,1,1,1,1,1,1,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,-1,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,0,1,
		1,0,0,0,0,0,-2,1,
		1,1,1,1,1,1,1,1
	};
	bool levelOpened = true;



	// Blocks
	Wall walls[64];					 // 1
	InvisableWall invisWalls[64];    // 2
	InvisableWall invisWalls3D[64];  // 3
	Trap traps[64];					 // 4
	Trap traps3D[64];				 // 5
	Door doors[64];					 // 6
	Door doors3D[64];				 // 7
	MovingTrap trapSide[64];         // 8
	MovingTrap trapUpDown[64];       // 9
	MovingTrap trapSide3D[64];       // 10
	MovingTrap trapUpDown3D[64];     // 11
	Exit exit;                       // -2


	// Rays
	void drawRays3D();
	void makeLight();
	float dist(float ax, float ay, float bx, float by, float t_angle) { return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay))); }
	sf::Vector2f pointOnALine(sf::Vector2f t_startPoint, sf::Vector2f t_endPoint, float t_angle, int t_distance);
	sf::VertexArray ray;
	sf::VertexArray light; // Visable

	// Floor 2D
	sf::Texture floorTexture;
	sf::Sprite floorSprite;

	// 3D
	bool topDown = true;

	sf::VertexArray wallSegment;
	sf::RectangleShape floor;
	sf::Texture gadgetTexture;
	sf::Sprite gadgetSprite;


	sf::Vector2f spawnPos;

	bool exitGame = false;

};


