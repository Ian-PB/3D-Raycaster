#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class Block
{
public:

	void spawn(int t_size, sf::Vector2f t_pos);
	sf::RectangleShape getBody() { return body; }
	sf::Sprite getSprite() { return sprite; }

	bool active = false;

protected: // Can be used in the inherited class

	sf::RectangleShape body;
	float size;

	sf::Vector2f position;

	sf::Sprite sprite;

private:

};

