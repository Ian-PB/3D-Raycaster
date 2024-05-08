// Player class declaration
#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"   // include Globals header file


enum class Direction
{
	None,
	Up,
	Down,
	Left,
	Right
};

class Player
{
public:

	Player();
	void setup(sf::Vector2f t_pos);

	// "Get" functions
	sf::RectangleShape getBody() { return body; }
	sf::Vector2f getPos() { return position; }
	void setPos(sf::Vector2f t_newPos) { position = t_newPos; }
	float getAngle() { return angleR; }

	// Movement
	void checkDirection(bool t_2D);
	void rotateToMouse(sf::Vector2f t_mousePos, bool t_2D);

	bool alive = true;

private:

	// Functions
	void checkBoundries();
	void move(bool t_2D);

	// Variables
	sf::RectangleShape body;
	float size = 10.0f;
	sf::Vector2f position;

	// Movement Variables
	float speed = 1.0f;
	Direction direction;
	float angleR = 0.0f; // Radians
	
};