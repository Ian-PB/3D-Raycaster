#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "Game.h"

enum class Scene
{
	None,
	MainMenu,
	Game
};

class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	static Scene currentMode;

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	Game game;

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame = false; // control exiting game
};

