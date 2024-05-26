#include "Exit.h"

Exit::Exit()
{
	body.setFillColor(EXIT_COLOR);
}

void Exit::collisionDetection(Player& t_player, bool& t_exitGame)
{
	if (t_player.getBody().getGlobalBounds().intersects(body.getGlobalBounds()))
	{
		Scenes::levelComplete[Scenes::level - 1] = true;


		t_exitGame = true;
	}
}
