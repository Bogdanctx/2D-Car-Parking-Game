#include "Menu.h"
#include <iostream>

Menu::Menu()
{
	if (!menuBackgroundImageTexture.loadFromFile("res/img/menu_background.png"))
		std::cout << "menu_background.png could not be loaded.\n";
	if(!pressStart2P.loadFromFile("res/fonts/PressStart2P-Regular.ttf"))
		std::cout << "PressStart2P-Regular.ttf could not get loaded.\n";
	if (!bangers.loadFromFile("res/fonts/Bangers-Regular.ttf"))
		std::cout << "Bangers-Regular.ttf could not get loaded.\n";
	if (!arial.loadFromFile("res/fonts/arial.ttf"))
		std::cout << "arial.ttf could not get loaded.\n";

	menuIsActive = true;
	settingsActive = false;

	startGameButton = Button(sf::Vector2f(405, 245), sf::Vector2f(220, 100), sf::Vector3i(105, 74, 37), sf::Vector3i(163, 115, 57));
	settingsButton = Button(sf::Vector2f(405, 375), sf::Vector2f(220, 100), sf::Vector3i(105, 74, 37), sf::Vector3i(163, 115, 57));

    startGameButton.SetButtonName("START GAME", bangers, 40);
    settingsButton.SetButtonName("SETTINGS", bangers, 40);


	menuBackgroundImage.setTexture(menuBackgroundImageTexture);

	gameTitle.setCharacterSize(20);
	gameTitle.setFillColor(sf::Color::White);
	gameTitle.setFont(pressStart2P);
	gameTitle.setString("2D Car Parking Game");
	gameTitle.setPosition(sf::Vector2f(213, 106));
}

void Menu::SetMenuWindow(sf::RenderWindow* window)
{
	gameWindow = window;

	return;
}

void Menu::HandleMenuEvent()
{
	while (gameWindow->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				gameWindow->close();
				break;
			}
			case sf::Event::MouseButtonPressed:
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i mPos = sf::Mouse::getPosition(*gameWindow);

					if (startGameButton.IsPressed(mPos) && !settingsActive)
					{
						menuIsActive = false;
					}
					else if (settingsButton.IsPressed(mPos) && !settingsActive)
					{
						settingsActive = true;
						vehicleSelectedColor = 0;

						goBackButton = Button(sf::Vector2f(405, 630), sf::Vector2f(150, 80), sf::Vector3i(105, 74, 37), sf::Vector3i(163, 115, 57));
						goBackButton.SetButtonName("APPLY", bangers, 30);

						previousColorButton = Button(sf::Vector2f(380, 290), sf::Vector2f(30, 30), sf::Vector3i(105, 74, 37), sf::Vector3i(163, 115, 57));
						previousColorButton.SetButtonName("<", arial, 30);

						nextColorButton = Button(sf::Vector2f(430, 290), sf::Vector2f(30, 30), sf::Vector3i(105, 74, 37), sf::Vector3i(163, 115, 57));
						nextColorButton.SetButtonName(">", arial, 30);

						gameTitle.setString("2D Car Parking Game\n\n      SETTINGS");
						gameTitle.setCharacterSize(20);

						chooseVehicleColor.setString("CHOOSE VEHICLE COLOR");
						chooseVehicleColor.setCharacterSize(25);
						chooseVehicleColor.setFillColor(sf::Color::White);
						chooseVehicleColor.setPosition(sf::Vector2f(310, 200));
						chooseVehicleColor.setFont(bangers);

						vehicleColor.setString(vehicleColors[vehicleSelectedColor]);
						vehicleColor.setCharacterSize(25);
						vehicleColor.setFillColor(sf::Color::White);
						vehicleColor.setPosition(sf::Vector2f(380, 230));
						vehicleColor.setFont(bangers);
					}

					if(settingsActive)
					{
						if (goBackButton.IsPressed(mPos))
						{
							settingsActive = false;

							gameTitle.setString("2D Car Parking Game");
							gameTitle.setCharacterSize(20);
						}
						else if (previousColorButton.IsPressed(mPos))
						{
							if (vehicleSelectedColor - 1 < 0)
								vehicleSelectedColor = 9;

							vehicleColor.setString(vehicleColors[--vehicleSelectedColor]);
							vehicleCustomColor.loadFromFile(vehiclesImages[vehicleSelectedColor]);
							
						}
						else if (nextColorButton.IsPressed(mPos))
						{
							if (vehicleSelectedColor + 1 > 8)
								vehicleSelectedColor = -1;

							vehicleColor.setString(vehicleColors[++vehicleSelectedColor]);
							vehicleCustomColor.loadFromFile(vehiclesImages[vehicleSelectedColor]);
						}

					}

				}
				break;
			}
			default:
				break;
		}
	}
}
