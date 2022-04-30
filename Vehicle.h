#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Vehicle
{
public:
	Vehicle(float x, float y, float rotation, bool specialVehicle, unsigned short customColorIndex);

	void PseudoMoveVehicle(float deltaTime);
	bool VehicleCollidesWithObject(std::vector<Vehicle*>staticVehicles, unsigned short numberOfStaticVehicles, sf::RectangleShape collisionBox[], unsigned numberOfCollisionBoxes);

	sf::Sprite vehicle;

	float vehicleNewX, vehicleNewY;
private:
	sf::Texture vehicleTexture;

	float vehicleVelocity;
	float vehicleRotation;

	const char vehiclesImages[9][35] = { "res/img/car_aqua.png", "res/img/car_blue.png", "res/img/car_grey.png", "res/img/car_orange.png", "res/img/car_red.png", "res/img/car_yellow.png", "res/img/car_green.png", "res/img/car_pink.png", "res/img/car_lime.png" };
};

