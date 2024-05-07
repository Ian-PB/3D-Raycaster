#include "MainMenu.h"

MainMenu::MainMenu()
{
	for (int i = 0; i < 3; i++)
	{
		colliding[i] = false;

		sf::Vector2f tempPos = { (i * 2.0f) * 180 + 150, SCREEN_HEIGHT / 2.0f };
		buttons[i].setup(tempPos, 200, 200, sf::Color::Red);
	}
}

void MainMenu::processEvents(sf::Event t_event)
{
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
	for (int i = 0; i < 3; i++)
	{
		colliding[i] = buttons[i].checkForMouse(mousePos);
	}
}

void MainMenu::render(sf::RenderWindow& t_window)
{
	t_window.clear({ 180, 180, 180, 255 });

	for (int i = 0; i < 3; i++)
	{
		t_window.draw(buttons[i].getBody());
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
	for (int i = 0; i < 3; i++)
	{
		if (colliding[i])
		{
			switch (i)
			{
				// Start button
			case 0:
				Scenes::currentMode = Scene::Game;
				break;

				// Help
			case 1:
				std::cout << "Help";
				break;

				// Exit
			case 2:
				std::cout << "Close";
				break;
			}
		}
	}
}

void MainMenu::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		
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
