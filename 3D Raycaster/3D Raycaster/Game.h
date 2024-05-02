/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "Player.h"
#include "Block.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processMouseMove(sf::Event t_event);
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupObjects();

	sf::RenderWindow m_window; // main SFML window

	bool m_exitGame; // control exiting game

	// Player
	sf::Vector2f mousePos;
	Player player;

	// Map
	void drawMap();
	int mapX = 8;
	int mapY = 8;
	int blockSize = 64;

	int map[64] =
	{
		1,1,1,1,1,1,1,1,
		1,1,1,0,0,0,0,1,
		1,1,2,0,0,0,0,1,
		1,0,0,0,0,1,0,1,
		1,0,0,0,0,0,0,1,
		1,0,2,0,0,0,0,1,
		1,0,0,0,0,2,0,1,
		1,1,1,1,1,1,1,1
	};

	// Blocks
	Block blocks[64];

	// Rays
	void drawRays3D();
	float dist(float ax, float ay, float bx, float by, float t_angle) { return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay))); }
	sf::VertexArray ray;

	sf::VertexArray wallSegment;



};

#endif // !GAME_HPP

