#pragma once

#include <SFML/Graphics.hpp>
#include "Block.h"

class Trap : public Block
{
public:
	Trap();

	void collisionDetection(Player& t_player, sf::Vector2f t_spawnPos);

private:


};

