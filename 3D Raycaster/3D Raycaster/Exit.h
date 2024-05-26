#pragma once

#include <SFML/Graphics.hpp>
#include "Block.h"
#include "Scenes.h"

class Exit : public Block
{
public:

	Exit();

	void collisionDetection(Player& t_player, bool& t_exitGame);

private:


};

