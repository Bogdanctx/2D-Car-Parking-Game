#include "Vehicle.h"
#include <random>
#include <iostream>

#define PI 3.14159265
#define VEHICLE_MAX_SPEED 8
#define VEHICLE_ACCELERATION 0.4
#define VEHICLE_TURN 4

Vehicle::Vehicle(float x, float y, float rotation, bool specialVehicle, unsigned short customColorIndex)
{
	unsigned short vehicleTextureIndex = rand() % 9;

	if (specialVehicle)
	{
		vehicleTextureIndex = customColorIndex;

		vehicle.setOrigin(sf::Vector2f(60, 30));
	}

	if (!vehicleTexture.loadFromFile(vehiclesImages[vehicleTextureIndex]))
		std::cout << vehiclesImages[vehicleTextureIndex] << " could not be loaded.\n";

	vehicleVelocity = 0;
	vehicleRotation = rotation;

	vehicle.setTexture(vehicleTexture);
	vehicle.setPosition(sf::Vector2f(x, y));
	vehicle.setRotation(rotation);
}

void Vehicle::PseudoMoveVehicle(float deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (vehicleVelocity < VEHICLE_MAX_SPEED)
			vehicleVelocity += VEHICLE_ACCELERATION;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (vehicleVelocity > -VEHICLE_MAX_SPEED)
			vehicleVelocity -= VEHICLE_ACCELERATION;
	}
	else
	{
		if (vehicleVelocity >= 0.7)
			vehicleVelocity -= VEHICLE_ACCELERATION;
		else if (vehicleVelocity <= -0.7)
			vehicleVelocity += VEHICLE_ACCELERATION;
		else
			vehicleVelocity = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (vehicleVelocity > 0)
			vehicleRotation -= VEHICLE_TURN;
		else if (vehicleVelocity < 0)
			vehicleRotation += VEHICLE_TURN;

		if (vehicleRotation < 0)
			vehicleRotation = 360;
		else if (vehicleRotation > 360)
			vehicleRotation = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (vehicleVelocity > 0)
			vehicleRotation += VEHICLE_TURN;
		else if (vehicleVelocity < 0)
			vehicleRotation -= VEHICLE_TURN;

		if (vehicleRotation < 0)
			vehicleRotation = 360;
		else if (vehicleRotation > 360)
			vehicleRotation = 0;
	}
	vehicle.setRotation(vehicleRotation);

	vehicleNewX = cos(vehicleRotation * PI / 180) * vehicleVelocity * deltaTime * 60;
	vehicleNewY = sin(vehicleRotation * PI / 180) * vehicleVelocity * deltaTime * 60;
}

bool Vehicle::VehicleCollidesWithObject(std::vector<Vehicle*>staticVehicles, unsigned short numberOfStaticVehicles, sf::RectangleShape collisionBox[], unsigned numberOfCollisionBoxes)
{
	sf::FloatRect vehicleBounds = vehicle.getGlobalBounds();
	vehicleBounds.left += vehicleNewX;
	vehicleBounds.top += vehicleNewY;
	vehicleBounds.height -= 10;
	vehicleBounds.width -= 10;
	
	// Checking collision with static vehicles
	for (auto i : staticVehicles)
	{
		sf::FloatRect staticVehicleBounds = i->vehicle.getGlobalBounds();
		staticVehicleBounds.height -= 15;
		staticVehicleBounds.width -= 15;

		if (vehicleBounds.intersects(staticVehicleBounds))
			return true;
	}
	for (unsigned short i=0;i<numberOfCollisionBoxes;i++)
	{
		sf::FloatRect collisionBoxBounds = collisionBox[i].getGlobalBounds();

		if (vehicleBounds.intersects(collisionBoxBounds))
			return true;

	}

	if (vehicleBounds.left < -15 || vehicleBounds.left > 760 || vehicleBounds.top < -15 || vehicleBounds.top > 760)
		return true;

	return false;

}