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

	void processEvents(sf::Event t_event, sf::RenderWindow& t_window);
	void update(sf::Time t_deltaTime);
	void render(sf::RenderWindow& t_window);

private:

	void processMouseMove(sf::Event t_event);
	void processMouseDown(sf::Event t_event);

	void setupFontAndText();
	void setupSprites();
	void setupObjects();


	sf::Vector2f mousePos;
	sf::Font font;

	Button buttons[LEVELS_AMOUNT];
	bool colliding[LEVELS_AMOUNT];
	sf::Text numbers[LEVELS_AMOUNT];

	// Background
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	// Instructions
	sf::Text instructions;
};

