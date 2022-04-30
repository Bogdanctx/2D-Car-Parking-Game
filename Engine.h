#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Menu.h"
#include "Vehicle.h"
#include "ParkingSlot.h"


class Engine
{
public:
	Engine();

	void CreateWindow();
	void RestartLevel();
	void CreateLevel();
	void HandleEngineEvent();

	sf::Sprite map;

private:
	Menu menu;
	Vehicle* playerVehicle;
	std::vector<Vehicle*>staticVehicle;
	std::vector<ParkingSlot*>parkingSlot;
	sf::RenderWindow window;
	sf::Texture mapTexture;
	sf::Event event;
	sf::Clock clock;
	sf::Clock countDown;
	sf::Font squaredFont;
	sf::Text congratsText;
	sf::RectangleShape collisionBox[8];

	float deltaTime;

	unsigned short randomMap;
	unsigned short numberOfParkingSlots;
	unsigned short numberOfStaticVehicles;
	unsigned short numberOfCollisionBoxes;
	unsigned short playerParkingSlot;
	bool playerParkedVehicle;
	const char levelMaps[2][20] = { "res/img/level_0.png", "res/img/level_1.png" };
	const char fileParkingSlots[2][40] = { "res/data/level_0_parkingSlotsXYZ.txt", "res/data/level_1_parkingSlotsXYZ.txt" };
	const char fileCollisionBoxes[2][40] = { "res/data/level_0_collisionObjects.txt", "res/data/level_1_collisionObjects.txt" };

	const unsigned vehicleSpawnXYZ[2][3] = { 735, 270, 180,
										   190, 715, 270 };
};

