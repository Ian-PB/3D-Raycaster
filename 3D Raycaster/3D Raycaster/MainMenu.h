#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Globals.h"
#include "Button.h"
#include "Scenes.h"

class MainMenu
{
public:
	MainMenu();

	void processEvents(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);

private:

	void processMouseMove(sf::Event t_event);
	void processMouseDown(sf::Event t_event);
	void processKeys(sf::Event t_event);

	void setupFontAndText();
	void setupSprites();
	void setupObjects();


	sf::Vector2f mousePos;

	Button buttons[3];
	bool colliding[3];
};

