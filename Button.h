#pragma once

#include <SFML/Graphics.hpp>

class Button
{
public:
	Button();
	Button(sf::Vector2f position, sf::Vector2f size, sf::Vector3i defaultColors, sf::Vector3i hoverColors);

	bool IsPressed(sf::Vector2i mousePosition);
	void CheckHover(sf::Vector2i mousePosition);
    void SetButtonName(const sf::String _buttonName, sf::Font &font, unsigned short fontSize);

	sf::RectangleShape button;
	sf::Text buttonName;

private:
	sf::Vector3i _hoverColors;
	sf::Vector3i _defaultColors;
};

