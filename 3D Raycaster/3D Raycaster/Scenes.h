#pragma once

enum class Scene
{
	None,
	MainMenu,
	Game
};

class Scenes
{
public:
	Scenes() { currentMode = Scene::None; }
	static Scene currentMode;
};