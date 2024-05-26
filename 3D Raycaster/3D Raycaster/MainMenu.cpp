#include "MainMenu.h"

MainMenu::MainMenu()
{
	if (!font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading Font" << std::endl;
	}

	// Floor Sprite
	if (!backgroundTexture.loadFromFile("ASSETS\\IMAGES\\Floor.png"))
	{
		std::cout << "problem loading Floor" << std::endl;
	}
	backgroundTexture.setRepeated(true);
	backgroundTexture.setSmooth(true);
	backgroundSprite.setTextureRect(sf::IntRect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT });
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setColor({50, 50, 50, 255});

	for (int i = 0; i < LEVELS_AMOUNT; i++)
	{
		float xValue = 0.0f;
		float yValue = 0.0f;
		colliding[i] = false;

		if (i < LEVELS_AMOUNT / 2)
		{
			yValue = (SCREEN_HEIGHT / 4.0f) + 100;
		}
		else
		{
			yValue = ((SCREEN_HEIGHT / 4.0f) * 3) - 25;
		}

		xValue = (i * 2.0f) * 50 + 55;

		if (i >= LEVELS_AMOUNT / 2)
		{
			xValue -= 500; // The multiplied value * the added value in the first xValue equation
		}

		sf::Vector2f tempPos = { xValue, yValue };
		buttons[i].setup(tempPos, 75, 75, sf::Color::Red);

		// Numbers
		numbers[i].setFont(font);
		numbers[i].setCharacterSize(25);
		numbers[i].setFillColor(sf::Color::White);
		numbers[i].setOutlineColor(sf::Color::Black);
		numbers[i].setOutlineThickness(2);

		numbers[i].setString(std::to_string(i + 1));
		if (numbers[i].getString() == "10")
		{
			numbers[i].setPosition({ tempPos.x - 17, tempPos.y - 15 });
		}
		else
		{
			numbers[i].setPosition({ tempPos.x - 8, tempPos.y - 15 });
		}
	}

	// Instructions
	instructions.setFont(font);
	instructions.setCharacterSize(15);
	instructions.setPosition(15, 15);
	instructions.setString("(Currently there is no sound, missing sprites and no death screen) \nUse W or Up-Arrow to move forwards. \nUse S or Down-Arrow to move backwards. \nD or Right-Arrow to rotate clockwise. \nA or Left-Arrow to rotate counter-clockwise. \nUse E to open doors(blue) \nUse Q to swap between 3D and 2D.");
}

void MainMenu::processEvents(sf::Event t_event, sf::RenderWindow& t_window)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		t_window.close();
	}

	// Mouse
	if (sf::Event::MouseMoved == t_event.type)
	{
		processMouseMove(t_event);
	}
	if (sf::Event::MouseButtonPressed == t_event.type)
	{
		processMouseDown(t_event);
	}
}

void MainMenu::update(sf::Time t_deltaTime)
{
	for (int i = 0; i < LEVELS_AMOUNT; i++)
	{
		// Check what the mouse is over
		colliding[i] = buttons[i].checkForMouse(mousePos);
	}

	for (int i = 0; i < LEVELS_AMOUNT; i++)
	{
		if (Scenes::levelComplete[i])
		{
			buttons[i].changeColor(sf::Color::Green);
		}
	}
}

void MainMenu::render(sf::RenderWindow& t_window)
{
	t_window.clear({ 10, 15, 10, 255 });

	t_window.draw(backgroundSprite);
	t_window.draw(instructions);

	for (int i = 0; i < LEVELS_AMOUNT; i++)
	{
		// t_window.draw(buttons[i].getBody());
		t_window.draw(buttons[i].getSprite());

		t_window.draw(numbers[i]);
	}

	t_window.display();
}

void MainMenu::processMouseMove(sf::Event t_event)
{
	// Gets the position of the mouse
	mousePos.x = static_cast<float>(t_event.mouseMove.x);
	mousePos.y = static_cast<float>(t_event.mouseMove.y);
}

void MainMenu::processMouseDown(sf::Event t_event)
{
	for (int i = 0; i < LEVELS_AMOUNT; i++)
	{
		if (colliding[i])
		{
			switch (i)
			{
				// Start button
			case 0:
				Scenes::level = 1;
				Scenes::currentMode = Scene::Game;
				break;


			case 1:
				Scenes::level = 2;
				Scenes::currentMode = Scene::Game;
				break;


			case 2:
				Scenes::level = 3;
				Scenes::currentMode = Scene::Game;
				break;

			case 3:
				Scenes::level = 4;
				Scenes::currentMode = Scene::Game;
				break;

			case 4:
				Scenes::level = 5;
				Scenes::currentMode = Scene::Game;
				break;

			case 5:
				Scenes::level = 6;
				Scenes::currentMode = Scene::Game;
				break;

			case 6:
				Scenes::level = 7;
				Scenes::currentMode = Scene::Game;
				break;

			case 7:
				Scenes::level = 8;
				Scenes::currentMode = Scene::Game;
				break;

			case 8:
				Scenes::level = 9;
				Scenes::currentMode = Scene::Game;
				break;

			case 9:
				Scenes::level = 10;
				Scenes::currentMode = Scene::Game;
				break;
			}
		}
	}
}

void MainMenu::setupFontAndText()
{
}

void MainMenu::setupSprites()
{
}

void MainMenu::setupObjects()
{
}
