#pragma once

#include <SFML/Graphics.hpp>

class ParkingSlot
{
public:
	ParkingSlot(float x, float y, float rotation, bool playerParkingSlot);
	bool PlayerParkedInParkingSlot(sf::Sprite vehicle);

	sf::RectangleShape parkingSlot;
};

