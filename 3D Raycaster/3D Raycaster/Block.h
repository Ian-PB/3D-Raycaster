#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class Block
{
public:
	Block();


	void spawn(int t_size, sf::Vector2f t_pos);
	sf::RectangleShape getBody() { return body; }

	void collisionDetection(Player& t_player);

	bool active = false;

private:

	sf::RectangleShape body;
	float size;

	sf::Vector2f position;

	sf::Vector2f safePos;

};

