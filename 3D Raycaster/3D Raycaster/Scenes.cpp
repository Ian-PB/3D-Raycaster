#include "Scenes.h"

Scenes::Scenes()
{
	currentMode = Scene::None; 
	
	level = 0;

	for (int i = 0; i < LEVELS_AMOUNT; i++)
	{
		levelComplete[i] = false;
	}
}
