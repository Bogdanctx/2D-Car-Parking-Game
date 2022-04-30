#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"

class Menu
{
public:
	Menu();

	void HandleMenuEvent();
	void SetMenuWindow(sf::RenderWindow *window);


	sf::Sprite menuBackgroundImage;

	Button startGameButton;
	Button settingsButton;
    Button goBackButton;
    Button previousColorButton, nextColorButton;

	sf::Text gameTitle;
    sf::Text chooseVehicleColor;
    sf::Text vehicleColor;

	bool menuIsActive;
	bool settingsActive;

	short vehicleSelectedColor;

	sf::Texture vehicleCustomColor;

private:
	sf::Event event;

	sf::Texture menuBackgroundImageTexture;

	sf::Font pressStart2P;
	sf::Font bangers;
	sf::Font arial;

	sf::RenderWindow *gameWindow;

	const char vehicleColors[9][15] = { "AQUA", "BLUE", "GREY", "ORANGE", "RED", "YELLOW", "GREEN", "PINK", "LIME" };
	const char vehiclesImages[9][35] = { "res/img/car_aqua.png", "res/img/car_blue.png", "res/img/car_grey.png", "res/img/car_orange.png", "res/img/car_red.png", "res/img/car_yellow.png", "res/img/car_green.png", "res/img/car_pink.png", "res/img/car_lime.png" };
};

