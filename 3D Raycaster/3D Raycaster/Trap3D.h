#pragma once

#include <SFML/Graphics.hpp>
#include "Block.h"

class Trap3D : public Block
{
public:
	Trap3D();

	void collisionDetection(Player& t_player, sf::Vector2f t_spawnPos);

private:


};

