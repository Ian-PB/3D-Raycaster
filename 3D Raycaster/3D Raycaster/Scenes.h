#pragma once

#include "Globals.h"

enum class Scene
{
	None,
	MainMenu,
	Game
};

class Scenes
{
public:
	Scenes();
	static Scene currentMode;

	// Level
	static int level;
	static bool levelComplete[LEVELS_AMOUNT];
};