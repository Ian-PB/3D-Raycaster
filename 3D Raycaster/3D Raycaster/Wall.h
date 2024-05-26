#pragma once

#include <SFML/Graphics.hpp>
#include "Block.h"

class Wall : public Block
{
public:

	Wall();

	void collisionDetection(Player& t_player);

private:

	sf::Vector2f safePos;

	sf::Texture texture;
};

