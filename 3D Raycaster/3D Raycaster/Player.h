// Player class declaration
#pragma once

#include <SFML/Graphics.hpp>
#include "Globals.h"   // include Globals header file


enum class Direction
{
	None,
	Up,
	Down,
};

class Player
{
public:

	Player();
	void setup(sf::Vector2f t_pos);

	// "Get" functions
	sf::RectangleShape getBody() { return body; }
	sf::Sprite getSprite() { return sprite; }
	sf::Vector2f getPos() { return position; }
	void setPos(sf::Vector2f t_newPos) { position = t_newPos; body.setPosition(position); sprite.setPosition(position); }
	float getAngle() { return angleR; }

	// Movement
	void checkDirection(bool t_2D);

	bool alive = true;

private:

	// Functions
	void checkBoundries();
	void move(bool t_2D);

	// Variables
	sf::Sprite sprite;
	sf::Texture texture;
	sf::RectangleShape body;
	float size = 20.0f;
	sf::Vector2f position;

	// Movement Variables
	float speed = 1.0f;
	Direction direction;
	float angleR = 0.0f; // Radians

	
	// 3D mouse movement
	sf::Vector2f prevMousePos;
	float prevAngleR = 0.0f;
};