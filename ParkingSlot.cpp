#include "ParkingSlot.h"

#define PI 3.14159265

ParkingSlot::ParkingSlot(float x, float y, float rotation, bool playerParkingSlot)
{
	parkingSlot.setRotation(rotation);
	parkingSlot.setPosition(x, y);
	parkingSlot.setSize(sf::Vector2f(137, 65));

	if (playerParkingSlot)
		parkingSlot.setFillColor(sf::Color(255, 187, 0, 150));
}

bool ParkingSlot::PlayerParkedInParkingSlot(sf::Sprite vehicle)
{
	sf::Vector2f t = vehicle.getPosition();
	sf::FloatRect r = parkingSlot.getGlobalBounds();
	
	t.x += -cos(vehicle.getRotation()*PI/180)*60;
	t.y += -sin(vehicle.getRotation() * PI / 180)*60;

	if (r.contains(t))
	{
		return true;
	}
	return false;
}