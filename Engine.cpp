#include "Engine.h"
#include <iostream>
#include <fstream>
#include <random>

Engine::Engine()
{
	CreateLevel();

	if (!squaredFont.loadFromFile("res/fonts/PressStart2P-Regular.ttf"))
		std::cout << "PressStart2p-Regular.ttf could not get loaded.\n";

	congratsText.setCharacterSize(70);
	congratsText.setString("WELL DONE");
	congratsText.setFont(squaredFont);
	congratsText.setFillColor(sf::Color(247, 160, 72));
	sf::FloatRect congratsTextBounds = congratsText.getLocalBounds();
	congratsText.setOrigin(sf::Vector2f(congratsTextBounds.width / 2, congratsTextBounds.height / 2));
	congratsText.setPosition(sf::Vector2f(400, 400));
}

void Engine::CreateWindow()
{
	window.create(sf::VideoMode(800, 800), "2D Car Parking");
	window.setFramerateLimit(60);

	menu.SetMenuWindow(&window);

	while (window.isOpen())
	{
		window.clear();

		if (menu.menuIsActive)
		{
			menu.HandleMenuEvent();

			window.draw(menu.menuBackgroundImage);
			window.draw(menu.gameTitle);

			if(!menu.settingsActive) // Settings button was not clicked
            {
                menu.startGameButton.CheckHover(sf::Mouse::getPosition(window));
                menu.settingsButton.CheckHover(sf::Mouse::getPosition(window));

                window.draw(menu.startGameButton.button);
                window.draw(menu.startGameButton.buttonName);

                window.draw(menu.settingsButton.button);
                window.draw(menu.settingsButton.buttonName);
            }
            else // Settings button was clicked
            {
                menu.goBackButton.CheckHover(sf::Mouse::getPosition(window));
				menu.previousColorButton.CheckHover(sf::Mouse::getPosition(window));
				menu.nextColorButton.CheckHover(sf::Mouse::getPosition(window));

                window.draw(menu.goBackButton.button);
                window.draw(menu.goBackButton.buttonName);

				window.draw(menu.nextColorButton.button);
				window.draw(menu.nextColorButton.buttonName);

                window.draw(menu.chooseVehicleColor);
                window.draw(menu.vehicleColor);
                window.draw(menu.previousColorButton.button);
                window.draw(menu.previousColorButton.buttonName);

				if (menu.previousColorButton.IsPressed(sf::Mouse::getPosition(window)) || menu.nextColorButton.IsPressed(sf::Mouse::getPosition(window)))
				{
					playerVehicle->vehicle.setTexture(menu.vehicleCustomColor);
				}
            }
		}
		else
		{
			HandleEngineEvent();

			window.draw(map);

			window.draw(parkingSlot[playerParkingSlot]->parkingSlot); // Parking position where player should park its vehicle

			for (auto i : staticVehicle)
			{
				window.draw(i->vehicle); // drawing static vehicles
			}
			if (playerVehicle)
				window.draw(playerVehicle->vehicle);


			deltaTime = clock.restart().asSeconds();

			if (!playerParkedVehicle)
			{
				playerVehicle->PseudoMoveVehicle(deltaTime); // Calculating new positions before moving the vehicle

				if (!playerVehicle->VehicleCollidesWithObject(staticVehicle, numberOfStaticVehicles, collisionBox, numberOfCollisionBoxes)) // Checking collisions with the new positions player vehicle will have
				{
					playerVehicle->vehicle.move(playerVehicle->vehicleNewX, playerVehicle->vehicleNewY); // if new vehicle position does not collide with anything we'll move it

					if (!playerParkedVehicle && parkingSlot[playerParkingSlot]->PlayerParkedInParkingSlot(playerVehicle->vehicle)) // checking if player parked in the specific parking slot
					{
						playerParkedVehicle = true;
						countDown.restart();
					}
				}
			}
			else
			{
				if (countDown.getElapsedTime().asSeconds() <= 3)
					window.draw(congratsText);
				else
				{
					staticVehicle.clear();
					parkingSlot.clear();
					CreateLevel();
				}
			}

		}

		window.display();
	}
}

void Engine::CreateLevel()
{
	randomMap = rand() % 2;
	playerParkedVehicle = false;

	playerVehicle = new Vehicle(vehicleSpawnXYZ[randomMap][0], vehicleSpawnXYZ[randomMap][1], vehicleSpawnXYZ[randomMap][2], true, menu.vehicleSelectedColor);

	if (!mapTexture.loadFromFile(levelMaps[randomMap]))
		std::cout << levelMaps[randomMap] << " could not be loaded.\n";

	map.setTexture(mapTexture);

	std::ifstream fin(fileParkingSlots[randomMap]);

	fin >> numberOfParkingSlots;

	numberOfStaticVehicles = rand() % numberOfParkingSlots;
	playerParkingSlot = rand() % numberOfParkingSlots;

	float x, y, rotation;
	for (unsigned short i = 0; i < numberOfParkingSlots; i++)
	{
		fin >> x >> y >> rotation;
		if (i != playerParkingSlot)
		{
			parkingSlot.push_back(new ParkingSlot(x, y, rotation, false));

			if (i < numberOfStaticVehicles)
			{
				if (rand() % 50 >= 5)
					staticVehicle.push_back(new Vehicle(x, y, rotation, false, NULL));
			}
		}
		else
		{
			parkingSlot.push_back(new ParkingSlot(x, y, rotation, true));
		}

	}
	fin.close();
	fin = std::ifstream(fileCollisionBoxes[randomMap]);
	fin >> numberOfCollisionBoxes;
	float width, height;
	for (unsigned short i = 0; i < numberOfCollisionBoxes; i++)
	{
		fin >> x >> y >> width >> height;

		collisionBox[i].setSize(sf::Vector2f(width, height));
		collisionBox[i].setPosition(sf::Vector2f(x, y));
	}
}


void Engine::HandleEngineEvent()
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
			{
				window.close();
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape)
				{

				}
			}
			default:
				break;
		}
	}

	return;
}
