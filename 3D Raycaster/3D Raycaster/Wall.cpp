#include "Wall.h"

void Wall::collisionDetection(Player& t_player)
{

	if (t_player.getBody().getGlobalBounds().intersects(body.getGlobalBounds()))
	{
		t_player.setPos(safePos);
	}
	else
	{
		safePos = t_player.getPos();
	}
}