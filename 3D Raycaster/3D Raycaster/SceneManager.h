#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Globals.h"
#include "MainMenu.h"
#include "Game.h"
#include "Scenes.h"



class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();


private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame = false; // control exiting game


	MainMenu menu;
	Game game;
};

